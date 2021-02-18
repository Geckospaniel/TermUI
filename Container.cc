#include "Container.hh"
#include "Color.hh"

Container::Container() : Window(initscr())
{
	if(!Color::initialize())
	{
	}

	Color::useColor(Color::Red, Color::Blue);
	printw("moi");

	getch();
	refresh();
}
