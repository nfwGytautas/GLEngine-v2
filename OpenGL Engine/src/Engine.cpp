#include "Engine.h"
#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\gtc\matrix_transform.hpp>
#include "graphics\api\GraphicsAPI.h"
#include "graphics\display\Display.h"
#include "input\InputManager.h"
#include "components\EntityManager.h"
#include "graphics\gtypes\gTypes.h"
#include "graphics\FrameworkAssert.h"
#include "graphics\shader\DynamicShader.h"
#include "graphics\display\Camera.h"
#include "data manager\BatchManager.h"
#include "data manager\DataManager.h"
#include "data manager\OBJLoader.h"
#include "maths\Maths.h"
#include "systems\render\RenderSystem.h"
#include "systems\update\UpdateSystem.h"
#include "systems\physics\PhysicsSystem.h"

bool Engine::m_initialized = false;
DataManager* Engine::m_loader = nullptr;
DynamicShader* Engine::m_shader = nullptr;
Camera* Engine::m_camera = nullptr;
EntityManager* Engine::m_entityManager = nullptr;
BatchManager* Engine::m_batchManager = nullptr;
RenderSystem* Engine::m_renderSystem = nullptr;
UpdateSystem* Engine::m_updateSystem = nullptr;
PhysicsSystem* Engine::m_physicsSystem = nullptr;

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
	m_renderSystem = new RenderSystem(m_shader, m_entityManager, m_batchManager);
	m_renderSystem->selectViewport(m_camera);
	m_physicsSystem = new PhysicsSystem(m_entityManager);
	m_updateSystem = new UpdateSystem(m_entityManager, m_physicsSystem);
	m_updateSystem->selectViewport(m_camera);

	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glCullFace(GL_BACK));

	m_shader->bind();
	m_shader->setMatrix4fUniform("projectionMatrix", createProjectionMatrix());
	m_shader->unbind();

	m_initialized = true;
	std::cout << "[Engine] Engine initialized!" << std::endl;
}
void Engine::terminate()
{
	m_loader->cleanUp();

	delete m_loader;
	delete m_shader;
	delete m_camera;
	delete m_entityManager;
	delete m_batchManager;
	delete m_renderSystem;
	delete m_physicsSystem;
	delete m_updateSystem;

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
float Engine::deltaTime()
{
	return Display::getDelta();
}
void Engine::render()
{
	if (m_initialized)
	{
		m_renderSystem->render();
	}
}
void Engine::update()
{
	if (m_initialized)
	{
		m_updateSystem->update();
	}
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