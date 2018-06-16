#pragma once

#include "algorithm\Algorithm.h"

#include "graphics\renderables\Model.h"
#include "graphics\renderables\Entity.h"
#include "graphics\renderables\Light.h"

#include "input\InputKeys.h"

class StaticShader;
class DataManager;
class Renderer3D;
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
		static void Prepare();
		static void SetLight(Light& light);
		static void Render(Entity& entity);
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
	static Renderer3D* m_renderer;
	static Camera* m_camera;
};