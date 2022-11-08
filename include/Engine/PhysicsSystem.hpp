#pragma once

#include <Engine/Export.hpp>
#include <entt/fwd.hpp> //< header sp�cial qui fait des d�clarations anticip�es des classes de la lib

class GE2DX_ENGINE_API PhysicsSystem
{
public:
	PhysicsSystem(entt::registry& registry);

	void Update(float deltaTime);

private:
	entt::registry& m_registry;
};