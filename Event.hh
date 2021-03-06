#ifndef EVENT_HEADER
#define EVENT_HEADER

#include "Vector2.hh"

struct Event
{
	union ValueType
	{
		int key;

		struct
		{
			int x;
			int y;

			bool leftDown;
		} mouseInfo;
	};

	enum class Type
	{
		KeyPress,
		Mouse,
		None
	};

	ValueType value;
	Type type = Type::None;
};

#endif
