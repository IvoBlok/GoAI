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

    std::cout << "img size: " << img.maxWidth << " " << img.maxHeight << " " << img.maxDepth << std::endl;
    // create conv layer structure
    // -----------------------------------------------------------------------
    
    // instantiate the convolutional layer structure class
    ConvStructureCLS convStructure(ConvStructureSettings{false});
    
    
    // first calc stage
    convStructure.addStructureElement(CalcLayerCLS{});
    CalcLayerSettings& calcLayerSettings = convStructure.calcLayerList[convStructure.calcLayerList.size() - 1].settings;
   
    calcLayerSettings.initialFilter = arr_3d_data::createRandomFilter(3, 3, 3);
    calcLayerSettings.compensateBorder = true;
    calcLayerSettings.compensateDepthBorder = false;

    // first activation stages
    convStructure.addStructureElement(ActivationLayerCLS{ ActivationLayerSettings{ActivationFunctionTypes::RELU} });
    convStructure.addStructureElement(ActivationLayerCLS{ ActivationLayerSettings{ActivationFunctionTypes::SIGMOID} });
    
    // first pooling stage
    convStructure.addStructureElement(CalcPoolsCLS{});
    CalcPoolsSettings& pool1Settings = convStructure.calcPoolList[convStructure.calcPoolList.size() - 1].settings;
    int stride[3]{ 3, 3, 1 };
    pool1Settings.setStride(stride);
    

    convStructure.printStructure();

    // running the neural network
    // -----------------------------------------------------------------------
    
    //img = convStructure.runConvStructure(img);
    convStructure.calcLayerList[convStructure.structure[0][0][0].respectiveIndex].run(img);

    /*
    for (int i = 0; i < 0; i++)
    {
        std::cout << "==============================================" << std::endl;
        std::cout << "GENERATION : " << i + 1 << std::endl;
        std::cout << "==============================================" << std::endl;
        convStructure.mutateConvStructure((float)0.2);

        std::cout << tempCalcScore(convStructure.runConvStructure(img)) << std::endl;
    }
    */
    imageHandler.saveImageFromVector((prjPath + relativeOutputPath + getCurrentTimeString() + ".png").c_str(), img);
    
    system("pause");

    return 1;
}
