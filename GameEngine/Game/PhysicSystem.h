#pragma once
#include <vector>
#include <algorithm>
#include <memory>
#include "GameEngine/ISystem.h"

class PhysicSystem : public ISystem
{
public:
	PhysicSystem();
	~PhysicSystem();
	//ISystem
	virtual bool DoesEntityMatch(std::shared_ptr<Entity> entity) override;
	virtual void Update(Engine* engine, float dt) override;

private:
	void inline UpdateSingleEntityPosition(std::shared_ptr<Entity> entity, float dt);
	void inline UpdateSingleEntityCollision(std::shared_ptr<Entity> entity, float dt);
private:
	std::shared_ptr<Entity> m_LevelEntity = nullptr;
};