#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_

#include <memory>

template<typename T>
struct Vector2;

class Transform
{
public:
	Transform(const Vector2<float>);
	Transform(const Vector2<float>, const float);
	Transform(const Vector2<float>, const float, const Vector2<float>);
	
	Transform(Transform&&) noexcept;
	Transform(const Transform&) = delete;
	~Transform();

	Transform& operator=(const Transform&) = delete;
	Transform& operator=(Transform&&) noexcept;


	void SetPosition(const Vector2<float>&);
	void SetRotation(const float&);
	void SetScale(const Vector2<float>&);

	void TransformPoint(const Vector2<float>&);


public:
	std::unique_ptr<Vector2<float>> position;
	float rotation;
	std::unique_ptr<Vector2<float>> scale;

private:

};

#endif // !_TRANSFORM_HPP_
