#include "Engine.h"

#include <iostream>

bool Engine::m_initialized = false;
DataManager* Engine::m_loader = nullptr;
Renderer3D* Engine::m_renderer = nullptr;

void Engine::Initialize()
{
	m_initialized = true;

	m_loader = new DataManager();
	m_renderer = new Renderer3D();

	std::cout << "[Engine] Engine initialized!" << std::endl;
}

void Engine::Terminate()
{
	m_initialized = false;

	m_loader->CleanUp();
	delete m_loader;
	delete m_renderer;

	std::cout << "[Engine] Engine terminated!" << std::endl;
}
