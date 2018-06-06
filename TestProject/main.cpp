#include "Engine.h"

#include <iostream>

int main()
{
	Engine::Initialize(1280, 720, "Game");

	float vertices[] = {
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};

	unsigned int indices[] = {
		0,1,3,
		3,1,2
	};

	Mesh testMesh = Engine::Loader::LoadToVAO(ArrayToVector(vertices), ArrayToVector(indices));

	while (!Engine::ShouldClose())
	{
		Engine::Renderer::Prepare();
		Engine::Renderer::Render(testMesh);


		Engine::Update();
	}

	Engine::Terminate();
	return 0;
}