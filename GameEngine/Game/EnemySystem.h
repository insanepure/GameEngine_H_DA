#pragma once

#include "GameEngine/ISystem.h"

class EnemySystem : public ISystem
{
public:
	EnemySystem();
	~EnemySystem();
public:
	//ISystem
	virtual bool DoesEntityMatch(std::shared_ptr<Entity> entity) override;
	virtual void Update(Engine* engine, float dt) override;
private:
	bool inline UpdateSingleEntity(Engine* engine, std::shared_ptr<Entity> entity, float dt);

private:
	std::weak_ptr<Entity> m_PlayerEntity;
};