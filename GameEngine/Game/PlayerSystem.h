#pragma once

#include "GameEngine/ISystem.h"

class PlayerSystem : public ISystem
{
public:
	PlayerSystem();
	~PlayerSystem();
public:
	//ISystem
	virtual bool DoesEntityMatch(std::shared_ptr<Entity> entity) override;
	virtual void Update(Engine* engine, float dt) override;
private:
	bool inline UpdateSingleEntity(Engine* engine, std::shared_ptr<Entity> entity, float dt);

private:
	float m_Camera_X = 0.f;
	float m_Camera_Y = 0.f;
};