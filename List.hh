#ifndef LIST_HEADER
#define LIST_HEADER

#include "Window.hh"

class List : public Window
{
public:
	List(const Vector2& start, const Vector2& end);

	void draw() override;
	void onKeyPress(char key) override;

private:
	std::string a;
};

#endif
