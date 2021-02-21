#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include "Vector2.hh"

#include <ncurses.h>

#include <functional>
#include <utility>
#include <memory>
#include <string>

class Window
{
public:
	virtual ~Window();

protected:
	Window(const Vector2& start, const Vector2& end)
		: start(start), end(end)
	{}

	virtual void draw();
	virtual void onSetActive();
	virtual void onKeyPress(char key);
	virtual void onUpdate();

	void drawBorders(const std::string& title);
	Vector2 translatePosition(const Vector2& position);

	Vector2 start;
	Vector2 end;

	bool needsRedraw = true;

private:
	//	Container needs exclusive access to private members
	friend class Container;

	void update();
	WINDOW* window;
};

#endif
