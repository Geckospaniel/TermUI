#include "Window.hh"

Window::~Window()
{
	//	Deallocate the window
	delwin(window);

	//	If this has the root window, quit ncurses
	if(window == stdscr)
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
