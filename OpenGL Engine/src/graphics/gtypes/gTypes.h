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
	const char* const Vertex =   "E:/CV/OpenGL engine/OpenGL Engine/Shaders/current/vertex.shader";
	const char* const Fragment = "E:/CV/OpenGL engine/OpenGL Engine/Shaders/current/fragment.shader";

	const char* const TerrainVertex = "E:/CV/OpenGL engine/OpenGL Engine/Shaders/v6/terrainVertex.shader";
	const char* const TerrainFragment = "E:/CV/OpenGL engine/OpenGL Engine/Shaders/v6/terrainFragment.shader";
}