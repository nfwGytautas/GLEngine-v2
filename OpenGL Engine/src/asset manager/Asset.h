#pragma once
#include <string>

enum class AssetType
{
	Model = 0,
	Image = 1,
	UNKNOWN
};

class Asset
{
public:
	std::string GetName();
	void SetName(std::string newName);

	std::string GetPath();
	void SetPath(std::string filepath);

	virtual AssetType GetType()
	{
		return AssetType::UNKNOWN;
	}
public:
	Asset();
	virtual ~Asset();
protected:
	std::string m_Name;
	std::string m_Filepath;
};

class AModel : public Asset
{
public:

	AssetType GetType() override
	{
		return AssetType::Model;
	}

	AModel();
	~AModel();
private:
};

class AImage: public Asset
{
public:

	AssetType GetType() override
	{
		return AssetType::Image;
	}

	AImage(int Width, int Height, int BPP, unsigned char* ImageBuffer);
	~AImage();
private:
	int m_Width;
	int m_Height;
	int m_BPP;

	//Temporary variables
	unsigned char* m_ImageBuffer;
};