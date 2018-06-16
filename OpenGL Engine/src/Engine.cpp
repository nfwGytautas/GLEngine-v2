#include "Engine.h"

#include "graphics\display\Display.h"
#include "input\InputManager.h"

#include "graphics\shader\StaticShader.h"
#include "graphics\renderer\Renderer.h"
#include "graphics\data manager\DataManager.h"
#include "graphics\data manager\OBJLoader.h"
#include "graphics\display\Camera.h"

#include <iostream>

bool Engine::m_initialized = false;
DataManager* Engine::m_loader = nullptr;
StaticShader* Engine::m_shader = nullptr;
Renderer3D* Engine::m_renderer = nullptr;
Camera* Engine::m_camera = nullptr;

//============================================================================================================================
//ENGINE
//============================================================================================================================
void Engine::Initialize(unsigned int width, unsigned int height, const char* title, bool fullscreen)
{
	Display::CreateDisplay(width, height, title, fullscreen);
	m_loader = new DataManager();
	m_shader = new StaticShader();
	m_renderer = new Renderer3D(m_shader);
	m_camera = new Camera();


	m_initialized = true;
	std::cout << "[Engine] Engine initialized!" << std::endl;
}

void Engine::Terminate()
{
	m_loader->CleanUp();

	delete m_loader;
	delete m_shader;
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
void Engine::Renderer::Prepare()
{
	m_camera->Move();
	m_renderer->Prepare();
}

//TODO: Optimize
void Engine::Renderer::SetLight(Light& light)
{
	m_shader->Bind();
	m_shader->LoadLight(light);
	m_shader->Unbind();
}

void Engine::Renderer::Render(Entity& entity)
{
	m_shader->Bind();
	m_shader->LoadViewMatrix(*m_camera);
	m_renderer->Render(entity, m_shader);
	m_shader->Unbind();
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

Material Engine::Loader::LoadMaterial(std::string filePath)
{
	return Material(LoadTexture(filePath));
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
