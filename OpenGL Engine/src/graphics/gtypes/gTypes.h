#pragma once

//Header containing all the variables used by the graphics engine
namespace AttributeLocation
{
	enum ALoc
	{
		Position = 0,
		UVs = 1,
		Normal = 2
	};
}

namespace ShaderPath
{
	const char* const Vertex =   "E:/CV/OpenGL engine/OpenGL Engine/Shaders/v5/vertex.shader";
	const char* const Fragment = "E:/CV/OpenGL engine/OpenGL Engine/Shaders/v5/fragment.shader";
}