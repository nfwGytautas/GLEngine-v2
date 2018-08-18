#pragma once
#include "..\..\algorithm\Algorithm.h"

class PhysicsSystem
{
public:
	void update(float delta);
	void registerHeightMap(continuous2DArray<float>& mHeightMap, float mGroundSize);
	float getHeightAtPoint(float X, float Z);

	PhysicsSystem();
private:
	continuous2DArray<float> m_heightMap;
	float m_groundSize;
};