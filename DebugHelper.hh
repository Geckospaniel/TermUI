#ifndef DEBUG_HELPER_HEADER
#define DEBUG_HELPER_HEADER

#include "Logger.hh"

class DebugHelper
{
public:
	static Logger* logger;

	template <typename... Args>
	inline static void log(LogLevel l, Args&& ...args)
	{
		if(logger != nullptr)
			logger->addMessage(l, std::forward <Args> (args)...);
	}
};

#endif
