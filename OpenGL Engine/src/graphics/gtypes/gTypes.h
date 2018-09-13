#pragma once
#include <string>

//Header containing all the variables used by the graphics engine
namespace AttributeLocation
{
	enum ALoc
	{
		Position = 0,
		UVs = 1,
		Normal = 2,

		InstanceSlot1 = 3,
		InstanceSlot2 = 4,
		InstanceSlot3 = 5,
		InstanceSlot4 = 6,
	};
}

namespace ShaderNames
{
	const char* const Entity = "entity";
	const char* const GUI = "gui";
	const char* const Skybox = "skybox";
	const char* const MultiMaterial = "multiMat";
	const char* const InstancedShader = "instanced";
}

namespace ShaderLocations
{
	enum SLoc
	{
		Diffuse = 0,
		Specular = 1
	};
}