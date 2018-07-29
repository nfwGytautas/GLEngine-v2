#pragma once

namespace EntityGroups
{
	enum EGroups : size_t
	{
		StaticEntity = 0,
		DynamicEntity = 1,
		LightEmittingEntity = 2,
		HasInput = 3,
		HasPhysics = 4,
		Camera = 5,
		HasHook = 6,
		IsGround = 7
	};
}