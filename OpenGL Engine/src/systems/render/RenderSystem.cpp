#include "RenderSystem.h"
#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "..\..\SGEDefs.h"
#include "..\..\Settings.h"
#include "..\..\graphics\FrameworkAssert.h"
#include "..\..\graphics\shader\DynamicShader.h"
#include "..\..\components\EntityManager.h"
#include "..\..\components\Entity.h"
#include "..\..\components\PreDefinedComponents.h"
#include "..\..\data manager\BatchManager.h"
#include "..\..\graphics\api\GraphicsAPI.h"
#include "..\..\graphics\gTypes\gTypes.h"
#include "..\..\graphics\gui\GUI.h"
#include "..\..\maths\Maths.h"

void RenderSystem::render()
{
	//Prepare for rendering
	prepare();	
	
	//MAIN RENDER CODE
	//================================================
	if (Settings::camera == nullptr)
	{
		std::cout << "[Engine][Renderer] No specified camera!" << std::endl;
		return;
	}

	//========ENTITY========
	//Load camera
	(*m_shaders)[ShaderNames::Entity]->bind();
	loadViewport(ShaderNames::Entity);
	//Load all the lights
	loadLights(ShaderNames::Entity);
	//Render entities
	renderEntities();
	(*m_shaders)[ShaderNames::Entity]->unbind();
	//======================

	//=========GUI==========
	(*m_shaders)[ShaderNames::GUI]->bind();
	//Render GUI
	renderGUI();
	(*m_shaders)[ShaderNames::GUI]->unbind();
	//======================

	//================================================

	
}

RenderSystem::RenderSystem(std::unordered_map<std::string, DynamicShader*>* mShaders, EntityManager* mEntityManager, BatchManager* mBatchManager, std::pair<unsigned int, unsigned int> mGUIQuad)
	: m_shaders(mShaders), m_entityManager(mEntityManager), m_batchManager(mBatchManager), m_GUIQuad(mGUIQuad)
{
}

void RenderSystem::prepare()
{
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCall(glClearColor(Settings::skyColor.r, Settings::skyColor.g, Settings::skyColor.b, 0.0f));
}
void RenderSystem::loadViewport(std::string mShader)
{
	(*m_shaders)[mShader]->setMatrix4fUniform("viewMatrix", Settings::camera->viewMatrix);
}
void RenderSystem::loadLights(std::string mShader)
{
	auto lights = m_entityManager->getEntitiesByGroup(EntityGroups::LightEmittingEntity);
	for (unsigned int i = 0; i < lights.size() && i < SGE_MAX_SUPPORTED_LIGHTS; i++)
	{
		CColor& cColor = lights[i]->getComponent<CColor>();
		CTransformation& cTransformation = lights[i]->getComponent<CTransformation>();
		CLightEmiter& cLightEmiter = lights[i]->getComponent<CLightEmiter>();
		(*m_shaders)[mShader]->setVec3Uniform("lightColour[" + std::to_string(i) + "]", cColor.value);
		(*m_shaders)[mShader]->setVec3Uniform("lightPosition[" + std::to_string(i) + "]", cTransformation.position + cLightEmiter.lightOffset);
		(*m_shaders)[mShader]->setVec3Uniform("attenuation[" + std::to_string(i) + "]", cLightEmiter.attenuation);
	}
	(*m_shaders)[mShader]->setFloatUniform("lightCount", lights.size());
	(*m_shaders)[mShader]->setVec3Uniform("skyColor", Settings::skyColor);
}
void RenderSystem::renderEntities()
{
	auto knownMeshes = m_batchManager->allKnownMeshes();
	for (unsigned int meshID : knownMeshes)
	{
		auto sameMeshEntities = m_batchManager->getEntityBatch(meshID);
		if (sameMeshEntities.size() != 0)
		{
			auto mesh = sameMeshEntities[0]->getComponent<CMesh>();
			GraphicsAPI::bindVAO(mesh);
		}
		else
		{
			continue;
		}
		GLCall(glEnableVertexAttribArray(AttributeLocation::Position));
		GLCall(glEnableVertexAttribArray(AttributeLocation::UVs));
		GLCall(glEnableVertexAttribArray(AttributeLocation::Normal));
		for (Entity* entity : sameMeshEntities)
		{
			if (entity->hasComponent<CMaterial>())
			{
				auto material = entity->getComponent<CMaterial>();
				if (m_currentMaterial == nullptr || *m_currentMaterial != material)
				{
					GraphicsAPI::bindTexture(material);		
					(*m_shaders)[ShaderNames::Entity]->setFloatUniform("shineDamper", material.shineDamper);
					(*m_shaders)[ShaderNames::Entity]->setFloatUniform("reflectivity", material.reflectivity);
					m_currentMaterial = &material;
				}
			}
			else if (entity->hasComponent<CMultiTexture>())
			{
				CMultiTexture pack = entity->getComponent<CMultiTexture>();
				(*m_shaders)[ShaderNames::Entity]->setIntUniform("blendMap", 1);
				GraphicsAPI::bindTexture(pack.textureBlendMap, 1);
				(*m_shaders)[ShaderNames::Entity]->setIntUniform("backgroundTexture", 2);
				GraphicsAPI::bindTexture(pack.background, 2);
				(*m_shaders)[ShaderNames::Entity]->setIntUniform("rTexture", 3);
				GraphicsAPI::bindTexture(pack.r, 3);
				(*m_shaders)[ShaderNames::Entity]->setIntUniform("gTexture", 4);
				GraphicsAPI::bindTexture(pack.g, 4);
				(*m_shaders)[ShaderNames::Entity]->setIntUniform("bTexture", 5);
				GraphicsAPI::bindTexture(pack.b, 5);
			}
			if (entity->hasComponent<CTransformation>())
			{
				(*m_shaders)[ShaderNames::Entity]->setMatrix4fUniform("transformationMatrix", entity->getComponent<CTransformation>().transformationMatrix);
			}
			loadDefaultRenderSettings(ShaderNames::Entity);
			if (entity->hasComponent<CRenderer>())
			{
				loadRenderSettings(ShaderNames::Entity, entity);
			}
			GLCall(glDrawElements(GL_TRIANGLES, entity->getComponent<CMesh>().vertexCount, GL_UNSIGNED_INT, (void*)0));
		}
		GLCall(glDisableVertexAttribArray(AttributeLocation::Position));
		GLCall(glDisableVertexAttribArray(AttributeLocation::UVs));
		GLCall(glDisableVertexAttribArray(AttributeLocation::Normal));
		GLCall(glBindVertexArray(0));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		m_currentMaterial = nullptr;
	}
}

void RenderSystem::renderGUI()
{
	auto guis = m_batchManager->allKnownGUIs();
	if(guis.size() > 0)
	{
		GLCall(glDisable(GL_DEPTH_TEST));
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GraphicsAPI::bindVAO(m_GUIQuad.first);
		GLCall(glEnableVertexAttribArray(AttributeLocation::Position));
		for (GUI gui : guis)
		{
			GraphicsAPI::bindTexture(gui);
			glm::mat4 transformation = Maths::createTransformationMatrix(gui.getPosition(), gui.getRotation(), gui.getScale());
			(*m_shaders)[ShaderNames::GUI]->setMatrix4fUniform("transformationMatrix", transformation);
			GLCall(glDrawArrays(GL_TRIANGLE_STRIP, 0, m_GUIQuad.second));
		}
		GLCall(glDisableVertexAttribArray(AttributeLocation::Position));
		GLCall(glBindVertexArray(0));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		GLCall(glDisable(GL_BLEND));
		GLCall(glEnable(GL_DEPTH_TEST));
	}	
}

void RenderSystem::loadRenderSettings(std::string mShader, Entity* entity)
{
	CRenderer cRenderer = entity->getComponent<CRenderer>();
	(*m_shaders)[mShader]->setFloatUniform("cRenderer_tileCount", (float)cRenderer.tileCount);

	if (cRenderer.transparent)
	{
		GLCall(glDisable(GL_CULL_FACE));
	}

	if (cRenderer.fakeLighting)
	{
		(*m_shaders)[mShader]->setBooleanUniform("cRenderer_fakeLighting", true);
	}

	if (cRenderer.multiTexture)
	{
		(*m_shaders)[mShader]->setBooleanUniform("cRenderer_multiTexture", true);
	}

	if (cRenderer.disableSpecular)
	{
		(*m_shaders)[mShader]->setBooleanUniform("cRenderer_disableSpecular", true);
	}

	if (cRenderer.hasAtlas)
	{
		(*m_shaders)[mShader]->setFloatUniform("cRenderer_numberOfRows", (float) cRenderer.atlasRowCount);
		int column = cRenderer.atlasIndex % cRenderer.atlasRowCount;
		float xOffSet = (float)column / (float) cRenderer.atlasRowCount;
		int row = cRenderer.atlasIndex / cRenderer.atlasRowCount;
		float yOffSet = (float)row / (float)cRenderer.atlasRowCount;
		glm::vec2 textureOffset(xOffSet, yOffSet);
		(*m_shaders)[mShader]->setVec2Uniform("uv_offset", textureOffset);
	}

	m_usingDefaults = false;
}
void RenderSystem::loadDefaultRenderSettings(std::string mShader)
{
	if (!m_usingDefaults)
	{
		(*m_shaders)[mShader]->setFloatUniform("cRenderer_tileCount", 1);
		(*m_shaders)[mShader]->setFloatUniform("cRenderer_numberOfRows", 1);
		(*m_shaders)[mShader]->setVec2Uniform("uv_offset", glm::vec2(0,0));

		GLCall(glEnable(GL_CULL_FACE));
		GLCall(glCullFace(GL_BACK));

		(*m_shaders)[mShader]->setBooleanUniform("cRenderer_fakeLighting", false);
		(*m_shaders)[mShader]->setBooleanUniform("cRenderer_multiTexture", false);
		(*m_shaders)[mShader]->setBooleanUniform("cRenderer_disableSpecular", false);
	}

	m_usingDefaults = true;
}