#pragma once

#include "GameEngine/ISystem.h"

class BulletSystem : public ISystem
{
public:
	BulletSystem();
	~BulletSystem();
public:
	//ISystem
	virtual bool DoesEntityMatch(std::shared_ptr<Entity> entity) override;
	virtual void Update(Engine* engine, float dt) override;

private:
	bool UpdateSingleEntity(Engine* engine, std::shared_ptr<Entity> entity, float dt);
};