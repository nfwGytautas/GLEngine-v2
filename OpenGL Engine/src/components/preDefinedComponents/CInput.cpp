#include "CInput.h"
#include "..\Entity.h"

#include <iostream>

CInput::CInput()
	: curentlyEnabled(true)
{
}

void CInput::init()
{
	entity->addGroup(EntityGroups::HasInput);
}

void CInput::react(const std::vector<Key>& mKeys)
{
	for(unsigned int i = 0; i < mKeys.size(); i++)
	{
		if (m_behaviors.find(mKeys[i]) != m_behaviors.end())
		{
			m_behaviors[mKeys[i]](*entity);
		}
	}
}

void CInput::reactsTo(Key mKey, InputBehavior mBehavior)
{
	m_behaviors[mKey] = mBehavior;
}
