#pragma once
#include <string>

class ImageLoader
{
public:
	static bool loadImage(std::string mFilePath, std::string mFormat);
	static void freeData();
	static unsigned char* imageBuffer;
	static int width;
	static int height;
	static int BPP;

	static void loadFallbackImage();
};

