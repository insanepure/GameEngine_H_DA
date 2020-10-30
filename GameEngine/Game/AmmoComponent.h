#pragma once
#include "GameEngine/IComponent.h"

class AmmoComponent : public IComponent
{
public:
	AmmoComponent();
	~AmmoComponent();

public:
	void GetAmmo(int& ammo);
	void SetAmmo(int ammo);

private:
	int m_Ammo = 0;
};