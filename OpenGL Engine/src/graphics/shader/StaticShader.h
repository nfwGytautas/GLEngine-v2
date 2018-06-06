#pragma once

#include "Shader.h"

class StaticShader : public Shader
{
public:
	StaticShader();
	~StaticShader();
protected:
	void BindAttributes() override; 
private:
	static const char* VERTEX_FILE;
	static const char* FRAGMENT_FILE;
};

