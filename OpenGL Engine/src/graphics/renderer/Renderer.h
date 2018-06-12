#pragma once

class Mesh;
class Model;
class Entity;
class StaticShader;

class Renderer3D
{
public:
	Renderer3D();
	~Renderer3D();

	void Prepare();

	void Render(Mesh mesh);
	void Render(Model model);
	void Render(Entity entity, StaticShader* shader);
};

