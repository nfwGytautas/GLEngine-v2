#pragma once

class Mesh;
class Model;

class Renderer3D
{
public:
	Renderer3D();
	~Renderer3D();

	void Prepare();

	void Render(Mesh mesh);
	void Render(Model model);
};

