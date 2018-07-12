#pragma once
#include <string>
#include <glm\glm.hpp>
#include "algorithm\Algorithm.h"
#include "components\Component.h"
#include "components\Entity.h"
#include "components\EntityBlueprint.h"
#include "components\EntityGroups.h"
#include "components\PreDefinedComponents.h"
#include "input\InputKeys.h"

class StaticShader;
class DynamicShader;
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
		static Entity& createEntity(EntityBlueprint& mBlueprint);
		static EntityBlueprint& newBlueprint();
	};

	class Loader
	{
	public:
		static std::pair<unsigned int, unsigned int> loadMesh(std::string filePath);
		static std::pair<unsigned int, unsigned int> createFlatMesh(unsigned int vertexCount, unsigned int size);
		static unsigned int loadMaterial(std::string filePath);
		static unsigned int loadTexture(std::string filePath);
	};

	struct GameState
	{
		static glm::vec3 skyColor;
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
		static void loadRenderSettings(Entity* entity);
		static void loadDefaultRenderSettings();

		static CMaterial* m_currentMaterial;
		static bool m_usingDefaults;
	};

	class UpdateSystem
	{
	public:
		static void update();
	};

	class GraphicsAPI
	{
	public:
		static void loadTexture(unsigned int id, unsigned int slot = 0);
	};
private:
	static bool m_initialized;
	static DataManager* m_loader;
	static DynamicShader* m_shader;
	static Camera* m_camera;
	static EntityManager* m_entityManager;
	static BatchManager* m_batchManager;

	static float m_EngineFoV;
	static float m_NearRenderPlane;
	static float m_FarRenderPlane;
};