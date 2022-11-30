#include <SDL.h>
#include <A4Engine/AnimationSystem.hpp>
#include <A4Engine/CameraComponent.hpp>
#include <A4Engine/ChipmunkShape.hpp>
#include <A4Engine/ChipmunkSpace.hpp>
#include <A4Engine/CollisionShape.hpp>
#include <A4Engine/GraphicsComponent.hpp>
#include <A4Engine/InputManager.hpp>
#include <A4Engine/PhysicsSystem.hpp>
#include <A4Engine/RenderSystem.hpp>
#include <A4Engine/ResourceManager.hpp>
#include <A4Engine/CollisionLayersManager.hpp>
#include <A4Engine/RigidBodyComponent.hpp>
#include <A4Engine/SDLpp.hpp>
#include <A4Engine/SDLppImGui.hpp>
#include <A4Engine/SDLppRenderer.hpp>
#include <A4Engine/SDLppWindow.hpp>
#include <A4Engine/Sprite.hpp>
#include <A4Engine/SpritesheetComponent.hpp>
#include <A4Engine/Transform.hpp>
#include <chipmunk/chipmunk.h>
#include <entt/entt.hpp>
#include <fmt/core.h>
#include <imgui.h>
#include <A4Game/GameManager.hpp>
#include <A4Engine/CollisionHandlerManager.hpp>
#include <A4Game/PipesManager.hpp>

entt::entity CreateCamera(entt::registry& registry);
entt::entity CreateBird(entt::registry& registry);

cpBool BirdDeath(cpArbiter* arb, cpSpace* space, void* data);
cpBool RespawnPipes(cpArbiter* arb, cpSpace* space, void* data);


void EntityInspector(const char* windowName, entt::registry& registry, entt::entity entity);

void Menu(SDLppWindow& _window, SDLppRenderer& _renderer);
void Game(SDLppWindow& _window, SDLppRenderer& _renderer);

struct InputComponent
{
	bool jump = false;
};

struct PlayerControlled {};
struct NoGravity {};

void PlayerControllerSystem(entt::registry& registry);
void PlayerInputSystem(entt::registry& registry);
void NoGravitySystem(entt::registry& registry);

int main()
{
	SDLpp sdl;
	SDLppWindow window("A4Engine", 1280, 720);
	SDLppRenderer renderer(window, "direct3d11", SDL_RENDERER_PRESENTVSYNC);


	GameManager gameManager;
	
	while (gameManager.IsWindowOpen())
	{
		switch (gameManager.GetGameState())
		{
			case EWindowGameState::Menu:
				Menu(window, renderer);
				break;

			case EWindowGameState::Game:
				Game(window, renderer);
				break;

			case EWindowGameState::End: 
				break;

			default: 
				break;
		}
	}

	return 0;
}

void Menu(SDLppWindow& _window, SDLppRenderer& _renderer)
{
	GameManager::Instance().OpenState();



	SDLppImGui imgui(_window, _renderer);
	ImGui::SetCurrentContext(imgui.GetContext());

	Uint64 lastUpdate = SDL_GetPerformanceCounter();

	while (GameManager::Instance().IsStateOpen())
	{
		Uint64 now = SDL_GetPerformanceCounter();
		float deltaTime = (now - lastUpdate) / SDL_GetPerformanceFrequency();
		lastUpdate = now;

		SDL_Event event;
		while (SDLpp::PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				GameManager::Instance().CloseState();
				GameManager::Instance().CloseWindow();
			}

			if (event.key.state == SDL_PRESSED)
			{
				if (event.key.keysym.sym == SDLK_SPACE)
				{
					GameManager::Instance().CloseState();
					GameManager::Instance().SetGameState(EWindowGameState::Game);
				}

				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					GameManager::Instance().CloseState();
					GameManager::Instance().CloseWindow();
				}
			}

			imgui.ProcessEvent(event);
		}

		imgui.NewFrame();

		_renderer.SetDrawColor(0, 0, 0, 255);
		_renderer.Clear();

		ImGui::Begin("Menu");

		ImGui::Text("Press SPACE to start");

		ImGui::End();

		imgui.Render();
		_renderer.Present();
	}
}

void Game(SDLppWindow& _window, SDLppRenderer& _renderer)
{
	GameManager::Instance().OpenState();

	srand(time(NULL));


	SDLppImGui imgui(_window, _renderer);
	ImGui::SetCurrentContext(imgui.GetContext());


	ResourceManager resourceManager(_renderer);
	InputManager inputManager;
	CollisionLayersManager collisionLayers;
	CollisionHandlerManager collisionHandler;


	entt::registry registry;

	PipesManager pipesManager(registry);
	
	AnimationSystem animSystem(registry);
	RenderSystem renderSystem(_renderer, registry);
	PhysicsSystem physicsSystem(registry);

	physicsSystem.SetGravity({ 0.f, 981.f });
	physicsSystem.SetDamping(0.1f);


	// Set collisions layer
	CollisionLayersManager::Instance().AddCollisionLayer("DEFAULT");
	CollisionLayersManager::Instance().AddCollisionLayer("BIRD");
	CollisionLayersManager::Instance().AddCollisionLayer("DEATH");
	CollisionLayersManager::Instance().AddCollisionLayer("BORDER");
	CollisionLayersManager::Instance().AddCollisionLayer("PIPE");
	CollisionLayersManager::Instance().AddCollisionLayer("PIPES_DESTROYER");

	//Set collisions trigger/handler
	/*
	* ! NOT WORKING !
	*/
	//CollisionHandlerManager::Instance().AddCollisionHandler("BW_Death", PhysicsSystem::Instance()->GetSpace(), "BIRD", "WALL");
	//CollisionHandlerManager::Instance().SetHandlerPostSolveFunc("BW_Death", cpCollisionPostSolveFunc(BirdDeath));

	// Collision between bird and border -> death
	cpCollisionHandler* collisionHandlerBirdBorder = cpSpaceAddCollisionHandler(
		PhysicsSystem::Instance()->GetSpace().GetHandle(),
		CollisionLayersManager::Instance().Get("BIRD"),
		CollisionLayersManager::Instance().Get("BORDER"));
	collisionHandlerBirdBorder->postSolveFunc = cpCollisionPostSolveFunc(BirdDeath);

	// Collision between bird and death object -> death
	cpCollisionHandler* collisionHandlerBirdDeathObject = cpSpaceAddCollisionHandler(
		PhysicsSystem::Instance()->GetSpace().GetHandle(),
		CollisionLayersManager::Instance().Get("BIRD"),
		CollisionLayersManager::Instance().Get("DEATH"));
	collisionHandlerBirdDeathObject->postSolveFunc = cpCollisionPostSolveFunc(BirdDeath);

	// Collision between bird and pipes -> death
	cpCollisionHandler* collisionHandlerBirdPipe = cpSpaceAddCollisionHandler(
		PhysicsSystem::Instance()->GetSpace().GetHandle(),
		CollisionLayersManager::Instance().Get("BIRD"),
		CollisionLayersManager::Instance().Get("PIPE"));
	collisionHandlerBirdPipe->postSolveFunc = cpCollisionPostSolveFunc(BirdDeath);

	// Collision between pipes and pipe destroyer line
	cpCollisionHandler* collisionHandlerPipeDestroyer = cpSpaceAddCollisionHandler(
		PhysicsSystem::Instance()->GetSpace().GetHandle(),
		CollisionLayersManager::Instance().Get("PIPE"),
		CollisionLayersManager::Instance().Get("PIPES_DESTROYER"));
	collisionHandlerPipeDestroyer->postSolveFunc = cpCollisionPostSolveFunc(RespawnPipes);//
	


	entt::entity cameraEntity = CreateCamera(registry);
	registry.get<Transform>(cameraEntity).SetPosition({ 0.f, 0.f });


	// Game's border shape
	std::shared_ptr<CollisionShape> borderShape = std::make_shared<SegmentShape>(Vector2f(0.f, 0.f), Vector2f(1280.f, 0.f));
	borderShape->SetCollisionLayer("BORDER");

	// Upper border
	entt::entity upperBorder = registry.create();
	auto& upperPhysics = registry.emplace<RigidBodyComponent>(upperBorder, RigidBodyComponent::Static{});
	upperPhysics.AddShape(borderShape);

	// Lower border
	entt::entity lowerBorder = registry.create();
	auto& lowerPhysics = registry.emplace<RigidBodyComponent>(lowerBorder, RigidBodyComponent::Static{});
	lowerPhysics.AddShape(borderShape);
	lowerPhysics.TeleportTo({ 0.f, 720.f });

	// Pipes border destroyer shape
	std::shared_ptr<CollisionShape> pDestroyerShape = std::make_shared<SegmentShape>(Vector2f(0.f, 0.f), Vector2f(0.f, 720.f));
	pDestroyerShape->SetCollisionLayer("PIPES_DESTROYER");

	// Pipes destroyer
	entt::entity pDestroyerBorder = registry.create();
	auto& pdPhysics = registry.emplace<RigidBodyComponent>(pDestroyerBorder, 10.f, 0.f);
	pdPhysics.AddShape(pDestroyerShape);
	pdPhysics.TeleportTo({ -256.f, 0.f });
	registry.emplace<NoGravity>(pDestroyerBorder);


	entt::entity bird = CreateBird(registry);
	// Player pressed space in menu, so make the bird jump right away
	registry.get<RigidBodyComponent>(bird).SetLinearVelocity({0.f, -500.f});
	// Bind Space key to bird jump
	InputManager::Instance().BindKeyPressed(SDLK_SPACE, "Jump");


	std::shared_ptr<CollisionShape> boxShape = std::make_shared<BoxShape>(256.f, 256.f);
	boxShape->SetCollisionLayer("BORDER");

	std::string pipeCollisionLayerName = "PIPE";
	std::string pipeCollisionDeathLayerName = "DEATH";

	PipesManager::Instance().CreatePipes(1408.f, 300.f);
	PipesManager::Instance().CreatePipes(2176.f, 300.f);

	/*entt::entity pipe1 = PipesManager::Instance().CreatePipe({1408.f, 0.f}, 300.f, pipeCollisionLayerName);
	entt::entity pipe2 = PipesManager::Instance().CreatePipe({ 1408.f, 720.f }, 300.f, pipeCollisionDeathLayerName);
	entt::entity pipe3 = PipesManager::Instance().CreatePipe({ 2176.f, 0.f }, 300.f, pipeCollisionLayerName);
	entt::entity pipe4 = PipesManager::Instance().CreatePipe({ 2176.f, 720.f }, 300.f, pipeCollisionDeathLayerName);*/

	/*entt::entity pipeU = CreatePipes(registry, boxShape);
	registry.get<RigidBodyComponent>(pipeU).TeleportTo({ 960.f, 0.f });
	entt::entity pipeD = CreatePipes(registry, boxShape);
	registry.get<RigidBodyComponent>(pipeD).TeleportTo({ 960.f, 720.f });*/

	Uint64 lastUpdate = SDL_GetPerformanceCounter();

	while (GameManager::Instance().IsStateOpen())
	{
		Uint64 now = SDL_GetPerformanceCounter();
		float deltaTime = static_cast<float>(now - lastUpdate) / SDL_GetPerformanceFrequency();
		lastUpdate = now;


		SDL_Event event;
		while (SDLpp::PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				GameManager::Instance().CloseState();
				GameManager::Instance().CloseWindow();
			}

			if (event.key.state == SDL_PRESSED)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					GameManager::Instance().CloseState();
					GameManager::Instance().SetGameState(EWindowGameState::Menu);
				}
			}

			imgui.ProcessEvent(event);

			InputManager::Instance().HandleEvent(event);
		}


		imgui.NewFrame();

		_renderer.SetDrawColor(0, 0, 0, 255);
		_renderer.Clear();

		physicsSystem.Update(deltaTime);
		animSystem.Update(deltaTime);
		renderSystem.Update(deltaTime);

		NoGravitySystem(registry);

		PlayerInputSystem(registry);
		PlayerControllerSystem(registry);

		//pipesManager.FreePipes();
		pipesManager.Update();

		ImGui::Begin("Score");

		ImGui::Text("%i", GameManager::Instance().m_gameScore);

		ImGui::End();

		//physicsSystem.DebugDraw(_renderer, registry.get<Transform>(cameraEntity).GetTransformMatrix().Inverse());

		imgui.Render();
		_renderer.Present();
	}
}

void PlayerControllerSystem(entt::registry& registry)
{
	auto view = registry.view<RigidBodyComponent, InputComponent>();
	for (entt::entity entity : view)
	{
		auto& entityInput = view.get<InputComponent>(entity);
		auto& entityPhysics = view.get<RigidBodyComponent>(entity);

		Vector2f velocity = Vector2f(0.f, 0.f);
		velocity.y = entityPhysics.GetLinearVelocity().y;

		if (entityInput.jump)
		{
			velocity.y = -500.f;
			/*GameManager::Instance().m_gameScore++;
			printf("%i", GameManager::Instance().m_gameScore);*/
		}

		entityPhysics.SetLinearVelocity(velocity);
	}
}

void PlayerInputSystem(entt::registry& registry)
{
	auto view = registry.view<PlayerControlled, InputComponent>();
	for (entt::entity entity : view)
	{
		auto& entityInput = view.get<InputComponent>(entity);
		entityInput.jump = InputManager::Instance().IsActive("Jump");
	}
}

void NoGravitySystem(entt::registry& registry)
{
	auto view = registry.view<RigidBodyComponent, NoGravity>();
	for (entt::entity entity : view)
	{
		auto& entityPhysics = view.get<RigidBodyComponent>(entity);

		entityPhysics.SetLinearVelocity({0.f, 0.f});
	}
}

cpBool BirdDeath(cpArbiter* arb, cpSpace* space, void* data)
{
	GameManager::Instance().CloseState();
	GameManager::Instance().SetGameState(EWindowGameState::Menu); // Change to END

	return cpTrue;
}

cpBool RespawnPipes(cpArbiter* arb, cpSpace* space, void* data)
{
	PipesManager::Instance().EreaseFirstTwoPipes();

	PipesManager::Instance().CreatePipes(1408.f, 300.f);

	/*PipesManager::Instance().CreatePipe({1408.f, 0.f}, 300.f, "PIPE");
	PipesManager::Instance().CreatePipe({ 1408.f, 720.f }, 300.f, "DEATH");*/

	return cpTrue;
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

entt::entity CreateBox(entt::registry& registry, std::shared_ptr<CollisionShape> shape)
{
	std::shared_ptr<Sprite> box = std::make_shared<Sprite>(ResourceManager::Instance().GetTexture("assets/box.png"));
	box->SetOrigin({ 0.5f, 0.5f });

	entt::entity entity = registry.create();
	registry.emplace<GraphicsComponent>(entity, std::move(box));
	registry.emplace<Transform>(entity);

	auto& entityPhysics = registry.emplace<RigidBodyComponent>(entity, 250.f);
	entityPhysics.AddShape(std::move(shape));

	return entity;
}

entt::entity CreateCamera(entt::registry& registry)
{
	entt::entity entity = registry.create();
	registry.emplace<CameraComponent>(entity);
	registry.emplace<Transform>(entity);
	/*RigidBodyComponent& rgbc = registry.emplace<RigidBodyComponent>(entity, RigidBodyComponent::Static{});

	rgbc.SetLinearVelocity({ 100.f, 0.f });*/

	return entity;
}

entt::entity CreateBird(entt::registry& registry)
{
	std::shared_ptr<Spritesheet> birdSpriteSheet = std::make_shared<Spritesheet>();
	birdSpriteSheet->AddAnimation("idle", 3, 0.1f, Vector2i{ 0, 488 }, Vector2i{ 28, 24 });

	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(ResourceManager::Instance().GetTexture("assets/fpb.png"));
	sprite->SetOrigin({ 0.5f, 0.5f });
	sprite->Resize(256, 256);
	sprite->SetRect(SDL_Rect{ 0, 488, 30, 24 });

	std::shared_ptr<CollisionShape> collider = std::make_shared<BoxShape>(128.f, 128.f);
	collider->SetCollisionLayer("BIRD");

	entt::entity entity = registry.create();
	registry.emplace<SpritesheetComponent>(entity, birdSpriteSheet, sprite);
	registry.emplace<GraphicsComponent>(entity, std::move(sprite));
	registry.emplace<Transform>(entity);
	registry.emplace<InputComponent>(entity);
	registry.emplace<PlayerControlled>(entity);

	auto& entityBody = registry.emplace<RigidBodyComponent>(entity, 80.f, std::numeric_limits<float>::infinity());
	entityBody.AddShape(collider, Vector2f(-15.f, -30.f), false);
	entityBody.TeleportTo({ 640.f, 360.f });

	return entity;
}