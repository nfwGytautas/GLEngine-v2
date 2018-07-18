#include "CInput.h"
#include "..\Entity.h"

#include <iostream>

CInput::CInput()
	: enabled(true), m_hasMouseBehavior(false)
{
}

void CInput::init()
{
	entity->addGroup(EntityGroups::HasInput);
}

void CInput::react(const std::vector<Key>& mKeys)
{
	if(enabled)
	{
		for(unsigned int i = 0; i < mKeys.size(); i++)
		{
			if (m_behaviors.find(mKeys[i]) != m_behaviors.end())
			{
				m_behaviors[mKeys[i]](*entity);
			}
		}
	}
}

void CInput::reactToMouse()
{
	if(m_hasMouseBehavior)
	{
		m_mouseBehavior(*entity);
	}
}

void CInput::reactsTo(Key mKey, InputBehavior mBehavior)
{
	m_behaviors[mKey] = mBehavior;
}

void CInput::reactsToMouse(InputBehavior mBehavior)
{
	m_mouseBehavior = mBehavior;
	m_hasMouseBehavior = true;
}
