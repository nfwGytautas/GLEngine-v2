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

void CInput::react(const Key& mKey)
{
	if (m_behaviors.find(mKey) != m_behaviors.end())
	{
		m_behaviors[mKey](*entity);
	}
}

void CInput::reactsTo(Key mKey, InputBehavior mBehavior)
{
	m_behaviors[mKey] = mBehavior;
}
