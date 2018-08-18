#pragma once
#include "..\..\components\preDefinedComponents\CMesh.h"
#include "..\..\components\preDefinedComponents\CMaterial.h"
#include "..\gui\GUI.h"

class GraphicsAPI
{
public:
	static bool initialize();

	static void bindCubeMap(unsigned int id, unsigned int slot = 0);

	static void bindTexture(unsigned int id, unsigned int slot = 0);
	static void bindTexture(const CMaterial& mMaterial, unsigned int slot = 0);
	static void bindTexture(const GUI* mGui, unsigned int slot = 0);

	static void bindVAO(unsigned int id);
	static void bindVAO(const CMesh& mMesh);

};