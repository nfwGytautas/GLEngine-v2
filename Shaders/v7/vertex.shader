#version 400 core

in vec3 position;
in vec2 textureCoordinates;
in vec3 normal;

out vec2 pass_textureCoordinates;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;

//CRenderer component uniforms
uniform float cRenderer_tileCount;
uniform float cRenderer_fakeLighting;

void main(void){
	vec4 worldPosition = transformationMatrix * vec4(position,1.0);
	gl_Position = projectionMatrix * viewMatrix * worldPosition;
	pass_textureCoordinates = textureCoordinates * cRenderer_tileCount;

	vec3 actualNormal = normal;
	if(cRenderer_fakeLighting > 0.5)
	{
		actualNormal = vec3(0.0, 1.0, 0.0);
	}

	surfaceNormal = (transformationMatrix * vec4(actualNormal, 0.0)).xyz; 
	toLightVector = lightPosition - worldPosition.xyz;
	toCameraVector = (inverse(viewMatrix) * vec4(0.0,0.0,0.0,1.0)).xyz - worldPosition.xyz;
}