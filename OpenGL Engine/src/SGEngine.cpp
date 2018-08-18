#include "SGEngine.h"

SGE::SGEngine::SGEngine()
{
	StateControl::_sgeInit();
	StateControl::_sgePrepareShaders();
}


SGE::SGEngine::~SGEngine()
{
	StateControl::_sgeTerminate();
}

SGE::Types::Renderer SGE::SGEngine::getRenderer()
{
	return SGE::Instances::instances->renderSystemInstance;
}

SGE::Types::UpdateSystem SGE::SGEngine::getUpdateSystem()
{
	return SGE::Instances::instances->updateSystemInstance;
}

SGE::Types::Physics SGE::SGEngine::getPhysicsManager()
{
	return SGE::Instances::instances->physicsSystemInstance;
}

SGE::Types::DataManager SGE::SGEngine::getDataManager()
{
	return SGE::Instances::instances->dataManagerInstance;
}

void SGE::SGEngine::markAsGround(Entity& mEntity, continuous2DArray<float>& mHeightMap, float mGroundSize)
{
	mEntity.addGroup(EntityGroups::IsGround);
	SGE::Instances::instances->physicsSystemInstance->registerHeightMap(mHeightMap, mGroundSize);
}