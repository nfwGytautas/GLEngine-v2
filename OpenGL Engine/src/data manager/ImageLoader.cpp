#include "ImageLoader.h"
#include <vector>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb image\stb_image.h"

unsigned char* ImageLoader::imageBuffer = nullptr;
int ImageLoader::width = 0;
int ImageLoader::height = 0;
int ImageLoader::BPP = 0;

bool ImageLoader::loadImage(std::string mFilePath, std::string mFormat)
{
	try
	{
		if(mFormat == ".png")
		{
			stbi_set_flip_vertically_on_load(1);
		}

		imageBuffer = stbi_load(mFilePath.c_str(), &width, &height, &BPP, 4);
		stbi_failure_reason();
		return true;
	}
	catch (...)
	{
		std::cout << "[Engine][Data manager] Error: Loading image! Using fallback for: " << mFilePath << std::endl;
		return false;
	}
}

void ImageLoader::freeData()
{
	stbi_image_free(imageBuffer);
}

void ImageLoader::loadFallbackImage()
{
	std::vector<float> tempBuffer;
	tempBuffer.reserve(8 * 8 * 8 * 8);
	//Starts with pink block
	bool drawPink = true;
	//8 Lines
	for (int i = 0; i < 8; i++)
	{
		// 8 Collumns
		for (int j = 0; j < 8; j++)
		{
			//8 Pixels in a block
			for (int k = 0; k < 8; k++)
			{
				//Alternating blocks
				if (drawPink)
				{
					for (int z = 0; z < 8; z++)
					{
						//Pink pixel
						tempBuffer.push_back(255);
						tempBuffer.push_back(0);
						tempBuffer.push_back(165);
					}
					drawPink = false;
				}
				else
				{
					for (int z = 0; z < 8; z++)
					{
						//Black pixel
						tempBuffer.push_back(0);
						tempBuffer.push_back(0);
						tempBuffer.push_back(0);
					}
					drawPink = true;
				}
			}
		}
		drawPink = !drawPink;
	}
	imageBuffer = reinterpret_cast<unsigned char *>(&(tempBuffer[0]));
	width = 64;
	height = 64;
}
