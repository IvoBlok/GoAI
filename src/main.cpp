// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define STRINGIFY(x) #x
#define EXPAND(x) STRINGIFY(x)

#include "neuralnetwork/nodetypes/convolution/ConvStructureCLS.hpp"

#include "imageLoading/ImageHandlingCLS.hpp"

#include "helperFunctions.hpp"

#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <ctime>
#include <sstream>

int main()
{
    // initial setup
    // -----------------------------------------------------------------------
    initRandomnessSeed();

    std::string prjPath = getProjectPath();

    std::string relativeInputPath = "src\\neuralnetwork\\inputData\\btimg-02_5_640_x_480.png";
    std::string relativeOutputPath = "src\\neuralnetwork\\outputData\\btimg-conv-1-layer";

    // load data
    // -----------------------------------------------------------------------
    std::vector<std::vector<std::vector<float>>> data;
    ImageHandlingCLS imageHandler;
    imageHandler.loadImageTo3dVector((prjPath + relativeInputPath).c_str(), data, false);

    std::cout << "data memory size: " << (sizeof(std::vector<float>) + (sizeof(float) * data.size() * data[0].size() * data[0][0].size())) / (float)1000000 << "MB" << std::endl;
    std::cout << data.size() << " " << data[0].size() << " " << data[0][0].size() << std::endl;
    // create conv layer structure
    // -----------------------------------------------------------------------
    
    
    
    // instantiate the convolutional layer structure class
    ConvStructureCLS convStructure(ConvStructureSettings{false});
    
    
    // first conv stages
    CalcLayerSettings calcLayerSettings{};
    calcLayerSettings.initialFilter = CalcLayerSettings::createRandomFilter(3, 3, 3);
    calcLayerSettings.compensateBorder = true;
    calcLayerSettings.compensateDepthBorder = false;
    convStructure.addStructureElement(CalcLayerCLS{ calcLayerSettings });

    
    // first activation stages
    convStructure.addStructureElement(ActivationLayerCLS{ ActivationLayerSettings{ActivationFunctionTypes::RELU} });
    convStructure.addStructureElement(ActivationLayerCLS{ ActivationLayerSettings{ActivationFunctionTypes::SIGMOID} });
    
    
    // first pooling stage
    CalcPoolsSettings pool1Settings{};
    int stride[3]{ 3, 3, 1 };
    pool1Settings.setStride(stride);
    convStructure.addStructureElement(CalcPoolsCLS{ pool1Settings });
    
    convStructure.printStructure();
    
    // running the neural network
    // -----------------------------------------------------------------------
    
    data = convStructure.runConvStructure(data);

    for (int i = 0; i < 0; i++)
    {
        std::cout << "==============================================" << std::endl;
        std::cout << "GENERATION : " << i + 1 << std::endl;
        std::cout << "==============================================" << std::endl;
        convStructure.mutateConvStructure((float)0.2);

        std::cout << tempCalcScore(convStructure.runConvStructure(data)) << std::endl;
    }

    imageHandler.saveImageFromVector((prjPath + relativeOutputPath + getCurrentTimeString() + ".png").c_str(), data);
    
    system("pause");
    return 1;
}
