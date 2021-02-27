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

		Vector2 tStart = translatePosition(child->start);
		Vector2 tSize = translatePosition(child->end - child->start);

		//	TODO check somewhere if end is less than start
		unsigned columns = tSize.x;
		unsigned rows = tSize.y;

		child->window = derwin(window, rows, columns, tStart.y, tStart.x);
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
