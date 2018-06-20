#pragma once
#include "Component.h"

#include <glm/glm.hpp>

//For now none of the components will have private members until messaging is added 
//since there would be no way to change them during runtime. Also none of the functions
//are filled until next commit

//TODO: Add dependencies so that components would add a component that it requires if it doesn't have it

class StaticShader;

struct CPosition : Component
{
	glm::vec3 position;

	CPosition() = default;
	CPosition(const glm::vec3& mPosition) : position{ Position } {}
};
struct CTransformation : Component
{
	glm::mat4 transformationMatrix;
	CPosition* cPosition;
	//Could be seperate componenets
	float rotationX, rotationY, rotationZ;
	float scale;

	void init() override;
	void draw() override;

	CTransformation(StaticShader* mShader) : m_shader{ mShader } {}
private:
	StaticShader* m_shader;
};

struct CMesh : Component
{
	void draw() override;

	unsigned int vertexCount;

	CMesh(unsigned int mVaoID, unsigned int mVertexCount) : m_vaoID{ mVaoID }, vertexCount{ mVertexCount } {}

private:
	unsigned int m_vaoID;
};

struct CMaterial : Component
{
	void draw() override;

	float shineDamper;
	float reflectivity;

	CMaterial(StaticShader* mShader, unsigned int mTextureID, float mShineDamper, float mReflectivity) : m_shader{ mShader }, m_textureID { mTextureID }, shineDamper{ mShineDamper }, reflectivity{ reflectivity } {}
private:
	StaticShader* m_shader;
	unsigned int m_textureID;
};