#include "EventSystem.h"
#include "..\..\components\preDefinedComponents\CInput.h"

EventSystem::EventSystem()
{
	m_observers.resize((size_t)EventType::EVENT_TYPE_MAX);
}

void EventSystem::subscribe(const EventType& mType, CInput* mInput)
{
	m_observers[(size_t)mType].push_back(mInput);
}

void EventSystem::post(const Event& mEvent) const
{
	auto type = mEvent.type();

	if (m_observers[(size_t)type].size() == 0)
	{
		return;
	}

	auto&& observers = m_observers.at((size_t)type);

	for (auto&& observer : observers)
	{
		observer->react(mEvent);
	}
}