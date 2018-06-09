#pragma once

#ifdef NFW_DLL_EXPORT
#	define NFW_API __declspec(dllexport)
#else
#	define NFW_API __declspec(dllimport)
#endif


#include "algorithm\Algorithm.h"

#include "graphics\mesh\Mesh.h"
#include "graphics\material\Material.h"

#include "graphics\renderables\Model.h"

class StaticShader;
class DataManager;
class Renderer3D;

class Engine
{

public:
	class Loader
	{
	public:
		NFW_API static Mesh LoadToVAO(std::vector<float> positions, std::vector<float> textureCoords, std::vector<unsigned int> indices);
		NFW_API static Material LoadMaterial(std::string filePath);

		NFW_API static unsigned int LoadTexture(std::string filePath);
	};

	class Renderer
	{
	public:
		NFW_API static void Prepare();
		NFW_API static void Render(Mesh mesh);
		NFW_API static void Render(Model model);
	};

	NFW_API static bool IsInitialized()
	{
		return m_initialized;
	}

	NFW_API static void Update();
	NFW_API static bool ShouldClose();

	NFW_API static void Initialize(unsigned int width, unsigned int height, const char* title, bool fullscreen = false);
	NFW_API static void Terminate();

private:
	static bool m_initialized;
	static DataManager* m_loader;
	static Renderer3D* m_renderer;
	static StaticShader* m_shader;
};