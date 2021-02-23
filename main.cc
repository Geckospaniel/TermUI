#include "Container.hh"

int main()
{
	Container root;
	Container& canvas = root.create <Container> (Vector2(25, 25), Vector2(75, 75));
	Container& abc = canvas.create <Container> (Vector2(25, 25), Vector2(75, 75));

	{
		root.update();
	}

	return 0;
}
