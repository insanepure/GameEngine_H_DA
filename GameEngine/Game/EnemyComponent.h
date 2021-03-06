#pragma once
#include "GameEngine/IComponent.h"

class EnemyComponent : public IComponent
{
public:
	EnemyComponent();
	~EnemyComponent();

public:
	void GetSpeedPerSecond(float& speedPerSecond);
	void SetSpeedPerSecond(float speedPerSecond);

	void GetHP(int& hp);
	void SetHP(int hp);

private:
	float m_SpeedPerSecond = 0.f;
	int m_HP = 0;
};