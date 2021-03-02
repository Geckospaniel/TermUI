#ifndef LOGGER_HEADER
#define LOGGER_HEADER

#include "Window.hh"

#include <utility>
#include <sstream>
#include <vector>
#include <string>
#include <array>

enum class LogLevel : unsigned char
{
	Normal,
	Debug,
	Warning,
	Error
};

class Logger : public Window
{
public:
	Logger(const Vector2& start, const Vector2& end, bool showTimestamps) :
		Window(start, end), showTimestamps(showTimestamps)
	{
		levelUsed.fill(true);
	}

	
	inline void setState(LogLevel l, bool state)
	{
		levelUsed[static_cast <size_t> (l)] = state;
	}

	void onKeyPress(int key) override;
	void draw() override;

	template <typename... Args>
	void addMessage(LogLevel l, Args&& ...args)
	{
		//	Save all the arguments with a fold expression
		std::ostringstream ss;
		((ss << args), ...);

		cursorPosition = messages.size();
		messages.push_back( { ss.str(), l } );
	}
	
private:
	struct Message
	{
		std::string msg;
		LogLevel level;
	};

	std::array <bool, 4> levelUsed;
	std::vector <Message> messages;

	size_t cursorPosition = 0;
	bool showTimestamps;
};

#endif
