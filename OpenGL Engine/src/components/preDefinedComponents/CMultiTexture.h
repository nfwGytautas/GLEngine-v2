#pragma once
#include "..\Component.h"
//Dependencies

//Subject to change with full implementation of materials
struct CMultiTexture : Component
{
	unsigned int textureBlendMap;

	unsigned int background;
	unsigned int r;
	unsigned int g;
	unsigned int b;

	CMultiTexture();
	~CMultiTexture();


	virtual CMultiTexture* clone() { return new CMultiTexture(*this); }
};

