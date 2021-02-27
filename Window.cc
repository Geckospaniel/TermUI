#include "Window.hh"
#include "Color.hh"

#include <cmath>

Window::~Window()
{
	bool isRoot = window == stdscr;

	//	Deallocate the window
	delwin(window);

	//	If this has the root window, quit ncurses
	if(isRoot)
		endwin();
}

void Window::drawBorders()
{
	//	Color the border depending on whether the window is active
	Color::Name fg = isFocused ? Color::Green : Color::White;
	setColor(fg, Color::Black);

	box(window, 0, 0);

	std::string windowTitle = title;

	//	If the title is too long, cut the overflow and signal the user that it doesn't fit
	if(title.length() > static_cast <size_t> (getmaxx(window)))
	{
		windowTitle.erase(windowTitle.begin() + getmaxx(window) - 5, windowTitle.end());
		windowTitle += std::string("...");
	}

	//	Print the title in the top middle of the box
	unsigned titleX = getmaxx(window) / 2 - windowTitle.length() / 2;
	mvwprintw(window, 0, titleX, "%s", windowTitle.c_str());

	//	If borders are drawn, we can assume other stuff is drawn so reset needsRedraw
	needsRedraw = false;
}

void Window::drawTextLine(const std::string& str, int x, int y)
{
	mvwprintw(window, y, x, "%s", str.c_str());
}

Vector2 Window::translatePosition(const Vector2& position)
{
	return Vector2(
		(static_cast <float> (position.x) / 100) * getmaxx(window),
		(static_cast <float> (position.y) / 100) * getmaxy(window)
	);
}

void Window::handleEvent(Event event)
{
	switch(event.type)
	{
		case Event::Type::KeyPress:
			onKeyPress(event.value.key);
		break;

		case Event::Type::MouseClick: break;
		case Event::Type::None: break;
	}
}

void Window::stealFocus()
{
	//	Climb all the way to root and request focus
	if(parent != nullptr)
	{
		wantsFocus = true;
		parent->stealFocus();
	}

	setActiveChild();
}

void Window::setTitle(const std::string& str)
{
	title = str;
	needsRedraw = true;
}
