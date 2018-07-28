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
	stallEntity1.getComponent<CTransformation>().rotationX = 90.0f;

	Entity& stallEntity2(Engine::EntityFactory::createEntity(stallBlueprint));
	stallEntity2.getComponent<CPosition>().value = glm::vec3(10.0f, 0.0f, -20.0f);

	Entity& stallEntity3(Engine::EntityFactory::createEntity(stallBlueprint));
	stallEntity3.getComponent<CPosition>().value = glm::vec3(20.0f, 10.0f, -30.0f);

	Entity& testTerrain1(Engine::EntityFactory::createEntity());
	testTerrain1.addComponent<CPosition>(glm::vec3(0, 0, 0));
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

	Entity& testPlayer(Engine::EntityFactory::createEntity());
	testPlayer.addComponent<CPosition>(glm::vec3(50, 0, 50));
	testPlayer.addComponent<CTransformation>(0, 0, 0, 1);
	testPlayer.addComponent<CMesh>(Engine::Loader::loadMesh("E:/Test files/nfw/person.obj"));
	testPlayer.addComponent<CMaterial>(Engine::Loader::loadMaterial("E:/Test files/nfw/playerTexture.png"), 10, 0);
	testPlayer.addComponent<CInput>();
	testPlayer.addComponent<CPhysics>().affectedByGravity = true;
	CInput& input = testPlayer.getComponent<CInput>();
	InputBehavior aBehavior = [](Entity& mEntity)
	{
		mEntity.getComponent<CTransformation>().rotationY += (160 * Engine::deltaTime());
	};
	InputBehavior dBehavior = [](Entity& mEntity)
	{
		mEntity.getComponent<CTransformation>().rotationY -= (160 * Engine::deltaTime());
	};
	InputBehavior wBehavior = [](Entity& mEntity)
	{
		float distance = 50 * Engine::deltaTime();
		float dx = (float)(distance * std::sin(Maths::DegreesToRadians(mEntity.getComponent<CTransformation>().rotationY)));
		float dz = (float)(distance * std::cos(Maths::DegreesToRadians(mEntity.getComponent<CTransformation>().rotationY)));
		mEntity.getComponent<CPosition>().value.x += dx;
		mEntity.getComponent<CPosition>().value.z += dz;
	};
	InputBehavior sBehavior = [](Entity& mEntity)
	{
		float distance = -50 * Engine::deltaTime();
		float dx = distance * (float)(std::sin(Maths::DegreesToRadians(mEntity.getComponent<CTransformation>().rotationY)));
		float dz = distance * (float)(std::cos(Maths::DegreesToRadians(mEntity.getComponent<CTransformation>().rotationY)));
		mEntity.getComponent<CPosition>().value.x += dx;
		mEntity.getComponent<CPosition>().value.z += dz;
	};
	InputBehavior spaceBehavior = [](Entity& mEntity)
	{
		if (mEntity.getComponent<CPosition>().value.y <= 0)
		{
			mEntity.getComponent<CPhysics>().velocity.y = 30;
		}
	};
	input.reactsTo(Key::KEY_W, wBehavior);
	input.reactsTo(Key::KEY_S, sBehavior);
	input.reactsTo(Key::KEY_A, aBehavior);
	input.reactsTo(Key::KEY_D, dBehavior);
	input.reactsTo(Key::KEY_SPACE, spaceBehavior);

	InputBehavior mouseBehavior = [](Entity& mEntity) 
	{
		mEntity.getComponent<CCamera>().distanceToHook += (Engine::Input::Mouse::getScrollY());

		if (Engine::Input::Mouse::isMouseKeyDown(MouseKey::BUTTON_RIGHT))
		{
			mEntity.getComponent<CCamera>().pitch += Engine::Input::Mouse::getMovedY();
		}

		if (Engine::Input::Mouse::isMouseKeyDown(MouseKey::BUTTON_LEFT))
		{
			mEntity.getComponent<CCamera>().angleAroundHook += Engine::Input::Mouse::getMovedX();
		}
	};
	Entity& testCamera(Engine::EntityFactory::createEntity());
	testCamera.addComponent<CPosition>(glm::vec3(0,10,5));
	testCamera.addComponent<CTransformation>(0,0,0,1);
	testCamera.addComponent<CCamera>().hookTo(&testPlayer, 50, 0);
	testCamera.addComponent<CCamera>().pitch = 30;
	testCamera.addComponent<CInput>().reactsToMouse(mouseBehavior);
	Settings::camera = &testCamera.getComponent<CCamera>();


	Engine::Window::vSync(true);
	while (!Engine::Window::shouldClose())
	{
		Engine::render();
		Engine::update();
	}

	Engine::terminate();
	return 0;
}