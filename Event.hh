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
		} mouseInfo;
	};

	enum class Type
	{
		KeyPress,
		MouseClick,
		None
	};

	ValueType value;
	Type type = Type::None;
};

#endif
