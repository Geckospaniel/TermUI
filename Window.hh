#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include "Vector2.hh"

#include <ncurses.h>

#include <functional>
#include <utility>
#include <string>

class Window
{
public:
	template <typename T, typename ...Args>
	static inline T* create(Args&& ...args)
	{
		return new T(std::forward <Args> (args)...);
	}

	void update(int y)
	{
		mvprintw(y, 10, "MOI");
	}

	//Window(const Window& rhs) = delete;
	virtual ~Window()
	{
	}

protected:
	Window(const Vector2& start, const Vector2& end)
		: start(start), end(end)
	{}

	virtual void draw();
	virtual void onSetActive();
	virtual void onKeyPress(char key);

	void drawBorders(const std::string& title);
	Vector2 translatePosition(const Vector2& position);

	Vector2 start;
	Vector2 end;

	bool needsRedraw = true;

private:
	//	Container needs exclusive access to window
	friend class Container;
	WINDOW* window;
};

#endif
