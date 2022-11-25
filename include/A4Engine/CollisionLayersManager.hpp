#pragma once

#pragma once

#include <A4Engine/Export.hpp>
#include <chipmunk/chipmunk.h>
#include <unordered_map>
#include <string>

class A4ENGINE_API CollisionLayersManager
{
	public:
		CollisionLayersManager();
		CollisionLayersManager(const CollisionLayersManager&) = delete;
		CollisionLayersManager(CollisionLayersManager&&) = delete;
		~CollisionLayersManager();

		void AddCollisionLayer(const std::string& _LAYER_NAME);

		bool Exist(const std::string& _LAYER_NAME);

		cpCollisionType& GetCollisionLayer(const std::string& _LAYER_NAME);
		cpCollisionType& Get(const std::string& _LAYER_NAME);

		CollisionLayersManager& operator=(const CollisionLayersManager&) = delete;
		CollisionLayersManager& operator=(CollisionLayersManager&&) = delete;

		static CollisionLayersManager& Instance();

	private:
		std::unordered_map<std::string, cpCollisionType> m_collisionLayers;
		int m_layersCount;

		static CollisionLayersManager* s_instance;
};
