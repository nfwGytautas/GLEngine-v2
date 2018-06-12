#include "StaticShader.h"

#include "..\gtypes\gTypes.h"

const char* StaticShader::VERTEX_FILE = "E:/CV/OpenGL engine/OpenGL Engine/Shaders/v2/vertex.shader";
const char* StaticShader::FRAGMENT_FILE = "E:/CV/OpenGL engine/OpenGL Engine/Shaders/v2/fragment.shader";

StaticShader::StaticShader()
	: Shader()
{
	loadShaders(VERTEX_FILE, FRAGMENT_FILE);
}
StaticShader::~StaticShader()
{
}

void StaticShader::LoadTransformationMatrix(glm::mat4 matrix)
{
	this->SetMatrix4fUniform(m_location_transformationMatrix, matrix);
}

void StaticShader::BindAttributes()
{
	this->bindAttribute(AttributeLocation::Position, "position");
	this->bindAttribute(AttributeLocation::UVs,	"textureCoords");
}
void StaticShader::GetAllUniformLocations()
{
	m_location_transformationMatrix = this->getUniformLocation("transformationMatrix");
}
