#include "CBoundingObject.h"
#include "..\..\data manager\data structures\BoundingObjects.h"

void CBoundingObject::preRender()
{
	if (m_object->insideFrustum())
	{
		insideFrustum = true;
	}
	else
	{ 
		insideFrustum = false;
	}
}
