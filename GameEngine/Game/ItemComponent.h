#pragma once
#include "GameEngine/IComponent.h"

class ItemComponent : public IComponent
{
public:
	ItemComponent()
	{
	}

	~ItemComponent()
	{
	}

public:
	void GetAmmo(int& ammo) { ammo = m_Ammo; };
	void SetAmmo(int ammo) { m_Ammo = ammo; };

	void GetHP(int& hp) { hp = m_HP; };
	void SetHP(int hp) { m_HP = hp; };

private:
	int m_Ammo = 0;
	int m_HP = 0;
};