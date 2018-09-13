#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;
layout (location = 3) in mat4 transformationMatrix;

out vec3 pass_position;
out vec2 pass_texCoords;
out vec3 pass_normal;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	pass_position = vec3(transformationMatrix * vec4(position, 1.0));
	pass_texCoords = texCoords;
	pass_normal = mat3(transpose(inverse(transformationMatrix))) * normal;
	gl_Position = projectionMatrix * viewMatrix * vec4(pass_position, 1.0);
}