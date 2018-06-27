#include "StaticShader.h"
#include "..\..\components\Entity.h"
#include "..\..\components\PreDefinedComponents.h"
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

void StaticShader::loadTransformationMatrix(glm::mat4 matrix)
{
	this->SetMatrix4fUniform(m_location_transformationMatrix, matrix);
}
void StaticShader::loadProjectionMatrix(glm::mat4 matrix)
{
	this->SetMatrix4fUniform(m_location_projectionMatrix, matrix);
}
void StaticShader::loadViewMatrix(Camera& camera)
{
	glm::mat4 viewMatrix = Maths::CreateViewMatrix(&camera);
	this->SetMatrix4fUniform(m_location_viewMatrix, viewMatrix);
}
void StaticShader::loadLight(Entity& mLight)
{
	glm::vec3 position = mLight.getComponent<CPosition>().value;
	glm::vec3 color = mLight.getComponent<CColor>().value;
	this->SetVec3Uniform(m_location_lightPosition, position);
	this->SetVec3Uniform(m_location_lightColor, color);
}
void StaticShader::loadShineVariables(float damper, float reflectivity)
{
	this->SetFloatUniform(m_location_shineDamper, damper);
	this->SetFloatUniform(m_location_reflectivity, reflectivity);
}

void StaticShader::BindAttributes()
{
	this->bindAttribute(AttributeLocation::Position, "position");
	this->bindAttribute(AttributeLocation::UVs,	"textureCoords");
	this->bindAttribute(AttributeLocation::Normal, "normal");
}
void StaticShader::GetAllUniformLocations()
{
	m_location_transformationMatrix = this->getUniformLocation("transformationMatrix");
	m_location_projectionMatrix = this->getUniformLocation("projectionMatrix");
	m_location_viewMatrix = this->getUniformLocation("viewMatrix");
	m_location_lightPosition = this->getUniformLocation("lightPosition");
	m_location_lightColor = this->getUniformLocation("lightColour");
	m_location_shineDamper = this->getUniformLocation("shineDamper");
	m_location_reflectivity = this->getUniformLocation("reflectivity");
}
