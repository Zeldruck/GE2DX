#pragma once
#pragma once

#include <Engine/Export.hpp>

class SDLpp_renderer;
class SDLpp_texture;
class Transform;

class GE2DX_ENGINE_API Renderable // interface
{
public:
	// Il est important pour une classe virtuelle de base d'avoir un destructeur virtuel
	virtual ~Renderable() = default;

	virtual void Draw(SDLpp_renderer& renderer, const Transform& cameraTransform, const Transform& transform) = 0;
};