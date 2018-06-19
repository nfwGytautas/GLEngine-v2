#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Component.h"

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
		T* c(new T(std::forward <TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		m_components.emplace_back(std::move(uPtr));
		return *c;
	}

private:
	bool m_alive{ true };
	std::vector<std::unique_ptr<Component>> m_components;
};

