#pragma once
//For now just to get the system working only update and draw methods will be used

class Entity;

struct Component
{
	Entity* entity{ nullptr };

	virtual void init() {}
	virtual void update(float frameTime) {}
	virtual void draw() {}
	virtual void handleMessage(const char* message) {}

	virtual ~Component() {}
};