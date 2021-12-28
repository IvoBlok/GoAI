// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define STRINGIFY(x) #x
#define EXPAND(x) STRINGIFY(x)

#include "neuralnetwork/convolution/CalcLayerCLS.hpp"
#include "neuralnetwork/convolution/CalcPoolsCLS.hpp"
#include "neuralnetwork/convolution/ActivationLayerCLS.hpp"
#include "neuralnetwork/convolution/ConvStructureCLS.hpp"

#include "imageLoading/LoadImageCLS.h"

#include <iostream>
#include <iomanip>
#include <memory>
#include <string>

float tempCalcScore(std::vector<std::vector<float>> data);

int main()
{
    // get prjPath and remove the string quotes
    std::string prjPath = EXPAND(GOAIPRJPATH);
    prjPath.erase(0, 1); prjPath.erase(prjPath.size() - 2);

    std::string relativePath = "src\\inputData\\btimg-02_5_640_x_480.png";

    std::vector<std::vector<float>> data2;
    LoadImageCLS loadImage;
    loadImage.loadImageTo2dVector((prjPath + relativePath).c_str(), data2);

    
    std::vector<std::vector<float>> data =
    {
        {1, 0, 0, 1, 1, 1, 0, 0, 1},
        {1, 0, 0, 1, 1, 1, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 0, 1},
        {1, 1, 1, 1, 0, 1, 0, 0, 1},
        {1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 1, 0, 1, 1},
        {1, 0, 0, 0, 1, 1, 0, 1, 1},
    };

    std::vector<std::vector<float>> CalcFilter =
    {
        {-1, -1, -1},
        {-1, 8, -1},
        {-1, -1, -1},
    };

    /*
    // instantiate the convolutional layer structure
    ConvStructureCLS convStructure(ConvStructureSettings{false});

    // instantiate the first layer in the structure
    CalcLayerSettings layer1Settings; //layer1Settings.initialFilter = CalcFilter;
    convStructure.addStructureElement(CalcLayerCLS(layer1Settings));

    // instantiate activation layers
    convStructure.addStructureElement(ActivationLayerCLS{ ActivationLayerSettings{ActivationFunctionTypes::RELU} });
    convStructure.addStructureElement(ActivationLayerCLS{ ActivationLayerSettings{ActivationFunctionTypes::SIGMOID} });

    // instantiate pooling layer
    CalcPoolsSettings pool1Settings{};
    int stride[2]{ 3, 3 };
    pool1Settings.set2Dstride(stride);
    pool1Settings.functionType = PoolFunctionTypes::MAX;
    convStructure.addStructureElement(CalcPoolsCLS{ pool1Settings });

    // run the convolutional structure once
    convStructure.runConvStructure(data);

    for (int i = 0; i < 2500; i++)
    {
        std::cout << "==============================================" << std::endl;
        std::cout << "GENERATION : " << i + 1 << std::endl;
        std::cout << "==============================================" << std::endl;
        convStructure.mutateConvStructure(0.2);

        std::cout << tempCalcScore(convStructure.runConvStructure(data)) << std::endl;
    }
    convStructure.printFilters("final filter"); */
    return 1;
}


float tempCalcScore(std::vector<std::vector<float>> data) {
    float sum = 0;
    for (size_t i = 0; i < data.size(); i++)
    {
        for (size_t j = 0; j < data[0].size(); j++)
        {
            sum += data[i][j];
        }
    }
    return sum;
}

