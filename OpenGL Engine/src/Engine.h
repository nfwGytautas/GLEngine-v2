#pragma once
#include <string>
#include <glm\glm.hpp>
#include "algorithm\Algorithm.h"
#include "components\Entity.h"
#include "components\PreDefinedComponents.h"
#include "input\InputKeys.h"

class StaticShader;
class DataManager;
class Camera;
class EntityManager;
class BatchManager;

class Engine
{
public:
	class Window
	{
	public:
		static bool shouldClose();
		static void vSync(bool option);
	};

	class Input
	{
	public:
		class Keyboard
		{
		public:
			bool isKeyDown(Key key);
		};

		class Mouse
		{
		public:

		};
	};

	class EntityFactory
	{
	public:
		static Entity& createEntity();
	};

	class EntityEditor
	{
	public:
		static void addPositionComponent(Entity& mTarget, glm::vec3 mValue);
		static void addTransformationComponent(Entity& mTarget);
		static void addMeshComponent(Entity& mTarget, std::string mFilePath);
		static void addMaterialComponent(Entity& mTarget, std::string mFilePath, float mShineDamper, float mReflectivity);
		static void addRenderComponent(Entity& mTarget);
		static void addColorComponent(Entity& mTarget, glm::vec3 mValue);
		static void addLightEmiterComponent(Entity& mTarget);
	};

	static void initialize(unsigned int width, unsigned int height, const char* title, bool fullscreen = false);
	static void render();
	static void update();
	static bool isInitialized()
	{
		return m_initialized;
	}
	static void terminate();

private:
	static glm::mat4 createProjectionMatrix();

	class RenderSystem
	{
	public:
		static void render();
	private:
		static void prepare();
		static void loadLights();
		static void renderEntities();

		static CMaterial* m_currentMaterial;
	};

	class UpdateSystem
	{
	public:
		static void update();
	};
private:
	static bool m_initialized;
	static DataManager* m_loader;
	static StaticShader* m_shader;
	static Camera* m_camera;
	static EntityManager* m_entityManager;
	static BatchManager* m_batchManager;

	static float m_EngineFoV;
	static float m_NearRenderPlane;
	static float m_FarRenderPlane;
};