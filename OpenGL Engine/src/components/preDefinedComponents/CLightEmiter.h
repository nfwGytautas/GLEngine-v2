#pragma once
#include "..\Component.h"
//Dependencies
#include "CPosition.h"
#include "CColor.h"

struct CLightEmiter : Component
{
	void init() override;

	CPosition* cPosition;
	CColor* cColor;
	CLightEmiter() {};

	virtual CLightEmiter* clone() { return new CLightEmiter(*this); }
};