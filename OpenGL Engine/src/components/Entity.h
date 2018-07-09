#pragma once
#include <vector>
#include <array>
#include <memory>
#include <bitset>
#include <glm/glm.hpp>
#include "Component.h"
#include "EntityGroups.h"

#include <iostream>

class EntityManager;
class EntityBlueprint;

constexpr size_t maxComponents{ 32 };
constexpr size_t maxGroups{ 32 };
using Group = size_t;
class Entity
{
public:
	void init();
	void update(float frameTime);
	void draw();
	void handleMessage(const char* message);

	bool isAlive() const;
	void destroy();

	template<typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		if (hasComponent<T>())
		{
			return getComponent<T>();
		}

		T* c(new T(std::forward <TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		m_components.emplace_back(std::move(uPtr));

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

	Entity(EntityManager& mManager);
	~Entity();
private:
	using ComponentID = size_t;
	static inline ComponentID getUniqueComponentID() noexcept
	{
		static ComponentID lastID{ 0u };
		return lastID++;
	}
	template<typename T>
	static inline ComponentID getComponentTypeID() noexcept
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
		static ComponentID typeID{ getUniqueComponentID() };
		return typeID;
	}	
private:
	EntityManager& m_manager;

	bool m_alive{ true };
	std::vector<std::unique_ptr<Component>> m_components;

	using ComponentBitset = std::bitset<maxComponents>;
	using ComponentArray = std::array<Component*, maxComponents>;
	ComponentArray m_componentArray;
	ComponentBitset m_componentBitset;

	using GroupBitset = std::bitset<maxGroups>;
	GroupBitset m_groupBitset;
};

