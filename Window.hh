#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include "Vector2.hh"
#include "Event.hh"
#include "Color.hh"

#include <ncurses.h>

#include <functional>
#include <utility>
#include <string>
#include <sstream>

class Window
{
public:
	virtual ~Window();

	void stealFocus();
	void setTitle(const std::string& str);

	std::function <void()> onFocus;

protected:
	Window(const Vector2& start, const Vector2& end)
		: start(start), end(end)
	{
	}

	virtual void draw() {}
	virtual void update() {}
	virtual void onKeyPress(int) {}

	void drawTextLine(const std::string& str, int x, int y, bool fillLine);
	void drawBorders();

	Vector2 translatePosition(const Vector2& position);

	inline void setColor(Color::Name fg, Color::Name bg)
	{
		Color::set(fg, bg, window);
	}

	inline void clear()
	{
		wclear(window);
	}

	bool needsRedraw = true;
	bool isFocused = false;

	Vector2 size;

private:
	//	TODO maybe create a buffer used in drawing?

	//	Container needs exclusive access to private members
	friend class Container;

	//	Only container and window implement these
	virtual void resizeWindow();
	virtual void setActiveChild() {}
	virtual void handleEvent(Event event);

	bool wantsFocus = false;
	std::string title;

	Vector2 start;
	Vector2 end;

	Window* parent = nullptr;
	WINDOW* window;
};

#endif
