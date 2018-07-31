#pragma once
#include <vector>
#include <array>
#include <memory>
#include <bitset>
#include "Component.h"
#include "Entity.h"

class EntityManager;
class EntityBlueprint
{
public:
	EntityBlueprint(EntityManager& mManager);
	~EntityBlueprint();

	template<typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		if (hasComponent<T>())
		{
			return getComponent<T>();
		}
		T* c(new T(std::forward <TArgs>(mArgs)...));
		m_componentArray[getComponentTypeID<T>()] = c;
		m_componentBitset[getComponentTypeID<T>()] = true;
		return *c;
	}

	template<typename T>
	bool hasComponent() const
	{
		return m_componentBitset[getComponentTypeID<T>()];
	}
	template<typename T>
	T& getComponent() const
	{
		assert(hasComponent<T>());
		auto ptr(m_componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
private:
	EntityManager& m_manager;

	using ComponentBitset = std::bitset<maxComponents>;
	using ComponentArray = std::array<Component*, maxComponents>;
	ComponentArray m_componentArray;
	ComponentBitset m_componentBitset;

	friend Entity;
};