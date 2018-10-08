#pragma once
#include <vector>
#include "Asset.h"

class AssetManager
{
public:

public:
	AssetManager();
	~AssetManager();

private:
	std::vector<Asset*> m_assetStorage;
};

