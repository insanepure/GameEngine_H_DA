#include "PhysicComponent.h"

PhysicComponent::PhysicComponent()
{

}

PhysicComponent::~PhysicComponent()
{

}

void PhysicComponent::SetVelocity(const float X, const float Y)
{
	m_Velocity_X = X;
	m_Velocity_Y = Y;
}

void PhysicComponent::GetVelocity(float& X, float& Y)
{
	X = m_Velocity_X;
	Y = m_Velocity_Y;
}

void PhysicComponent::SetDamping(const float damping)
{
	m_Damping = damping;
}

void PhysicComponent::GetDamping(float& damping)
{
	damping = m_Damping;
}

void PhysicComponent::SetCollisions(std::vector<std::shared_ptr<Entity>>& collisions)
{
	m_Collisions = collisions;
}

void PhysicComponent::GetCollisions(std::vector<std::shared_ptr<Entity>>& collisions)
{
	collisions = m_Collisions;
}

void PhysicComponent::SetCollisionFlag(int flag)
{
	m_CollisionFlag = flag;
}

void PhysicComponent::SetTargetFlag(int flag)
{
	m_TargetFlag = flag;
}

bool PhysicComponent::CanCollide(const std::shared_ptr<PhysicComponent> otherComp)
{
	return m_TargetFlag & otherComp->m_CollisionFlag;
}
