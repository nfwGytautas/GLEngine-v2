#include "Engine.h"
#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\gtc\matrix_transform.hpp>
#include "input\InputManager.h"
#include "components\EntityManager.h"
#include "graphics\display\Display.h"
#include "graphics\FrameworkAssert.h"
#include "graphics\shader\StaticShader.h"
#include "graphics\data manager\DataManager.h"
#include "graphics\data manager\OBJLoader.h"
#include "graphics\display\Camera.h"

bool Engine::m_initialized = false;
DataManager* Engine::m_loader = nullptr;
StaticShader* Engine::m_shader = nullptr;
Camera* Engine::m_camera = nullptr;
EntityManager* Engine::m_entityManager = nullptr;

float Engine::m_EngineFoV = 70;
float Engine::m_NearRenderPlane = 0.1f;
float Engine::m_FarRenderPlane = 1000.0f;

//============================================================================================================================
//ENGINE
//============================================================================================================================
void Engine::initialize(unsigned int width, unsigned int height, const char* title, bool fullscreen)
{
	Display::CreateDisplay(width, height, title, fullscreen);
	m_loader = new DataManager();
	m_shader = new StaticShader();
	m_camera = new Camera();
	m_entityManager = new EntityManager();

	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glCullFace(GL_BACK));

	m_shader->Bind();
	m_shader->LoadProjectionMatrix(createProjectionMatrix());
	m_shader->Unbind();

	m_initialized = true;
	std::cout << "[Engine] Engine initialized!" << std::endl;
}

void Engine::render()
{
	if (m_initialized)
	{
		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GLCall(glClearColor(0, 0.3f, 0.0f, 1));
		m_shader->Bind();
		//TODO: light and camera into entities with specific components
		m_shader->LoadViewMatrix(*m_camera);
		m_entityManager->draw();
		m_shader->Unbind();
	}
}

void Engine::update()
{
	if (m_initialized)
	{
		m_camera->Move();
		Display::UpdateDisplay();
		m_entityManager->refresh();
		m_entityManager->update(Display::GetDelta());
	}
}

void Engine::terminate()
{
	m_loader->cleanUp();

	delete m_loader;
	delete m_shader;
	delete m_camera;
	delete m_entityManager;

	Display::DestroyDisplay();

	m_initialized = false;
	std::cout << "[Engine] Engine terminated!" << std::endl;
}

glm::mat4 Engine::createProjectionMatrix()
{
	glm::mat4 returnMatrix = glm::mat4(1);

	float aspectRatio = (float)Display::GetWidth() / (float)Display::GetHeight();
	float y_scale = (float)((1.0f / glm::tan(glm::radians(m_EngineFoV / 2.0f))) * aspectRatio);
	float x_scale = y_scale / aspectRatio;
	float frustum_length = m_FarRenderPlane - m_NearRenderPlane;

	returnMatrix[0] = glm::vec4(x_scale, 0, 0, 0);
	returnMatrix[1] = glm::vec4(0, y_scale, 0, 0);
	returnMatrix[2] = glm::vec4(0, 0, -((m_FarRenderPlane + m_NearRenderPlane) / frustum_length), -1);
	returnMatrix[3] = glm::vec4(0, 0, -((2 * m_FarRenderPlane * m_NearRenderPlane) / frustum_length), 0);

	return returnMatrix;
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
//INPUT
//============================================================================================================================
bool Engine::Input::Keyboard::isKeyDown(Key key)
{
	return InputManager::Keyboard::IsKeyDown(key);
}

//============================================================================================================================
//ENTITY FACTORY
//============================================================================================================================
Entity& Engine::EntityFactory::createEntity()
{
	return m_entityManager->addEntity();
}
//============================================================================================================================
//ENTITY EDITOR
//============================================================================================================================
void Engine::EntityEditor::addPositionComponent(Entity& mTarget, glm::vec3 mValue)
{
	mTarget.addComponent<CPosition>(mValue);	
}
void Engine::EntityEditor::addTransformationComponent(Entity& mTarget)
{
	if (!mTarget.hasComponent<CPosition>())
	{
		addPositionComponent(mTarget, glm::vec3(0, 0, 0));
	}
	mTarget.addComponent<CTransformation>(m_shader, 0, 0, 0, 1);
}
void Engine::EntityEditor::addMeshComponent(Entity& mTarget, std::string mFilePath)
{
	m_loader->loadMesh(mTarget, mFilePath);
}
void Engine::EntityEditor::addMaterialComponent(Entity& mTarget, std::string mFilePath, float mShineDamper, float mReflectivity)
{	
	unsigned int materialID = m_loader->loadMaterial(mFilePath);
	mTarget.addComponent<CMaterial>(m_shader, materialID, mShineDamper, mReflectivity);
}
void Engine::EntityEditor::addRenderComponent(Entity& mTarget)
{
	if (!mTarget.hasComponent<CMesh>())
	{
		std::cout << "[Engine] No mesh for rendering!" << std::endl;
		return;
	}
	mTarget.addComponent<CRenderer>();
}
void Engine::EntityEditor::addColorComponent(Entity& mTarget, glm::vec3 mValue)
{
	mTarget.addComponent<CColor>(mValue);
}
void Engine::EntityEditor::addLightEmiterComponent(Entity& mTarget)
{
	if (!mTarget.hasComponent<CPosition>())
	{
		addPositionComponent(mTarget, glm::vec3(100, 100, 100));
	}
	if (!mTarget.hasComponent<CColor>())
	{
		addColorComponent(mTarget, glm::vec3(1, 1, 1));
	}
	mTarget.addComponent<CLightEmiter>(m_shader);
}