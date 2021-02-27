#ifndef CONTAINER_HEADER
#define CONTAINER_HEADER

#include "Window.hh"

#include <vector>

class Container : public Window
{
public:
	template <typename T, typename... Args>
	T& create(Args&& ...args)
	{
		children.push_back(new T(std::forward <Args> (args)...));
		Window* child = children.back();

		Vector2 pos = translatePosition(child->start);
		child->size = translatePosition(child->end - child->start);

		//	TODO check somewhere if end is less than start
		unsigned columns = child->size.x;
		unsigned rows = child->size.y;

		//	Create the window relative to parent window and save parent
		child->window = derwin(window, rows, columns, pos.y, pos.x);
		child->parent = this;

		//	Always focus on the latest window
		child->stealFocus();

		return *(static_cast <T*> (child));
	}

	//	Initializes ncurses
	Container();
	~Container();

	//	Creates a child container
	Container(const Vector2& start, const Vector2& end);

	void update() override;

private:
	void handleEvent(Event event) override;
	void setActiveChild() override;
	void draw() override;

	Window* activeChild = nullptr;
	std::vector <Window*> children;
};

#endif
