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
	//	Color the border depending on whether the window is active
	Color::Name fg = isFocused ? Color::Green : Color::White;
	setColor(fg, Color::Black);

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
