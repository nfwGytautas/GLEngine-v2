#include "PhysicsSystem.h"
#include <iostream>
#include "..\..\SGEDefs.h"
#include "..\..\Settings.h"
#include "..\..\components\Entity.h"
#include "..\..\components\preDefinedComponents\CPhysics.h"
#include "..\..\components\preDefinedComponents\CTransformation.h"
#include "..\..\components\EntityManager.h"
#include "..\..\maths\Maths.h"



PhysicsSystem::PhysicsSystem()
{
}

void PhysicsSystem::calculateFrustum()
{
	m_frustum.calculatePlanes(Settings::camera);

	glm::vec3 testPos = glm::vec3(0.0f, 0.0f, -20.0f);

	if (m_frustum.sphereInFrustum(testPos, 0.5f) != Frustum::OUTSIDE)
	{
		std::cout << "In frustum" << std::endl;
	}
}

void PhysicsSystem::update(float delta)
{
	calculateFrustum();

	auto physicsEntities = SGE::Instances::instances->entityManagerInstance->getEntitiesByGroup(EntityGroups::HasPhysics);
	for (Entity* e : physicsEntities)
	{
		CPhysics& currentEntityPhysics = e->getComponent<CPhysics>();
		CTransformation& currentEntityTransformation = e->getComponent<CTransformation>();

		currentEntityTransformation.position += currentEntityPhysics.velocity * delta;

		if (currentEntityPhysics.affectedByGravity)
		{
			currentEntityPhysics.velocity.y += Settings::gravity * delta;

			float heightAtEntity = getHeightAtPoint(currentEntityTransformation.position.x, currentEntityTransformation.position.z);
			if (currentEntityTransformation.position.y < heightAtEntity)
			{
				currentEntityPhysics.velocity.y = 0;
				currentEntityTransformation.position.y = heightAtEntity;
			}
		}
	}
}

void PhysicsSystem::registerHeightMap(continuous2DArray<float>& mHeightMap, float mGroundSize)
{
	//Temporary, later on the system will combine the maps into 1 big height map
	m_heightMap = mHeightMap;
	m_groundSize = mGroundSize;
}

float PhysicsSystem::getHeightAtPoint(float X, float Z)
{
	auto groundEntities = SGE::Instances::instances->entityManagerInstance->getEntitiesByGroup(EntityGroups::IsGround);
	for (auto groundEntity : groundEntities)
	{
		CTransformation& transformation = groundEntity->getComponent<CTransformation>();
		float groundX = X - (transformation.position.x * m_groundSize);
		float groundZ = Z - (transformation.position.z * m_groundSize);
		unsigned int length = m_heightMap.rowCount();
		float gridSquareSize = m_groundSize / ((float)length - 1);
		int gridX = (int)std::floor(groundX / gridSquareSize);
		int gridZ = (int)std::floor(groundZ / gridSquareSize);
		if ((unsigned int)gridX >= length - 1 || (unsigned int)gridZ >= length - 1 || gridX < 0 || gridZ < 0)
		{
			return 0.0f;
		}
		float xCoord = (gridX % (int)gridSquareSize) / gridSquareSize;
		float zCoord = (gridZ % (int)gridSquareSize) / gridSquareSize;
		float result;
		if (xCoord <= (1 - zCoord))
		{
			result = Maths::barryCentric(
				glm::vec3(0, m_heightMap(gridX, gridZ), 0),
				glm::vec3(1, m_heightMap((gridX + 1), gridZ), 0),
				glm::vec3(0, m_heightMap(gridX, gridZ + 1), 1),
				glm::vec2(xCoord, zCoord));
		}
		else
		{
			result = Maths::barryCentric(
				glm::vec3(1, m_heightMap((gridX + 1), gridZ), 0),
				glm::vec3(1, m_heightMap((gridX + 1), gridZ + 1), 1),
				glm::vec3(0, m_heightMap(gridX, gridZ + 1), 1),
				glm::vec2(xCoord, zCoord));
		}
		return result;
	}
	return 0.0f;
}