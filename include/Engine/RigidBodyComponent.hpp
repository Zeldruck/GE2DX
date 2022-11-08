#pragma once

#include <Engine/Export.hpp>
#include <memory>
#include <chipmunk/chipmunk.h>

class GE2DX_ENGINE_API RigidBodyComponent
{
public:
	RigidBodyComponent(float _mass);
	~RigidBodyComponent() = default;

private:
	float mass;

	std::shared_ptr<cpBody> body;
	std::shared_ptr<cpShape> shape;
};