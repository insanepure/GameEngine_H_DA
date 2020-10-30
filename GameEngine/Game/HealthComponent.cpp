#include "HealthComponent.h"

HealthComponent::HealthComponent()
{

}

HealthComponent::~HealthComponent()
{

}

void HealthComponent::GetHealth(int& health)
{
	health = m_Health;
}

void HealthComponent::SetHealth(int health)
{
	m_Health = health;
}
