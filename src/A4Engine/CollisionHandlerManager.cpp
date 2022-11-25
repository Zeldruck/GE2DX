#include <A4Engine/CollisionHandlerManager.hpp>
#include <A4Engine/ChipmunkSpace.hpp>
#include <A4Engine/CollisionLayersManager.hpp>
#include <stdexcept>

CollisionHandlerManager::CollisionHandlerManager()
{
	if (s_instance != nullptr)
		throw std::runtime_error("only one CollisionHandlerManager can be created");

	s_instance = this;
	/*
	
	collisionHandlerBirdWall->postSolveFunc = cpCollisionPostSolveFunc(BirdDeath);
	*/
}

CollisionHandlerManager::~CollisionHandlerManager()
{
	s_instance = nullptr;
}

void CollisionHandlerManager::AddCollisionHandler(const std::string& _collisionHandlerName, ChipmunkSpace& _space, const std::string& _LAYER_NAME_A, const std::string& _LAYER_NAME_B)
{
	cpCollisionHandler* collisionHandler = cpSpaceAddCollisionHandler(
		_space.GetHandle(),
		CollisionLayersManager::Instance().Get(_LAYER_NAME_A),
		CollisionLayersManager::Instance().Get(_LAYER_NAME_B));

	m_collisionHandler[_collisionHandlerName] = std::make_shared<cpCollisionHandler>(*collisionHandler);
}

void CollisionHandlerManager::SetHandlerPostSolveFunc(const std::string& _collisionHandlerName, cpCollisionPostSolveFunc _postSolveFunction)
{
	auto it = m_collisionHandler.find(_collisionHandlerName);

	if (it == m_collisionHandler.end())
		return;

	it->second->postSolveFunc = _postSolveFunction;
}

CollisionHandlerManager& CollisionHandlerManager::Instance()
{
	if (!s_instance)
		throw std::runtime_error("CollisionHandlerManager hasn't been instantied");

	return *s_instance;
}

CollisionHandlerManager* CollisionHandlerManager::s_instance = nullptr;