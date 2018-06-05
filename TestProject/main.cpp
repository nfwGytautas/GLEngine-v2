#include "Engine.h"

#include <iostream>

int main()
{
	Engine::Initialize();
	Display::CreateDisplay(1280,720, "Game");

	float vertices[] = {
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	Mesh testMesh = Engine::Loader().LoadToVAO(ArrayToVector<float>(vertices));

	while (!Display::Closed())
	{
		Engine::Renderer().Prepare();
		Engine::Renderer().Render(testMesh);


		Display::UpdateDisplay();
	}

	Engine::Terminate();
	Display::DestroyDisplay();

	return 0;
}