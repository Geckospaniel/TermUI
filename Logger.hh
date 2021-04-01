#ifndef LOGGER_HEADER
#define LOGGER_HEADER

#include "Window.hh"

#include <utility>
#include <sstream>
#include <vector>
#include <chrono>
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

	void onMouseEvent(Vector2 mouse, bool leftDown) override;
	void onKeyPress(int key) override;
	void draw() override;

	template <typename... Args>
	void addMessage(LogLevel l, Args&& ...args)
	{
		//	Current time
		auto time = std::chrono::system_clock::now();

		//	Save all the arguments with a fold expression
		std::ostringstream ss;
		((ss << args), ...);

		cursorPosition = messages.size();
		messages.push_back( { time, ss.str(), l } );

		setRedraw();
	}
	
private:
	struct Message
	{
		std::chrono::time_point <std::chrono::system_clock> time;
		std::string msg;
		LogLevel level;
	};

	std::array <bool, 4> levelUsed;
	std::vector <Message> messages;

	size_t cursorPosition = 0;
	bool showTimestamps;
};

#endif
