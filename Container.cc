#include "DebugHelper.hh"
#include "Container.hh"
#include "Color.hh"

Container::Container(bool blockOnInput) : Window(Vector2(0, 0), Vector2(100, 100))
{
	static bool isInitialized = false;

	if(isInitialized)
	{
		setColor(Color::White, Color::Red);
		printw("ERROR: Root container has already been made\n");
		getch();
		endwin();
		std::quick_exit(1);
	}

	if(!Color::initialize())
	{
	}

	window = initscr();
	Color::initialize();
	wclear(window);

	//	Don't echo pressed keys
	noecho();

	//	Support arrow keys
	keypad(window, true);

	//	Support mouse input
	mousemask(BUTTON1_PRESSED | BUTTON2_PRESSED, NULL);
	//mousemask(ALL_MOUSE_EVENTS, NULL);

	//	Hide the cursor
	curs_set(0);

	// If set, don't block on getch
	nodelay(window, !blockOnInput);

	isFocused = true;
	isInitialized = true;
}

Container::~Container()
{
	close();
}

Container::Container(const Vector2& start, const Vector2& end) :
	Window(start, end)
{
}

void Container::draw()
{
	for(auto& child : children)
	{
		if(child->needsRedraw)
		{
			child->draw();
			child->drawBorders();
			touchwin(child->window);
			wrefresh(child->window);

			//	Child has been drawn
			child->needsRedraw = false;
		}
	}

	//	This container has been drawn
	needsRedraw = false;
}

void Container::handleEvent(Event event)
{
	//	If the event is empty, check user input
	if(event.type == Event::Type::None)
	{
		int c = wgetch(window);

		//	Was there any input?
		if(c == ERR)
			return;

		/*	FIXME there's a really odd bug where when the
		 *	terminal gets resized, every window will resize
		 *	how they are supposed to, but the next redraw the
		 *	active window goes to its last position. Resizing
		 *	every time fixes it though but is wasteful	*/
		//resizeWindow();

		//	If there's a terminal resize, resize each window
		if(c == KEY_RESIZE)
		{
			resizeWindow();
			return;
		}

		//	If there's mouse input, it's a mouse event
		if(c == KEY_MOUSE)
		{
			MEVENT mouseEvent;
			if(getmouse(&mouseEvent) == OK)
			{
				event.type = Event::Type::Mouse;

				//	Fill the mouse event info
				event.value.mouseInfo.leftDown = (mouseEvent.bstate & BUTTON1_PRESSED);
				event.value.mouseInfo.x = mouseEvent.x;
				event.value.mouseInfo.y = mouseEvent.y;

				//	If left click is held down, handle window focus
				if(event.value.mouseInfo.leftDown)
					checkMouseFocus(event);
			}
		}

		//	Otherwise it's key input
		else
		{
			event.type = Event::Type::KeyPress;
			event.value.key = c;
		}
	}

	//	Send events to the active window
	if(activeChild != nullptr)
		activeChild->handleEvent(event);
}

void Container::setActiveChild()
{
	for(auto& child : children)
	{
		if(child->wantsFocus)
		{
			DebugHelper::log(LogLevel::Debug, "Child ", child->title, " wants focus");

			//	If a window wants the focus, set it as active
			activeChild = child;
			activeChild->isFocused = true;
			activeChild->wantsFocus = false;
			
			//	Call the window focus callback
			if(activeChild->onFocus)
			{
				activeChild->setActiveChild();
				activeChild->onFocus();
			}
		}

		else
		{
			//	Unfocus any windows that don't want the focus
			child->isFocused = false;
		}

		child->setRedraw();
	}
}

bool Container::checkMouseFocus(Event event)
{
	event.value.mouseInfo.x -= translatedStart.x;
	event.value.mouseInfo.y -= translatedStart.y;

	for(auto& child : children)
	{
		//	If the mouse is inside some child window, focus on it
		if(child->checkMouseFocus(event))
		{
			child->stealFocus();
			return false;
		}
	}

	//	Mouse wasn't inside this container
	return false;
}

void Container::resizeWindow()
{
	Window::resizeWindow();

	for(auto& child : children)
		child->resizeWindow();
}

void Container::update()
{
	//	If this container is the root, draw everything and check user input
	if(parent == nullptr)
	{
		draw();
		handleEvent({});
	}

	//	Update each child
	for(size_t i = 0; i < children.size(); i++)
	{
		//	Has the window closed?
		if(children[i]->window == NULL)
		{
			if(children[i] == activeChild)
				activeChild = nullptr;

			setRedraw();
			delete children[i];
			children.erase(children.begin() + i);
			i--;

			continue;
		}

		children[i]->update();
	}
}

void Container::close()
{
	//	Close all child windows first
	for(auto& child : children)
		child->close();

	//	Close this container
	Window::close();
}
