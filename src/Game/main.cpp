#include <iostream>
#include <Engine/InputSystem.hpp>
#include <Engine/ResourceManager.hpp>
#include <Engine/SDLpp.hpp>
#include <Engine/SDLpp_window.hpp>
#include <Engine/SDLpp_renderer.hpp>
#include <Engine/SDLpp_texture.hpp>
#include <Engine/sprite.hpp>
#include <Engine/transform.hpp>
#include <fmt/core.h>

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>

#include <entt/entt.hpp>

struct Position
{
    Vector2f pos;
};

struct Velocity
{
    Vector2f vel;
};

int main(int argc, char** argv)
{
    /*entt::registry registry;

    entt::entity entity = registry.create();
    Position& entityPos = registry.emplace<Position>(entity);
    entityPos.pos = Vector2f(0.5f, 0.f);
    Velocity& entityVel = registry.emplace<Velocity>(entity);

    auto view = registry.view<Position, Velocity>();

    for (entt::entity e : view)
    {

    }

    return 0;*/

    SDLpp sdlpp;

    SDLpp_window windowpp("GE2DX", 1280, 720);
    SDLpp_renderer rendererpp(windowpp);

    ResourceManager resourceManager(rendererpp);


    // Setup imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(windowpp.GetHandle(), rendererpp.GetHandle());
    ImGui_ImplSDLRenderer_Init(rendererpp.GetHandle());


    InputSystem::Instance().BindKeyPressed(SDLK_h, "SayHello");
    InputSystem::Instance().BindMouseButtonPressed(MouseButton::Right, "SayHello");

    InputSystem::Instance().OnAction("SayHello", []()
    {
        std::cout << "Hello world" << std::endl;
    });

    Sprite bg(ResourceManager::Instance().GetTexture("assets/test.jpg"));
    bg.Resize(1280, 720);

    Sprite sprsh(ResourceManager::Instance().GetTexture("assets/sprsh.png"));
    sprsh.SetRect(SDL_Rect{ 0, 0, 64, 64});
    sprsh.Resize(256, 256);

    Transform transform;
    Transform bgTransform;
    

    Uint64 lastUpdate = SDL_GetPerformanceCounter();

    float speedTime = 0.1f;
    float duration = speedTime;
    int index = 0;

    bool isRunning = true;

    while (isRunning)
    {
        Uint64 now = SDL_GetPerformanceCounter();
        float deltaTime = static_cast<float>(now - lastUpdate) / SDL_GetPerformanceFrequency();
        lastUpdate = now;

        if (duration > 0.f)
            duration -= deltaTime;
        else
        {
            duration = speedTime;
            index++;

            if (index * 64 >= 832)
            {
                index = 0;
            }

            sprsh.SetRect(SDL_Rect{ index * 64, 0, 64, 64 });
        }

        transform.Rotate(0.5f * deltaTime);

        SDL_Event event;

        while (SDLpp::PollEvent(&event) > 0) // Still have events to fetch
        {
	        if (event.type == SDL_QUIT)
	        {
                isRunning = false;
                break;
	        }

            ImGui_ImplSDL2_ProcessEvent(&event);

            InputSystem::Instance().HandleEvent(event);
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        rendererpp.SetDrawColor(0, 0, 0);
        rendererpp.Clear();

        ImGui::LabelText("Hello", "zzz");

        bg.Draw(rendererpp, bgTransform);
        sprsh.Draw(rendererpp, transform);

        ImGui::Render();
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

        rendererpp.Present();
    }

    // Cleanup
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return 0;
}