#include "Engine.h"

#include <iostream>

int main()
{
	Engine::initialize(1280, 720, "TestWindow");

	Entity& testEntity(Engine::EntityFactory::createEntity());
	Engine::EntityEditor::addPositionComponent(testEntity, glm::vec3(0.0f, 0.0f, -10.0f));
	Engine::EntityEditor::addTransformationComponent(testEntity);
	Engine::EntityEditor::addMeshComponent(testEntity, "E:/Test files/nfw/dragon.obj");
	Engine::EntityEditor::addMaterialComponent(testEntity,"E:/Test files/nfw/dragon.png", 10, 1);
	Engine::EntityEditor::addRenderComponent(testEntity);

	Entity& testLight(Engine::EntityFactory::createEntity());
	Engine::EntityEditor::addLightEmiterComponent(testLight);

	Engine::Window::vSync(true);
	while (!Engine::Window::shouldClose())
	{
		Engine::render();
		Engine::update();
	}

	Engine::terminate();
	return 0;
}