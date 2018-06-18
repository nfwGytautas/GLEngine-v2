#include "TerrainShader.h"

#include "..\gtypes\gTypes.h"
#include "..\..\maths\Maths.h"

#include "..\renderables\Light.h"

const char* TerrainShader::VERTEX_FILE = ShaderPath::TerrainVertex;
const char* TerrainShader::FRAGMENT_FILE = ShaderPath::TerrainFragment;

TerrainShader::TerrainShader()
	: Shader()
{
	loadShaders(VERTEX_FILE, FRAGMENT_FILE);
}
TerrainShader::~TerrainShader()
{
}

void TerrainShader::LoadTransformationMatrix(glm::mat4 matrix)
{
	this->SetMatrix4fUniform(m_location_transformationMatrix, matrix);
}
void TerrainShader::LoadProjectionMatrix(glm::mat4 matrix)
{
	this->SetMatrix4fUniform(m_location_projectionMatrix, matrix);
}
void TerrainShader::LoadViewMatrix(Camera& camera)
{
	glm::mat4 viewMatrix = Maths::CreateViewMatrix(&camera);
	this->SetMatrix4fUniform(m_location_viewMatrix, viewMatrix);
}
void TerrainShader::LoadLight(Light& light)
{
	this->SetVec3Uniform(m_location_lightPosition, light.GetPosition());
	this->SetVec3Uniform(m_location_lightColor, light.GetColor());
}
void TerrainShader::LoadShineVariables(float damper, float reflectivity)
{
	this->SetFloatUniform(m_location_shineDamper, damper);
	this->SetFloatUniform(m_location_reflectivity, reflectivity);
}

void TerrainShader::BindAttributes()
{
	this->bindAttribute(AttributeLocation::Position, "position");
	this->bindAttribute(AttributeLocation::UVs, "textureCoords");
	this->bindAttribute(AttributeLocation::Normal, "normal");
}
void TerrainShader::GetAllUniformLocations()
{
	m_location_transformationMatrix = this->getUniformLocation("transformationMatrix");
	m_location_projectionMatrix = this->getUniformLocation("projectionMatrix");
	m_location_viewMatrix = this->getUniformLocation("viewMatrix");
	m_location_lightPosition = this->getUniformLocation("lightPosition");
	m_location_lightColor = this->getUniformLocation("lightColour");
	m_location_shineDamper = this->getUniformLocation("shineDamper");
	m_location_reflectivity = this->getUniformLocation("reflectivity");
}