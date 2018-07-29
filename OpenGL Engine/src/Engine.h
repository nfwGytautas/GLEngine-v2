#pragma once
#include <string>
#include <glm\glm.hpp>
#include "Settings.h"
#include "maths\Maths.h"
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
class EntityManager;
class BatchManager;
class RenderSystem;
class UpdateSystem;
class PhysicsSystem;

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
			static bool isMouseKeyDown(MouseKey key);
			static float getScrollY();
			static float getMovedY();
			static float getMovedX();
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
		static std::pair<unsigned int, unsigned int> createHeightMappedMesh(std::string mHeightMapFilePath, float mMaxHeight, unsigned int size, std::vector<std::vector<float>>& mCalculatedHeights);
		static unsigned int loadMaterial(std::string filePath);
		static unsigned int loadTexture(std::string filePath);
	};

	static void initialize(unsigned int width, unsigned int height, const char* title, bool fullscreen = false);
	static void render();
	static void update();
	static bool isInitialized()
	{
		return m_initialized;
	}
	static void terminate();
	static float deltaTime();

	static void setCamera(Entity& mEntity);
	static void markAsGround(Entity& mEntity, std::vector<std::vector<float>>& mHeightMap, float mGroundSize);
private:
	static glm::mat4 createProjectionMatrix();
private:
	static bool m_initialized;
	static DataManager* m_loader;
	static DynamicShader* m_shader;
	static EntityManager* m_entityManager;
	static BatchManager* m_batchManager;
	static RenderSystem* m_renderSystem;
	static UpdateSystem* m_updateSystem;
	static PhysicsSystem* m_physicsSystem;

	static float m_EngineFoV;
	static float m_NearRenderPlane;
	static float m_FarRenderPlane;
};