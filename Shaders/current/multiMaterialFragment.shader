#version 330 core
out vec4 outColor;

in vec3 pass_position;
in vec2 pass_texCoords;
in vec3 pass_normal;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
	float hasDiffuseMap;
	float hasSpecularMap;
};

struct Light
{
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;
uniform float lightCount;

uniform vec3 cameraPos;

//CRenderer component uniforms
uniform float cRenderer_disableSpecular;

void main()
{    
	vec3 ambient = vec3(0, 0, 0);
	vec3 diffuse = vec3(0, 0, 0);
	vec3 specular = vec3(0, 0, 0);

	vec3 norm = normalize(pass_normal);
	vec3 lightDir = normalize(light.position - pass_position);

	if(material.hasDiffuseMap > 0.5)
	{
		ambient = light.ambient * vec3(texture(material.diffuse, pass_texCoords));		
		float diff = max(dot(norm, lightDir), 0.0);
		diffuse = light.diffuse * diff * vec3(texture(material.diffuse, pass_texCoords));
	}
	else
	{
		ambient = light.ambient;
		float diff = max(dot(norm, lightDir), 0.0);
		diffuse = light.diffuse * diff;
	}

	if (material.hasSpecularMap > 0.5)
	{
		vec3 viewDir = normalize(cameraPos - pass_position);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		specular = light.specular * spec * vec3(texture(material.specular, pass_texCoords));
	}

	vec3 result = ambient + diffuse + specular;
    outColor = vec4(result, 1.0);
}