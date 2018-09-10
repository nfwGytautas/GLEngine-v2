#pragma once
#include "..\Component.h"
//Dependencies

struct CRenderer : Component
{
	//Amount of times a textured should be repeated on a single mesh
	unsigned int tileCount;
	//If true shader uses multitexture textures
	bool multiTexture;
	//If true specular lighting will be disabled
	bool disableSpecular;
	//If true then the entity has a textureAtlas
	bool hasAtlas; 
	/* If entity has an atlas, then the index of the texture inside the atlas and the amount of rows in that atlas */ int atlasIndex; int atlasRowCount;
	//If true the entity will reflect skybox fragments
	bool skyboxReflection;

	CRenderer() : tileCount(1), multiTexture(false), disableSpecular(false), hasAtlas(false), atlasIndex(0), atlasRowCount(1), skyboxReflection(false) {}

	virtual CRenderer* clone() { return new CRenderer(*this); }
};