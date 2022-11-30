#include <A4Game/PipesManager.hpp>
#include <A4Engine/Sprite.hpp>
#include <A4Engine/ResourceManager.hpp>
#include <A4Engine/GraphicsComponent.hpp>
#include <A4Engine/RigidBodyComponent.hpp>
#include <A4Engine/Transform.hpp>
#include <stdexcept>
#include <cstdlib>

PipesManager::PipesManager(entt::registry& _registry) :
	registry(_registry)
{
	if (s_instance != nullptr)
		throw std::runtime_error("only one PipesManager can be created");

	s_instance = this;
}

PipesManager::~PipesManager()
{
	s_instance = nullptr;
}

entt::entity PipesManager::CreatePipe(Vector2f _position, float _speed, const std::string& _collisionLayer = "")
{
	std::shared_ptr<Sprite> box = std::make_shared<Sprite>(ResourceManager::Instance().GetTexture("assets/box.png"));
	box->SetOrigin({ 0.5f, 0.5f });
	box->Resize(box->GetWidth(), 384);

	std::shared_ptr<CollisionShape> boxShape = std::make_shared<BoxShape>(box->GetWidth(), box->GetHeight());
	if (!_collisionLayer.empty())
		boxShape->SetCollisionLayer(_collisionLayer);

	entt::entity entity = registry.create();
	registry.emplace<GraphicsComponent>(entity, std::move(box));
	registry.emplace<Transform>(entity);

	pipeEntitiesToConstruct.push_back(PipePoolData{ std::make_shared<entt::entity>(entity), boxShape, _position, _speed });

	return entity;
}

void PipesManager::CreatePipes(float _xPosition, float _speed)
{
	float yPercentage = (rand() % 51 - 25) / 100.f;

	printf("Y Percentage: %f\n", yPercentage);

	CreatePipe(Vector2f{ _xPosition, yPercentage * 720.f }, _speed, "PIPE");
	CreatePipe(Vector2f{ _xPosition, (1.f + yPercentage) * 720.f }, _speed, "DEATH");
}

void PipesManager::AddPipe(entt::entity& _pipeEntity)
{
	pipesEntities.push_back(_pipeEntity);
}

void PipesManager::EreaseFirstTwoPipes()
{
	if (pipesEntities.size() < 2)
		return;

	auto firstPipe = pipesEntities.front();
	registry.get<RigidBodyComponent>(firstPipe).SetAllCollisionsLayer("DEFAULT");
	pipesEntities.erase(pipesEntities.begin());
	pipesEntitiesToFree.push_back(firstPipe);

	auto secondPipe = pipesEntities.front();
	registry.get<RigidBodyComponent>(secondPipe).SetAllCollisionsLayer("DEFAULT");
	pipesEntities.erase(pipesEntities.begin());
	pipesEntitiesToFree.push_back(secondPipe);
}

void PipesManager::FreePipes()
{
	while (pipesEntitiesToFree.size() > 0)
	{
		auto pipeToFree = pipesEntitiesToFree.front();
		pipesEntitiesToFree.erase(pipesEntitiesToFree.begin());
		registry.destroy(pipeToFree);
	}
}

void PipesManager::Update()
{
	FreePipes();
	CnstructPipes();
}

void PipesManager::CnstructPipes()
{
	while (pipeEntitiesToConstruct.size() > 0)
	{
		auto pipeData = pipeEntitiesToConstruct.front();

		auto& entityPhysics = registry.emplace<RigidBodyComponent>(*pipeData.entity.get(), RigidBodyComponent::Kinematic{});
		entityPhysics.AddShape(std::move(pipeData.shape));
		entityPhysics.TeleportTo(pipeData.position);
		entityPhysics.SetLinearVelocity({ -pipeData.speed, 0.f });

		AddPipe(*pipeData.entity.get());

		pipeEntitiesToConstruct.erase(pipeEntitiesToConstruct.begin());
	}
}

PipesManager& PipesManager::Instance()
{
	if (!s_instance)
		throw std::runtime_error("PipesManager hasn't been instantied");

	return *s_instance;
}

PipesManager* PipesManager::s_instance = nullptr;