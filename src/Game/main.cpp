#include <SDL.h>
#include <Engine/AnimationSystem.hpp>
#include <Engine/CameraComponent.hpp>
#include <Engine/GraphicsComponent.hpp>
#include <Engine/SpritesheetComponent.hpp>
#include <Engine/InputSystem.hpp>
#include <Engine/Model.hpp>
#include <Engine/RenderSystem.hpp>
#include <Engine/ResourceManager.hpp>
#include <Engine/SDLpp.hpp>
#include <Engine/SDLpp_Window.hpp>
#include <Engine/SDLpp_ImGui.hpp>
#include <Engine/SDLpp_Renderer.hpp>
#include <Engine/Sprite.hpp>
#include <Engine/Transform.hpp>
#include <Engine/RigidBodyComponent.hpp>
#include <Engine/VelocitySystem.hpp>
#include <Engine/PhysicsSystem.hpp>
#include <entt/entt.hpp>
#include <fmt/core.h>
#include <imgui.h>


entt::entity CreateCamera(entt::registry& registry);
entt::entity CreateHouse(entt::registry& registry);
entt::entity CreateRunner(entt::registry& registry, std::shared_ptr<Spritesheet> spritesheet);

void EntityInspector(const char* windowName, entt::registry& registry, entt::entity entity);

void HandleCameraMovement(entt::registry& registry, entt::entity camera, float deltaTime);
void HandleRunnerMovement(entt::registry& registry, entt::entity runner, float deltaTime);

int main(int argc, char** argv)
{
    SDLpp sdlpp;

    SDLpp_window windowpp("GE2DX", 1280, 720);
    SDLpp_renderer rendererpp(windowpp);

    ResourceManager resourceManager(rendererpp);
    InputSystem inputManager;

    SDLpp_imgui imgui(windowpp, rendererpp);

    ImGui::SetCurrentContext(imgui.GetContext());

    // ZQSD
    InputSystem::Instance().BindKeyPressed(SDLK_q, "MoveLeft");
    InputSystem::Instance().BindKeyPressed(SDLK_d, "MoveRight");
    InputSystem::Instance().BindKeyPressed(SDLK_z, "MoveUp");
    InputSystem::Instance().BindKeyPressed(SDLK_s, "MoveDown");

    // Touches directionnelles (caméra)
    InputSystem::Instance().BindKeyPressed(SDLK_LEFT, "CameraMoveLeft");
    InputSystem::Instance().BindKeyPressed(SDLK_RIGHT, "CameraMoveRight");
    InputSystem::Instance().BindKeyPressed(SDLK_UP, "CameraMoveUp");
    InputSystem::Instance().BindKeyPressed(SDLK_DOWN, "CameraMoveDown");

    std::shared_ptr<Spritesheet> spriteSheet = std::make_shared<Spritesheet>();
    spriteSheet->AddAnimation("idle", 5, 0.1f, Vector2i{ 0, 0 }, Vector2i{ 32, 32 });
    spriteSheet->AddAnimation("run", 8, 0.1f, Vector2i{ 0, 32 }, Vector2i{ 32, 32 });
    spriteSheet->AddAnimation("jump", 4, 0.1f, Vector2i{ 0, 64 }, Vector2i{ 32, 32 });


    entt::registry registry;

    AnimationSystem animSystem(registry);
    RenderSystem renderSystem(rendererpp, registry);
    VelocitySystem velocitySystem(registry);
    PhysicsSystem physicsSystem(registry);

    entt::entity cameraEntity = CreateCamera(registry);

    entt::entity house = CreateHouse(registry);
    registry.get<Transform>(house).SetPosition({ 750.f, 275.f });
    registry.get<Transform>(house).SetScale({ 2.f, 2.f });

    entt::entity runner = CreateRunner(registry, spriteSheet);
    registry.get<Transform>(runner).SetPosition({ 300.f, 250.f });

    Uint64 lastUpdate = SDL_GetPerformanceCounter();

    float speedTime = 0.1f;
    float duration = speedTime;
    int index = 0;

    InputSystem::Instance().BindKeyPressed(SDL_KeyCode::SDLK_r, "PlayRun");

    InputSystem::Instance().OnAction("PlayRun", [&](bool pressed)
        {
            if (pressed)
                registry.get<SpritesheetComponent>(runner).PlayAnimation("run");
            else
                registry.get<SpritesheetComponent>(runner).PlayAnimation("idle");
        });

    bool isRunning = true;

    while (isRunning)
    {
        Uint64 now = SDL_GetPerformanceCounter();
        float deltaTime = static_cast<float>(now - lastUpdate) / SDL_GetPerformanceFrequency();
        lastUpdate = now;

        SDL_Event event;

        while (SDLpp::PollEvent(&event) > 0) // Still have events to fetch
        {
	        if (event.type == SDL_QUIT)
	        {
                isRunning = false;
                break;
	        }

            imgui.ProcessEvent(event);

            InputSystem::Instance().HandleEvent(event);
        }

        imgui.NewFrame();

        rendererpp.SetDrawColor(0, 0, 0);
        rendererpp.Clear();

        HandleCameraMovement(registry, cameraEntity, deltaTime);
        HandleRunnerMovement(registry, runner, deltaTime);

        EntityInspector("Camera", registry, cameraEntity);
        EntityInspector("Runner", registry, runner);

        animSystem.Update(deltaTime);
        velocitySystem.Update(deltaTime);
        renderSystem.Update(deltaTime);
        physicsSystem.Update(deltaTime);

        imgui.Render();

        RenderSystem(rendererpp, registry);

        ImGui::Render();

        rendererpp.Present();
    }

    return 0;
}

void EntityInspector(const char* windowName, entt::registry& registry, entt::entity entity)
{
    Transform& transform = registry.get<Transform>(entity);

    float rotation = transform.GetRotation();
    Vector2f pos = transform.GetPosition();
    Vector2f scale = transform.GetScale();

    ImGui::Begin(windowName);

    ImGui::LabelText("Position", "X: %f\nY: %f", pos.x, pos.y);

    if (ImGui::SliderFloat("Rotation", &rotation, -180.f, 180.f))
        transform.SetRotation(rotation);

    float scaleVal[2] = { scale.x, scale.y };
    if (ImGui::SliderFloat2("Scale", scaleVal, -5.f, 5.f))
        transform.SetScale({ scaleVal[0], scaleVal[1] });

    if (ImGui::Button("Reset"))
    {
        transform.SetScale({ 1.f, 1.f });
        transform.SetRotation(0.f);
        transform.SetPosition(Vector2f(0.f, 0.f));
    }

    ImGui::End();
}

entt::entity CreateCamera(entt::registry& registry)
{
    entt::entity entity = registry.create();
    registry.emplace<CameraComponent>(entity);
    registry.emplace<Transform>(entity);

    return entity;
}

entt::entity CreateHouse(entt::registry& registry)
{
    std::shared_ptr<Model> house = ResourceManager::Instance().GetModel("assets/house.bmodel");

    entt::entity entity = registry.create();
    registry.emplace<GraphicsComponent>(entity, std::move(house));
    registry.emplace<Transform>(entity);

    return entity;
}

entt::entity CreateRunner(entt::registry& registry, std::shared_ptr<Spritesheet> spritesheet)
{
    std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(ResourceManager::Instance().GetTexture("assets/runner.png"));
    sprite->Resize(256, 256);
    sprite->SetRect(SDL_Rect{ 0, 0, 32, 32 });

    entt::entity entity = registry.create();
    registry.emplace<SpritesheetComponent>(entity, spritesheet, sprite);
    registry.emplace<GraphicsComponent>(entity, std::move(sprite));
    registry.emplace<Transform>(entity);
    registry.emplace<RigidBodyComponent>(entity, 100.f);

    return entity;
}

void HandleCameraMovement(entt::registry& registry, entt::entity camera, float deltaTime)
{
    Transform& cameraTransform = registry.get<Transform>(camera);

    if (InputSystem::Instance().IsActive("CameraMoveDown"))
        cameraTransform.Translate(Vector2f(0.f, 500.f * deltaTime));

    if (InputSystem::Instance().IsActive("CameraMoveLeft"))
        cameraTransform.Translate(Vector2f(-500.f * deltaTime, 0.f));

    if (InputSystem::Instance().IsActive("CameraMoveRight"))
        cameraTransform.Translate(Vector2f(500.f * deltaTime, 0.f));

    if (InputSystem::Instance().IsActive("CameraMoveUp"))
        cameraTransform.Translate(Vector2f(0.f, -500.f * deltaTime));
}

void HandleRunnerMovement(entt::registry& registry, entt::entity runner, float deltaTime)
{
    Transform& transform = registry.get<Transform>(runner);

    if (InputSystem::Instance().IsActive("MoveDown"))
        transform.Translate(Vector2f(0.f, 500.f * deltaTime));

    if (InputSystem::Instance().IsActive("MoveLeft"))
        transform.Translate(Vector2f(-500.f * deltaTime, 0.f));

    if (InputSystem::Instance().IsActive("MoveRight"))
        transform.Translate(Vector2f(500.f * deltaTime, 0.f));

    if (InputSystem::Instance().IsActive("MoveUp"))
        transform.Translate(Vector2f(0.f, -500.f * deltaTime));
}