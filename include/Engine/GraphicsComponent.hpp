#pragma once

#include <Engine/Export.hpp>
#include <memory>

class Renderable;

struct GE2DX_ENGINE_API GraphicsComponent
{
	std::shared_ptr<Renderable> renderable;
};