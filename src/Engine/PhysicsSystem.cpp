#include <Engine/PhysicsSystem.hpp>
#include <Engine/RigidBodyComponent.hpp>
#include <Engine/Components/VelocityComponent.hpp>
#include <Engine/transform.hpp>
#include <entt/entt.hpp>

PhysicsSystem::PhysicsSystem(entt::registry& registry):
	m_registry(registry)
{
}

void PhysicsSystem::Update(float deltaTime)
{
	auto view = m_registry.view<Transform, VelocityComponent, RigidBodyComponent>();
	for (entt::entity entity : view)
	{
		RigidBodyComponent& entityRigidBody = view.get<RigidBodyComponent>(entity);
		Transform& entityTransform = view.get<Transform>(entity);
		VelocityComponent& entityVelocity = view.get<VelocityComponent>(entity);

		entityTransform.Translate(entityVelocity.linearVel * deltaTime);
		entityTransform.Rotate(entityVelocity.angularVel * deltaTime);
	}
}
