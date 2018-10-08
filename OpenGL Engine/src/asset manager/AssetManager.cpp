#include "AssetManager.h"



AssetManager::AssetManager()
{
}


AssetManager::~AssetManager()
{
	for (int i = 0; i < m_assetStorage.size(); i++)
	{
		delete m_assetStorage[i];
	}
}
