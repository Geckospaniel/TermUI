#include "List.hh"

List::List(const Vector2& start, const Vector2& end) : Window(start, end)
{
}

void List::draw()
{
	if(needsRedraw)
	{
		drawTextLine(a, 1, 1);
	}
}

void List::onKeyPress(char key)
{
	a += key;
	needsRedraw = true;
}
