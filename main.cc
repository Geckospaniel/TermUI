#include "Container.hh"
#include "List.hh"
#include "Menu.hh"

int main()
{
	Container root;

	Container& side1 = root.create <Container> (Vector2(5, 5), Vector2(50, 95));
	Menu& side2 = root.create <Menu> (Vector2(50, 5), Vector2(95, 95));

	MenuEntry& test = side2.root.add("test");
	MenuEntry& test2 = side2.root.add("test2");

	MenuEntry& testsub1 = test.add("test1");
	MenuEntry& testsub2 = test.add("test2");

	while(true)
	{
		root.update();
	}

	return 0;
}
