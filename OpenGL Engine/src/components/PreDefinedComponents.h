#pragma once
#include "Component.h"

#include <glm/glm.hpp>

//For now none of the components will have private members until messaging is added 
//since there would be no way to change them during runtime. Also none of the functions
//are filled until next commit
struct CTransformation : Component
{
	void update(float frameTime) override {}
	void draw() override {}

	glm::mat4 transformationMatrix;
	//Could be seperate componenets
	glm::vec3 position;
	float rotationX, rotationY, rotationZ;
	float scale;
};

struct CMesh : Component
{
	void update(float frameTime) override {}
	void draw() override {}

	unsigned int vaoID;
	unsigned int vertexCount;
};

struct CMaterial : Component
{
	void update(float frameTime) override {}
	void draw() override {}

	unsigned int textureID;
	float shineDamper;
	float reflectivity;
};

struct CModel : Component
{
	void update(float frameTime) override {}
	void draw() override {}

	CModel(CMesh& mMeshComponent, CMaterial& mMaterialComponent)
		: cMesh(mMeshComponent), cMaterial(mMaterialComponent)
	{}

	CMesh& cMesh;
	CMaterial& cMaterial;
};