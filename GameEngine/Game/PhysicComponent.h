#pragma once
#include "GameEngine/IComponent.h"
#include <vector>
#include <memory>

class Entity;

class PhysicComponent : public IComponent
{
public:
	PhysicComponent();
	~PhysicComponent();
public:
	void SetVelocity(const float X, const float Y);
	void GetVelocity(float& X, float& Y);
	void SetDamping(const float damping);
	void GetDamping(float& damping);
	void SetCollisions(std::vector<std::shared_ptr<Entity>>& collisions);
	void GetCollisions(std::vector<std::shared_ptr<Entity>>& collisions);

	void SetCollisionFlag(int flag);
	void SetTargetFlag(int flag);

	bool CanCollide(const std::shared_ptr<PhysicComponent> otherComp);
private:
	float m_Velocity_X = 0.f;
	float m_Velocity_Y = 0.f;

	float m_Damping = 0.f;

	int m_CollisionFlag = 0;
	int m_TargetFlag = 0;

	std::vector<std::shared_ptr<Entity>> m_Collisions;
};