#include "ScoreComponent.h"

ScoreComponent::ScoreComponent()
{

}

ScoreComponent::~ScoreComponent()
{

}

void ScoreComponent::GetScore(int& score)
{
	score = m_Score;
}

void ScoreComponent::SetScore(int score)
{
	m_Score = score;
}
