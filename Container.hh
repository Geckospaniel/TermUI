#ifndef CONTAINER_HEADER
#define CONTAINER_HEADER

#include "Window.hh"

#include <vector>

class Container : public Window
{
public:
	template <typename T, typename... Args>
	inline T& create(Args&& ...args)
	{
		children.push_back(Window::create <T> (std::forward(args)...));
		return *(static_cast <T*> (children.back()));
	}

	//	Initializes ncurses
	Container();

private:
	std::vector <Window*> children;
};

#endif
