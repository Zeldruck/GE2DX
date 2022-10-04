#include <Engine/transform.hpp>
#include <Engine/vector2.hpp>
#include <Engine/utilities.hpp>
#include <cmath>

Transform::Transform():
m_position(0.f, 0.f),
m_rotation(0.f),
m_scale(1.f, 1.f)
{
}

Transform::~Transform()
{
}

void Transform::SetPosition(const Vector2<float>& _translation)
{
	m_position.x = _translation.x;
	m_position.y = _translation.y;
}

void Transform::SetRotation(float _rotation)
{
	m_rotation = _rotation;
}

void Transform::SetScale(const Vector2<float>& _scale)
{
	m_scale.x = _scale.x;
	m_scale.y = _scale.y;
}

void Transform::TransformPoint(const Vector2<float>& _point)
{
	float radiant = Deg2Rad(m_rotation);

	float xPos = _point.x - m_position.x;
	float yPos = _point.y - m_position.y;

	float cos = std::cos(radiant);
	float sin = std::sin(radiant);

	float tempX = xPos * cos - yPos * sin;
	float tempY = xPos * cos + yPos * sin;

	m_position->x = tempX + m_position.x;
	m_position->y = tempY + m_position.y;
}
