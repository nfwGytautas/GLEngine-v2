#include "Engine.h"

#include <iostream>

int main()
{
	Engine::initialize(1280, 720, "TestWindow");

	Entity& testEntity1(Engine::EntityFactory::createEntity());
	Engine::EntityEditor::addPositionComponent(testEntity1, glm::vec3(0.0f, 0.0f, -20.0f));
	Engine::EntityEditor::addTransformationComponent(testEntity1);
	testEntity1.getComponent<CTransformation>().rotationX = 90;
	Engine::EntityEditor::addMeshComponent(testEntity1, "E:/Test files/nfw/stall.obj");
	Engine::EntityEditor::addMaterialComponent(testEntity1,"E:/Test files/nfw/stallTexture.png", 10, 1);
	Engine::EntityEditor::addRenderComponent(testEntity1);

	Entity& testEntity2(Engine::EntityFactory::createEntity());
	Engine::EntityEditor::addPositionComponent(testEntity2, glm::vec3(10.0f, 0.0f, -20.0f));
	Engine::EntityEditor::addTransformationComponent(testEntity2);
	Engine::EntityEditor::addMeshComponent(testEntity2, "E:/Test files/nfw/stall.obj");
	Engine::EntityEditor::addMaterialComponent(testEntity2, "E:/Test files/nfw/stallTexture.png", 10, 1);
	Engine::EntityEditor::addRenderComponent(testEntity2);

	Entity& testEntity3(Engine::EntityFactory::createEntity());
	Engine::EntityEditor::addPositionComponent(testEntity3, glm::vec3(20.0f, 0.0f, -30.0f));
	Engine::EntityEditor::addTransformationComponent(testEntity3);
	Engine::EntityEditor::addMeshComponent(testEntity3, "E:/Test files/nfw/stall.obj");
	Engine::EntityEditor::addMaterialComponent(testEntity3, "E:/Test files/nfw/stallTexture.png", 10, 1);
	Engine::EntityEditor::addRenderComponent(testEntity3);

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