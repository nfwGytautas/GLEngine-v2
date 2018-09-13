#pragma once
#include <vector>
#include <array>
#include <memory>
#include <bitset>
#include <glm/glm.hpp>
#include "Component.h"
#include "EntityGroups.h"

static const size_t maxComponents = 32;
static const size_t maxGroups = 32;
using Group = size_t;

class EntityBlueprint;
class Entity
{
public:
	void init();
	void update(float frameTime);
	void preRender();
	void render();
	void postRender();
public:

	bool isAlive() const;
	void destroy();

	template<typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		if (hasComponent<T>())
		{
			return getComponent<T>();
		}

		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		m_componentArray[getComponentTypeID<T>()] = c;
		m_componentBitset[getComponentTypeID<T>()] = true;

		c->init();

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

	bool hasGroup(Group mGroup) const noexcept;
	void addGroup(Group mGroup) noexcept;
	void delGroup(Group mGroup) noexcept;

	Entity();
	Entity(EntityBlueprint& mBlueprint);
	~Entity();
	void releaseMemory();
private:

	bool m_alive{ true };

	bool m_memoryReleased{ false };

	using ComponentBitset = std::bitset<maxComponents>;
	using ComponentArray = std::array<Component*, maxComponents>;
	ComponentArray m_componentArray;
	ComponentBitset m_componentBitset;

	using GroupBitset = std::bitset<maxGroups>;
	GroupBitset m_groupBitset;

	friend EntityBlueprint;
};

