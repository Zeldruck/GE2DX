#pragma once

#include <Engine/vector2.hpp>

struct VelocityComponent
{
	Vector2f linearVel = Vector2f(0.f, 0.f);
	float angularVel = 0.f;
};