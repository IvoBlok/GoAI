#pragma once

extern "C" {
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
}

#include <iostream>
#include <vector>

class LoadImageCLS
{
private:

public:
    void loadImageTo2dVector(const char* filePath, std::vector<std::vector<float>>& dataDestination) {
        int width, height, channels;
        unsigned char* img = stbi_load(filePath, &width, &height, &channels, 0);

        
        // ... process data if not NULL ..
        if (img != nullptr && width > 0 && height > 0 && (channels == 3 || channels == 1))
        {
            std::cout << "jeej something is working!" << std::endl;
            std::vector<std::vector<float>> dataHolder(height, std::vector<float>(width, 0));
        
            if (channels == 3) {
                for (int i = 0; i < height; i++)
                {
                    for (int j = 0; j < width; j++)
                    {
                        dataHolder[i][j] = 0.23 * img[i * width + j] + 0.59 * img[i * width + j + 1] + 0.11 * img[i * width + j + 2];
                    }
                }
            }
            else {
                for (int i = 0; i < height; i++)
                {
                    for (int j = 0; j < width; j++)
                    {
                        dataHolder[i][j] = img[i * width + j];
                    }
                }
            }

            dataDestination = dataHolder;
        }
	}
};

