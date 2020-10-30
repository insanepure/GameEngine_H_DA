#pragma once
#include "GameEngine/IComponent.h"

class PlayerComponent : public IComponent
{
public:
	PlayerComponent();
	~PlayerComponent();

public:
	void GetSpeedPerSecond(float& speedPerSecond);
	void SetSpeedPerSecond(float speedPerSecond);

	void GetBulletSpeedPerSecond(float& bulletSpeedPerSecond);
	void SetBulletSpeedPerSecond(float bulletSpeedPerSecond);

	void GetBulletSpawnCooldown(float& spawnCD);
	void SetBulletSpawnCooldown(float spawnCD);

	void GetMaxBulletSpawnCooldown(float& spawnCD);
	void SetMaxBulletSpawnCooldown(float spawnCD);

	void GetHP(int& hp);
	void SetHP(int hp);

	void GetAmmo(int& ammo);
	void SetAmmo(int ammo);

	void GetHitCooldown(float& hitCooldown);
	void SetHitCooldown(float hitCooldown);

private:
	float m_SpeedPerSecond = 0.f;
	float m_BulletSpeedPerSecond = 0.f;
	float m_CurrentBulletSpawnCD = 0.f;
	float m_MaxBulletSpawnCD = 0.f;
	int m_HP = 0;
	int m_Ammo = 0;
	float m_HitCooldown = 0;
};