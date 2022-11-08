#include <Engine/sdlpp_imgui.hpp>
#include <Engine/sdlpp_renderer.hpp>
#include <Engine/sdlpp_window.hpp>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>

SDLpp_imgui::SDLpp_imgui(SDLpp_window& window, SDLpp_renderer& renderer)
{
	// Setup imgui
	IMGUI_CHECKVERSION();
	m_context = ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForSDLRenderer(window.GetHandle(), renderer.GetHandle());
	ImGui_ImplSDLRenderer_Init(renderer.GetHandle());
}

SDLpp_imgui::~SDLpp_imgui()
{
	// Cleanup
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext(m_context);
}

ImGuiContext* SDLpp_imgui::GetContext()
{
	return m_context;
}

void SDLpp_imgui::Render()
{
	ImGui::Render();
	ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}

void SDLpp_imgui::NewFrame()
{
	ImGui_ImplSDLRenderer_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
}

void SDLpp_imgui::ProcessEvent(SDL_Event& event)
{
	ImGui_ImplSDL2_ProcessEvent(&event);
}