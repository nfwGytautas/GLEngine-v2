#include "SGEDefs.h"
#include <iostream>
#include <string>

SGE::Instances::InstanceManager* SGE::Instances::instances;

void SGE::StateControl::_sgeInit()
{
	assert(GraphicsAPI::initialize());

	Instances::instances = new Instances::InstanceManager();	

	InputManager::Mouse::centerCursorPosition();

	#ifdef SGE_GRAPHICS_TECHNOLOGY_OPENGL
	std::cout << "[SGE] OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	#endif // SGE_GRAPHICS_TECHNOLOGY_OPENGL
}

void SGE::StateControl::_sgeTerminate()
{
	Instances::instances->dataManagerInstance->cleanUp();

	delete Instances::instances;

	Display::destroyDisplay();
	std::cout << "[SGE] Engine terminated" << std::endl;
}

void SGE::StateControl::_sgePrepareShaders()
{
	#if SGE_DEVELOPMENT_STATUS == 1
	SGE::Instances::instances->shaderManagerInstance->addShader
	(
		ShaderNames::Entity,
		"E:/CV/OpenGL engine/OpenGL Engine/Shaders/current/vertex.shader",
		"E:/CV/OpenGL engine/OpenGL Engine/Shaders/current/fragment.shader"
	);
	SGE::Instances::instances->shaderManagerInstance->addShader
	(
		ShaderNames::GUI,
		"E:/CV/OpenGL engine/OpenGL Engine/Shaders/current/guiV.shader",
		"E:/CV/OpenGL engine/OpenGL Engine/Shaders/current/guiF.shader"
	);
	SGE::Instances::instances->shaderManagerInstance->addShader
	(
		ShaderNames::Skybox,
		"E:/CV/OpenGL engine/OpenGL Engine/Shaders/current/skyboxV.shader",
		"E:/CV/OpenGL engine/OpenGL Engine/Shaders/current/skyboxF.shader"
	);
	#elif SGE_DEVELOPMENT_STATUS == 0

	std::string path;
	path += "SGE/Shaders/release ";
	path += std::to_string((unsigned int)SGE_VERSION_MAJOR);
	path += ".";
	path += std::to_string((unsigned int)SGE_VERSION_MINOR);
	path += " shader/";


	SGE::Instances::instances->shaderManagerInstance->addShader
	(
		ShaderNames::Entity,
		path + "vertex.shader",
		path + "fragment.shader"
	);
	SGE::Instances::instances->shaderManagerInstance->addShader
	(
		ShaderNames::GUI,
		path + "guiV.shader",
		path + "guiF.shader"
	);
	SGE::Instances::instances->shaderManagerInstance->addShader
	(
		ShaderNames::Skybox,
		path + "skyboxV.shader",
		path + "skyboxF.shader"
	);
	#endif

	_sgeSendProjectionMatrix(SGE::Instances::instances->shaderManagerInstance->getShader(ShaderNames::Entity));
	_sgeSendProjectionMatrix(SGE::Instances::instances->shaderManagerInstance->getShader(ShaderNames::Skybox));
}

void SGE::StateControl::_sgeSendProjectionMatrix(DynamicShader* targetShader)
{
	targetShader->bind();
	targetShader->setMatrix4fUniform("projectionMatrix", Maths::createProjectionMatrix());
	targetShader->unbind();
}

SGE::Instances::InstanceManager::InstanceManager()
	:
	entityManagerInstance(new EntityManager()),
	batchManagerInstance(new BatchManager()),
	dataManagerInstance(new DataManager()),
	shaderManagerInstance(new ShaderManager()),
	eventSystemInstance(new EventSystem()),
	physicsSystemInstance(new PhysicsSystem()),
	renderSystemInstance(new RenderSystem()),
	updateSystemInstance(new UpdateSystem())
{}

SGE::Instances::InstanceManager::~InstanceManager()
{
	entityManagerInstance.reset();
	batchManagerInstance.reset();
	dataManagerInstance.reset();
	shaderManagerInstance.reset();
	eventSystemInstance.reset();
	physicsSystemInstance.reset();
	renderSystemInstance.reset();
	updateSystemInstance.reset();
}