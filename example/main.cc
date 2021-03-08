#include "../Container.hh"
#include "../Logger.hh"
#include "../Menu.hh"

#include <thread>
#include <chrono>

int main()
{
	Container root(false);

	Logger& side1 = root.create <Logger> (Vector2(5, 5), Vector2(50, 50), true);
	Menu& side2 = root.create <Menu> (Vector2(50, 5), Vector2(95, 95));

	MenuEntry& test = side2.root.add("test");
	test.onSelect = [&root, &side2]()
	{
		auto waitForSubmit = [](Container& c, Menu& s2)
		{
			Menu& inner = c.create <Menu> (Vector2(10, 10), Vector2(90, 90));
			MenuEntry& ok = inner.root.add("moi");
			bool done = false;

			ok.onSelect = [&done]()
			{
				done = true;
			};

			while(!done)
			{
				std::this_thread::sleep_for(std::chrono::seconds(1));
				inner.root.add("ok");
			}

			inner.root.add("Is done");
			inner.close();
		};

		Container& c = root.create <Container> (Vector2(5, 50), Vector2(50, 95));
		std::thread th(waitForSubmit, std::ref(c), std::ref(side2));
		th.detach();
	};

	while(true)
	{
		root.update();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	return 0;
}
