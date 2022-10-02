#include "transform.hpp"
#include "vector2.hpp"
#include "utilities.hpp"
#include <cmath>

Transform::Transform(const Vector2<float> _pos)
{
	position = std::make_unique<Vector2<float>>(_pos.x, _pos.y);
	rotation = 0.f;
	scale = std::make_unique<Vector2<float>>(1.f, 1.f);
}

Transform::Transform(const Vector2<float> _pos, const float _rot)
{
	position = std::make_unique<Vector2<float>>(_pos.x, _pos.y);
	rotation = _rot;
	scale = std::make_unique<Vector2<float>>(1.f, 1.f);
}

Transform::Transform(const Vector2<float> _pos, const float _rot, const Vector2<float> _scale)
{

	position = std::make_unique<Vector2<float>>(_pos.x, _pos.y);
	rotation = _rot;
	scale = std::make_unique<Vector2<float>>(_scale.x, _scale.y);
}

Transform::Transform(Transform&& _transform) noexcept
{
	std::swap(position, _transform.position);
	std::swap(scale, _transform.scale);
	rotation = _transform.rotation;
}

Transform::~Transform()
{
}

Transform& Transform::operator=(Transform&& _transform) noexcept
{
	std::swap(position, _transform.position);
	std::swap(scale, _transform.scale);

	return *this;
}

void Transform::SetPosition(const Vector2<float>& _translation)
{
	position->x = _translation.x;
	position->y = _translation.y;
}

void Transform::SetRotation(const float& _rotation)
{
	rotation = _rotation;
}

void Transform::SetScale(const Vector2<float>& _scale)
{
	scale->x = _scale.x;
	scale->y = _scale.y;
}

void Transform::TransformPoint(const Vector2<float>& _point)
{
	float radiant = Deg2Rad(rotation);

	float xPos = _point.x - position->x;
	float yPos = _point.y - position->y;

	float cos = std::cos(radiant);
	float sin = std::sin(radiant);

	float tempX = xPos * cos - yPos * sin;
	float tempY = xPos * cos + yPos * sin;

	position->x = tempX + position->x;
	position->y = tempY + position->y;
}
