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
#include <Engine/Components/VelocityComponent.hpp>

void RenderSystem(entt::registry&, SDLpp_renderer&);
void VelocitySystem(entt::registry&, float);

int main(int argc, char** argv)
{
    SDLpp sdlpp;

    SDLpp_window windowpp("GE2DX", 1280, 720);
    SDLpp_renderer rendererpp(windowpp);

    ResourceManager resourceManager(rendererpp);

    entt::registry registry;

    /* BG */
    entt::entity bg = registry.create();
    Transform& bgTransform = registry.emplace<Transform>(bg);
    Sprite& bgSprite = registry.emplace<Sprite>(bg);
    bgSprite.SetTexture(ResourceManager::Instance().GetTexture("assets/test.jpg"));

    /* Other */
    entt::entity other = registry.create();
    Transform& otherTransform = registry.emplace<Transform>(other);

    Sprite& otherSprite = registry.emplace<Sprite>(other);
    otherSprite.SetTexture(ResourceManager::Instance().GetTexture("assets/sprsh.png"));
    otherSprite.SetRect(SDL_Rect{ 0, 0, 64, 64 });
    otherSprite.Resize(256, 256);

    VelocityComponent& otherVelocity = registry.emplace<VelocityComponent>(other);
    otherVelocity.velocity = Vector2f(1.f, 0.f);


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

        /*if (duration > 0.f)
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

        transform.Rotate(0.5f * deltaTime);*/

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

        VelocitySystem(registry, deltaTime);

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        rendererpp.SetDrawColor(0, 0, 0);
        rendererpp.Clear();

        ImGui::LabelText("Hello", "zzz");

        /*bg.Draw(rendererpp, bgTransform);
        sprsh.Draw(rendererpp, transform);*/

        RenderSystem(registry, rendererpp);

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

void RenderSystem(entt::registry& _registry, SDLpp_renderer& _renderer)
{
    auto view = _registry.view<Transform, Sprite>();
    for (entt::entity entity : view)
    {
        auto& entityTransform = view.get<Transform>(entity);
        auto& entitySprite = view.get<Sprite>(entity);

        entitySprite.Draw(_renderer, entityTransform);
    }
}

void VelocitySystem(entt::registry& _registry, float _deltaTime)
{
    auto view = _registry.view<Transform, VelocityComponent>();
    for (entt::entity entity : view)
    {
        auto& entityTransform = view.get<Transform>(entity);
        auto& entityVelocity = view.get<VelocityComponent>(entity);

        entityTransform.Translate(entityVelocity.velocity * _deltaTime);
    }
}