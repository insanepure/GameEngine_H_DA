#include "AmmoComponent.h"

AmmoComponent::AmmoComponent()
{

}

AmmoComponent::~AmmoComponent()
{

}

void AmmoComponent::GetAmmo(int& ammo)
{
	ammo = m_Ammo;
}

void AmmoComponent::SetAmmo(int ammo)
{
	m_Ammo = ammo;
}
