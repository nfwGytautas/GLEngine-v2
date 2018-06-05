#pragma once

#include "algorithm\Algorithm.h"

#include "graphics\mesh\Mesh.h"
#include "graphics\display\Display.h"

#include "graphics\data manager\DataManager.h"
#include "graphics\renderer\Renderer.h"

class Engine
{

public:
	static bool IsInitialized()
	{
		return m_initialized;
	}

	static DataManager& Loader()
	{
		return *m_loader;
	}

	static Renderer3D& Renderer()
	{
		return *m_renderer;
	}

	static void Initialize();
	static void Terminate();

private:
	static bool m_initialized;
	static DataManager* m_loader;
	static Renderer3D* m_renderer;
};