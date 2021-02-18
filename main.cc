#include "Container.hh"

class Canvas : public Window
{
public:
	Canvas() : Window(NULL)
	{
	}
};

int main()
{
	auto root = Window::create <Container> ();
	auto canvas = root->create <Canvas> ();

	{
	}

	return 0;
}
