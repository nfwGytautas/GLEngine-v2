#include "Engine.h"
#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\gtc\matrix_transform.hpp>
#include "input\InputManager.h"
#include "components\EntityManager.h"
#include "graphics\gtypes\gTypes.h"
#include "graphics\display\Display.h"
#include "graphics\FrameworkAssert.h"
#include "graphics\shader\StaticShader.h"
#include "graphics\display\Camera.h"
#include "data manager\BatchManager.h"
#include "data manager\DataManager.h"
#include "data manager\OBJLoader.h"

bool Engine::m_initialized = false;
DataManager* Engine::m_loader = nullptr;
StaticShader* Engine::m_shader = nullptr;
Camera* Engine::m_camera = nullptr;
EntityManager* Engine::m_entityManager = nullptr;
BatchManager* Engine::m_batchManager = nullptr;

CMaterial* Engine::RenderSystem::m_currentMaterial = nullptr;

float Engine::m_EngineFoV = 70;
float Engine::m_NearRenderPlane = 0.1f;
float Engine::m_FarRenderPlane = 1000.0f;

//============================================================================================================================
//ENGINE
//============================================================================================================================
void Engine::initialize(unsigned int width, unsigned int height, const char* title, bool fullscreen)
{
	Display::createDisplay(width, height, title, fullscreen);
	m_loader = new DataManager();
	m_shader = new StaticShader();
	m_camera = new Camera();
	m_batchManager = new BatchManager();
	m_entityManager = new EntityManager(m_batchManager);

	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glCullFace(GL_BACK));

	m_shader->Bind();
	m_shader->loadProjectionMatrix(createProjectionMatrix());
	m_shader->Unbind();

	m_initialized = true;
	std::cout << "[Engine] Engine initialized!" << std::endl;
}
void Engine::render()
{
	if (m_initialized)
	{
		RenderSystem::render();		
	}
}
void Engine::update()
{
	if (m_initialized)
	{
		m_camera->Move();
		Display::updateDisplay();
		m_entityManager->refresh();
		m_entityManager->update(Display::getDelta());
	}
}
void Engine::terminate()
{
	m_loader->cleanUp();

	delete m_loader;
	delete m_shader;
	delete m_camera;
	delete m_entityManager;
	delete m_batchManager;

	Display::destroyDisplay();

	m_initialized = false;
	std::cout << "[Engine] Engine terminated!" << std::endl;
}
glm::mat4 Engine::createProjectionMatrix()
{
	glm::mat4 returnMatrix = glm::mat4(1);

	float aspectRatio = (float)Display::getWidth() / (float)Display::getHeight();
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
	return Display::closed();
}
void Engine::Window::vSync(bool option)
{
	Display::switchVerticalSync(option);
}

//============================================================================================================================
//INPUT
//============================================================================================================================
bool Engine::Input::Keyboard::isKeyDown(Key key)
{
	return InputManager::Keyboard::isKeyDown(key);
}

//============================================================================================================================
//ENTITY FACTORY
//============================================================================================================================
Entity& Engine::EntityFactory::createEntity()
{
	return m_entityManager->addEntity();
}

//============================================================================================================================
//LOADER
//============================================================================================================================
std::pair<unsigned int, unsigned int> Engine::Loader::loadMesh(std::string filePath)
{
	auto result = m_loader->loadMesh(filePath);
	m_batchManager->acknowledgeMesh(result.first);
	return result;
}
unsigned int Engine::Loader::loadMaterial(std::string filePath)
{
	auto result = m_loader->loadMaterial(filePath);
	m_batchManager->acknowledgeMaterial(result);
	return result;
}

//============================================================================================================================
//RENDER SYSTEM
//============================================================================================================================
void Engine::RenderSystem::render()
{
	//Prepare for rendering
	prepare();
	m_shader->Bind();

	//MAIN RENDER CODE
	//================================================
	m_shader->loadViewMatrix(*m_camera);

	//Load all the lights
	loadLights();

	//Render entities
	renderEntities();
	
	//================================================

	m_shader->Unbind();
}

void Engine::RenderSystem::prepare()
{
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCall(glClearColor(0, 0.3f, 0.0f, 1));
}
void Engine::RenderSystem::loadLights()
{
	auto lights = m_entityManager->getEntitiesByGroup(EntityGroups::LightEmittingEntity);
	for (Entity* light : lights)
	{
		m_shader->loadLight(*light);
	}
}
void Engine::RenderSystem::renderEntities()
{
	auto knownMeshes = m_batchManager->allKnownMeshes();
	for (unsigned int meshID : knownMeshes)
	{
		auto sameMeshEntities = m_batchManager->getEntityBatch(meshID);
		if(sameMeshEntities.size() != 0)
		{
			auto mesh = sameMeshEntities[0]->getComponent<CMesh>();
			mesh.use();
		}
		else
		{
			continue;
		}

		GLCall(glEnableVertexAttribArray(AttributeLocation::Position));
		GLCall(glEnableVertexAttribArray(AttributeLocation::UVs));
		GLCall(glEnableVertexAttribArray(AttributeLocation::Normal));
		for (Entity* entity : sameMeshEntities)
		{
			if (entity->hasComponent<CMaterial>())
			{
				auto material = entity->getComponent<CMaterial>();
				if (m_currentMaterial == nullptr)
				{
					material.use();
					m_shader->loadShineVariables(material.shineDamper, material.reflectivity);
					m_currentMaterial = &material;
				}
				else if(*m_currentMaterial != material)
				{
					material.use();
					m_shader->loadShineVariables(material.shineDamper, material.reflectivity);
					m_currentMaterial = &material;
				}
			}
			if (entity->hasComponent<CTransformation>())
			{
				m_shader->loadTransformationMatrix(entity->getComponent<CTransformation>().transformationMatrix);
			}
			GLCall(glDrawElements(GL_TRIANGLES, entity->getComponent<CMesh>().vertexCount, GL_UNSIGNED_INT, (void*)0));
		}
		GLCall(glDisableVertexAttribArray(AttributeLocation::Position));
		GLCall(glDisableVertexAttribArray(AttributeLocation::UVs));
		GLCall(glDisableVertexAttribArray(AttributeLocation::Normal));
		GLCall(glBindVertexArray(0));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		m_currentMaterial = nullptr;
	}
}