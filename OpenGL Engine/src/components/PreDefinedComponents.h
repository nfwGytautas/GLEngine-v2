#pragma once
#include "Component.h"
#include <glm/glm.hpp>

class StaticShader;

struct CPosition : Component
{
	glm::vec3 value;

	CPosition() = default;
	CPosition(const glm::vec3& mPosition) : value{ mPosition } {}
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

	CTransformation(StaticShader* mShader, float mXRotation, float mYRotation, float mZRotation, float mScale) : m_shader{ mShader }, rotationX{ mXRotation }, rotationY{ mYRotation }, rotationZ{ mZRotation }, scale{ mScale } {}
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

	CMaterial(StaticShader* mShader, unsigned int mTextureID, float mShineDamper, float mReflectivity) : m_shader{ mShader }, m_textureID { mTextureID }, shineDamper{ mShineDamper }, reflectivity{ mReflectivity } {}
private:
	StaticShader* m_shader;
	unsigned int m_textureID;
};
struct CRenderer : Component
{
	void draw() override;

	CRenderer() {}
};
struct CColor : Component
{
	glm::vec3 value;

	CColor() = default;
	CColor(const glm::vec3& mColor) : value{ mColor } {}
};
struct CLightEmiter : Component
{
	CPosition* cPosition;
	CColor* cColor;

	void init() override;
	void draw() override;

	CLightEmiter(StaticShader* mShader) : m_shader{ mShader } {}
private:
	StaticShader* m_shader;
};