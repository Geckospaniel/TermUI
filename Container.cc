#include "Container.hh"
#include "Color.hh"

Container::Container() : Window(Vector2(0, 0), Vector2(100, 100))
{
	static bool isInitialized = false;

	if(isInitialized)
	{
		Color::useColor(Color::White, Color::Red);
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

	//	Hide the cursor
	curs_set(0);

	isInitialized = true;
}

Container::Container(const Vector2& start, const Vector2& end) :
	Window(start, end)
{
}

void Container::draw()
{
	if(!needsRedraw)
		return;

	drawBorders("");
	mvwprintw(window, 1, 1, "%lu", children.size());
	wrefresh(window);

	for(auto& child : children)
		child->draw();

	needsRedraw = false;
}
