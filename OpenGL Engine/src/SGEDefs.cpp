#include "SGEDefs.h"
#include <iostream>
#include <string>

#if SGE_DEVELOPMENT_STATUS == 1
#ifdef SGE_SYSTEM_WINDOWS
#pragma message ("warning: You are using the development build of SGE")
#else
#warning ("warning: You are using the development build of SGE")
#endif
#endif

SGE::Instances::InstanceManager* SGE::Instances::instances;

void SGE::StateControl::_sgeInit()
{
	std::cout 
		<< "Simple Graphics Engine: \n "
		<< (SGE_DEVELOPMENT_STATUS == 1 ? "Development build of version " : "Full release of version ")
		<< SGE_VERSION_MAJOR
		<< ":"
		<< SGE_VERSION_MINOR
		<< std::endl;

	assert(GraphicsAPI::initialize());

	Instances::instances = new Instances::InstanceManager();	

	InputManager::Mouse::centerCursorPosition();

	_sgeCreateProjectionMatrix();

	#ifdef SGE_GRAPHICS_TECHNOLOGY_OPENGL
	std::cout << "[SGE] OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	#endif // SGE_GRAPHICS_TECHNOLOGY_OPENGL
}

void SGE::StateControl::_sgeTerminate()
{
	Instances::instances->dataManagerInstance->cleanUp();

	delete Instances::instances;
	delete Settings::frustum;

	Display::destroyDisplay();
	std::cout << "[SGE] Engine terminated" << std::endl;
}

void SGE::StateControl::_sgePrepareShaders()
{
	#if SGE_DEVELOPMENT_STATUS == 1
	SGE::Instances::instances->shaderManagerInstance->addShader
	(
		ShaderNames::Entity,
		"C:/dev/SGE/SGE/Shaders/current/vertex.shader",
		"C:/dev/SGE/SGE/Shaders/current/fragment.shader"
	);
	SGE::Instances::instances->shaderManagerInstance->addShader
	(
		ShaderNames::GUI,
		"C:/dev/SGE/SGE/Shaders/current/guiV.shader",
		"C:/dev/SGE/SGE/Shaders/current/guiF.shader"
	);
	SGE::Instances::instances->shaderManagerInstance->addShader
	(
		ShaderNames::Skybox,
		"C:/dev/SGE/SGE/Shaders/current/skyboxV.shader",
		"C:/dev/SGE/SGE/Shaders/current/skyboxF.shader"
	);
	SGE::Instances::instances->shaderManagerInstance->addShader
	(
		ShaderNames::MultiMaterial,
		"C:/dev/SGE/SGE/Shaders/current/multiMaterialVertex.shader",
		"C:/dev/SGE/SGE/Shaders/current/multiMaterialFragment.shader"
	);
	SGE::Instances::instances->shaderManagerInstance->addShader
	(
		ShaderNames::InstancedShader,
		"C:/dev/SGE/SGE/Shaders/current/instancedV.shader",
		"C:/dev/SGE/SGE/Shaders/current/instancedF.shader"
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
	SGE::Instances::instances->shaderManagerInstance->addShader
	(
		ShaderNames::MultiMaterial,
		path + "multiMaterialVertex.shader",
		path + "multiMaterialFragment.shader"
	);
	SGE::Instances::instances->shaderManagerInstance->addShader
	(
		ShaderNames::InstancedShader,
		path + "instancedV.shader",
		path + "instancedF.shader"
	);
	#endif

	_sgeSendProjectionMatrix(SGE::Instances::instances->shaderManagerInstance->getShader(ShaderNames::Entity));
	_sgeSendProjectionMatrix(SGE::Instances::instances->shaderManagerInstance->getShader(ShaderNames::Skybox));
	_sgeSendProjectionMatrix(SGE::Instances::instances->shaderManagerInstance->getShader(ShaderNames::MultiMaterial));
	_sgeSendProjectionMatrix(SGE::Instances::instances->shaderManagerInstance->getShader(ShaderNames::InstancedShader));
}

void SGE::StateControl::_sgeSendProjectionMatrix(DynamicShader* targetShader)
{
	targetShader->bind();
	targetShader->setMatrix4fUniform("projectionMatrix", Instances::instances->dataManagerInstance->getProjectionMatrix());
	targetShader->unbind();
}

void SGE::StateControl::_sgeCreateProjectionMatrix()
{
	Instances::instances->dataManagerInstance->setProjectionMatrix(Maths::createProjectionMatrix());
}

void SGE::StateControl::_sgeCreateFrustumClass()
{
	Settings::frustum = new Frustum();
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