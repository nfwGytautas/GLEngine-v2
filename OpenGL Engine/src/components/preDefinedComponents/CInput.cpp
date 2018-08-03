#include "CInput.h"
#include "..\..\Engine.h"
#include "..\Entity.h"
#include "..\..\systems\event\EventSystem.h"

CInput::CInput()
{}

void CInput::init()
{
	entity->addGroup(EntityGroups::HasInput);
}

void CInput::subscribe(const EventType& mType, EventBehavior& mBehavior)
{
	Engine::Systems::Event::subscribe(mType, this);
	m_reactions[mType] = mBehavior;
}

void CInput::react(const Event& mEvent)
{
	if (m_reactions.find(mEvent.type()) != m_reactions.end())
	{
		m_reactions[mEvent.type()](*entity, mEvent);
	}
}
