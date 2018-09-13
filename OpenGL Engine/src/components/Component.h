#pragma once
#include <type_traits>

class Entity;
struct Component
{
	Entity* entity{ nullptr };

	//This method is called after construction of the component
	virtual void init() {}
	//This method is called after every update cycle
	virtual void update(float frameTime) {}
	//This method is called before every render cycle
	virtual void preRender() {}
	//This method is called during every render cycle
	virtual void render() {}
	//This method is called after every render cycle
	virtual void postRender() {}

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