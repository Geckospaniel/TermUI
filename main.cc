#include "Container.hh"

int main()
{
	auto root = Window::create <Container> ();
	auto canvas = root->create <Container> (Vector2(25, 25), Vector2(75, 75));
	auto abc = canvas.create <Container> (Vector2(25, 25), Vector2(75, 75));

	root->draw();
	canvas.draw();
	abc.draw();

	while(true)
	{
	}

	return 0;
}
