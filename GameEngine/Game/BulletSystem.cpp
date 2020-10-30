#include "BulletSystem.h"
#include "BulletComponent.h"
#include "PhysicComponent.h"
#include "ScoreEvent.h"
#include <GameEngine/EventManager.h>
#include <GameEngine/Engine.h>

BulletSystem::BulletSystem()
{

}

BulletSystem::~BulletSystem()
{

}

bool BulletSystem::DoesEntityMatch(std::shared_ptr<Entity> entity)
{
	if (entity->HasComponent<BulletComponent>())
	{
		return true;
	}
	return false;
}

void BulletSystem::Update(Engine* engine, float dt)
{
	if (m_Entities.size() == 0)
	{
		return;
	}
	std::vector<std::shared_ptr<Entity>> copiedEntities = m_Entities;
	for (std::vector<std::shared_ptr<Entity>>::iterator entityItr = copiedEntities.begin(); entityItr != copiedEntities.end();)
	{
		std::shared_ptr<Entity> entity = *entityItr;
		if (!UpdateSingleEntity(engine, entity, dt))
		{
			engine->RemoveEntity(entity);
		}
		++entityItr;
	}
}

bool BulletSystem::UpdateSingleEntity(Engine* engine, std::shared_ptr<Entity> entity, float dt)
{
	std::shared_ptr<BulletComponent> bulletComp = entity->GetComponent<BulletComponent>();
	std::shared_ptr<PhysicComponent> physicComp = entity->GetComponent<PhysicComponent>();

	float Vel_X = 0.f;
	float Vel_Y = 0.f;
	physicComp->GetVelocity(Vel_X, Vel_Y);
	//decrease lifetime, if it's 0, return false
	float lifeTime = 0.f;
	bulletComp->GetLifeTime(lifeTime);
	lifeTime -= dt;
	if (lifeTime < 0.0f || Vel_X == 0 && Vel_Y == 0)
	{
		return false;
	}

	bulletComp->SetLifeTime(lifeTime);
	std::vector<std::shared_ptr<Entity>> collisions;
	physicComp->GetCollisions(collisions);
	if (collisions.size() == 0)
	{
		return true;
	}

	//throw a score event
	std::shared_ptr<ScoreEvent> event = std::make_shared<ScoreEvent>();
	event->Score = 10;
	EventManager::GetInstance().PushEvent(event);
	return false;
	
}

