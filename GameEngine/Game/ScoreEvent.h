#pragma once
#include "GameEngine/EventManager.h"

class DeadEvent : public IEvent
{
};

class ScoreEvent : public IEvent
{
public:
	int Score = 0;
};

class ScoreEventHandler : public IEventHandler
{
public:
	bool DoesEventMatch(std::shared_ptr<IEvent> event)
	{
		if (std::dynamic_pointer_cast<ScoreEvent>(event) != nullptr
			|| std::dynamic_pointer_cast<DeadEvent>(event) != nullptr)
		{
			return true;
		}
		return false;
	}
};