#include "Renderer.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\gtypes\gTypes.h"

#include "..\FrameworkAssert.h"

#include "..\mesh\Mesh.h"

Renderer3D::Renderer3D()
{
}
Renderer3D::~Renderer3D()
{
}


void Renderer3D::Prepare()
{
	GLCall(glClearColor(1, 0, 0, 1));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer3D::Render(Mesh mesh)
{
	GLCall(glBindVertexArray(mesh.GetRenderID()));
	GLCall(glEnableVertexAttribArray(AttributeLocation::Position));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, (GLsizei)mesh.GetVertexCount()));
	GLCall(glDisableVertexAttribArray(AttributeLocation::Position));
	GLCall(glBindVertexArray(0));
}