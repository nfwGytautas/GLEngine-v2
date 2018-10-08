#pragma once
/*
==========================DISCLAYMER===========================

	This header provides with all the underlying system
pointers and should not be changed or could cause unexpected
behavior. If these pointers are needed then they should be
requested by the engine and not recieved from here. However
if there is a need for them then make sure to not delete them
and leave that to the automatic termination process.

==============================================================

*/
//Engine major version
#define SGE_VERSION_MAJOR 0
//Engine minor version
#define SGE_VERSION_MINOR 3
//Is the engine in development 0(no), 1(yes)
#define SGE_DEVELOPMENT_STATUS 1
//Does the engine support DirectX
#define SGE_DIRECTX_CAPABLE 0

#pragma region SystemDefiner

#ifdef _WIN64

	//Only x64
	#define SGE_SYSTEM_WINDOWS
	#define SGE_SYSTEM_WINDOWS_PROCESSOR 64

#elif _WIN32

	//Only x32
	#define SGE_SYSTEM_WINDOWS
	#define SGE_SYSTEM_WINDOWS_PROCESSOR 32

#elif __APPLE__
#include "TargetConditionals.h"

#if TARGET_IPHONE_SIMULATOR && TARGET_IPHONE_SIMULATOR
	# error "IPhone not supported"

#elif TARGET_OS_IPHONE
	# error "IPhone not supported"

#elif TARGET_OS_MAC
	#define SGE_SYSTEM_APPLE

#else
#   error "Unknown Apple platform"

#endif

#elif __linux__
	#define SGE_SYSTEM_LINUX

#elif __unix__ // all unices not caught above
	#define SGE_SYSTEM_UNIX

#elif defined(_POSIX_VERSION)
	#define SGE_SYSTEM_POSIX

#else
	#error "Unknown compiler"

#endif

#ifdef SGE_SYSTEM_WINDOWS
#if (SGE_DIRECTX_CAPABLE == 1)
	#define SGE_GRAPHICS_TECHNOLOGY_DIRECTX

#elif (SGE_DIRECTX_CAPABLE == 0)
	#define SGE_GRAPHICS_TECHNOLOGY_OPENGL

#endif

#elif
	#define SGE_GRAPHICS_TECHNOLOGY_OPENGL

#endif


#pragma endregion

/*
==============================================================

#defines show current engine limitations
unlike settings these should not be changed.

StateControl functions control the states of all the system
pointers
==============================================================
*/
#define SGE_MAX_SUPPORTED_LIGHTS 4		//Max supported lights by the engine
#define SGE_MAX_INSTANCES 10000			//Max amount of vaos in a single instance
#define SGE_INSTANCING_THRESHOLD 100	//The amount of vaos an instance needs to have in order to be instanced

#define SGE_SHADER_MAP_DIFFUSE_SUPPORT 1
#define SGE_SHADER_MAP_SPECULAR_SUPPORT 1
#define SGE_SHADER_MAP_OPACITY_SUPPORT 0
#define SGE_SHADER_MAP_BUMP_SUPPORT 0
#define SGE_SHADER_MAP_NORMAL_SUPPORT 0
#define SGE_SHADER_MAP_GLOW_SUPPORT 0
#define SGE_SHADER_MAP_REFLECTION_SUPPORT 0

#pragma region INCLUDES

#pragma region GraphicsTechonology

#ifdef SGE_GRAPHICS_TECHNOLOGY_OPENGL
	//OpenGL libraries
	#include <GL\glew.h>
	#include <GLFW\glfw3.h>
	#include <glm\glm.hpp>
#elif SGE_GRAPHICS_TECHNOLOGY_DIRECTX
	//DirectX librariies
#endif

#pragma endregion

//Does not have a managed instance
#include "Settings.h"

//Does not have a managed instance
#include "algorithm\Algorithm.h"

//Does not have a managed instance
#include "maths\Maths.h"

//Does not have a managed instance
#include "utility\Time.h"

//Frustum is managed
#include "utility\Frustum.h"

//Batch, Data, Shader and Input managers are managed
#include "data manager\ManagerSystems.h"

//Display is managed
#include "graphics\GraphicsSystem.h"

//EventSystem is managed
#include "systems\event\EventSystem.h"

//PhysicsSystem is managed
#include "systems\physics\PhysicsSystem.h"

//RenderSystem is managed
#include "systems\render\RenderSystem.h"

//UpdateSystem is managed
#include "systems\update\UpdateSystem.h"

//EntityManager is managed
#include "components\EntityComponentSystem.h"

#pragma endregion

#include <memory>

namespace SGE
{
	namespace Types
	{
		typedef std::shared_ptr<RenderSystem>		Renderer;
		typedef std::shared_ptr<UpdateSystem>		UpdateSystem;
		typedef std::shared_ptr<PhysicsSystem>		Physics;
		typedef std::shared_ptr<DataManager>		DataManager;
	}

	//All SGE instances
	namespace Instances
	{
		class InstanceManager
		{
		public:
			std::shared_ptr<EntityManager>	 entityManagerInstance;
			std::shared_ptr<DataManager>	 dataManagerInstance;
			std::shared_ptr<PhysicsSystem>	 physicsSystemInstance;
			std::shared_ptr<RenderSystem>	 renderSystemInstance;
			std::shared_ptr<UpdateSystem>	 updateSystemInstance;
			std::shared_ptr<EventSystem>	 eventSystemInstance;
			std::shared_ptr<BatchManager>	 batchManagerInstance;
			std::shared_ptr<ShaderManager>	 shaderManagerInstance;
			std::shared_ptr<Frustum>		 frustumInstance;

			InstanceManager();
			~InstanceManager();
		};	

		extern InstanceManager* instances;
	}

	//Instance and other SGE state controls
	namespace StateControl
	{
		//Initializes the engine
		void _sgeInit();
		//Terminates the engine thus deleting all the data
		void _sgeTerminate();
		//Adds shaders depending on SGE status
		void _sgePrepareShaders();
		//Sends a projection matrix to a shader 
		void _sgeSendProjectionMatrix(DynamicShader* targetShader);
		//Creates a projection matrix and stores it into storage file
		void _sgeCreateProjectionMatrix();	
		//Creates the frustum variable
		void _sgeCreateFrustumClass();
	}

}