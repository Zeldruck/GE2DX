#ifndef _PIPESMANAGER_HPP_
#define _PIPESMANAGER_HPP_

#include <A4Engine/CollisionShape.hpp>
#include <entt/entt.hpp>
#include <chipmunk/chipmunk.h>
#include <vector>
#include <memory>

struct PipePoolData
{
	std::shared_ptr<entt::entity> entity;
	std::shared_ptr<CollisionShape> shape;
	Vector2f position;
	float speed;
};

class PipesManager
{
	public:
		PipesManager(entt::registry& _registry);
		PipesManager(const PipesManager&) = delete;
		PipesManager(PipesManager&&) = delete;
		~PipesManager();

		entt::entity CreatePipe(Vector2f _position, float _speed);

		void AddPipe(entt::entity& _pipeEntity);
		void EreaseFirstTwoPipes();

		void Update();

		PipesManager& operator=(const PipesManager&) = delete;
		PipesManager& operator=(PipesManager&&) = delete;

		static PipesManager& Instance();

	private:
		void FreePipes();
		void CnstructPipes();


	private:
		entt::registry& registry;

		std::vector<entt::entity> pipesEntities;

		std::vector<entt::entity> pipesEntitiesToFree;
		std::vector<PipePoolData> pipeEntitiesToConstruct;

		static PipesManager* s_instance;
};

#endif // !_PIPESMANAGER_HPP_