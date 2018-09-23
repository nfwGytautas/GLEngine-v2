#pragma once
#include <type_traits>

class Entity;
struct Component
{
	Entity* entity{ nullptr };

	virtual void init() {}
	virtual void update(float frameTime) {}
	virtual void draw() {}
	virtual void handleMessage(const char* message) {}

	//Required for blueprints
	virtual Component* clone() { return new Component(*this); }

	virtual ~Component() {}
};

using ComponentID = size_t;
ComponentID getUniqueComponentID() noexcept;
template<typename T>
ComponentID getComponentTypeID() noexcept
{
	static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
	static ComponentID typeID{ getUniqueComponentID() };
	return typeID;
}