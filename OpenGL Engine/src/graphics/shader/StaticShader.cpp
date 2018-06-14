#include "StaticShader.h"

#include "..\gtypes\gTypes.h"
#include "..\..\maths\Maths.h"

const char* StaticShader::VERTEX_FILE = ShaderPath::Vertex;
const char* StaticShader::FRAGMENT_FILE = ShaderPath::Fragment;

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
void StaticShader::LoadProjectionMatrix(glm::mat4 matrix)
{
	this->SetMatrix4fUniform(m_location_projectionMatrix, matrix);
}
void StaticShader::LoadViewMatrix(Camera& camera)
{
	glm::mat4 viewMatrix = Maths::CreateViewMatrix(&camera);
	this->SetMatrix4fUniform(m_location_viewMatrix, viewMatrix);
}

void StaticShader::BindAttributes()
{
	this->bindAttribute(AttributeLocation::Position, "position");
	this->bindAttribute(AttributeLocation::UVs,	"textureCoords");
}
void StaticShader::GetAllUniformLocations()
{
	m_location_transformationMatrix = this->getUniformLocation("transformationMatrix");
	m_location_projectionMatrix = this->getUniformLocation("projectionMatrix");
	m_location_viewMatrix = this->getUniformLocation("viewMatrix");
}
