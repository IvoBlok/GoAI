#pragma once


#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

#include <iostream>
#include <vector>

class ImageHandlingCLS
{
private:

public:
    void test() {

    }

    void loadImageTo3dVector(const char* filePath, std::vector<std::vector<std::vector<float>>>& dataDestination, bool grayScale = true) {
        int width, height, channels;
        unsigned char* img = stbi_load(filePath, &width, &height, &channels, 0);
        
        int desiredResultLayerCount;
        if (grayScale) { desiredResultLayerCount = 1; }
        else { desiredResultLayerCount = channels; }

        // ... process data if not NULL ..
        if (img != nullptr && width > 0 && height > 0 && (channels == 3 || channels == 1))
        {
            dataDestination = std::vector<std::vector<std::vector<float>>>(height, std::vector<std::vector<float>>(width, std::vector<float>(desiredResultLayerCount, 0)));

            /*
            if (channels == 3) {
                for (int i = 0; i < height; i++)
                {
                    for (int j = 0; j < width; j++)
                    {
                        if (grayScale) {
                            // convert RGB to Grayscale with the standard rgb proportions, and scale it to a value between 0 and 1
                            dataDestination[i][j][0] = ((float)0.23 * img[(i * width + j) * 3] + (float)0.59 * img[(i * width + j) * 3 + 1] + (float)0.11 * img[(i * width + j) * 3 + 2]) / (float)(256.0);
                        }
                        else {
                            for (int k = 0; k < channels; k++)
                            {
                                //std::cout << (0.23 * img[(i * width + j) * 3] + 0.59 * img[(i * width + j) * 3 + 1] + 0.11 * img[(i * width + j) * 3 + 2]) << " ";
                                //std::cout << 1.0 * img[(i * width + j) * 3] << std::endl;
                                dataDestination[i][j][k] = (float)(1.0) * img[(i * width + j) * 3 + k] / 256;
                            }
                        }
                    }
                }
            }
            else {
                for (int i = 0; i < height; i++)
                {
                    for (int j = 0; j < width; j++)
                    {
                        dataDestination[i][j][0] = img[i * width + j] / 256;
                    }
                }
            }
            */
        }
        else {
            std::cout << "ERROR::GIVEN_IMAGE_IS_INVALID" << std::endl;
        }
        stbi_image_free(img); // same as free(img)
	}
    void saveImageFromVector(const char* filePath, std::vector<std::vector<float>>& data) {
        uint8_t* pixels = new uint8_t[data[0].size() * data.size()];

        int index = 0;
        for (size_t i = 0; i < data.size(); i++)
        {
            for (size_t j = 0; j < data[0].size(); j++)
            {
                // convert the grayscale 0-1 scale to 0-256 scale
                pixels[index++] = (int)std::round(data[i][j] * 256);
            }
        }

        stbi_write_png(filePath, (int)data[0].size(), (int)data.size(), 1, pixels, 0);
        delete[] pixels;
    }
    void saveImageFromVector(const char* filePath, std::vector<std::vector<std::vector<float>>>& data) {
        uint8_t* pixels = new uint8_t[data.size() * data[0].size() * data[0][0].size()];

        int index = 0;
        for (size_t i = 0; i < data.size(); i++)
        {
            for (size_t j = 0; j < data[0].size(); j++)
            {
                for (size_t k = 0; k < data[0][0].size(); k++)
                {
                    pixels[index++] = (int)std::round(data[i][j][k] * 256);
                }
            }
        }
        stbi_write_png(filePath, (int)data[0].size(), (int)data.size(), (int)data[0][0].size(), pixels, 0);
        delete[] pixels;
    }
};

