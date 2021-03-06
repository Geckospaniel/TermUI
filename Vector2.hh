#ifndef VECTOR2_HEADER
#define VECTOR2_HEADER

struct Vector2
{
	Vector2() : x(0), y(0) {}
	Vector2(int x, int y) : x(x), y(y) {}

	Vector2 operator+(const Vector2& rhs) const { return Vector2(x + rhs.x, y + rhs.y); }
	Vector2 operator-(const Vector2& rhs) const { return Vector2(x - rhs.x, y - rhs.y); }

	void operator+=(const Vector2& rhs) { x += rhs.x; y += rhs.y; }
	void operator-=(const Vector2& rhs) { x -= rhs.x; y -= rhs.y; }

	bool operator<(const Vector2& rhs) { return x < rhs.x && y < rhs.y; }
	bool operator>(const Vector2& rhs) { return x > rhs.x && y > rhs.y; }

	int x;
	int y;
};

#endif
