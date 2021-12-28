// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define STRINGIFY(x) #x
#define EXPAND(x) STRINGIFY(x)

#include "neuralnetwork/convolution/ConvStructureCLS.hpp"

#include "imageLoading/ImageHandlingCLS.hpp"

#include "helperFunctions.hpp"

#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <ctime>
#include <sstream>

void main()
{
    // initial setup
    // -----------------------------------------------------------------------
    initRandomnessSeed();

    std::string prjPath = getProjectPath();

    std::string relativeInputPath = "src\\neuralnetwork\\inputData\\btimg-02_5_640_x_480.png";
    std::string relativeOutputPath = "src\\neuralnetwork\\outputData\\btimg-conv-1-layer";

    // load data
    // -----------------------------------------------------------------------
    std::vector<std::vector<float>> data;
    ImageHandlingCLS imageHandler;
    imageHandler.loadImageTo2dVector((prjPath + relativeInputPath).c_str(), data);

    // create conv layer structure
    // -----------------------------------------------------------------------
    
    // instantiate the convolutional layer structure class
    ConvStructureCLS convStructure(ConvStructureSettings{false});
    
    // first conv stages
    convStructure.addStructureElement(CalcLayerCLS());
    convStructure.addStructureElement(CalcLayerCLS());

    // first activation stages
    convStructure.addStructureElement(ActivationLayerCLS{ ActivationLayerSettings{ActivationFunctionTypes::RELU} });
    convStructure.addStructureElement(ActivationLayerCLS{ ActivationLayerSettings{ActivationFunctionTypes::SIGMOID} });

    // first pooling stage
    CalcPoolsSettings pool1Settings{};
    int stride[2]{ 3, 3 };
    pool1Settings.set2Dstride(stride);
    convStructure.addStructureElement(CalcPoolsCLS{ pool1Settings });

    // running the neural network
    // -----------------------------------------------------------------------

    // run the convolutional structure once
    data = convStructure.runConvStructure(data);

    for (int i = 0; i < 3; i++)
    {
        std::cout << "==============================================" << std::endl;
        std::cout << "GENERATION : " << i + 1 << std::endl;
        std::cout << "==============================================" << std::endl;
        convStructure.mutateConvStructure(0.2);

        std::cout << tempCalcScore(convStructure.runConvStructure(data)) << std::endl;
    }
    imageHandler.saveImageFrom2dVector((prjPath + relativeOutputPath + getCurrentTimeString() + ".png").c_str(), data);
    return;
}
