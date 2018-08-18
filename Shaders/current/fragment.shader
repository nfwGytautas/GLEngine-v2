#version 400 core

in vec3 reflectionPosition;
in vec3 reflectionNormal;
in vec2 pass_textureCoordinates;
in vec3 surfaceNormal;
in vec3 toLightVector[4];
in vec3 toCameraVector;
in float visibility;

out vec4 out_Color;

uniform samplerCube skybox;
uniform sampler2D material;

uniform sampler2D blendMap;
uniform sampler2D backgroundTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;

uniform float lightCount;
uniform vec3 lightColour[4];
uniform vec3 attenuation[4];
uniform float shineDamper;
uniform float reflectivity;
uniform vec3 skyColor;
uniform vec3 cameraPos;

//CRenderer component uniforms
uniform float cRenderer_tileCount;
uniform float cRenderer_multiTexture;
uniform float cRenderer_disableSpecular;
uniform float cRenderer_skyboxReflection;

void main(void){
	vec4 totalColor;
	vec2 tiledCoords = pass_textureCoordinates * cRenderer_tileCount;	
	if(cRenderer_multiTexture > 0.5)
	{
		vec4 blendMapColor = texture(blendMap, pass_textureCoordinates);
		float backTextureAmount = 1 - (blendMapColor.r + blendMapColor.g + blendMapColor.b);
		vec4 backgroundTextureColor = texture(backgroundTexture, tiledCoords) * backTextureAmount;
		vec4 rTextureColor = texture(rTexture, tiledCoords) * blendMapColor.r;
		vec4 gTextureColor = texture(gTexture, tiledCoords) * blendMapColor.g;
		vec4 bTextureColor = texture(bTexture, tiledCoords) * blendMapColor.b;

		totalColor = backgroundTextureColor + rTextureColor + gTextureColor + bTextureColor;
	}
	else
	{
		if (cRenderer_skyboxReflection > 0.5)
		{
			vec3 viewDirection = normalize(reflectionPosition - cameraPos);
			vec3 reflectionVector = reflect(viewDirection, normalize(reflectionNormal));
			totalColor = vec4(texture(skybox, reflectionVector).rgb, 1.0);
		}	
		else
		{
			totalColor = texture(material, pass_textureCoordinates);
		}
	
		if(totalColor.a < 0.5)
		{
			discard;
		}
	}

	vec3 unitNormal  = normalize(surfaceNormal);
	vec3 unitVectorToCamera = normalize(toCameraVector);

	vec3 totalDiffuse = vec3(0.0);
	vec3 totalSpecular = vec3(0.0);

	for(int i = 0; i < lightCount; i++)
	{
		float distance = length(toLightVector[i]);
		float attFactor = attenuation[i].x + (attenuation[i].y * distance) + (attenuation[i].z * distance * distance);
		vec3 unitLightVector = normalize(toLightVector[i]);	
		float nDot1 = dot(unitNormal, unitLightVector);
		float brightness = max(nDot1, 0.0);		
		vec3 lightDirection = -unitLightVector;
		vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
		float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
		specularFactor = max(specularFactor, 0.0);
		float dampedFactor = pow(specularFactor, shineDamper);
		totalDiffuse = totalDiffuse + (brightness * lightColour[i]) / attFactor;
		totalSpecular = totalSpecular + (dampedFactor * reflectivity * lightColour[i]) / attFactor;
	}
	totalDiffuse = max(totalDiffuse, 0.2);	

	if(cRenderer_disableSpecular > 0.5)
	{
		out_Color = vec4(totalDiffuse, 1.0) * totalColor;
	}
	else 
	{
		out_Color = vec4(totalDiffuse, 1.0) * totalColor + vec4(totalSpecular, 1.0);
	}

	out_Color = mix(vec4(skyColor, 1.0), out_Color, visibility);
}