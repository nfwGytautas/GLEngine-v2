#version 400

in vec3 position;
out vec3 textureCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main(void){
	textureCoords = position;
	vec4 pos = projectionMatrix * viewMatrix * vec4(position, 1.0); 	
	gl_Position = pos.xyww;
}