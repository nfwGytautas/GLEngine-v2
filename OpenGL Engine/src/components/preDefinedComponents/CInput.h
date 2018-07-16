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

	bool curentlyEnabled;

	void react(const std::vector<Key>& mKeys);
	void reactsTo(Key mKey, InputBehavior mBehavior);
private:
	std::unordered_map<Key, InputBehavior> m_behaviors;
};

