#pragma once
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