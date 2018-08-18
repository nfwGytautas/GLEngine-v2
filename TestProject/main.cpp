#include "SGEngine.h"
#include <iostream>

void applySettings()
{
	Settings::skyboxFiles[0] = "E:/Test files/nfw/right.jpg";
	Settings::skyboxFiles[1] = "E:/Test files/nfw/left.jpg";
	Settings::skyboxFiles[2] = "E:/Test files/nfw/top.jpg";
	Settings::skyboxFiles[3] = "E:/Test files/nfw/bottom.jpg";
	Settings::skyboxFiles[4] = "E:/Test files/nfw/front.jpg";
	Settings::skyboxFiles[5] = "E:/Test files/nfw/back.jpg";
}

int main()
{
	applySettings();

	SGE::SGEngine engine;
	SGE::Types::UpdateSystem updateManager = engine.getUpdateSystem();
	SGE::Types::Renderer renderer = engine.getRenderer();
	SGE::Types::Physics physics = engine.getPhysicsManager();
	SGE::Types::DataManager dataManager = engine.getDataManager();

	EntityBlueprint stallBlueprint;
	stallBlueprint.addComponent<CTransformation>();
	stallBlueprint.addComponent<CMesh>(dataManager->loadMesh("E:/Test files/nfw/stall.obj"));
	stallBlueprint.addComponent<CMaterial>(dataManager->loadMaterial("E:/Test files/nfw/stallTexture.png"), 10, 1);

	Entity stallEntity1(stallBlueprint);
	CTransformation& stallEntityTransform1 = stallEntity1.getComponent<CTransformation>();
	stallEntityTransform1.position = glm::vec3(0.0f, 0.0f, -20.0f);
	stallEntityTransform1.rotation.x = 90.0f;

	Entity stallEntity2(stallBlueprint);
	CTransformation& stallEntityTransform2 = stallEntity2.getComponent<CTransformation>();
	stallEntityTransform2.position = glm::vec3(10.0f, 0.0f, -20.0f);

	Entity stallEntity3(stallBlueprint);
	CTransformation& stallEntityTransform3 = stallEntity3.getComponent<CTransformation>();
	stallEntityTransform3.position = glm::vec3(20.0f, 10.0f, -30.0f);

	Entity testTerrain1;
	testTerrain1.addComponent<CTransformation>();
	continuous2DArray<float> calculatedHeights;
	testTerrain1.addComponent<CMesh>(dataManager->createHeightMappedMesh("E:/Test files/nfw/heightMap.png", 20, 800, calculatedHeights));
	CMultiTexture& pack = testTerrain1.addComponent<CMultiTexture>();
	pack.background = dataManager->loadTexture("E:/Test files/nfw/grassy.png");
	pack.r = dataManager->loadTexture("E:/Test files/nfw/mud.png");
	pack.g = dataManager->loadTexture("E:/Test files/nfw/grassFlowers.png");
	pack.b = dataManager->loadTexture("E:/Test files/nfw/path.png");
	pack.textureBlendMap = dataManager->loadTexture("E:/Test files/nfw/blendMap.png");
	testTerrain1.addComponent<CRenderer>().tileCount = 40;
	testTerrain1.getComponent<CRenderer>().multiTexture = true;
	testTerrain1.getComponent<CRenderer>().disableSpecular = true;
	engine.markAsGround(testTerrain1, calculatedHeights, 800);

	Entity testTransparent1;
	testTransparent1.addComponent<CTransformation>(glm::vec3(20, 0, 10), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	testTransparent1.addComponent<CMesh>(dataManager->loadMesh("E:/Test files/nfw/grassModel.obj"));
	testTransparent1.addComponent<CMaterial>(dataManager->loadMaterial("E:/Test files/nfw/grassTexture.png"), 10, 0);
	testTransparent1.addComponent<CRenderer>().transparent = true;
	testTransparent1.getComponent<CRenderer>().fakeLighting = true;

	EntityBlueprint fernBlueprint;
	fernBlueprint.addComponent<CTransformation>();
	fernBlueprint.addComponent<CMesh>(dataManager->loadMesh("E:/Test files/nfw/fern.obj"));
	fernBlueprint.addComponent<CMaterial>(dataManager->loadMaterial("E:/Test files/nfw/fernAtlas.png"), 10, 0);
	CRenderer& renderComponent = fernBlueprint.addComponent<CRenderer>();
	renderComponent.transparent = true;
	renderComponent.fakeLighting = true;
	renderComponent.hasAtlas = true;
	renderComponent.atlasRowCount = 2;

	Entity fern1(fernBlueprint);
	fern1.getComponent<CTransformation>().position = glm::vec3(20, 0, 50);
	fern1.getComponent<CRenderer>().atlasIndex = 0;
	Entity fern2(fernBlueprint);
	fern2.getComponent<CTransformation>().position = glm::vec3(10, 0, 50);
	fern2.getComponent<CRenderer>().atlasIndex = 1;
	Entity fern3(fernBlueprint);
	fern3.getComponent<CTransformation>().position = glm::vec3(0, 0, 50);
	fern3.getComponent<CRenderer>().atlasIndex = 2;
	Entity fern4(fernBlueprint);
	fern4.getComponent<CTransformation>().position = glm::vec3(-10, 0, 50);
	fern4.getComponent<CRenderer>().atlasIndex = 3;

	Entity sun;
	sun.addComponent<CLightEmiter>();
	sun.getComponent<CTransformation>().position = glm::vec3(0, 1000, -7000);
	sun.getComponent<CColor>().value = glm::vec3(0.4f, 0.4f, 0.4f);

	EntityBlueprint lightBlueprint;
	CLightEmiter& cEmiterBP = lightBlueprint.addComponent<CLightEmiter>();
	cEmiterBP.attenuation = glm::vec3(1.0f, 0.01f, 0.002f);
	cEmiterBP.lightOffset = glm::vec3(0.0f, 10.0f, 0.0f);
	lightBlueprint.addComponent<CTransformation>().position = glm::vec3(20000, 40000, 20000);
	lightBlueprint.addComponent<CColor>().value = glm::vec3(1, 1, 1);
	lightBlueprint.addComponent<CMesh>(dataManager->loadMesh("E:/Test files/nfw/lamp.obj"));
	lightBlueprint.addComponent<CMaterial>(dataManager->loadMaterial("E:/Test files/nfw/lamp.png"), 10, 0);

	Entity testLight2(lightBlueprint);
	testLight2.getComponent<CTransformation>().position = glm::vec3(185, physics->getHeightAtPoint(185, 293), 293);
	testLight2.getComponent<CColor>().value = glm::vec3(2, 0, 0);
	Entity testLight3(lightBlueprint);
	testLight3.getComponent<CTransformation>().position = glm::vec3(370, physics->getHeightAtPoint(370, 300), 300);
	testLight3.getComponent<CColor>().value = glm::vec3(0, 2, 2);
	Entity testLight4(lightBlueprint);
	testLight4.getComponent<CTransformation>().position = glm::vec3(293, physics->getHeightAtPoint(293, 305), 305);
	testLight4.getComponent<CColor>().value = glm::vec3(2, 2, 0);

	Entity testPlayer;
	testPlayer.addComponent<CTransformation>(glm::vec3(50, 0, 50), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	testPlayer.addComponent<CMesh>(dataManager->loadMesh("E:/Test files/nfw/person.obj"));
	testPlayer.addComponent<CMaterial>(dataManager->loadMaterial("E:/Test files/nfw/playerTexture.png"), 10, 0);
	testPlayer.addComponent<CPhysics>().affectedByGravity = true;
	CInput& input = testPlayer.addComponent<CInput>();
	EventBehavior keyDownBehavior = [&](Entity& mEntity, const Event& e)
	{
		const KeyDownEvent& kDEvent = static_cast<const KeyDownEvent&>(e);

		CTransformation& transformation = mEntity.getComponent<CTransformation>();

		switch (kDEvent.pressedKey)
		{
		case Key::KEY_A:
			transformation.rotation.y += (160 * Time::deltaTime);
			break;

		case Key::KEY_D:
			transformation.rotation.y -= (160 * Time::deltaTime);
			break;

		case Key::KEY_W:
			transformation.position.x += (float)((50 * Time::deltaTime) * std::sin(Maths::DegreesToRadians(transformation.rotation.y)));
			transformation.position.z += (float)((50 * Time::deltaTime) * std::cos(Maths::DegreesToRadians(transformation.rotation.y)));
			break;

		case Key::KEY_S:
			transformation.position.x += (float)((-50 * Time::deltaTime) * std::sin(Maths::DegreesToRadians(transformation.rotation.y)));
			transformation.position.z += (float)((-50 * Time::deltaTime) * std::cos(Maths::DegreesToRadians(transformation.rotation.y)));
			break;

		case Key::KEY_SPACE:
			if (transformation.position.y <= physics->getHeightAtPoint(transformation.position.x, transformation.position.z))
			{
				mEntity.getComponent<CPhysics>().velocity.y = 30;
			}
			break;
		case Key::KEY_T:
			mEntity.getComponent<CTransformation>().position = glm::vec3(-50, 10, 5);
			break;
		}
	};
	input.subscribe(EventType::KeyDown, keyDownBehavior);

	bool right = false;
	bool left = false;

	EventBehavior mouseKeyDownBehavior = [&](Entity& mEntity, const Event& e)
	{
		const MouseKeyDownEvent& kDEvent = static_cast<const MouseKeyDownEvent&>(e);

		right = false;
		left = false;

		switch (kDEvent.pressedKey)
		{
		case MouseKey::BUTTON_RIGHT:
			right = true;
			break;

		case MouseKey::BUTTON_LEFT:
			left = true;
			break;
		}

	};
	EventBehavior mouseKeyUpBehavior = [&](Entity& mEntity, const Event& e)
	{
		const MouseKeyUpEvent& kUEvent = static_cast<const MouseKeyUpEvent&>(e);

		switch (kUEvent.releasedKey)
		{
		case MouseKey::BUTTON_RIGHT:
			right = false;
			break;

		case MouseKey::BUTTON_LEFT:
			left = false;
			break;
		}

	};
	EventBehavior mouseMoveBehavior = [&](Entity& mEntity, const Event& e)
	{
		const MouseMovedEvent& mMEvent = static_cast<const MouseMovedEvent&>(e);

		CCamera& camera = mEntity.getComponent<CCamera>();

		if (right)
		{
			camera.pitch += mMEvent.y * Settings::cameraSensetivity;
		}

		if (left)
		{
			camera.angleAroundHook += mMEvent.x * Settings::cameraSensetivity;
		}
	};
	EventBehavior mouseScrollBehavior = [&](Entity& mEntity, const Event& e)
	{
		const MouseScrollEvent& mSEvent = static_cast<const MouseScrollEvent&>(e);

		mEntity.getComponent<CCamera>().distanceToHook += mSEvent.y;
	};

	Entity testCamera;
	testCamera.addComponent<CTransformation>(glm::vec3(0, 10, 5), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	testCamera.addComponent<CCamera>().hookTo(&testPlayer, 50, 0);
	testCamera.addComponent<CCamera>().pitch = 30;
	CInput& cameraInput = testCamera.addComponent<CInput>();
	cameraInput.subscribe(EventType::MouseKeyDown, mouseKeyDownBehavior);
	cameraInput.subscribe(EventType::MouseKeyUp, mouseKeyUpBehavior);
	cameraInput.subscribe(EventType::MouseMoved, mouseMoveBehavior);
	cameraInput.subscribe(EventType::MouseScroll, mouseScrollBehavior);
	Settings::camera = &testCamera.getComponent<CCamera>();

	GUI testGui("E:/Test files/nfw/testGUI3.png", glm::vec2(0.5f, 0.5f), 0, glm::vec2(0.25f, 0.25f));

	Entity testSkyboxReflection;
	testSkyboxReflection.addComponent<CTransformation>(glm::vec3(-50, 10, 5), glm::vec3(0, 0, 0), glm::vec3(10, 10, 10));
	testSkyboxReflection.addComponent<CMesh>(dataManager->loadMesh("E:/Test files/nfw/simple_cube.obj"));
	testSkyboxReflection.addComponent<CRenderer>().skyboxReflection = true;

	Display::switchVerticalSync(true);
	while (!Display::closed())
	{
		renderer->render();
		updateManager->update();
	}

	return 0;
}