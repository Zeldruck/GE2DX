#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_

#include <Engine/Export.hpp>
#include <memory>

template<typename T>
struct Vector2;

class GE2DX_ENGINE_API Transform
{
public:
	Transform();
	
	Transform(Transform&&) = default;
	Transform(const Transform&) = default;
	~Transform();

	Transform& operator=(const Transform&) = default;
	Transform& operator=(Transform&&) = default;


	void SetPosition(const Vector2<float>&);
	void SetRotation(float);
	void SetScale(const Vector2<float>&);

	void TransformPoint(const Vector2<float>&);

public:
	Vector2<float> m_position;
	float m_rotation;
	Vector2<float> m_scale;

private:

};

#endif // !_TRANSFORM_HPP_
