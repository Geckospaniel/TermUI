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
		//	Create the actual pointer and get a reference to it
		children.push_back(Window::create <T> (std::forward <Args> (args)...));
		T& child = *(static_cast <T*> (children.back()));

		Vector2 tStart = translatePosition(child.start);
		Vector2 tEnd = translatePosition(child.end);

		//	TODO check somewhere if end is less than start
		unsigned columns = tEnd.x - tStart.x;
		unsigned rows = tEnd.y - tStart.y;

		child.window = derwin(window, rows, columns, tStart.y, tStart.x);
		return child;
	}

	//	Initializes ncurses
	Container();

	//	Creates a child container
	Container(const Vector2& start, const Vector2& end);

	~Container() override
	{
	}

	void draw() override;

private:
	std::vector <Window*> children;
};

#endif
