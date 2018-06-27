#pragma once
#include "Component.h"
#include <glm/glm.hpp>

class BatchManager;

struct CPosition : Component
{
	glm::vec3 value;

	CPosition() = default;
	CPosition(const glm::vec3& mPosition) : value{ mPosition } {}
};
struct CTransformation : Component
{
	void init() override;
	void update(float frameTime) override;

	glm::mat4 transformationMatrix;
	CPosition* cPosition;
	//Could be seperate componenets
	float rotationX, rotationY, rotationZ;
	float scale;

	CTransformation(float mXRotation, float mYRotation, float mZRotation, float mScale) : rotationX{ mXRotation }, rotationY{ mYRotation }, rotationZ{ mZRotation }, scale{ mScale } {}
};
struct CMesh : Component
{
	void use();

	unsigned int vertexCount;

	CMesh(unsigned int mVaoID, unsigned int mVertexCount) : m_vaoID{ mVaoID }, vertexCount{ mVertexCount } {}

	size_t hash() const;
	bool operator==(const CMesh& mesh) const
	{
		if (hash() == mesh.hash())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
private:
	unsigned int m_vaoID;
	friend BatchManager;
};
struct CMaterial : Component
{
	void use();

	float shineDamper;
	float reflectivity;

	CMaterial(unsigned int mTextureID, float mShineDamper, float mReflectivity): m_textureID { mTextureID }, shineDamper{ mShineDamper }, reflectivity{ mReflectivity } {}

	size_t hash() const;
	bool operator==(const CMaterial& mat) const
	{
		if (hash() == mat.hash())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator!=(const CMaterial& mat) const
	{
		return !(*this == mat);
	}
private:
	unsigned int m_textureID;
	friend BatchManager;
};
struct CRenderer : Component
{
	void loadSettings();

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
	void init() override;

	CPosition* cPosition;
	CColor* cColor;
	CLightEmiter() {};
};