#include "PhysicSystem.h"
#include "GameEngine/SpriteComponent.h"
#include "GameEngine/LevelComponent.h"
#include "PhysicComponent.h"

PhysicSystem::PhysicSystem()
{

}

PhysicSystem::~PhysicSystem()
{

}

bool PhysicSystem::DoesEntityMatch(std::shared_ptr<Entity> entity)
{
	if (entity->HasComponent<LevelComponent>())
	{
		m_LevelEntity = entity;
		return false;
	}
	if (entity->HasComponent<SpriteComponent>() && entity->HasComponent<PhysicComponent>())
	{
		return true;
	}
	return false;
}

void PhysicSystem::Update(Engine* engine, float dt)
{
	std::vector<std::shared_ptr<Entity>> copiedEntities = m_Entities;
	for (std::vector<std::shared_ptr<Entity>>::iterator entityItr = copiedEntities.begin(); entityItr != copiedEntities.end();)
	{
		std::shared_ptr<Entity> entity = *entityItr;
		UpdateSingleEntityPosition(entity, dt);
		++entityItr;
	}
	for (std::vector<std::shared_ptr<Entity>>::iterator entityItr = copiedEntities.begin(); entityItr != copiedEntities.end();)
	{
		std::shared_ptr<Entity> entity = *entityItr;
		UpdateSingleEntityCollision(entity, dt);
		++entityItr;
	}
}

void PhysicSystem::UpdateSingleEntityPosition(std::shared_ptr<Entity> entity, float dt)
{
	std::shared_ptr<PhysicComponent> physicComp = entity->GetComponent<PhysicComponent>();
	std::shared_ptr<SpriteComponent> spriteComp = entity->GetComponent<SpriteComponent>();
	float X = 0.f;
	float Y = 0.f;
	float Vel_X = 0.f;
	float Vel_Y = 0.f;
	float damping = 0.f;
	unsigned int width = 0;
	unsigned int height = 0;
	spriteComp->GetPosition(X, Y);
	spriteComp->GetSize(width, height);
	physicComp->GetVelocity(Vel_X, Vel_Y);
	physicComp->GetDamping(damping);
	Vel_X *= damping;
	Vel_Y *= damping;
	if (Vel_X < 0.1f && Vel_X > -0.1f)
	{
		Vel_X = 0.f;
	}
	if (Vel_Y < 0.1f && Vel_Y > -0.1f)
	{
		Vel_Y = 0.f;
	}
	physicComp->SetVelocity(Vel_X, Vel_Y);

	if (Vel_X == 0.f && Vel_Y == 0.f)
	{
		return;
	}

	std::shared_ptr<LevelComponent> levelComp = m_LevelEntity->GetComponent<LevelComponent>();

	int newX = X + (Vel_X * dt);
	int newY = Y + (Vel_Y * dt);

	if (levelComp->IsWalkable(newX, newY, width, height))
	{
		spriteComp->SetPosition(newX, newY);
	}
	else
	{
		physicComp->SetVelocity(0, 0);
	}
}
void PhysicSystem::UpdateSingleEntityCollision(std::shared_ptr<Entity> entity, float dt)
{
	std::shared_ptr<PhysicComponent> physicComp = entity->GetComponent<PhysicComponent>();
	std::shared_ptr<SpriteComponent> spriteComp = entity->GetComponent<SpriteComponent>();
	float X = 0.f;
	float Y = 0.f;
	spriteComp->GetPosition(X, Y);

	std::vector<std::shared_ptr<Entity>> collisions;
	std::vector<std::shared_ptr<Entity>>& copiedEntities = m_Entities;
	for (std::vector<std::shared_ptr<Entity>>::iterator otherEntityItr = copiedEntities.begin(); otherEntityItr != copiedEntities.end();)
	{
		std::shared_ptr<Entity> otherEntity = (*otherEntityItr);

		if (entity == otherEntity)
		{
			++otherEntityItr;
			continue;
		}
		std::shared_ptr<PhysicComponent> otherPhysicComp = otherEntity->GetComponent<PhysicComponent>();
		std::shared_ptr<SpriteComponent> otherSpriteComp = otherEntity->GetComponent<SpriteComponent>();
		if (physicComp->CanCollide(otherPhysicComp) && (spriteComp->IsCollidingWith(otherSpriteComp)))
		{
			collisions.push_back(otherEntity);
		}
		++otherEntityItr;
	}

	physicComp->SetCollisions(collisions);
}