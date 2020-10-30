#pragma once
#include "GameEngine/IComponent.h"

class ScoreComponent : public IComponent
{
public:
	ScoreComponent();
	~ScoreComponent();

public:
	void GetScore(int& score);
	void SetScore(int score);

private:
	int m_Score = 0;
};