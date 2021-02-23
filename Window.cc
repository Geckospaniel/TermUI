#include "Window.hh"

Window::~Window()
{
	bool isRoot = window == stdscr;

	//	Deallocate the window
	delwin(window);

	//	If this has the root window, quit ncurses
	if(isRoot)
		endwin();
}

void Window::draw()
{
}

void Window::onSetActive()
{
}

void Window::onKeyPress(char key)
{
}

void Window::drawBorders(const std::string& title)
{
	box(window, 0, 0);
}

Vector2 Window::translatePosition(const Vector2& position)
{
	return Vector2(
		(static_cast <float> (position.x) / 100) * getmaxx(window),
		(static_cast <float> (position.y) / 100) * getmaxy(window)
	);
}

void Window::onUpdate()
{
}

void Window::handleEvent(Event event)
{
}
