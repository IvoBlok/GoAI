#pragma once


#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

#include "../neuralnetwork/nodetypes/convolution/arr_3d_data.hpp"

#include <iostream>
#include <vector>

class ImageHandlingCLS
{
private:

public:
    void test() {

    }

    void loadImageTo3dVector(const char* filePath, arr_3d_data& dataDestination, bool grayScale = true) {
        int width, height, channels;
        unsigned char* img = stbi_load(filePath, &width, &height, &channels, 0);
        
        int desiredResultLayerCount;
        if (grayScale) { desiredResultLayerCount = 1; }
        else { desiredResultLayerCount = channels; }

        // ... process data if not NULL ..
        if (img != nullptr && width > 0 && height > 0 && (channels == 3 || channels == 1))
        {
            int depth;
            (grayScale) ? depth = 1 : depth = channels;
            dataDestination.allocateSpace(width, height, depth);
            
            if (channels == 3) {
                for (int i = 0; i < height; i++)
                {
                    for (int j = 0; j < width; j++)
                    {
                        if (grayScale) {
                            // convert RGB to Grayscale with the standard rgb proportions, and scale it to a value between 0 and 1
                            //dataDestination[i][j][0] = ((float)0.23 * img[(i * width + j) * 3] + (float)0.59 * img[(i * width + j) * 3 + 1] + (float)0.11 * img[(i * width + j) * 3 + 2]) / (float)(256.0);
                            dataDestination.setValue(j, i, 0, ((float)0.23 * img[(i * width + j) * 3] + (float)0.59 * img[(i * width + j) * 3 + 1] + (float)0.11 * img[(i * width + j) * 3 + 2]) / (float)(256.0));
                        }
                        else {
                            for (int k = 0; k < channels; k++)
                            {
                                //dataDestination[i][j][k] = (float)(1.0) * img[(i * width + j) * 3 + k] / 256;
                                dataDestination.setValue(j, i, k, (float)(1.0) * img[(i * width + j) * 3 + k] / 256);
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
                        //dataDestination[i][j][0] = img[i * width + j] / 256;
                        dataDestination.setValue(j, i, 0, img[i * width + j] / (float)256);
                    }
                }
            }
        }
        else {
            std::cout << "ERROR::GIVEN_IMAGE_IS_INVALID" << std::endl;
        }
        stbi_image_free(img); // same as free(img)
	}

    void saveImageFromVector(const char* filePath, arr_3d_data& data) {
        uint8_t* pixels = new uint8_t[data.maxValueCount];

        int index = 0;
        for (int i = 0; i < data.maxHeight; i++)
        {
            for (int j = 0; j < data.maxWidth; j++)
            {
                for (int k = 0; k < data.maxDepth; k++)
                {
                    pixels[index++] = (uint8_t)std::round(data.getValue(j, i, k) * 256);
                }
            }
        }
        stbi_write_png(filePath, data.maxWidth, data.maxHeight, data.maxDepth, pixels, 0);
        delete[] pixels;
        pixels = nullptr;
    }
};

