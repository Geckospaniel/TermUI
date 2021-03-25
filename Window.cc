#include "DebugHelper.hh"
#include "Window.hh"
#include "Color.hh"

Window::~Window()
{
	close();
}

void Window::close()
{
	bool isRoot = parent == nullptr;

	//	Get the window off of the screen
	wclear(window);

	//	Deallocate the window
	delwin(window);
	window = nullptr;

	//	If this has the root window, quit ncurses
	if(isRoot) endwin();
}

void Window::drawBorders()
{
	//	Color the border depending on whether the window is active
	Color::Name fg = isFocused ? Color::White : Color::Gray;
	setColor(fg, Color::Black);

	box(window, 0, 0);
	std::string windowTitle = title;

	//	If the title is too long, cut the overflow and signal the user that it doesn't fit
	if(title.length() > static_cast <size_t> (getmaxx(window)))
	{
		windowTitle.erase(windowTitle.begin() + size.x - 3, windowTitle.end());
		windowTitle += std::string("...");
	}

	//	Print the title in the top middle of the box
	unsigned titleX = getmaxx(window) / 2 - windowTitle.length() / 2;
	mvwprintw(window, 0, titleX, "%s", windowTitle.c_str());
}

void Window::drawTextLine(const std::string& str, int x, int y, bool fillLine)
{
	std::string text = str;

	//	If the string is too long, cut the overflow and signal the user that it doesn't fit
	if(str.length() > static_cast <size_t> (size.x))
	{
		text.erase(text.begin() + size.x - 3, text.end());
		text += std::string("...");
	}

	std::string leftPadding;
	std::string rightPadding;

	if(fillLine)
	{
		//	Initialize a padding that fills the line on both sides
		leftPadding = std::string(x, ' ');
		rightPadding = std::string(size.x - x - text.length(), ' ');

		x = 0;
	}

	/*	Increment x and y so that 0 0 is the origin instead of 1 1 and
	 *	print the string with padding if there's any */
	mvwprintw(window, ++y, ++x, "%s%s%s", leftPadding.c_str(),
										  text.c_str(),
										  rightPadding.c_str());
}

Vector2 Window::translatePosition(const Vector2& position)
{
	return Vector2(
		(static_cast <float> (position.x) / 100) * getmaxx(window),
		(static_cast <float> (position.y) / 100) * getmaxy(window)
	);
}

void Window::resizeWindow()
{
	//	If this is the root window, resize to terminal size
	if(parent == nullptr)
	{
		wresize(window, LINES, COLS);
		wclear(window);
	}

	//	If this is a child window
	else
	{
		//	Recalculate the position and size
		Vector2 tStart = parent->translatePosition(start);
		Vector2 tEnd = parent->translatePosition(end);
		size = tEnd - tStart;

		//	Resize and move the ncurses window
		mvderwin(window, tStart.y, tStart.x);
		wresize(window, size.y, size.x);

		size -= Vector2(2, 2);
		translatedStart = tStart;
		wclear(window);
	}

	setRedraw();
}

void Window::handleEvent(Event event)
{
	switch(event.type)
	{
		case Event::Type::KeyPress:
			onKeyPress(event.value.key);
		break;

		case Event::Type::Mouse:
		{
			Vector2 mousePos(event.value.mouseInfo.x, event.value.mouseInfo.y);

			/*	Since the mouse coordinate is given in 0 - terminal size,
			 *	subtract window position from it to get the coordinate relative to the window */
			mousePos -= translatedStart;

			//	Call the event handler
			onMouseEvent(mousePos, event.value.mouseInfo.leftDown);
			break;
		}

		case Event::Type::None: break;
	}

	setRedraw();
}

bool Window::checkMouseFocus(Event event)
{
	Vector2 mousePos(event.value.mouseInfo.x, event.value.mouseInfo.y);
	mousePos -= translatedStart;

	//	Is the cursor inside the window
	return mousePos > Vector2(0, 0) && mousePos < Vector2(getmaxx(window), getmaxy(window));
}

void Window::stealFocus()
{
	//	Climb all the way to root and request focus
	if(parent != nullptr)
	{
		wantsFocus = true;
		parent->stealFocus();
	}

	else setActiveChild();
}

void Window::setRedraw()
{
	//	Redraw the parent containers too
	if(parent != nullptr)
		parent->setRedraw();

	needsRedraw = true;
}

void Window::setTitle(const std::string& str)
{
	title = str;
	setRedraw();
}
