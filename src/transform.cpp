#include "transform.hpp"
#include "vector2.hpp"
#include "utilities.hpp"
#include <cmath>

Transform::Transform(const Vector2<float> _pos)
{
	origin = std::make_unique<Vector2<float>>(0.f, 0.f);

	position = std::make_unique<Vector2<float>>(_pos.x, _pos.y);
	rotation = 0.f;
	scale = std::make_unique<Vector2<float>>(1.f, 1.f);
}

Transform::Transform(const Vector2<float> _pos, const float _rot)
{
	origin = std::make_unique<Vector2<float>>(0.f, 0.f);

	position = std::make_unique<Vector2<float>>(_pos.x, _pos.y);
	rotation = _rot;
	scale = std::make_unique<Vector2<float>>(1.f, 1.f);
}

Transform::Transform(const Vector2<float> _pos, const float _rot, const Vector2<float> _scale)
{
	origin = std::make_unique<Vector2<float>>(0.f, 0.f);

	position = std::make_unique<Vector2<float>>(_pos.x, _pos.y);
	rotation = _rot;
	scale = std::make_unique<Vector2<float>>(_scale.x, _scale.y);
}

Transform::Transform(Transform&& _transform) noexcept
{
	std::swap(position, _transform.position);
	std::swap(scale, _transform.scale);
	std::swap(origin, _transform.origin);
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

void Transform::SetPosition(const Vector2<float> _translation)
{
	position->x = _translation.x;
	position->y = _translation.y;
}

void Transform::SetRotation(const float _rotation)
{
	rotation = _rotation;
}

void Transform::SetScale(const Vector2<float> _scale)
{
	scale->x = _scale.x;
	scale->y = _scale.y;
}

/*void Transform::OriginPoint(const Vector2 _origin)
{
	origin->x = _origin.x;
	origin->y = _origin.y;
}
*/