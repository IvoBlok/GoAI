// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define STRINGIFY(x) #x
#define EXPAND(x) STRINGIFY(x)

#include "neuralnetwork/nodetypes/convolution/ConvStructureCLS.hpp"

#include "imageLoading/ImageHandlingCLS.hpp"

#include "helperFunctions.hpp"
#include "neuralnetwork/nodetypes/convolution/arr_3d_data.hpp"

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
    arr_3d_data img;
    ImageHandlingCLS imageHandler;
    imageHandler.loadImageTo3dVector((prjPath + relativeInputPath).c_str(), img, false);

    // create conv layer structure
    // -----------------------------------------------------------------------
    
    // instantiate the convolutional layer structure class
    ConvStructureCLS convLayer1(ConvStructureSettings{false});
    
    // first calc stage
    convLayer1.addStructureElement(CalcLayerCLS{});
    CalcLayerSettings& calcLayerSettings = convLayer1.calcLayerList[convLayer1.calcLayerList.size() - 1].settings;
   
    calcLayerSettings.initialFilter = arr_3d_data::createRandomFilter(3, 3, 3);
    calcLayerSettings.compensateBorder = true;
    calcLayerSettings.compensateDepthBorder = false;
    
    // first activation stages
    convLayer1.addStructureElement(ActivationLayerCLS{ ActivationLayerSettings{ActivationFunctionTypes::RELU} });
    convLayer1.addStructureElement(ActivationLayerCLS{ ActivationLayerSettings{ActivationFunctionTypes::SIGMOID} });

    // first pooling stage
    convLayer1.addStructureElement(CalcPoolsCLS{});
    CalcPoolsSettings& pool1Settings = convLayer1.calcPoolList[convLayer1.calcPoolList.size() - 1].settings;
    int stride[3]{ 3, 3, 1 };
    pool1Settings.setStride(stride);
    

    convLayer1.printStructure();
    
    // running the neural network
    // -----------------------------------------------------------------------
    
    convLayer1.runConvLayer(img);
    
    for (int i = 0; i < 0; i++)
    {
        std::cout << "==============================================" << std::endl;
        std::cout << "GENERATION : " << i + 1 << std::endl;
        std::cout << "==============================================" << std::endl;
        convLayer1.mutateConvStructure((float)0.2);
        convLayer1.runConvLayer(img);
        std::cout << tempCalcScore(img) << std::endl;
    }
    imageHandler.saveImageFromVector((prjPath + relativeOutputPath + getCurrentTimeString() + ".png").c_str(), img);
    system("pause");

    return 1;
}
