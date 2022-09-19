#include "..\include\vector2.hpp"

Vector2::Vector2()
{
	x = 0.f;
	y = 0.f;
}

Vector2::Vector2(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vector2::~Vector2()
{
}

Vector2& Vector2::operator=(const Vector2& _vector2B)
{
	x = _vector2B.x;
	y = _vector2B.y;

	return *this;
}

Vector2& Vector2::operator+=(const Vector2& _vector2B)
{
	x += _vector2B.x;
	y += _vector2B.y;

	return *this;
}

Vector2 Vector2::operator+(const Vector2& _vector2B)
{
	return Vector2(x + _vector2B.x, y + _vector2B.y);
}

Vector2& Vector2::operator-=(const Vector2& _vector2B)
{
	x -= _vector2B.x;
	y -= _vector2B.y;

	return *this;
}

Vector2 Vector2::operator-(const Vector2& _vector2B)
{
	return Vector2(x - _vector2B.x, y - _vector2B.y);
}

Vector2& Vector2::operator*=(float _value)
{
	x *= _value;
	y *= _value;

	return *this;
}

Vector2 Vector2::operator*(float _value)
{
	return Vector2(x * _value, y * _value);
}

std::ostream& operator<<(std::ostream& _os, const Vector2& _vector)
{
	_os << "Vector2(" << _vector.x << ", " << _vector.y << ")";

	return _os;
}