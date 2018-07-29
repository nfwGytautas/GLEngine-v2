#pragma once
#include "..\Component.h"
//Dependencies

struct CRenderer : Component
{
	//Amount of times a textured should be repeated on a single mesh
	unsigned int tileCount;
	//Enable or disable back face culling
	bool transparent;
	//If true all normals face upwards from the model
	bool fakeLighting;
	//If true shader uses multitexture textures
	bool multiTexture;
	//If true specular lighting will be disabled
	bool disableSpecular;

	CRenderer() : tileCount(1), transparent(false), fakeLighting(false), multiTexture(false), disableSpecular(false) {}

	virtual CRenderer* clone() { return new CRenderer(*this); }
};