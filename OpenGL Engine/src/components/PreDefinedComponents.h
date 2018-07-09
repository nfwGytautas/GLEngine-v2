#pragma once
//==================================================================================================================================
//ALL THE NEEDED HEADERS SO YOU FOR THE COMPONENT SYSTEM
//==================================================================================================================================
#include "Component.h"		//Base class that all components derive from
#include "Entity.h"			//Class that uses these components
#include "EntityGroups.h"	//Header containing all predefined entity groups

#include "preDefinedComponents\CPosition.h"			//Position component
#include "preDefinedComponents\CColor.h"			//Color component

#include "preDefinedComponents\CTransformation.h"	//Transformation component

#include "preDefinedComponents\CMesh.h"				//Mesh component
#include "preDefinedComponents\CMaterial.h"			//Material component

#include "preDefinedComponents\CRenderer.h"			//Rendering component

#include "preDefinedComponents\CLightEmiter.h"		//Light emiting component

#include "preDefinedComponents\CMultiTexture.h"		//Multi texture component