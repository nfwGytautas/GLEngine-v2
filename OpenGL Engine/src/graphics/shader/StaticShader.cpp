#include "StaticShader.h"

#include "..\gtypes\gTypes.h"

const char* StaticShader::VERTEX_FILE = "E:/CV/OpenGL engine/OpenGL Engine/Shaders/v1/vertex.shader";
const char* StaticShader::FRAGMENT_FILE = "E:/CV/OpenGL engine/OpenGL Engine/Shaders/v1/fragment.shader";

StaticShader::StaticShader()
	: Shader(VERTEX_FILE, FRAGMENT_FILE)
{
}
StaticShader::~StaticShader()
{
}

void StaticShader::BindAttributes()
{
	this->bindAttribute(AttributeLocation::Position, "position");
	this->bindAttribute(AttributeLocation::UVs,	"textureCoords");
}
