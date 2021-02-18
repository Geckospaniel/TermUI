#ifndef COLOR_HEADER
#define COLOR_HEADER

#include <ncurses.h>

class Color
{
public:
	enum Name
	{
		Black, Red, Green,
		Yellow, Blue, Magenta,
		Cyan, White
	};

	static bool initialize()
	{
		if(!has_colors())
			return false;

		start_color();
		unsigned index = 1;

		//	Loop through each color and initialize them
		for(unsigned fg = 0; fg < size; fg++)
		{
			for(unsigned bg = 0; bg < size; bg++)
				init_pair(index++, fg, bg);
		}

		return true;
	}

	static void useColor(Name fg, Name bg)
	{
		/*	Since the colors are initialized in a 2 dimensional
		 *	for loop, we can treat fg and bg as x and y
		 *	and calculate the correct index	*/
		unsigned index = size * fg + bg + 1;
		attron(COLOR_PAIR(index));
	}

private:
	static constexpr unsigned size = 8;
};

#endif
