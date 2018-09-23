#include "UpdateSystem.h"
#include "..\..\SGEDefs.h"
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "..\..\Settings.h"
#include "..\..\graphics\display\Display.h"
#include "..\..\data manager\input\InputManager.h"
#include "..\physics\PhysicsSystem.h"
#include "..\event\EventSystem.h"
#include "..\..\algorithm\Algorithm.h"
#include "..\..\components\Entity.h"
#include "..\..\components\EntityManager.h"
#include "..\..\components\preDefinedComponents\CInput.h"
#include "..\..\components\preDefinedComponents\CCamera.h"
#include "..\..\maths\Maths.h"

void UpdateSystem::update()
{
	Display::updateDisplay();
	InputManager::update();
	SGE::Instances::instances->entityManagerInstance->refresh();

	postEvents();
	updatePhysics();
	updateEntitiesWthModels();

	SGE::Instances::instances->entityManagerInstance->update(Display::getDelta());
}
UpdateSystem::UpdateSystem()
{
}

void UpdateSystem::postEvents()
{
	auto downKeys = InputManager::getKeyDown();
	for (Key key : downKeys)
	{
		SGE::Instances::instances->eventSystemInstance->post(KeyDownEvent(key));
	}
	auto upKeys = InputManager::getKeyUp();
	for (Key key : upKeys)
	{
		SGE::Instances::instances->eventSystemInstance->post(KeyUpEvent(key));
	}
	auto mDownKeys = InputManager::getMKeyDown();
	for (MouseKey key : mDownKeys)
	{
		SGE::Instances::instances->eventSystemInstance->post(MouseKeyDownEvent(key));
	}
	auto mUpKeys = InputManager::getMKeyUp();
	for (MouseKey key : mUpKeys)
	{
		SGE::Instances::instances->eventSystemInstance->post(MouseKeyUpEvent(key));
	}
	SGE::Instances::instances->eventSystemInstance->post(MouseMovedEvent(InputManager::Mouse::getXOffset(), InputManager::Mouse::getYOffset()));
	SGE::Instances::instances->eventSystemInstance->post(MouseScrollEvent(InputManager::Mouse::getScrollAmountX(), InputManager::Mouse::getScrollAmountY()));
}
void UpdateSystem::updatePhysics()
{
	SGE::Instances::instances->physicsSystemInstance->update(Display::getDelta());
}

void UpdateSystem::updateEntitiesWthModels()
{
	auto renderables = SGE::Instances::instances->entityManagerInstance->getEntitiesByGroup(EntityGroups::Renderable);

	for (Entity* entity : renderables)
	{
		entity->getComponent<CModel>().m_rendered = false;
	}
}
