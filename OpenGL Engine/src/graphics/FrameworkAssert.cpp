#include "FrameworkAssert.h"

#include <GL/glew.h>
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR)
	{
		std::cout << "[Engine] ClearError called. \n";
	}
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[Engine] OpenGL Error: " << error << " at " << function << " in " << file << " line: " << line << std::endl;
		return false;
	}
	return true;
}