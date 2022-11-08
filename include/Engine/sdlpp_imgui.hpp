#pragma once

#include <Engine/Export.hpp>

class SDLpp_renderer;
class SDLpp_window;
union SDL_Event;
struct ImGuiContext;

class GE2DX_ENGINE_API SDLpp_imgui
{
public:
	SDLpp_imgui(SDLpp_window& window, SDLpp_renderer& renderer);
	SDLpp_imgui(const SDLpp_imgui&) = delete;
	SDLpp_imgui(SDLpp_imgui&&) = delete;
	~SDLpp_imgui();

	ImGuiContext* GetContext();

	void Render();

	void NewFrame();

	void ProcessEvent(SDL_Event& event);

	SDLpp_imgui& operator=(const SDLpp_imgui&) = delete;
	SDLpp_imgui& operator=(SDLpp_imgui&&) = delete;

private:
	ImGuiContext* m_context;
};