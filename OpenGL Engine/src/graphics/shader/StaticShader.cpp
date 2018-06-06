#include "StaticShader.h"

const char* StaticShader::VERTEX_FILE = "E:/CV/OpenGL engine/OpenGL Engine/Shaders/v0/vertex.shader";
const char* StaticShader::FRAGMENT_FILE = "E:/CV/OpenGL engine/OpenGL Engine/Shaders/v0/fragment.shader";

StaticShader::StaticShader()
	: Shader(VERTEX_FILE, FRAGMENT_FILE)
{
}
StaticShader::~StaticShader()
{
}

void StaticShader::BindAttributes()
{
	this->bindAttribute(0, "position");
}
