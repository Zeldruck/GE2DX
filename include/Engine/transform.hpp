#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_

#include <Engine/Export.hpp>
#include <Engine/vector2.hpp>
#include <vector>

class GE2DX_ENGINE_API Transform
{
public:
	Transform();
	Transform(const Transform& transform);
	Transform(Transform&&) noexcept;
	~Transform();

	Vector2f GetGlobalPosition() const;
	float GetGlobalRotation() const;
	Vector2f GetGlobalScale() const;

	Transform* GetParent() const;
	const Vector2f& GetPosition() const;
	float GetRotation() const;
	const Vector2f& GetScale() const;

	void Rotate(float rotation);
	void Scale(float scale);
	void Scale(const Vector2f& scale);

	void SetParent(Transform* parent);
	void SetPosition(const Vector2f& position);
	void SetRotation(float rotation);
	void SetScale(const Vector2f& scale);

	void Translate(const Vector2f& translation);

	Vector2f TransformInversePoint(Vector2f position) const;
	Vector2f TransformPoint(Vector2f position) const;

	Transform& operator=(const Transform&);
	Transform& operator=(Transform&&) noexcept;

private:
	void AttachChild(Transform* child);
	void DetachChild(Transform* child);

	std::vector<Transform*> m_children;
	Transform* m_parent;
	Vector2f m_position;
	float m_rotation;
	Vector2f m_scale;

};

#endif // !_TRANSFORM_HPP_
