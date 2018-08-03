#pragma once
#include "..\Component.h"
//Dependencies
#include <unordered_map>
#include <functional>
#include "..\..\systems\event\PreDefinedEvents.h"

using EventBehavior = std::function<void(Entity& mEntity, const Event& e)>;

struct CInput : Component
{
	CInput();
	~CInput() {};

	void init() override;

	void subscribe(const EventType& mType, EventBehavior& mBehavior);
	void react(const Event& mEvent);

private:
	std::unordered_map<EventType, EventBehavior> m_reactions;
};

