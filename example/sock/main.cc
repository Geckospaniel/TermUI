#include "../Container.hh"
#include "../Logger.hh"
#include "../Menu.hh"
#include "HostTCP.hh"

#include <thread>
#include <chrono>

int main()
{
	Container root(true);

	Logger& side1 = root.create <Logger> (Vector2(5, 5), Vector2(50, 50), true);
	//HostTCP host(side1, "127.0.0.1", 8000);

	while(true)
	{
		root.update();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	return 0;
}
