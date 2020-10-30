#include "TransformComponent.h"

TransformComponent::TransformComponent()
{
	m_X = 0.0f;
	m_Y = 0.0f;
	m_RotationInDegree = 0.0f;
}

TransformComponent::~TransformComponent()
{

}

void TransformComponent::SetPosition(const float X, const float Y)
{
	m_X = X;
	m_Y = Y;
}

void TransformComponent::SetRotation(const float Rotation)
{
	m_RotationInDegree = Rotation;
}

void TransformComponent::GetPosition(float& X, float& Y)
{
	X = m_X;
	Y = m_Y;
}

void TransformComponent::GetRotation(float& RotationInDegree)
{
	RotationInDegree = m_RotationInDegree;
}
