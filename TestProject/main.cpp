#include "Engine.h"

#include <iostream>

int main()
{
	Engine::Initialize(1280, 720, "Game");

	Mesh testMesh = Engine::Loader::LoadOBJ("E:/Test files/nfw/stall.obj");
	Material testMaterial = Engine::Loader::LoadMaterial("E:/Test files/nfw/stallTexture.png");

	Model testModel(testMesh, testMaterial);

	Entity testEntity(testModel, glm::vec3(0.0f, 0.0f, -50.0f), 0, 0, 0, 1);

	Engine::Window::VSync(true);
	while (!Engine::Window::ShouldClose())
	{
		testEntity.IncreaseRotation(0.0f, 0.001f, 0.0f);
		Engine::Renderer::Prepare();
		Engine::Renderer::Render(testEntity);

		Engine::Window::Update();
	}

	Engine::Terminate();
	return 0;
}