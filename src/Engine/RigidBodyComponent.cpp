#include <Engine/RigidBodyComponent.hpp>

RigidBodyComponent::RigidBodyComponent(float _mass):
	mass(_mass)
{
	body = std::make_shared<cpBody*>(cpBodyNew(_mass, std::numeric_limits<float>::infinity()));
	shape = std::make_shared<cpShape*>(cpBoxShapeNew(body.get(), 128.f, 256.f, 0.f));
}
