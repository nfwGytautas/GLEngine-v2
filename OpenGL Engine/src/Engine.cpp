#include "Engine.h"

#include "graphics\display\Display.h"
#include "input\InputManager.h"

#include "components\EntityManager.h"

#include "graphics\shader\StaticShader.h"
#include "graphics\shader\TerrainShader.h"
#include "graphics\renderer\MasterRenderer.h"
#include "graphics\data manager\DataManager.h"
#include "graphics\data manager\OBJLoader.h"
#include "graphics\display\Camera.h"

#include <iostream>

bool Engine::m_initialized = false;
DataManager* Engine::m_loader = nullptr;
StaticShader* Engine::m_shader = nullptr;
TerrainShader* Engine::m_terrainShader = nullptr;
MasterRenderer* Engine::m_renderer = nullptr;
Camera* Engine::m_camera = nullptr;
EntityManager* Engine::m_entityManager = nullptr;

//============================================================================================================================
//ENGINE
//============================================================================================================================
void Engine::initialize(unsigned int width, unsigned int height, const char* title, bool fullscreen)
{
	Display::CreateDisplay(width, height, title, fullscreen);
	m_loader = new DataManager();
	m_shader = new StaticShader();
	m_terrainShader = new TerrainShader();
	m_renderer = new MasterRenderer(*m_shader, *m_terrainShader);
	m_camera = new Camera();
	m_entityManager = new EntityManager();


	m_initialized = true;
	std::cout << "[Engine] Engine initialized!" << std::endl;
}

void Engine::update()
{
	if (m_initialized)
	{
		m_camera->Move();
		Display::UpdateDisplay();
		m_entityManager->update(Display::GetDelta());
	}
}

void Engine::terminate()
{
	m_loader->CleanUp();

	delete m_loader;
	delete m_shader;
	delete m_terrainShader;
	delete m_renderer;
	delete m_camera;
	delete m_entityManager;

	Display::DestroyDisplay();

	m_initialized = false;
	std::cout << "[Engine] Engine terminated!" << std::endl;
}

//============================================================================================================================
//WINDOW
//============================================================================================================================
bool Engine::Window::shouldClose()
{
	return Display::Closed();
}

void Engine::Window::vSync(bool option)
{
	Display::SwitchVerticalSync(option);
}

//============================================================================================================================
//RENDERER
//============================================================================================================================
void Engine::Renderer::addEntity(Entity& entity)
{
	m_renderer->ProcessEntity(entity);
}

void Engine::Renderer::addTerrain(Terrain& terrain)
{
	m_renderer->ProcessTerrain(terrain);
}

void Engine::Renderer::render(Light& sun)
{
	m_renderer->Render(sun, *m_camera);
}

//============================================================================================================================
//LOADER
//============================================================================================================================
Mesh Engine::Loader::loadOBJ(std::string filePath)
{
	return OBJLoader::loadOBJ(filePath, *m_loader);
}

Mesh Engine::Loader::loadToVAO(std::vector<float> positions, std::vector<float> textureCoords, std::vector<float> normals, std::vector<unsigned int> indices)
{
	return m_loader->LoadToVAO(positions, textureCoords, normals, indices);
}

Material Engine::Loader::loadMaterial(std::string filePath, float shineDamper, float reflectivity)
{
	return Material(LoadTexture(filePath), shineDamper, reflectivity);
}

unsigned int Engine::Loader::loadTexture(std::string filePath)
{
	return m_loader->LoadTexture(filePath);
}

//============================================================================================================================
//INPUT
//============================================================================================================================
bool Engine::Input::Keyboard::isKeyDown(Key key)
{
	return InputManager::Keyboard::IsKeyDown(key);
}

//============================================================================================================================
//ENTITY FACTORY
//============================================================================================================================
Entity & Engine::EntityFactory::createEntity()
{
	return m_entityManager->addEntity();
}
