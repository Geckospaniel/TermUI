#ifndef CONTAINER_HEADER
#define CONTAINER_HEADER

#include "Window.hh"

#include <memory>
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

		//	TODO check somewhere if end is less than start
		unsigned columns = tEnd.x - tStart.x;
		unsigned rows = tEnd.y - tStart.y;

		child->window = derwin(window, rows, columns, tStart.y, tStart.x);

		//	TODO find out a way to return a reference instead of a pointer
		return *(static_cast <T*> (child));
	}

	//	Initializes ncurses
	Container();
	~Container();

	//	Creates a child container
	Container(const Vector2& start, const Vector2& end);

	void draw() override;

private:
	std::vector <Window*> children;
};

#endif
