#pragma once
#include <vector>
#include <functional>
#include "Event.h"
#include "..\..\components\Entity.h"
#include "PreDefinedEvents.h"

struct CInput;

class EventSystem
{
public:
	EventSystem();

	void subscribe(const EventType& mType, CInput* mInput);

	void post(const Event& mEvent) const;

private:
	std::vector<std::vector<CInput*>> m_observers;
};