#include "Engine.h"

#include "graphics\display\Display.h"
#include "input\InputManager.h"

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

//============================================================================================================================
//ENGINE
//============================================================================================================================
void Engine::Initialize(unsigned int width, unsigned int height, const char* title, bool fullscreen)
{
	Display::CreateDisplay(width, height, title, fullscreen);
	m_loader = new DataManager();
	m_shader = new StaticShader();
	m_terrainShader = new TerrainShader();
	m_renderer = new MasterRenderer(*m_shader, *m_terrainShader);
	m_camera = new Camera();


	m_initialized = true;
	std::cout << "[Engine] Engine initialized!" << std::endl;
}

void Engine::Terminate()
{
	m_loader->CleanUp();

	delete m_loader;
	delete m_shader;
	delete m_terrainShader;
	delete m_renderer;
	delete m_camera;

	Display::DestroyDisplay();

	m_initialized = false;
	std::cout << "[Engine] Engine terminated!" << std::endl;
}

//============================================================================================================================
//WINDOW
//============================================================================================================================
void Engine::Window::Update()
{
	m_camera->Move();
	Display::UpdateDisplay();
}

bool Engine::Window::ShouldClose()
{
	return Display::Closed();
}

void Engine::Window::VSync(bool option)
{
	Display::SwitchVerticalSync(option);
}

//============================================================================================================================
//RENDERER
//============================================================================================================================
void Engine::Renderer::AddEntity(Entity& entity)
{
	m_renderer->ProcessEntity(entity);
}

void Engine::Renderer::AddTerrain(Terrain& terrain)
{
	m_renderer->ProcessTerrain(terrain);
}

void Engine::Renderer::Render(Light& sun)
{
	m_renderer->Render(sun, *m_camera);
}

//============================================================================================================================
//LOADER
//============================================================================================================================
Mesh Engine::Loader::LoadOBJ(std::string filePath)
{
	return OBJLoader::LoadOBJ(filePath, *m_loader);
}

Mesh Engine::Loader::LoadToVAO(std::vector<float> positions, std::vector<float> textureCoords, std::vector<float> normals, std::vector<unsigned int> indices)
{
	return m_loader->LoadToVAO(positions, textureCoords, normals, indices);
}

Material Engine::Loader::LoadMaterial(std::string filePath, float shineDamper, float reflectivity)
{
	return Material(LoadTexture(filePath), shineDamper, reflectivity);
}

unsigned int Engine::Loader::LoadTexture(std::string filePath)
{
	return m_loader->LoadTexture(filePath);
}

//============================================================================================================================
//INPUT
//============================================================================================================================
bool Engine::Input::Keyboard::IsKeyDown(Key key)
{
	return InputManager::Keyboard::IsKeyDown(key);
}
