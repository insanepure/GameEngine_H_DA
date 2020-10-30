#pragma once
#include "GameEngine/IComponent.h"

class HealthComponent : public IComponent
{
public:
	HealthComponent();
	~HealthComponent();

public:
	void GetHealth(int& health);
	void SetHealth(int health);

private:
	int m_Health = 0;
};