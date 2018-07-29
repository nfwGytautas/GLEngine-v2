#pragma once
#include "..\..\algorithm\Algorithm.h"

class EntityManager;
class PhysicsSystem
{
public:
	void update(float delta);
	void registerHeightMap(continuous2DArray<float>& mHeightMap, float mGroundSize);
	float getHeightAtPoint(float X, float Z);

	PhysicsSystem(EntityManager* mEntityManager);
private:
	EntityManager* m_entityManager;
	continuous2DArray<float> m_heightMap;
	float m_groundSize;
};

