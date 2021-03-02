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
		Vector2 tEnd = translatePosition(child->end);

		//	FIXME check if tEnd is less than tStart
		child->size = tEnd - tStart;

		//	Create the window relative to parent window and save parent
		child->window = derwin(window, child->size.y, child->size.x, tStart.y, tStart.x);
		child->parent = this;

		//	Ignore borders in the size
		child->size -= Vector2(2, 2);

		std::stringstream ss;
		ss << child->size.x << " " << child->size.y;
		child->title = ss.str();

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
