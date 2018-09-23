#include "CModel.h"
#include <functional>
#include "..\..\SGEDefs.h"
#include "..\Entity.h"

void CModel::init()
{
	entity->addGroup(EntityGroups::Renderable);

	for (Mesh mesh : m_model.getMeshes())
	{
		SGE::Instances::instances->batchManagerInstance->addEntityToVAOBatch(this->entity, mesh.getVAO());
	}
}

void CModel::preRender()
{
	//SGE::Instances::instances->batchManagerInstance->calculateInstance(m_model);
}

void CModel::render()
{

}

CModel::CModel(Model model)
	:m_model(model), m_rendered(false)
{}
