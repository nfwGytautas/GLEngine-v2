#include "Engine.h"

#include "graphics\display\Display.h"

#include "graphics\shader\StaticShader.h"
#include "graphics\renderer\Renderer.h"
#include "graphics\data manager\DataManager.h"

#include <iostream>

bool Engine::m_initialized = false;
DataManager* Engine::m_loader = nullptr;
Renderer3D* Engine::m_renderer = nullptr;
StaticShader* Engine::m_shader = nullptr;

void Engine::Initialize(unsigned int width, unsigned int height, const char* title, bool fullscreen)
{
	Display::CreateDisplay(width, height, title, fullscreen);
	m_loader = new DataManager();
	m_renderer = new Renderer3D();
	m_shader = new StaticShader();

	m_initialized = true;
	std::cout << "[Engine] Engine initialized!" << std::endl;
}

void Engine::Terminate()
{
	m_initialized = false;

	m_loader->CleanUp();
	delete m_loader;
	delete m_renderer;
	delete m_shader;
	Display::DestroyDisplay();

	std::cout << "[Engine] Engine terminated!" << std::endl;
}

void Engine::Update()
{
	Display::UpdateDisplay();
}

bool Engine::ShouldClose()
{
	return Display::Closed();
}

void Engine::Renderer::Prepare()
{
	m_renderer->Prepare();
}

void Engine::Renderer::Render(Mesh mesh)
{
	m_shader->Bind();
	m_renderer->Render(mesh);
	m_shader->Unbind();
}

void Engine::Renderer::Render(Model model)
{
	m_shader->Bind();
	m_renderer->Render(model);
	m_shader->Unbind();
}

Mesh Engine::Loader::LoadToVAO(std::vector<float> positions, std::vector<float> textureCoords, std::vector<unsigned int> indices)
{
	return m_loader->LoadToVAO(positions, textureCoords, indices);
}

Material Engine::Loader::LoadMaterial(std::string filePath)
{
	return Material(LoadTexture(filePath));
}

unsigned int Engine::Loader::LoadTexture(std::string filePath)
{
	return m_loader->LoadTexture(filePath);
}
