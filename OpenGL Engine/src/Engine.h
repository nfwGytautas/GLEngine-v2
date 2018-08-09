#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <glm\glm.hpp>
#include "SGEDefs.h"
#include "Settings.h"
#include "maths\Maths.h"
#include "algorithm\Algorithm.h"
#include "components\Component.h"
#include "components\Entity.h"
#include "components\EntityBlueprint.h"
#include "components\EntityGroups.h"
#include "components\PreDefinedComponents.h"
#include "input\InputKeys.h"
#include "graphics\gui\GUI.h"

class StaticShader;
class DynamicShader;
class DataManager;
class EntityManager;
class BatchManager;
class RenderSystem;
class UpdateSystem;
class PhysicsSystem;
class EventSystem;

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
		static std::pair<unsigned int, unsigned int> createHeightMappedMesh(std::string mHeightMapFilePath, float mMaxHeight, unsigned int size, continuous2DArray<float>& mCalculatedHeights);
		static GUI loadGUI(std::string filePath, glm::vec2 mPosition, float mRotation, glm::vec2 mScale);
		static unsigned int loadMaterial(std::string filePath);
		static unsigned int loadTexture(std::string filePath);
	};
	class Systems
	{
	public:
		class Physics
		{
		public:
			static float heightAtPoint(float X, float Z);
		};

		class Event
		{
		public:
			static void subscribe(const EventType& mType, CInput* mInput);
		};
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
	static void markAsGround(Entity& mEntity, continuous2DArray<float>& mHeightMap, float mGroundSize);
private:
	static glm::mat4 createProjectionMatrix();
private:

	static bool m_initialized;
	static DataManager* m_loader;
	static std::unordered_map<std::string, DynamicShader*> m_shaders;
	static EntityManager* m_entityManager;
	static BatchManager* m_batchManager;
	static RenderSystem* m_renderSystem;
	static UpdateSystem* m_updateSystem;
	static PhysicsSystem* m_physicsSystem;
	static EventSystem* m_eventSystem;

	static float m_EngineFoV;
	static float m_NearRenderPlane;
	static float m_FarRenderPlane;
};