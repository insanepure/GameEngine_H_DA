#pragma once

#include "GameEngine/ISystem.h"
#include "GameEngine/EventManager.h"
#include "ScoreEvent.h"

class UISystem : public ISystem
{
public:
	UISystem();
	~UISystem();
public:
	//ISystem
	virtual bool DoesEntityMatch(std::shared_ptr<Entity> entity) override;
	virtual void Update(Engine* engine, float dt) override;

	void OnScoreChange(std::shared_ptr<IEvent> event);
private:
	std::shared_ptr<ScoreEventHandler> m_Listener;
	EventFunctor m_ScoreEventFunctor;
	int m_Score = 0;
	int m_Health = 0;
	int m_Ammo = 0;
	bool m_Dead = false;
};