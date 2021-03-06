#include "../Container.hh"
#include "../Logger.hh"
#include "../Menu.hh"

int main()
{
	Container root;

	Logger& side1 = root.create <Logger> (Vector2(5, 5), Vector2(50, 50), true);
	Menu& side2 = root.create <Menu> (Vector2(50, 5), Vector2(95, 95));
	Container& side3 = root.create <Container> (Vector2(5, 50), Vector2(50, 95));

	Logger& cont1 = side3.create <Logger> (Vector2(5, 5), Vector2(50, 50), true);
	Logger& cont2 = side3.create <Logger> (Vector2(5, 50), Vector2(50, 95), true);
	Logger& cont3 = side3.create <Logger> (Vector2(50, 5), Vector2(95, 50), true);

	MenuEntry& test = side2.root.add("test");
	MenuEntry& test2 = side2.root.add("test2");

	MenuEntry& testsub1 = test.add("testsub1");
	MenuEntry& testsub2 = test.add("testsub2");

	for(int i = 0; i < 100; i++)
		side1.addMessage(LogLevel::Warning, i);

	cont1.stealFocus();

	while(true)
	{
		root.update();
	}

	return 0;
}
