#pragma once

#include "algorithm\Algorithm.h"

#include "components\Entity.h"

//This will be deleted as they are entities with specific components
#include "graphics\renderables\Model.h"
#include "graphics\renderables\Light.h"
#include "graphics\renderables\Terrain.h"

#include "input\InputKeys.h"

class StaticShader;
class TerrainShader;
class DataManager;
class MasterRenderer;
class Camera;

class Engine
{
public:
	class Loader
	{
	public:
		static Mesh LoadOBJ(std::string filePath);
		static Mesh LoadToVAO(std::vector<float> positions, std::vector<float> textureCoords, std::vector<float> normals, std::vector<unsigned int> indices);
		//TODO: Change this so that the engine would analyze a material file and figure out all the needed variables itself
		static Material LoadMaterial(std::string filePath, float shineDamper = 1, float reflectivity = 0);

		static unsigned int LoadTexture(std::string filePath);
	};

	class Renderer
	{
	public:
		static void AddEntity(Entity& entity);
		static void AddTerrain(Terrain& terrain);
		static void Render(Light& sun);
	};

	class Window
	{
	public:
		static void Update();
		static bool ShouldClose();
		static void VSync(bool option);
	};

	class Input
	{
	public:
		class Keyboard
		{
		public:
			bool IsKeyDown(Key key);
		};

		class Mouse
		{
		public:

		};
	};

	static bool IsInitialized()
	{
		return m_initialized;
	}
	static void Initialize(unsigned int width, unsigned int height, const char* title, bool fullscreen = false);
	static void Terminate();

private:
	static bool m_initialized;
	static DataManager* m_loader;
	static StaticShader* m_shader;
	static TerrainShader* m_terrainShader;
	static MasterRenderer* m_renderer;
	static Camera* m_camera;
};