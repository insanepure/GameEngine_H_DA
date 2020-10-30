#include "PlayerComponent.h"

PlayerComponent::PlayerComponent()
{

}

PlayerComponent::~PlayerComponent()
{

}

void PlayerComponent::GetSpeedPerSecond(float& speedPerSecond)
{
	speedPerSecond = m_SpeedPerSecond;
}

void PlayerComponent::SetSpeedPerSecond(float speedPerSecond)
{
	m_SpeedPerSecond = speedPerSecond;
}

void PlayerComponent::GetBulletSpeedPerSecond(float& bulletSpeedPerSecond)
{
	bulletSpeedPerSecond = m_BulletSpeedPerSecond;
}

void PlayerComponent::SetBulletSpeedPerSecond(float bulletSpeedPerSecond)
{
	m_BulletSpeedPerSecond = bulletSpeedPerSecond;
}

void PlayerComponent::GetBulletSpawnCooldown(float& spawnCD)
{
	spawnCD = m_CurrentBulletSpawnCD;
}

void PlayerComponent::SetBulletSpawnCooldown(float spawnCD)
{
	m_CurrentBulletSpawnCD = spawnCD;
}

void PlayerComponent::GetMaxBulletSpawnCooldown(float& spawnCD)
{
	spawnCD = m_MaxBulletSpawnCD;
}

void PlayerComponent::SetMaxBulletSpawnCooldown(float spawnCD)
{
	m_MaxBulletSpawnCD = spawnCD;
}

void PlayerComponent::GetHP(int& hp)
{
	hp = m_HP;
}

void PlayerComponent::SetHP(int hp)
{
	m_HP = hp;
}

void PlayerComponent::GetAmmo(int& ammo)
{
	ammo = m_Ammo;
}

void PlayerComponent::SetAmmo(int ammo)
{
	m_Ammo = ammo;
}

void PlayerComponent::GetHitCooldown(float& hitCooldown)
{
	hitCooldown = m_HitCooldown;
}

void PlayerComponent::SetHitCooldown(float hitCooldown)
{
	m_HitCooldown = hitCooldown;
}

