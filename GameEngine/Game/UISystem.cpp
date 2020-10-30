#include "UISystem.h"
#include "GameEngine/TextComponent.h"
#include "ScoreComponent.h"
#include "AmmoComponent.h"
#include "PlayerComponent.h"
#include "HealthComponent.h"

UISystem::UISystem()
{
	m_Listener = std::make_shared<ScoreEventHandler>();
	m_ScoreEventFunctor = std::bind(&UISystem::OnScoreChange , this, std::placeholders::_1);
	m_Listener->AddCallback(m_ScoreEventFunctor);
	EventManager::GetInstance().AddEventListener(m_Listener);
}

UISystem::~UISystem()
{
	EventManager::GetInstance().RemoveEventListener(m_Listener);
	m_Listener->RemoveCallback(m_ScoreEventFunctor);
}

bool UISystem::DoesEntityMatch(std::shared_ptr<Entity> entity)
{
	if (entity->HasComponent<ScoreComponent>())
	{
		std::shared_ptr<ScoreComponent> scoreComp = entity->GetComponent<ScoreComponent>();
		scoreComp->GetScore(m_Score);
		m_Dead = false;
	}

	if (entity->HasComponent<TextComponent>() || entity->HasComponent<PlayerComponent>())
	{
		return true;
	}
	return false;
}

void UISystem::Update(Engine* engine, float dt)
{
	if (m_Entities.size() == 0)
	{
		return;
	}
	std::vector<std::shared_ptr<Entity>> copiedEntities = m_Entities;
	for (std::vector<std::shared_ptr<Entity>>::iterator entityItr = copiedEntities.begin(); entityItr != copiedEntities.end();)
	{
		std::shared_ptr<Entity> entity = *entityItr;
		std::shared_ptr<TextComponent> textComp = entity->GetComponent<TextComponent>();
		std::shared_ptr<PlayerComponent> playerComp = entity->GetComponent<PlayerComponent>();
		std::shared_ptr<ScoreComponent> scoreComp = entity->GetComponent<ScoreComponent>();
		std::shared_ptr<AmmoComponent> ammoComp = entity->GetComponent<AmmoComponent>();
		std::shared_ptr<HealthComponent> healthComp = entity->GetComponent<HealthComponent>();
		if (playerComp != nullptr)
		{
			playerComp->GetAmmo(m_Ammo);
			playerComp->GetHP(m_Health);
		}
		if (ammoComp != nullptr)
		{
			ammoComp->SetAmmo(m_Ammo);
			if (m_Dead)
			{
				textComp->SetText("");
			}
			else
			{
				textComp->SetText("Ammo: " + std::to_string(m_Ammo));
			}
		}
		if (healthComp != nullptr)
		{
			healthComp->SetHealth(m_Health);
			if (m_Dead)
			{
				textComp->SetText("");
			}
			else
			{
				textComp->SetText("HP: " + std::to_string(m_Health));
			}
		}
		if (scoreComp != nullptr)
		{
			scoreComp->SetScore(m_Score);
			if (m_Dead)
			{
				textComp->SetPosition(640 / 5, 480 / 3);
				textComp->SetSize(48);
				textComp->SetText("You are dead");
			}
			else
			{
				textComp->SetText("Score: " + std::to_string(m_Score));
			}
		}
		++entityItr;
	}
}

void UISystem::OnScoreChange(std::shared_ptr<IEvent> event)
{
	std::shared_ptr<ScoreEvent> scoreEvent = std::dynamic_pointer_cast<ScoreEvent>(event);
	std::shared_ptr<DeadEvent> deadEvent = std::dynamic_pointer_cast<DeadEvent>(event);
	if (scoreEvent != nullptr)
	{
		m_Score += scoreEvent->Score;
	}
	if (deadEvent != nullptr)
	{
		m_Dead = true;
	}
}
