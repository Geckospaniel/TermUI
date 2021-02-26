#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include "Vector2.hh"
#include "Event.hh"
#include "Color.hh"

#include <ncurses.h>

#include <functional>
#include <utility>
#include <string>

class Window
{
public:
	virtual ~Window();

	void stealFocus();

	std::function <bool()> onUpdate;
	std::function <void()> onFocus;

protected:
	Window(const Vector2& start, const Vector2& end)
		: start(start), end(end)
	{}

	virtual void draw() {}
	virtual void update() {}

	void drawBorders(const std::string& title);
	Vector2 translatePosition(const Vector2& position);

	inline void setColor(Color::Name fg, Color::Name bg)
	{
		Color::set(fg, bg, window);
	}

	Vector2 start;
	Vector2 end;

	bool needsRedraw = true;

private:
	//	Container needs exclusive access to private members
	friend class Container;

	//	Only container and window implement these
	virtual void setActiveChild() {}
	virtual void handleEvent(Event event);

	bool wantsFocus = false;
	bool isFocused = false;

	Window* parent = nullptr;
	WINDOW* window;
};

#endif
