#ifndef LIST_HEADER
#define LIST_HEADER

#include "Window.hh"

#include <functional>
#include <string>
#include <vector>

class List : public Window
{
public:
	List(const Vector2& start, const Vector2& end);

	void draw() override;
	void onKeyPress(int key) override;

	void add(const std::string& str);
	std::function <void(const std::string& str)> onSelect;

private:
	std::vector <std::string> entries;
	size_t selected = 0;
};

#endif
