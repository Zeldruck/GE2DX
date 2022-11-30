#ifndef _COLLISIONHANDLERMANAGER_HPP_
#define _COLLISIONHANDLERMANAGER_HPP_

#include <A4Engine/Export.hpp>
#include <chipmunk/chipmunk.h>
#include <unordered_map>
#include <memory>
#include <string>

class ChipmunkSpace;

class A4ENGINE_API CollisionHandlerManager
{
	public:
		CollisionHandlerManager();
		CollisionHandlerManager(const CollisionHandlerManager&) = delete;
		CollisionHandlerManager(CollisionHandlerManager&&) = delete;
		~CollisionHandlerManager();

		void AddCollisionHandler(const std::string& _collisionHandlerName, ChipmunkSpace& _space, const std::string& _LAYER_NAME_A, const std::string& _LAYER_NAME_B);
		void SetHandlerPostSolveFunc(const std::string& _collisionHandlerName, cpCollisionPostSolveFunc _postSolveFunction);

		CollisionHandlerManager& operator=(const CollisionHandlerManager&) = delete;
		CollisionHandlerManager& operator=(CollisionHandlerManager&&) = delete;

		static CollisionHandlerManager& Instance();

	private:
		std::unordered_map<std::string, std::shared_ptr<cpCollisionHandler>> m_collisionHandler;

		static CollisionHandlerManager* s_instance;
};

#endif // !_COLLISIONHANDLERMANAGER_HPP_