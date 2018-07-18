#pragma once
#include "..\Component.h"
//Dependencies
#include <unordered_map>
#include <functional>
#include "..\..\input\InputKeys.h"

using InputBehavior = std::function<void(Entity& mEntity)>;

struct CInput : Component
{
	CInput();
	~CInput() {};

	void init() override;

	bool enabled;

	//Most likely will change after event system is implemented
	void react(const std::vector<Key>& mKeys);
	void reactToMouse();
	void reactsTo(Key mKey, InputBehavior mBehavior);
	void reactsToMouse(InputBehavior mBehavior);

	virtual CInput* clone() { return new CInput(*this); }
private:
	std::unordered_map<Key, InputBehavior> m_behaviors;
	InputBehavior m_mouseBehavior;
	bool m_hasMouseBehavior;
};

