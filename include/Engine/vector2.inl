#include "vector2.hpp"

template<typename T>
Vector2<T>::Vector2()
{
	x = 0.f;
	y = 0.f;
}

template<typename T>
Vector2<T>::Vector2(Vector2& _vec) :
	x(_vec.x), y(_vec.y)
{
}

template<typename T>
Vector2<T>::Vector2(T _x, T _y)
{
	x = _x;
	y = _y;
}

template<typename T>
Vector2<T>::~Vector2()
{
}
template<typename T>
Vector2<T>& Vector2<T>::operator+=(const Vector2& _vector2B)
{
	x += _vector2B.x;
	y += _vector2B.y;

	return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2& _vector2B)
{
	return Vector2(x + _vector2B.x, y + _vector2B.y);
}

template<typename T>
Vector2<T>& Vector2<T>::operator-=(const Vector2& _vector2B)
{
	x -= _vector2B.x;
	y -= _vector2B.y;

	return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2& _vector2B)
{
	return Vector2(x - _vector2B.x, y - _vector2B.y);
}

template<typename T>
Vector2<T>& Vector2<T>::operator*=(T _value)
{
	x *= _value;
	y *= _value;

	return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator*(T _value)
{
	return Vector2(x * _value, y * _value);
}

template<typename T>
Vector2<T>& Vector2<T>::operator/=(T _value)
{
	x *= _value;
	y *= _value;

	return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator/(T _value)
{
	return Vector2(x * _value, y * _value);
}

template<typename T>
std::ostream& operator<<(std::ostream& _os, const Vector2<T>& _vector)
{
	_os << "Vector2(" << _vector.x << ", " << _vector.y << ")";

	return _os;
}