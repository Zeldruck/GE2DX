#include <A4Engine/CollisionLayersManager.hpp>
#include <stdexcept>

CollisionLayersManager::CollisionLayersManager()
{
	if (s_instance != nullptr)
		throw std::runtime_error("only one CollisionLayersManager can be created\n");

	s_instance = this;

	m_layersCount = 0;
}

CollisionLayersManager::~CollisionLayersManager()
{
	s_instance = nullptr;
}

void CollisionLayersManager::AddCollisionLayer(const std::string& _LAYER_NAME)
{
	m_collisionLayers[_LAYER_NAME] = cpCollisionType(m_layersCount);
	m_layersCount++;
}

bool CollisionLayersManager::Exist(const std::string& _LAYER_NAME)
{
	return (m_collisionLayers.find(_LAYER_NAME) != m_collisionLayers.end());
}

cpCollisionType& CollisionLayersManager::GetCollisionLayer(const std::string& _LAYER_NAME)
{
	return m_collisionLayers.find(_LAYER_NAME)->second;
}

cpCollisionType& CollisionLayersManager::Get(const std::string& _LAYER_NAME)
{
	if (m_collisionLayers.find(_LAYER_NAME) == m_collisionLayers.end())
	{
		printf("Collision layer does not exist, creating it right away..., (%s)\n", _LAYER_NAME.c_str());
		AddCollisionLayer(_LAYER_NAME);
	}

	return GetCollisionLayer(_LAYER_NAME);
}

CollisionLayersManager& CollisionLayersManager::Instance()
{
	if (!s_instance)
		throw std::runtime_error("CollisionLayersManager hasn't been instantied");

	return *s_instance;
}

CollisionLayersManager* CollisionLayersManager::s_instance = nullptr;