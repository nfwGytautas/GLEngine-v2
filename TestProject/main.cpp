#include "Engine.h"

#include <iostream>

int main()
{
	Engine::Initialize(1280, 720, "Game");

	Mesh testMesh = Engine::Loader::LoadOBJ("E:/Test files/nfw/dragon.obj");
	Material testMaterial = Engine::Loader::LoadMaterial("E:/Test files/nfw/dragon.png", 10, 1);

	Model testModel(testMesh, testMaterial);

	Entity testEntity(testModel, glm::vec3(0.0f, 0.0f, -50.0f), 0, 0, 0, 1);
	Light testLight(glm::vec3(0, 0, -20), glm::vec3(1,1,1));

	Engine::Window::VSync(true);
	while (!Engine::Window::ShouldClose())
	{
		testEntity.IncreaseRotation(0.0f, 0.001f, 0.0f);
		Engine::Renderer::AddEntity(testEntity);
		Engine::Renderer::Render(testLight);
		Engine::Window::Update();
	}

	Engine::Terminate();
	return 0;
}