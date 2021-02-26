#include "Container.hh"

int main()
{
	Container root;

	Container& side1 = root.create <Container> (Vector2(5, 5), Vector2(50, 95));
	Container& side2 = root.create <Container> (Vector2(50, 5), Vector2(95, 95));

	Container& s1p1 = side1.create <Container> (Vector2(5, 5), Vector2(95, 50));
	Container& s1p2 = side1.create <Container> (Vector2(5, 50), Vector2(95, 95));

	Container& s2p1 = side2.create <Container> (Vector2(5, 5), Vector2(95, 50));
	Container& s2p2 = side2.create <Container> (Vector2(5, 50), Vector2(95, 95));

	while(true)
	{
		root.update();
	}

	return 0;
}
