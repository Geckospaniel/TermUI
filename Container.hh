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

		//	FIXME Make sure that Start if less than End
		Vector2 tStart = translatePosition(child->start);
		Vector2 tEnd = translatePosition(child->end);

		child->size = tEnd - tStart;
		child->translatedStart = tStart;

		//	Create a window relative to the parent window and save the parent
		child->window = derwin(window, child->size.y, child->size.x, tStart.y, tStart.x);
		child->parent = this;

		//	Ignore borders in the size
		child->size -= Vector2(2, 2);

		std::stringstream ss;
		ss << "Size " << child->size.x << " " << child->size.y << " Position " << tStart.x << " " << tStart.y;
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
	bool checkMouseFocus(Event event) override;
	void handleEvent(Event event) override;
	void setActiveChild() override;
	void resizeWindow() override;
	void draw() override;

	Window* activeChild = nullptr;
	std::vector <Window*> children;
};

#endif
