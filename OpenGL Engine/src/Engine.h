#pragma once

#include "algorithm\Algorithm.h"

#include "graphics\mesh\Mesh.h"
#include "graphics\material\Material.h"

#include "graphics\renderables\Model.h"
#include "graphics\renderables\Entity.h"

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
		static Mesh LoadToVAO(std::vector<float> positions, std::vector<float> textureCoords, std::vector<unsigned int> indices);
		static Material LoadMaterial(std::string filePath);

		static unsigned int LoadTexture(std::string filePath);
	};

	class Renderer
	{
	public:
		static void Prepare();
		static void Render(Mesh mesh);
		static void Render(Model model);
		static void Render(Entity entity);
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