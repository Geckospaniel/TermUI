#include "List.hh"

List::List(const Vector2& start, const Vector2& end) : Window(start, end)
{
}

void List::draw()
{
	//	TODO implement scrolling
	if(needsRedraw)
	{
		for(size_t i = 0; i < entries.size(); i++)
		{
			Color::Name fg = Color::White;
			Color::Name bg = Color::Black;

			if(i == selected)
			{
				fg = Color::Black;
				bg = Color::White;
			}

			setColor(fg, bg);
			drawTextLine(entries[i], 0, i, true);
		}
	}
}

void List::onKeyPress(int key)
{
	switch(key)
	{
		case KEY_UP:
			if(--selected >= entries.size())
				selected = entries.size() - 1;
		break;

		case KEY_DOWN:
			if(++selected >= entries.size())
				selected = 0;
		break;
	}

	needsRedraw = true;
}

void List::add(const std::string& str)
{
	entries.push_back(str);
	needsRedraw = true;
}
