#ifndef _VECTOR2_HPP_
#define _VECTOR2_HPP_

#include <iostream>



template<typename T>
struct Vector2
{
public:
	Vector2();
	Vector2(Vector2&);
	Vector2(T, T);
	~Vector2();

	Vector2& operator+=(const Vector2&);
	Vector2 operator+(const Vector2&);

	Vector2& operator-=(const Vector2&);
	Vector2 operator-(const Vector2&);

	Vector2& operator*=(T);
	Vector2 operator*(T);

	Vector2& operator/=(T);
	Vector2 operator/(T);
	
	friend std::ostream& operator<<(std::ostream&, const Vector2<T>&);

	T x, y;
};

#endif // !_VECTOR2_HPP_