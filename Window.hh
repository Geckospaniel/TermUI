#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include <ncurses.h>

#include <utility>

class Window
{
public:
	template <typename T, typename ...Args>
	static inline T* create(Args&& ...args)
	{
		return new T(std::forward(args)...);
	}

protected:
	Window(WINDOW* window);

private:
	WINDOW* window;
};

#endif
