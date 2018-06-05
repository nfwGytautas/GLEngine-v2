#pragma once

class Mesh;

class Renderer3D
{
public:
	Renderer3D();
	~Renderer3D();

	void Prepare();

	void Render(Mesh mesh);
};

