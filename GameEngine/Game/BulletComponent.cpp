#include "BulletComponent.h"

BulletComponent::BulletComponent()
{

}

BulletComponent::~BulletComponent()
{

}

void BulletComponent::SetLifeTime(float lifeTime)
{
	m_LifeTime = lifeTime;
}

void BulletComponent::GetLifeTime(float& lifeTime)
{
	lifeTime = m_LifeTime;
}
