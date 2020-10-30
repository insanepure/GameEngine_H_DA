#pragma once
#include "GameEngine/IComponent.h"

class BulletComponent : public IComponent
{
public:
	BulletComponent();
	~BulletComponent();

public:
	void SetLifeTime(float lifeTime);
	void GetLifeTime(float& lifeTime);

private:
	float m_LifeTime = 0.f;
};