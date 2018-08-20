#include "CModel.h"
#include <functional>
#include "..\Entity.h"

void CModel::init()
{
	entity->addGroup(EntityGroups::Renderable);
}

CModel::CModel(Model model)
	:m_model(model)
{
}
