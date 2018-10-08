#include "Asset.h"

Asset::Asset()
{
}
Asset::~Asset()
{
}

AModel::AModel()
{
}
AModel::~AModel()
{
}

AImage::AImage(int Width, int Height, int BPP, unsigned char* ImageBuffer)
	:m_Width(Width), m_Height(Height), m_BPP(BPP)
{
	m_ImageBuffer = new unsigned char(*ImageBuffer);
}
AImage::~AImage()
{
}