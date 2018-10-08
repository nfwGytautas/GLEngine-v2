#pragma once
#include "..\Component.h"
//Dependencies
class BoundingObject;

struct CBoundingObject : Component
{
public:
	void preRender() override;

	bool insideFrustum{ false };
private:
	BoundingObject* m_object;
};