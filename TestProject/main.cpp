#include "Engine.h"

#include <iostream>

int main()
{
	Engine::initialize(1280, 720, "TestWindow");

	Entity& testEntity1(Engine::EntityFactory::createEntity());
	testEntity1.addComponent<CPosition>(glm::vec3(0.0f, 0.0f, -20.0f));
	testEntity1.addComponent<CTransformation>(0,0,0,1);
	testEntity1.getComponent<CTransformation>().rotationX = 90;
	testEntity1.addComponent<CMesh>(Engine::Loader::loadMesh("E:/Test files/nfw/stall.obj"));
	testEntity1.addComponent<CMaterial>(Engine::Loader::loadMaterial("E:/Test files/nfw/stallTexture.png"), 10, 1);
	testEntity1.addComponent<CRenderer>();

	Entity& testEntity2(Engine::EntityFactory::createEntity());
	testEntity2.addComponent<CPosition>(glm::vec3(10.0f, 0.0f, -20.0f));
	testEntity2.addComponent<CTransformation>(0, 0, 0, 1);
	testEntity2.addComponent<CMesh>(Engine::Loader::loadMesh("E:/Test files/nfw/stall.obj"));
	testEntity2.addComponent<CMaterial>(Engine::Loader::loadMaterial("E:/Test files/nfw/stallTexture.png"), 10, 1);
	testEntity2.addComponent<CRenderer>();

	Entity& testEntity3(Engine::EntityFactory::createEntity());
	testEntity3.addComponent<CPosition>(glm::vec3(20.0f, 10.0f, -30.0f));
	testEntity3.addComponent<CTransformation>(0, 0, 0, 1);
	testEntity3.addComponent<CMesh>(Engine::Loader::loadMesh("E:/Test files/nfw/stall.obj"));
	testEntity3.addComponent<CMaterial>(Engine::Loader::loadMaterial("E:/Test files/nfw/stallTexture.png"), 10, 1);
	testEntity3.addComponent<CRenderer>();

	Entity& testLight(Engine::EntityFactory::createEntity());
	testLight.addComponent<CLightEmiter>();

	Engine::Window::vSync(true);
	while (!Engine::Window::shouldClose())
	{
		Engine::render();
		Engine::update();
	}

	Engine::terminate();
	return 0;
}