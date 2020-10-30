#include "PlayerSystem.h"
#include "PlayerComponent.h"
#include <GameEngine/SpriteComponent.h>
#include <GameEngine/Engine.h>
#include <GameEngine/EventManager.h>
#include "PhysicComponent.h"
#include "BulletComponent.h"
#include "EnemyComponent.h"
#include "ItemComponent.h"
#include "CollisionFlags.h"
#include "ScoreEvent.h"

PlayerSystem::PlayerSystem()
{

}

PlayerSystem::~PlayerSystem()
{

}

bool PlayerSystem::DoesEntityMatch(std::shared_ptr<Entity> entity)
{
	if (entity->HasComponent<PlayerComponent>())
	{
		return true;
	}
	return false;
}

void PlayerSystem::Update(Engine* engine, float dt)
{
	std::vector<std::shared_ptr<Entity>> copiedEntities = m_Entities;
	for (std::vector<std::shared_ptr<Entity>>::iterator entityItr = copiedEntities.begin(); entityItr != copiedEntities.end();)
	{
		std::shared_ptr<Entity> entity = *entityItr;
		if (!UpdateSingleEntity(engine, entity, dt))
		{
			engine->RemoveEntity(entity);

			//throw a dead event
			std::shared_ptr<DeadEvent> event = std::make_shared<DeadEvent>();
			EventManager::GetInstance().PushEvent(event);
		}
		++entityItr;
	}
	engine->SetViewCenter(m_Camera_X, m_Camera_Y);
}

bool PlayerSystem::UpdateSingleEntity(Engine* engine, std::shared_ptr<Entity> entity, float dt)
{
	std::shared_ptr<PhysicComponent> physicComp = entity->GetComponent<PhysicComponent>();
	std::shared_ptr<SpriteComponent> spriteComp = entity->GetComponent<SpriteComponent>();
	std::shared_ptr<PlayerComponent> playerComp = entity->GetComponent<PlayerComponent>();
	float rotationInDegree = 0.f;
	float Vel_X = 0.f;
	float Vel_Y = 0.f;
	float speedPerSecond = 0.f;
	float player_X = 0.f;
	float player_Y = 0.f;
	float bulletSpawnCD = 0.f;
	float bulletMaxSpawnCD = 0.f;
	int ammo = 0;
	int hp = 0;
	float hitCooldown = 0.f;
	spriteComp->GetRotation(rotationInDegree);
	spriteComp->GetPosition(player_X, player_Y);
	physicComp->GetVelocity(Vel_X, Vel_Y);
	playerComp->GetSpeedPerSecond(speedPerSecond);
	playerComp->GetBulletSpawnCooldown(bulletSpawnCD);
	playerComp->GetMaxBulletSpawnCooldown(bulletMaxSpawnCD);
	playerComp->GetAmmo(ammo);
	playerComp->GetHP(hp);
	playerComp->GetHitCooldown(hitCooldown);

	m_Camera_X = player_X;
	m_Camera_Y = player_Y;

	const float PI = 3.141592654f;

	float cursorX, cursorY = 0.f;
	engine->GetCursorPosition(cursorX, cursorY);
	float rotation = std::atan2(cursorY - player_Y, cursorX - player_X);
	rotationInDegree = rotation / PI * 180.0f;
	

	spriteComp->SetRotation(rotationInDegree);

	if (engine->IsKeyPressed(Key::S))
	{
		Vel_Y = speedPerSecond;
	}
	else if (engine->IsKeyPressed(Key::W))
	{
		Vel_Y = -speedPerSecond;
	}

	if (engine->IsKeyPressed(Key::D))
	{
		Vel_X = speedPerSecond;
	}
	else if (engine->IsKeyPressed(Key::A))
	{
		Vel_X = -speedPerSecond;
	}

	physicComp->SetVelocity(Vel_X, Vel_Y);

	if (engine->IsMousePressed(MouseButton::MouseLeft) && bulletSpawnCD <= 0.f && ammo > 0)
	{
		bulletSpawnCD = bulletMaxSpawnCD;

		const float bulletSpeedPerSecond = 600.0f;
		float shootRotation = (rotationInDegree + 90.0f) * PI / 180.0f;
		float bulletVelocity_X = sin(shootRotation) * bulletSpeedPerSecond;
		float bulletVelocity_Y = -cos(shootRotation) * bulletSpeedPerSecond;
		std::shared_ptr<Entity> bulletEntity = std::make_shared<Entity>();
		std::shared_ptr<SpriteComponent> bulletSprite = bulletEntity->AddComponent<SpriteComponent>();
		std::shared_ptr<PhysicComponent> bulletPhysics = bulletEntity->AddComponent<PhysicComponent>();
		std::shared_ptr<BulletComponent> bulletComp = bulletEntity->AddComponent<BulletComponent>();

		bulletSprite->CreateSprite("levels/graphics/bullet.png");
		bulletSprite->SetPosition(player_X, player_Y);
		bulletPhysics->SetVelocity(bulletVelocity_X, bulletVelocity_Y);
		bulletPhysics->SetDamping(1.0f);
		bulletPhysics->SetTargetFlag(EnemyCollisionFlag);
		bulletPhysics->SetCollisionFlag(BulletCollisionFlag);
		bulletComp->SetLifeTime(10.0f);
		engine->AddEntity(bulletEntity);
		ammo--;
		playerComp->SetAmmo(ammo);
	}
	else if (bulletSpawnCD > 0.f)
	{
		bulletSpawnCD -= dt;
	}
	playerComp->SetBulletSpawnCooldown(bulletSpawnCD);

	std::vector<std::shared_ptr<Entity>> collisions;
	physicComp->GetCollisions(collisions);
	if (hitCooldown > 0)
	{
		hitCooldown -= dt;
	}
	if (hitCooldown < 0)
	{
		hitCooldown = 0;
	}
	playerComp->SetHitCooldown(hitCooldown);
	int flashCD = (int)std::round(hitCooldown * 20) % 2;
	spriteComp->SetVisible(flashCD == 0);
	if (collisions.size() == 0)
	{
		return true;
	}

	for (std::shared_ptr<Entity>& collision : collisions)
	{
		std::shared_ptr<EnemyComponent> enemyComp = collision->GetComponent<EnemyComponent>();
		std::shared_ptr<ItemComponent> itemComp = collision->GetComponent<ItemComponent>();
		if (enemyComp != nullptr && hitCooldown <= 0)
		{
			hp--;
			if (hp == 0)
			{
				return false;
			}
			playerComp->SetHP(hp);
			playerComp->SetHitCooldown(1.0f);
			continue;
		}
		else if (itemComp != nullptr)
		{
			int itemAmmo = 0;
			int itemHP = 0;
			itemComp->GetAmmo(itemAmmo);
			itemComp->GetHP(itemHP);
			ammo += itemAmmo;
			hp += itemHP;
			playerComp->SetHP(hp);
			playerComp->SetAmmo(ammo);
			engine->RemoveEntity(collision);
		}
	}

	return true;
}
