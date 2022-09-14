#ifndef _VECTOR2_HPP_
#define _VECTOR2_HPP_

#include <iostream>

class Vector2
{
public:
	Vector2();
	Vector2(float, float);
	~Vector2();

	Vector2& operator=(const Vector2&);

	Vector2& operator+=(const Vector2&);
	Vector2 operator+(const Vector2&);

	Vector2& operator-=(const Vector2&);
	Vector2 operator-(const Vector2&);

	Vector2& operator*=(float);
	Vector2 operator*(float);
	

	friend std::ostream& operator<<(std::ostream&, const Vector2&);

private:
	float x, y;
};

#endif // !_VECTOR2_HPP_