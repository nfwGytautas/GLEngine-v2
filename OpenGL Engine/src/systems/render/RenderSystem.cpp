#include "RenderSystem.h"
#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "..\..\Settings.h"
#include "..\..\graphics\FrameworkAssert.h"
#include "..\..\graphics\shader\DynamicShader.h"
#include "..\..\components\EntityManager.h"
#include "..\..\components\Entity.h"
#include "..\..\components\PreDefinedComponents.h"
#include "..\..\data manager\BatchManager.h"
#include "..\..\graphics\api\GraphicsAPI.h"
#include "..\..\graphics\gTypes\gTypes.h"

void RenderSystem::render()
{
	//Prepare for rendering
	prepare();
	m_shader->bind();

	//MAIN RENDER CODE
	//================================================
	if (Settings::camera == nullptr)
	{
		std::cout << "[Engine][Renderer] No specified camera!" << std::endl;
		return;
	}
	m_shader->setMatrix4fUniform("viewMatrix", Settings::camera->viewMatrix);

	//Load all the lights
	loadLights();

	//Render entities
	renderEntities();

	//================================================

	m_shader->unbind();
}

RenderSystem::RenderSystem(DynamicShader* mShader, EntityManager* mEntityManager, BatchManager* mBatchManager)
	: m_shader(mShader), m_entityManager(mEntityManager), m_batchManager(mBatchManager)
{
}

void RenderSystem::prepare()
{
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCall(glClearColor(Settings::skyColor.r, Settings::skyColor.g, Settings::skyColor.b, 1));
}
void RenderSystem::loadLights()
{
	auto lights = m_entityManager->getEntitiesByGroup(EntityGroups::LightEmittingEntity);
	for (Entity* light : lights)
	{
		m_shader->setVec3Uniform("lightColour", light->getComponent<CColor>().value);
		m_shader->setVec3Uniform("lightPosition", light->getComponent<CPosition>().value);
	}

	m_shader->setVec3Uniform("skyColor", Settings::skyColor);
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
					m_shader->setFloatUniform("shineDamper", material.shineDamper);
					m_shader->setFloatUniform("reflectivity", material.reflectivity);
					m_currentMaterial = &material;
				}
			}
			else if (entity->hasComponent<CMultiTexture>())
			{
				CMultiTexture pack = entity->getComponent<CMultiTexture>();
				m_shader->setIntUniform("blendMap", 1);
				GraphicsAPI::bindTexture(pack.textureBlendMap, 1);
				m_shader->setIntUniform("backgroundTexture", 2);
				GraphicsAPI::bindTexture(pack.background, 2);
				m_shader->setIntUniform("rTexture", 3);
				GraphicsAPI::bindTexture(pack.r, 3);
				m_shader->setIntUniform("gTexture", 4);
				GraphicsAPI::bindTexture(pack.g, 4);
				m_shader->setIntUniform("bTexture", 5);
				GraphicsAPI::bindTexture(pack.b, 5);
			}
			if (entity->hasComponent<CTransformation>())
			{
				m_shader->setMatrix4fUniform("transformationMatrix", entity->getComponent<CTransformation>().transformationMatrix);
			}
			loadDefaultRenderSettings();
			if (entity->hasComponent<CRenderer>())
			{
				loadRenderSettings(entity);
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

void RenderSystem::loadRenderSettings(Entity* entity)
{
	CRenderer cRenderer = entity->getComponent<CRenderer>();
	m_shader->setFloatUniform("cRenderer_tileCount", (float)cRenderer.tileCount);

	if (cRenderer.transparent)
	{
		GLCall(glDisable(GL_CULL_FACE));
	}

	if (cRenderer.fakeLighting)
	{
		m_shader->setBooleanUniform("cRenderer_fakeLighting", true);
	}

	if (cRenderer.multiTexture)
	{
		m_shader->setBooleanUniform("cRenderer_multiTexture", true);
	}

	if (cRenderer.disableSpecular)
	{
		m_shader->setBooleanUniform("cRenderer_disableSpecular", true);
	}

	m_usingDefaults = false;
}
void RenderSystem::loadDefaultRenderSettings()
{
	if (!m_usingDefaults)
	{
		m_shader->setFloatUniform("cRenderer_tileCount", 1);

		GLCall(glEnable(GL_CULL_FACE));
		GLCall(glCullFace(GL_BACK));

		m_shader->setBooleanUniform("cRenderer_fakeLighting", false);
		m_shader->setBooleanUniform("cRenderer_multiTexture", false);
		m_shader->setBooleanUniform("cRenderer_disableSpecular", false);
	}

	m_usingDefaults = true;
}