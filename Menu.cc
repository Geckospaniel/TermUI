#include "Menu.hh"

MenuEntry& MenuEntry::add(const std::string& name)
{
	MenuEntry* next = new MenuEntry();

	next->parent = this;
	next->name = name;
	next->menu = menu;

	//	TODO set redraw if this is the active menu
	//	Redraw the newly added item
	menu->setRedraw();

	entries.push_back(next);
	return *next;
}

void MenuEntry::setName(const std::string& name)
{
	menu->setRedraw();
	this->name = name;
}

void MenuEntry::clear()
{
	//	Deallocate the the sub menus
	for(auto& entry : entries)
		delete entry;

	//	Remove all entries
	entries.clear();
	entries.shrink_to_fit();
}

MenuEntry* MenuEntry::findLastActive()
{
	//	If no menu is active, return this one
	return active == nullptr ? this : active->findLastActive();
}

void Menu::draw()
{
	MenuEntry* menu = root.findLastActive();

	size_t scrollAt = size.y;
	size_t offset = menu->selected >= scrollAt ? menu->selected - scrollAt + 1 : 0;

	for(size_t i = offset; i < menu->entries.size(); i++)
	{
		Color::Name fg = isFocused ? Color::White : Color::Gray;
		Color::Name bg = Color::Black;

		//	Highlight if this is the active menu
		if(i == menu->selected)
		{
			fg = Color::Black;
			bg = isFocused ? Color::White : Color::Gray;
		}

		setColor(fg, bg);
		drawTextLine(menu->entries[i]->name, 0, i - offset, true);
	}
}

void Menu::onKeyPress(int key)
{
	MenuEntry* menu = root.findLastActive();

	switch(key)
	{
		case KEY_UP:
			if(--menu->selected >= menu->entries.size())
				menu->selected = menu->entries.size() - 1;
		break;

		case KEY_DOWN:
			if(++menu->selected >= menu->entries.size())
				menu->selected = 0;
		break;

		case KEY_RIGHT: case 10:
		{
			MenuEntry* selectedMenu = menu->entries[menu->selected];

			//	Call the selection callback
			if(selectedMenu->onSelect)
				selectedMenu->onSelect();

			//	Only set the selected menu as active if it has something in it
			if(!selectedMenu->entries.empty())
			{
				menu->active = selectedMenu;
				Window::clear();
			}

			break;
		}

		case KEY_LEFT:
			//	Don't go backwards past root
			if(menu->parent != nullptr)
			{
				//	To go backwards, unset the active menu 
				menu->parent->active = nullptr;
				Window::clear();
			}
		break;
	}
}
