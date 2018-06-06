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
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	GLCall(glClearColor(1, 0, 0, 1));
}

void Renderer3D::Render(Mesh mesh)
{
	GLCall(glBindVertexArray(mesh.GetRenderID()));
	GLCall(glEnableVertexAttribArray(AttributeLocation::Position));
	GLCall(glDrawElements(GL_TRIANGLES, (GLsizei)mesh.GetVertexCount(), GL_UNSIGNED_INT, (void*)0 ));
	GLCall(glDisableVertexAttribArray(AttributeLocation::Position));
	GLCall(glBindVertexArray(0));
}