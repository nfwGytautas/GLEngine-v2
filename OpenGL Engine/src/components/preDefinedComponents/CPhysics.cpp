#include "CPhysics.h"
#include "..\Entity.h"

CPhysics::CPhysics()
	: affectedByGravity(false), velocity(0,0,0)
{
}

CPhysics::~CPhysics()
{
}

void CPhysics::init()
{
	entity->addGroup(EntityGroups::HasPhysics);
}