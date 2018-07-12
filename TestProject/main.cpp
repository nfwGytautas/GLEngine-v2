#include "Engine.h"

#include <iostream>

int main()
{
	Engine::initialize(1280, 720, "TestWindow");

	EntityBlueprint& stallBlueprint(Engine::EntityFactory::newBlueprint());
	stallBlueprint.addComponent<CPosition>(glm::vec3(0.0f, 0.0f, 0.0f));
	stallBlueprint.addComponent<CTransformation>(0, 0, 0, 1);
	stallBlueprint.addComponent<CMesh>(Engine::Loader::loadMesh("E:/Test files/nfw/stall.obj"));
	stallBlueprint.addComponent<CMaterial>(Engine::Loader::loadMaterial("E:/Test files/nfw/stallTexture.png"), 10, 1);

	Entity& stallEntity1(Engine::EntityFactory::createEntity(stallBlueprint));
	stallEntity1.getComponent<CPosition>().value = glm::vec3(0.0f, 0.0f, -20.0f);
	stallEntity1.getComponent<CTransformation>().rotationX = 90;

	Entity& stallEntity2(Engine::EntityFactory::createEntity(stallBlueprint));
	stallEntity2.getComponent<CPosition>().value = glm::vec3(10.0f, 0.0f, -20.0f);

	Entity& stallEntity3(Engine::EntityFactory::createEntity(stallBlueprint));
	stallEntity3.getComponent<CPosition>().value = glm::vec3(20.0f, 10.0f, -30.0f);

	Entity& testTerrain1(Engine::EntityFactory::createEntity());
	testTerrain1.addComponent<CPosition>(glm::vec3(0,0,0));
	testTerrain1.addComponent<CTransformation>(0, 0, 0, 1);
	testTerrain1.addComponent<CMesh>(Engine::Loader::createFlatMesh(128, 800));
	CMultiTexture& pack = testTerrain1.addComponent<CMultiTexture>();
	pack.background = Engine::Loader::loadTexture("E:/Test files/nfw/grassy.png");
	pack.r = Engine::Loader::loadTexture("E:/Test files/nfw/mud.png");
	pack.g = Engine::Loader::loadTexture("E:/Test files/nfw/grassFlowers.png"); 
	pack.b = Engine::Loader::loadTexture("E:/Test files/nfw/path.png");
	pack.textureBlendMap = Engine::Loader::loadTexture("E:/Test files/nfw/blendMap.png");
	testTerrain1.addComponent<CRenderer>().fakeLighting = true;
	testTerrain1.getComponent<CRenderer>().tileCount = 40;
	testTerrain1.getComponent<CRenderer>().multiTexture = true;

	Entity& testTransparent1(Engine::EntityFactory::createEntity());
	testTransparent1.addComponent<CPosition>(glm::vec3(20, 0, 10));
	testTransparent1.addComponent<CTransformation>(0, 0, 0, 1);
	testTransparent1.addComponent<CMesh>(Engine::Loader::loadMesh("E:/Test files/nfw/grassModel.obj"));
	testTransparent1.addComponent<CMaterial>(Engine::Loader::loadMaterial("E:/Test files/nfw/grassTexture.png"), 10, 0);
	testTransparent1.addComponent<CRenderer>().transparent = true;
	testTransparent1.getComponent<CRenderer>().fakeLighting = true;

	Entity& testTransparent2(Engine::EntityFactory::createEntity());
	testTransparent2.addComponent<CPosition>(glm::vec3(20, 0, 50));
	testTransparent2.addComponent<CTransformation>(0, 0, 0, 1);
	testTransparent2.addComponent<CMesh>(Engine::Loader::loadMesh("E:/Test files/nfw/fern.obj"));
	testTransparent2.addComponent<CMaterial>(Engine::Loader::loadMaterial("E:/Test files/nfw/fern.png"), 10, 0);
	testTransparent2.addComponent<CRenderer>().transparent = true;
	testTransparent2.getComponent<CRenderer>().fakeLighting = true;

	Entity& testLight(Engine::EntityFactory::createEntity());
	testLight.addComponent<CLightEmiter>();
	testLight.getComponent<CPosition>().value = glm::vec3(20000, 40000, 20000);

	Engine::Window::vSync(true);
	while (!Engine::Window::shouldClose())
	{
		Engine::render();
		Engine::update();
	}

	Engine::terminate();
	return 0;
}