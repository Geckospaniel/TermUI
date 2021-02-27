#include "Container.hh"
#include "Color.hh"

Container::Container() : Window(Vector2(0, 0), Vector2(100, 100))
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
	mousemask(ALL_MOUSE_EVENTS, NULL);

	//	Hide the cursor
	curs_set(0);

	isFocused = true;
	isInitialized = true;
}

Container::~Container()
{
	//	Deallocate each child
	for(auto& child : children)
		delete child;
}

Container::Container(const Vector2& start, const Vector2& end) :
	Window(start, end)
{
}

void Container::draw()
{
	if(needsRedraw)
	{
		drawBorders();
		mvwprintw(window, 1, 1, "%lu %s", children.size(), a.c_str());
		wrefresh(window);

		needsRedraw = false;
	}

	for(auto& child : children)
		child->draw();
}

void Container::handleEvent(Event event)
{
	//	If the event is empty, check user input
	if(event.type == Event::Type::None)
	{
		int c = wgetch(window);
		event.type = Event::Type::KeyPress;
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
			//	If a window wants the focus, set it as active
			activeChild = child;
			activeChild->isFocused = true;
			activeChild->wantsFocus = false;
		}

		else
		{
			//	Unfocus any windows that don't want it
			child->isFocused = false;
		}
	}
}

void Container::update()
{
	draw();

	//	If this container is the root, check user input
	if(parent == nullptr)
		handleEvent({});

	//	Update each child
	for(auto& child : children)
		child->update();
}
