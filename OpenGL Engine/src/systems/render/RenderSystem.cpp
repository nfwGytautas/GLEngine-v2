#include "RenderSystem.h"
#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "..\..\SGEDefs.h"
#include "..\..\Settings.h"
#include "..\..\graphics\GraphicsAssert.h"
#include "..\..\graphics\shader\DynamicShader.h"
#include "..\..\components\EntityManager.h"
#include "..\..\components\Entity.h"
#include "..\..\components\PreDefinedComponents.h"
#include "..\..\data manager\batch\BatchManager.h"
#include "..\..\graphics\api\GraphicsAPI.h"
#include "..\..\graphics\gTypes\gTypes.h"
#include "..\..\graphics\gui\GUI.h"
#include "..\..\maths\Maths.h"


void RenderSystem::render()
{
	//Prepare for rendering
	prepare();	

	//================================================
	//MAIN RENDER CODE
	//================================================
	if (Settings::camera == nullptr)
	{
		std::cout << "[SGE][Renderer] No specified camera!" << std::endl;
		return;
	}

	DynamicShader* loadedShader = nullptr;	

	//========ENTITY========	
	//Render entities
	renderEntities();	
	//======================

	//========Skybox========
	loadedShader = SGE::Instances::instances->shaderManagerInstance->getShader(ShaderNames::Skybox);
	loadedShader->bind();
	//Custom viewport for the skybox
	glm::mat4 skyboxViewPort = glm::mat4(glm::mat3(Settings::camera->viewMatrix));
	loadedShader->setMatrix4fUniform("viewMatrix", skyboxViewPort);
	//Render Skybox
	renderSkybox(loadedShader);
	loadedShader->unbind();
	//======================

	//=========GUI==========
	loadedShader = SGE::Instances::instances->shaderManagerInstance->getShader(ShaderNames::GUI);
	loadedShader->bind();
	//Render GUI
	renderGUI(loadedShader);
	loadedShader->unbind();
	//======================	

	//================================================

	SGE::Instances::instances->entityManagerInstance->postRender();
}

RenderSystem::RenderSystem()
	:m_firstTime(true)
{}

void RenderSystem::prepare()
{
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glCullFace(GL_BACK));
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glDepthFunc(GL_LESS));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCall(glClearColor(Settings::skyColor.r, Settings::skyColor.g, Settings::skyColor.b, 0.0f));

	if(m_firstTime)
	{
		m_GUIQuad = SGE::Instances::instances->dataManagerInstance->create2DQuad(Settings::guiQuad);
		m_skybox = SGE::Instances::instances->dataManagerInstance->createSkybox();
		m_instanceVBO = SGE::Instances::instances->dataManagerInstance->createVBO(instance_data_length * max_instances);
		m_firstTime = false;
	}

	SGE::Instances::instances->entityManagerInstance->preRender();
}
void RenderSystem::loadViewport(DynamicShader* shader)
{
	shader->setMatrix4fUniform("viewMatrix", Settings::camera->viewMatrix);
}
void RenderSystem::loadLights(DynamicShader* shader)
{
	auto lights = SGE::Instances::instances->entityManagerInstance->getEntitiesByGroup(EntityGroups::LightEmittingEntity);
	for (unsigned int i = 0; i < lights.size() && i < SGE_MAX_SUPPORTED_LIGHTS; i++)
	{
		CTransformation& cTransformation = lights[i]->getComponent<CTransformation>();
		CLightEmiter& cLightEmiter = lights[i]->getComponent<CLightEmiter>();
		shader->setVec3Uniform("light.ambient", cLightEmiter.ambient);
		shader->setVec3Uniform("light.diffuse", cLightEmiter.diffuse);
		shader->setVec3Uniform("light.specular", cLightEmiter.specular);
		shader->setVec3Uniform("light.position", cTransformation.position + cLightEmiter.lightOffset);
		//shader->setVec3Uniform("attenuation[" + std::to_string(i) + "]", cLightEmiter.attenuation);
	}
	if(lights.size() <= SGE_MAX_SUPPORTED_LIGHTS)
	{
		shader->setFloatUniform("lightCount", lights.size());
	}
	else
	{
		shader->setFloatUniform("lightCount", SGE_MAX_SUPPORTED_LIGHTS);
	}
	shader->setVec3Uniform("skyColor", Settings::skyColor);
}
void RenderSystem::renderEntities()
{
	DynamicShader* normalShader = SGE::Instances::instances->shaderManagerInstance->getShader(ShaderNames::MultiMaterial);
	DynamicShader* instancedShader = SGE::Instances::instances->shaderManagerInstance->getShader(ShaderNames::InstancedShader);

	std::unordered_map<unsigned int, std::vector<Entity*>> entityBatches;

	for (VAO vao : SGE::Instances::instances->batchManagerInstance->allKnownVAOS())
	{
		entityBatches[vao.ID] = SGE::Instances::instances->batchManagerInstance->getSameVAOEntities(vao.ID);
	}

	std::unordered_map<unsigned int, std::vector<glm::mat4>> transformationMatrixBatches;

	for (auto it : entityBatches)
	{
		transformationMatrixBatches[it.first].reserve(it.second.size());
		for(Entity* entity : it.second)
		{
			transformationMatrixBatches[it.first].push_back(entity->getComponent<CTransformation>().transformationMatrix);
		}
	}	

	setupShader(normalShader);
	setupShader(instancedShader);

	auto renderables = SGE::Instances::instances->entityManagerInstance->getEntitiesByGroup(EntityGroups::Renderable);
	for (Entity* entity : renderables)
	{
		entity->render();
	}

	auto vaos = SGE::Instances::instances->batchManagerInstance->allKnownVAOS();
	for (VAO vao : vaos)
	{
		//Bindint vao
		GraphicsAPI::bindVAO(vao.ID);
		for (auto it : transformationMatrixBatches)
		{
			if (it.first == vao.ID)
			{
				if (it.second.size() > SGE_INSTANCING_THRESHOLD)
				{
					CModel& model = entityBatches[vao.ID][0]->getComponent<CModel>();
					Mesh mesh = model.m_model.getMeshByVAO(vao);
					Material meshMaterial = mesh.getMaterial();
					loadMaterial(instancedShader, &meshMaterial);

					instancedShader->bind();
					GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO));
					GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, it.second.size() * sizeof(float) * 16, &it.second[0]));

					// vertex Attributes
					GLsizei vec4Size = sizeof(glm::vec4);
					GLCall(glEnableVertexAttribArray(AttributeLocation::InstanceSlot1));
					GLCall(glVertexAttribPointer(AttributeLocation::InstanceSlot1, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0));
					GLCall(glEnableVertexAttribArray(AttributeLocation::InstanceSlot2));
					GLCall(glVertexAttribPointer(AttributeLocation::InstanceSlot2, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size)));
					GLCall(glEnableVertexAttribArray(AttributeLocation::InstanceSlot3));
					GLCall(glVertexAttribPointer(AttributeLocation::InstanceSlot3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size)));
					GLCall(glEnableVertexAttribArray(AttributeLocation::InstanceSlot4));
					GLCall(glVertexAttribPointer(AttributeLocation::InstanceSlot4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size)));

					glVertexAttribDivisor(AttributeLocation::InstanceSlot1, 1);
					glVertexAttribDivisor(AttributeLocation::InstanceSlot2, 1);
					glVertexAttribDivisor(AttributeLocation::InstanceSlot3, 1);
					glVertexAttribDivisor(AttributeLocation::InstanceSlot4, 1);
				
					renderInstancedEntities(vao, it.second.size());

					GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
					glBindVertexArray(0);
				}
				else
				{
					normalShader->bind();
					for(unsigned int i = 0; i < entityBatches[vao.ID].size(); i++)
					{
						CModel& model = entityBatches[vao.ID][i]->getComponent<CModel>();
						Mesh mesh = model.m_model.getMeshByVAO(vao);
						Material meshMaterial = mesh.getMaterial();
						loadMaterial(normalShader, &meshMaterial);
						normalShader->setMatrix4fUniform("transformationMatrix", it.second[i]);						
						renderEntity(vao);
					}
				}
				break;
			}
		}
	}

	normalShader->unbind();
}

void RenderSystem::renderEntity(VAO vao)
{
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glEnableVertexAttribArray(AttributeLocation::Position));
	GLCall(glEnableVertexAttribArray(AttributeLocation::UVs));
	GLCall(glEnableVertexAttribArray(AttributeLocation::Normal));
	GLCall(glDrawElements(GL_TRIANGLES, vao.elementCount, GL_UNSIGNED_INT, (void*)0));
	GLCall(glDisableVertexAttribArray(AttributeLocation::Position));
	GLCall(glDisableVertexAttribArray(AttributeLocation::UVs));
	GLCall(glDisableVertexAttribArray(AttributeLocation::Normal));	
}

void RenderSystem::renderInstancedEntities(VAO vao, unsigned int count)
{
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glEnableVertexAttribArray(AttributeLocation::Position));
	GLCall(glEnableVertexAttribArray(AttributeLocation::UVs));
	GLCall(glEnableVertexAttribArray(AttributeLocation::Normal));
	GLCall(glEnableVertexAttribArray(AttributeLocation::InstanceSlot1));
	GLCall(glEnableVertexAttribArray(AttributeLocation::InstanceSlot2));
	GLCall(glEnableVertexAttribArray(AttributeLocation::InstanceSlot3));
	GLCall(glEnableVertexAttribArray(AttributeLocation::InstanceSlot4));
	GLCall(glDrawElementsInstanced(GL_TRIANGLES, vao.elementCount, GL_UNSIGNED_INT, (void*)0, count));
	GLCall(glDisableVertexAttribArray(AttributeLocation::Position));
	GLCall(glDisableVertexAttribArray(AttributeLocation::UVs));
	GLCall(glDisableVertexAttribArray(AttributeLocation::Normal));
	GLCall(glDisableVertexAttribArray(AttributeLocation::InstanceSlot1));
	GLCall(glDisableVertexAttribArray(AttributeLocation::InstanceSlot2));
	GLCall(glDisableVertexAttribArray(AttributeLocation::InstanceSlot3));
	GLCall(glDisableVertexAttribArray(AttributeLocation::InstanceSlot4));
}

void RenderSystem::renderGUI(DynamicShader* shader)
{
	auto guis = SGE::Instances::instances->batchManagerInstance->allKnownGUIs();
	if(guis.size() > 0)
	{
		GLCall(glDisable(GL_DEPTH_TEST));
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GraphicsAPI::bindVAO(m_GUIQuad.ID);
		GLCall(glEnableVertexAttribArray(AttributeLocation::Position));
		for (GUI* gui : guis)
		{
			GraphicsAPI::bindTexture(gui);
			glm::mat4 transformation = Maths::createTransformationMatrix(gui->getPosition(), gui->getRotation(), gui->getScale());
			shader->setMatrix4fUniform("transformationMatrix", transformation);
			GLCall(glDrawArrays(GL_TRIANGLE_STRIP, 0, m_GUIQuad.elementCount));
		}
		GLCall(glDisableVertexAttribArray(AttributeLocation::Position));
		GLCall(glBindVertexArray(0));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		GLCall(glDisable(GL_BLEND));
		GLCall(glEnable(GL_DEPTH_TEST));
	}	
}

void RenderSystem::renderSkybox(DynamicShader* shader)
{
	GLCall(glDepthFunc(GL_LEQUAL));
	GraphicsAPI::bindVAO(std::get<0>(m_skybox));
	GLCall(glEnableVertexAttribArray(AttributeLocation::Position));
	GraphicsAPI::bindCubeMap(std::get<2>(m_skybox));

	GLCall(glDrawArrays(GL_TRIANGLES, 0, std::get<1>(m_skybox)));

	GLCall(glDisableVertexAttribArray(AttributeLocation::Position));
	GLCall(glBindVertexArray(0));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
	GLCall(glDepthFunc(GL_LESS));
}

void RenderSystem::loadRenderSettings(DynamicShader* shader, Entity* entity)
{
	CRenderer cRenderer = entity->getComponent<CRenderer>();
	shader->setFloatUniform("cRenderer_tileCount", (float)cRenderer.tileCount);

	if (cRenderer.multiTexture)
	{
		shader->setBooleanUniform("cRenderer_multiTexture", true);
	}

	if (cRenderer.disableSpecular)
	{
		shader->setBooleanUniform("cRenderer_disableSpecular", true);
	}

	if (cRenderer.hasAtlas)
	{
		shader->setFloatUniform("cRenderer_numberOfRows", (float) cRenderer.atlasRowCount);
		int column = cRenderer.atlasIndex % cRenderer.atlasRowCount;
		float xOffSet = (float)column / (float) cRenderer.atlasRowCount;
		int row = cRenderer.atlasIndex / cRenderer.atlasRowCount;
		float yOffSet = (float)row / (float)cRenderer.atlasRowCount;
		glm::vec2 textureOffset(xOffSet, yOffSet);
		shader->setVec2Uniform("uv_offset", textureOffset);
	}

	if (cRenderer.skyboxReflection)
	{
		shader->setFloatUniform("cRenderer_skyboxReflection", true);
		GraphicsAPI::bindCubeMap(std::get<2>(m_skybox));
	}

	m_usingDefaults = false;
}
void RenderSystem::loadDefaultRenderSettings(DynamicShader* shader)
{
	if (!m_usingDefaults)
	{
		shader->setFloatUniform("cRenderer_tileCount", 1);
		shader->setFloatUniform("cRenderer_numberOfRows", 1);
		shader->setVec2Uniform("uv_offset", glm::vec2(0,0));

		GLCall(glEnable(GL_CULL_FACE));
		GLCall(glCullFace(GL_BACK));

		shader->setBooleanUniform("cRenderer_multiTexture", false);
		shader->setBooleanUniform("cRenderer_disableSpecular", false);
		shader->setFloatUniform("cRenderer_skyboxReflection", false);
	}

	m_usingDefaults = true;
}

void RenderSystem::loadMaterial(DynamicShader* shader, Material* material)
{
	ShadingMap diffuseMap = material->m_shaderMaps[(size_t)ShadingMapType::Diffuse];
	ShadingMap specularMap = material->m_shaderMaps[(size_t)ShadingMapType::Specular];

	if (diffuseMap.textureID != 0)
	{
		GraphicsAPI::bindTexture(diffuseMap.textureID, ShaderLocations::Diffuse);
		shader->setIntUniform(std::string("material.diffuse"), ShaderLocations::Diffuse);
		shader->setBooleanUniform(std::string("material.hasDiffuseMap"), true);
	}
	else
	{
		shader->setBooleanUniform(std::string("material.hasDiffuseMap"), false);
	}
	if (specularMap.textureID != 0)
	{
		GraphicsAPI::bindTexture(specularMap.textureID, ShaderLocations::Specular);
		shader->setIntUniform(std::string("material.specular"), ShaderLocations::Specular);
		shader->setBooleanUniform(std::string("material.hasSpecularMap"), true);
		shader->setFloatUniform(std::string("material.shininess"), material->m_shininess);
	}
	else
	{
		shader->setBooleanUniform(std::string("material.hasSpecularMap"), false);
		shader->setFloatUniform(std::string("material.shininess"), 0);
	}
}

void RenderSystem::setupShader(DynamicShader* shader)
{
	shader->bind();
	//Load camera	
	loadViewport(shader);
	//Load all the lights
	loadLights(shader);
	//Load camera
	shader->setVec3Uniform("cameraPos", Settings::camera->cTransformation->position);
}