#pragma once
#include <vector>
#include <array>
#include <memory>
#include <bitset>
#include "Component.h"
#include "Entity.h"

class EntityBlueprint
{
public:
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

	EntityBlueprint();
	~EntityBlueprint();
	void releaseMemory();
private:
	bool m_memoryReleased{ false };

	std::array<Component*, maxComponents> m_componentArray;
	std::bitset<maxComponents> m_componentBitset;

	friend Entity;
};