#ifndef MENU_HEADER
#define MENU_HEADER

#include "Window.hh"

#include <string>
#include <vector>

class MenuEntry
{
public:
	MenuEntry& add(const std::string& name);
	void clear();

	std::function <void()> onSelect;

private:
	friend class Menu;
	MenuEntry* findLastActive();

	struct Entry
	{
		MenuEntry* subMenu;
		std::string name;
	};

	std::vector <Entry> entries;

	//	Which menu entry is highlighted
	size_t selected = 0;

	//	Which menu is active and parent of this menu
	MenuEntry* active = nullptr;
	MenuEntry* parent = nullptr;
};

class Menu : public Window
{
public:
	Menu(const Vector2& start, const Vector2& end) :
		Window(start, end)
	{
	}

	void draw() override;
	void onKeyPress(int key) override;

	MenuEntry root;
};

#endif
