#ifndef HOST_TCP_HEADER
#define HOST_TCP_HEADER

#include "../Logger.hh"

#include <arpa/inet.h>

#include <functional>
#include <string>
#include <vector>

class HostTCP
{
public:
	HostTCP(Logger& logger, const char* address, unsigned port);

private:
	bool hasError(bool error, const char* description);

	int fdHost = -1;
	Logger& logger;

	struct Connection
	{
		int client;
	};
};

#endif
