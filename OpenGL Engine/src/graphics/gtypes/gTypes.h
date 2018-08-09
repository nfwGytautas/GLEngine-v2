#pragma once
#include <string>

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

namespace ShaderNames
{
	const char* const Entity = "entity";
	const char* const GUI = "gui";
}