#pragma once
#include <vector>

class EntityManager;
class PhysicsSystem
{
public:
	void update(float delta);
	void registerHeightMap(std::vector<std::vector<float>>& mHeightMap, float mGroundSize);
	float getHeightAtPoint(float X, float Z);

	PhysicsSystem(EntityManager* mEntityManager);
private:
	EntityManager* m_entityManager;
	std::vector<std::vector<float>> m_heightMap;
	float m_groundSize;
};

