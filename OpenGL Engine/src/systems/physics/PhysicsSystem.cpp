#include "PhysicsSystem.h"
#include <iostream>
#include "..\..\Settings.h"
#include "..\..\components\Entity.h"
#include "..\..\components\PreDefinedComponents.h"
#include "..\..\components\EntityManager.h"
#include "..\..\maths\Maths.h"

PhysicsSystem::PhysicsSystem(EntityManager* mEntityManager)
	: m_entityManager(mEntityManager)
{
}

void PhysicsSystem::update(float delta)
{
	auto physicsEntities = m_entityManager->getEntitiesByGroup(EntityGroups::HasPhysics);
	for (Entity* e : physicsEntities)
	{
		CPhysics& currentEntityPhysics = e->getComponent<CPhysics>();
		CPosition& currentEntityPosition = e->getComponent<CPosition>();

		currentEntityPhysics.velocity.y += Settings::gravity * delta;
		currentEntityPosition.value += currentEntityPhysics.velocity * delta;

		if (currentEntityPhysics.affectedByGravity)
		{
			float heightAtEntity = getHeightAtPoint(currentEntityPosition.value.x, currentEntityPosition.value.z);
			if (currentEntityPosition.value.y < heightAtEntity)
			{
				currentEntityPhysics.velocity.y = 0;
				currentEntityPosition.value.y = heightAtEntity;
			}
		}
	}
}

void PhysicsSystem::registerHeightMap(std::vector<std::vector<float>>& mHeightMap, float mGroundSize)
{
	//Temporary, later on the system will combine the maps into 1 big height map
	m_heightMap = mHeightMap;
	m_groundSize = mGroundSize;
}

float PhysicsSystem::getHeightAtPoint(float X, float Z)
{
	auto groundEntities = m_entityManager->getEntitiesByGroup(EntityGroups::IsGround);
	for(auto groundEntity : groundEntities)
	{
		CPosition& pos = groundEntity->getComponent<CPosition>();
		float groundX = X - (pos.value.x * m_groundSize);
		float groundZ = Z - (pos.value.z * m_groundSize);
		unsigned int length = m_heightMap.size();
		float gridSquareSize = m_groundSize / ((float)length - 1);
		int gridX = (int)std::floor(groundX / gridSquareSize);
		int gridZ = (int)std::floor(groundZ / gridSquareSize);
		if(gridX >= length - 1 || gridZ >= length - 1 || gridX < 0 || gridZ < 0)
		{
			return 0.0f;
		}
		float xCoord = (gridX % (int)gridSquareSize) / gridSquareSize;
		float zCoord = (gridZ % (int)gridSquareSize) / gridSquareSize;
		float result;
		if (xCoord <= (1 - zCoord))
		{
			result = Maths::barryCentric(
				glm::vec3(0, m_heightMap[gridX][gridZ], 0), 
				glm::vec3(1, m_heightMap[(gridX + 1)][gridZ], 0), 
				glm::vec3(0, m_heightMap[gridX][gridZ + 1], 1), 
				glm::vec2(xCoord, zCoord));
		}
		else
		{
			result = Maths::barryCentric(
				glm::vec3(1, m_heightMap[(gridX + 1)][gridZ], 0), 
				glm::vec3(1, m_heightMap[(gridX + 1)][gridZ + 1], 1), 
				glm::vec3(0, m_heightMap[gridX][gridZ + 1], 1), 
				glm::vec2(xCoord, zCoord));
		}
		return result;
	}
	return 0.0f;
}
