#include "HostTCP.hh"

#include <sys/socket.h>
#include <sys/types.h>

#include <cstring>
#include <cerrno>

HostTCP::HostTCP(Logger& logger, const char* address, unsigned port)
	: logger(logger)
{
	logger.addMessage(LogLevel::Debug, "Starting a host on ", address, ':', port);

	fdHost = socket(AF_INET, SOCK_STREAM, 0);
	if(hasError(fdHost < 0, "socket()"))
		return;

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(address);

	int result = bind(fdHost, reinterpret_cast <sockaddr*> (&addr), sizeof(sockaddr_in));
	if(hasError(result < 0, "bind()"))
		return;

	result = listen(fdHost, 5);
	if(hasError(result < 0, "listen()"))
		return;
}

bool HostTCP::hasError(bool error, const char* description)
{
	if(error)
	{
		const char* errorMsg = strerror(errno);
		logger.addMessage(LogLevel::Error, "Error in ", description, " : ", errorMsg);
	}

	return error;
}
