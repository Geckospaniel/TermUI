#include "Logger.hh"

#include <iomanip>

void Logger::draw()
{
	const size_t scrollHeight = size.y;
	size_t offset = cursorPosition >= scrollHeight ?
					cursorPosition - scrollHeight + 1 : 0;

	for(size_t i = offset; i < messages.size(); i++)
	{
		//	Does this message have a level that's displayed?
		if(!levelUsed[ static_cast <size_t> (messages[i].level) ])
			continue;

		Color::Name fg;
		bool sel = i == cursorPosition;
		size_t xPos = 0;

		//	Determine the message color
		switch(messages[i].level)
		{
			case LogLevel::Debug: fg = sel ? Color::LightGreen : Color::Green; break;
			case LogLevel::Error: fg = sel ? Color::LightRed : Color::Red; break;
			case LogLevel::Normal: fg = sel ? Color::LightWhite : Color::White; break;
			case LogLevel::Warning: fg = Color::LightYellow; break;
		}

		if(showTimestamps)
		{
			std::stringstream ss;
			std::time_t t = std::chrono::system_clock::to_time_t(messages[i].time);
			ss << std::put_time(std::localtime(&t), "%H:%M:%S ");

			setColor(Color::White, Color::Black);
			drawTextLine(ss.str(), 0, i - offset, true);
			xPos += ss.str().length();
		}

		setColor(fg, Color::Black);

		//	If the timestamp has been drawn, draw the message after it
		drawTextLine(messages[i].msg, xPos, i - offset, !showTimestamps);
	}
}

void Logger::onKeyPress(int key)
{
	switch(key)
	{
		case KEY_UP:
			if(--cursorPosition >= messages.size())
				cursorPosition = messages.size() - 1;
		break;

		case KEY_DOWN:
			if(++cursorPosition >= messages.size())
				cursorPosition = 0;
		break;
	}
}

void Logger::onMouseEvent(Vector2 mouse, bool leftDown)
{
	if(leftDown)
		addMessage(LogLevel::Debug, "Mouse at ", mouse.x, " ", mouse.y, " and left mouse ", leftDown);
}
