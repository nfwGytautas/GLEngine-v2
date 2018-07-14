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
#include "graphics\shader\DynamicShader.h"
#include "graphics\shader\StaticShader.h"
#include "graphics\display\Camera.h"
#include "data manager\BatchManager.h"
#include "data manager\DataManager.h"
#include "data manager\OBJLoader.h"
#include "maths\Maths.h"

bool Engine::m_initialized = false;
DataManager* Engine::m_loader = nullptr;
DynamicShader* Engine::m_shader = nullptr;
Camera* Engine::m_camera = nullptr;
EntityManager* Engine::m_entityManager = nullptr;
BatchManager* Engine::m_batchManager = nullptr;

bool Engine::RenderSystem::m_usingDefaults = false;
CMaterial* Engine::RenderSystem::m_currentMaterial = nullptr;

glm::vec3 Engine::GameState::skyColor = glm::vec3(0.529f, 0.807f, 0.980f);

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
	m_shader = new DynamicShader("E:/CV/OpenGL engine/OpenGL Engine/Shaders/current/vertex.shader", "E:/CV/OpenGL engine/OpenGL Engine/Shaders/current/fragment.shader");
	m_camera = new Camera();
	m_batchManager = new BatchManager();
	m_entityManager = new EntityManager(m_batchManager);	

	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glCullFace(GL_BACK));

	m_shader->bind();
	m_shader->setMatrix4fUniform("projectionMatrix", createProjectionMatrix());
	m_shader->unbind();

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
		UpdateSystem::update();
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
float Engine::deltaTime()
{
	return Display::getDelta();
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

Entity& Engine::EntityFactory::createEntity(EntityBlueprint& mBlueprint)
{
	return m_entityManager->addEntity(mBlueprint);
}

EntityBlueprint& Engine::EntityFactory::newBlueprint()
{
	return m_entityManager->addBlueprint();
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
std::pair<unsigned int, unsigned int> Engine::Loader::createFlatMesh(unsigned int vertexCount, unsigned int size)
{
	unsigned int count = vertexCount * vertexCount;

	std::vector<float> vertices;
	vertices.resize(count * 3);

	std::vector<float> normals;
	normals.resize(count * 3);

	std::vector<float> textureCoords;
	textureCoords.resize(count * 2);

	std::vector<unsigned int> indices;
	indices.resize(6 * (vertexCount - 1) * (vertexCount - 1));

	int vertexIndex = 0;
	for (unsigned int i = 0; i < vertexCount; i++) {
		for (unsigned int j = 0; j < vertexCount; j++) {
			vertices[vertexIndex * 3] = (float)j / ((float)vertexCount - 1) * size;
			vertices[vertexIndex * 3 + 1] = 0;
			vertices[vertexIndex * 3 + 2] = (float)i / ((float)vertexCount - 1) * size;
			normals[vertexIndex * 3] = 0;
			normals[vertexIndex * 3 + 1] = 1;
			normals[vertexIndex * 3 + 2] = 0;
			textureCoords[vertexIndex * 2] = (float)j / ((float)vertexCount - 1);
			textureCoords[vertexIndex * 2 + 1] = (float)i / ((float)vertexCount - 1);
			vertexIndex++;
		}
	}

	int index = 0;
	for (unsigned int gz = 0; gz < vertexCount - 1; gz++) {
		for (unsigned int gx = 0; gx < vertexCount - 1; gx++) {
			int topLeft = (gz * vertexCount) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * vertexCount) + gx;
			int bottomRight = bottomLeft + 1;
			indices[index++] = topLeft;
			indices[index++] = bottomLeft;
			indices[index++] = topRight;
			indices[index++] = topRight;
			indices[index++] = bottomLeft;
			indices[index++] = bottomRight;
		}
	}
	auto result = m_loader->createMesh(vertices, normals, textureCoords, indices);
	m_batchManager->acknowledgeMesh(result.first);
	return result;
}
unsigned int Engine::Loader::loadMaterial(std::string filePath)
{
	auto result = m_loader->loadMaterial(filePath);
	m_batchManager->acknowledgeMaterial(result);
	return result;
}
unsigned int Engine::Loader::loadTexture(std::string filePath)
{
	return m_loader->loadMaterial(filePath);
}

//============================================================================================================================
//RENDER SYSTEM
//============================================================================================================================
void Engine::RenderSystem::render()
{
	//Prepare for rendering
	prepare();
	m_shader->bind();

	//MAIN RENDER CODE
	//================================================
	m_shader->setMatrix4fUniform("viewMatrix", m_camera->viewMatrix());

	//Load all the lights
	loadLights();

	//Render entities
	renderEntities();
	
	//================================================

	m_shader->unbind();
}

void Engine::RenderSystem::prepare()
{
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCall(glClearColor(GameState::skyColor.r, GameState::skyColor.g, GameState::skyColor.b, 1));
}
void Engine::RenderSystem::loadLights()
{
	auto lights = m_entityManager->getEntitiesByGroup(EntityGroups::LightEmittingEntity);
	for (Entity* light : lights)
	{
		m_shader->setVec3Uniform("lightColour", light->getComponent<CColor>().value);
		m_shader->setVec3Uniform("lightPosition", light->getComponent<CPosition>().value);
	}

	m_shader->setVec3Uniform("skyColor", GameState::skyColor);
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
			GraphicsAPI::loadVAO(mesh.m_vaoID);
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
				if (m_currentMaterial == nullptr || *m_currentMaterial != material)
				{
					GraphicsAPI::loadTexture(material.m_textureID);
					m_shader->setFloatUniform("shineDamper", material.shineDamper);
					m_shader->setFloatUniform("reflectivity", material.reflectivity);
					m_currentMaterial = &material;
				}
			}
			else if (entity->hasComponent<CMultiTexture>())
			{
				CMultiTexture pack = entity->getComponent<CMultiTexture>();
				m_shader->setIntUniform("blendMap", 1);
				GraphicsAPI::loadTexture(pack.textureBlendMap, 1);
				m_shader->setIntUniform("backgroundTexture", 2);
				GraphicsAPI::loadTexture(pack.background, 2);
				m_shader->setIntUniform("rTexture", 3);
				GraphicsAPI::loadTexture(pack.r, 3);
				m_shader->setIntUniform("gTexture", 4);
				GraphicsAPI::loadTexture(pack.g, 4);
				m_shader->setIntUniform("bTexture", 5);
				GraphicsAPI::loadTexture(pack.b, 5);
			}
			if (entity->hasComponent<CTransformation>())
			{
				m_shader->setMatrix4fUniform("transformationMatrix", entity->getComponent<CTransformation>().transformationMatrix);
			}
			loadDefaultRenderSettings();
			if (entity->hasComponent<CRenderer>())
			{
				loadRenderSettings(entity);
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

void Engine::RenderSystem::loadRenderSettings(Entity* entity)
{
	CRenderer cRenderer = entity->getComponent<CRenderer>();
	m_shader->setFloatUniform("cRenderer_tileCount", cRenderer.tileCount);

	if(cRenderer.transparent)
	{
		GLCall(glDisable(GL_CULL_FACE));
	}

	if (cRenderer.fakeLighting)
	{
		m_shader->setBooleanUniform("cRenderer_fakeLighting", true);
	}

	if (cRenderer.multiTexture)
	{
		m_shader->setBooleanUniform("cRenderer_multiTexture", true);
	}

	m_usingDefaults = false;
}
void Engine::RenderSystem::loadDefaultRenderSettings()
{
	if (!m_usingDefaults)
	{
		m_shader->setFloatUniform("cRenderer_tileCount", 1);

		GLCall(glEnable(GL_CULL_FACE));
		GLCall(glCullFace(GL_BACK));

		m_shader->setBooleanUniform("cRenderer_fakeLighting", false);
		m_shader->setBooleanUniform("cRenderer_multiTexture", false);
	}

	m_usingDefaults = true;
}
//============================================================================================================================
//UPDATE SYSTEM
//============================================================================================================================
void Engine::UpdateSystem::update()
{
	Display::updateDisplay();
	m_entityManager->refresh();

	//Change to another component
	m_camera->Move();

	updateEntitiesWithInput();

	//Kinda redundant now
	m_entityManager->update(Display::getDelta());
}
void Engine::UpdateSystem::updateEntitiesWithInput()
{
	auto inputEntities = m_entityManager->getEntitiesByGroup(EntityGroups::HasInput);
	for (Entity* e : inputEntities)
	{
		e->getComponent<CInput>().react(InputManager::getKey());
	}
}
//============================================================================================================================
//GRAPHICS API
//============================================================================================================================
void Engine::GraphicsAPI::loadTexture(unsigned int id, unsigned int slot)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, id));
}
void Engine::GraphicsAPI::loadVAO(unsigned int id)
{
	GLCall(glBindVertexArray(id));
}