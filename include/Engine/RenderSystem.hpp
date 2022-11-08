#pragma once

#include <Engine/Export.hpp>
#include <entt/fwd.hpp> //< header sp�cial qui fait des d�clarations anticip�es des classes de la lib

class SDLpp_renderer;

class GE2DX_ENGINE_API RenderSystem
{
public:
	RenderSystem(SDLpp_renderer& renderer, entt::registry& registry);

	void Update(float deltaTime);

private:
	SDLpp_renderer& m_renderer;
	entt::registry& m_registry;
};