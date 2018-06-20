#pragma once

#include "algorithm\Algorithm.h"
#include "components\Entity.h"
#include "components\PreDefinedComponents.h"
#include "input\InputKeys.h"

class StaticShader;
class TerrainShader;
class DataManager;
class MasterRenderer;
class Camera;
class EntityManager;

class Engine
{
public:
	class Loader
	{
	public:
		static Mesh loadOBJ(std::string filePath);
		static Mesh loadToVAO(std::vector<float> positions, std::vector<float> textureCoords, std::vector<float> normals, std::vector<unsigned int> indices);
		//TODO: Change this so that the engine would analyze a material file and figure out all the needed variables itself
		static Material loadMaterial(std::string filePath, float shineDamper = 1, float reflectivity = 0);

		static unsigned int loadTexture(std::string filePath);
	};

	class Renderer
	{
	public:
		static void addEntity(Entity& entity);
		static void addTerrain(Terrain& terrain);
		static void render(Light& sun);
	};

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

	static void initialize(unsigned int width, unsigned int height, const char* title, bool fullscreen = false);
	static void update();
	static bool isInitialized()
	{
		return m_initialized;
	}
	static void terminate();

private:
	static bool m_initialized;
	static DataManager* m_loader;
	static StaticShader* m_shader;
	static TerrainShader* m_terrainShader;
	static MasterRenderer* m_renderer;
	static Camera* m_camera;
	static EntityManager* m_entityManager;
};