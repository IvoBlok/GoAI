#define stringify( name )
#include "ConvStructureCLS.hpp"
#include <cstring>

arr_3d_data ConvStructureCLS::runConvStructure(arr_3d_data& data) {
	arr_3d_data dataHolderSubStep = data;
	arr_3d_data sumHolder;

	std::cout << std::endl << "===============================" << std::endl << "conv structure has started!" << std::endl;
	// go over every structure step
	// every step can contain multiple substeps to generate the data for the next step
	for (size_t i = 0; i < structure.size(); i++)
	{
		sumHolder.allocateSpace(0, 0, 0);
		// every step can contain multiple series of substeps, which are summed up before going to the next step
		for (size_t j = 0; j < structure[i].size(); j++)
		{
			dataHolderSubStep = data;

			// getting the sum of the series of substeps
			for (size_t k = 0; k < structure[i][j].size(); k++)
			{
				if (structure[i][j][k].layerType == ConvLayerTypes::CalcLayer) {
					calcLayerList[structure[i][j][k].respectiveIndex].run(dataHolderSubStep);
					if (settings.printOutput) { std::cout << "Layer type: CalcLayer" << std::endl; }
				}
				else if (structure[i][j][k].layerType == ConvLayerTypes::ActivationLayer) {
					activationLayerList[structure[i][j][k].respectiveIndex].run(dataHolderSubStep);
					if (settings.printOutput) { std::cout << "Layer type: ActivationLayer" << std::endl; }
				}
				else if (structure[i][j][k].layerType == ConvLayerTypes::CalcPools) {
					calcPoolList[structure[i][j][k].respectiveIndex].run(dataHolderSubStep);
					if (settings.printOutput) { std::cout << "Layer type: CalcPoolsLayer" << std::endl; }
				}
			}
			std::cout << "substep has been run!" << std::endl;
			// check if the data from every series of substeps has the same width and height
			if (sumHolder.maxValueCount != 0) {
				if (sumHolder.maxWidth != dataHolderSubStep.maxWidth || sumHolder.maxHeight != dataHolderSubStep.maxHeight) { assert(false, "ERROR:SUBSTEPS_DONT_ALL_RETURN_DATA_OFF_THE_SAME_WIDTH_AND/OR_HEIGHT"); }
			}
			sumHolder.insert(dataHolderSubStep);
		}
		data.copy(sumHolder);
		std::cout << "step has been run!" << std::endl;
	}
	dataHolderSubStep.allocateSpace(0, 0, 0);
	sumHolder.allocateSpace(0, 0, 0);

	return data;
}

void ConvStructureCLS::addStructureElement(CalcLayerCLS calcLayer_, int step, int substep) {
	int respectiveIndex = (int)calcLayerList.size();
	calcLayerList.push_back(calcLayer_);
	
	if (step == NULL) {
		step = structure.size(); 
		std::vector<std::vector<ConvStructureElement>> newStepStructure(1, std::vector<ConvStructureElement>(1, ConvStructureElement(respectiveIndex, ConvLayerTypes::CalcLayer)));
		structure.push_back(newStepStructure);
	}
	else if (substep == NULL) {
		substep = structure[step - 1].size();
		std::vector<ConvStructureElement> newSubStepStructure(1, ConvStructureElement(respectiveIndex, ConvLayerTypes::CalcLayer));
		structure[step - 1].push_back(newSubStepStructure);
	}
	else {
		structure[step - 1][substep - 1].push_back(ConvStructureElement(respectiveIndex, ConvLayerTypes::CalcLayer));
	}
}

void ConvStructureCLS::addStructureElement(CalcPoolsCLS calcPools_, int step, int substep) {
	int respectiveIndex = (int)calcPoolList.size();
	calcPoolList.push_back(calcPools_);

	if (step == NULL) {
		step = structure.size();
		std::vector<std::vector<ConvStructureElement>> newStepStructure(1, std::vector<ConvStructureElement>(1, ConvStructureElement(respectiveIndex, ConvLayerTypes::CalcPools)));
		structure.push_back(newStepStructure);
	}
	else if (substep == NULL) {
		substep = structure[step - 1].size();
		std::vector<ConvStructureElement> newSubStepStructure(1, ConvStructureElement(respectiveIndex, ConvLayerTypes::CalcPools));
		structure[step - 1].push_back(newSubStepStructure);
	}
	else {
		structure[step - 1][substep - 1].push_back(ConvStructureElement(respectiveIndex, ConvLayerTypes::CalcPools));
	}
}

void ConvStructureCLS::addStructureElement(ActivationLayerCLS activationLayer_, int step, int substep) {
	int respectiveIndex = (int)activationLayerList.size();
	activationLayerList.push_back(activationLayer_);

	if (step == NULL) {
		step = structure.size();
		std::vector<std::vector<ConvStructureElement>> newStepStructure(1, std::vector<ConvStructureElement>(1, ConvStructureElement(respectiveIndex, ConvLayerTypes::ActivationLayer)));
		structure.push_back(newStepStructure);
	}
	else if (substep == NULL) {
		substep = structure[step - 1].size();
		std::vector<ConvStructureElement> newSubStepStructure(1, ConvStructureElement(respectiveIndex, ConvLayerTypes::ActivationLayer));
		structure[step - 1].push_back(newSubStepStructure);
	}
	else {
		structure[step - 1][substep - 1].push_back(ConvStructureElement(respectiveIndex, ConvLayerTypes::ActivationLayer));
	}
}

void ConvStructureCLS::mutateConvStructure(float severity) {
	// CalcLayers have filters that can be mutated
	for (size_t i = 0; i < calcLayerList.size(); i++)
	{
		calcLayerList[i].mutateFilter(severity);
	}
}

void ConvStructureCLS::printFilters(std::string filterName) {
	for (size_t i = 0; i < calcLayerList.size(); i++)
	{
		std::cout << "Filter: " << filterName << " " << i << std::endl;
		calcLayerList[i].settings.initialFilter.print();
	}
}

void ConvStructureCLS::printStructure() {
	for (size_t i = 0; i < structure.size(); i++)
	{
		std::cout << "======  step: " << i + 1 << "  ==========" << std::endl;
		for (size_t j = 0; j < structure[i].size(); j++)
		{
			std::cout << "======  substep: " << j + 1 << "  =======" << std::endl;
			for (size_t k = 0; k < structure[i][j].size(); k++)
			{
				if (structure[i][j][k].layerType == ConvLayerTypes::CalcLayer) {
					arr_3d_data& filter = calcLayerList[structure[i][j][k].respectiveIndex].settings.initialFilter;
					std::cout << "Conv layer: " << " x: " << filter.maxWidth << " y: " << filter.maxHeight << " z: " << filter.maxDepth << std::endl;
				}
				else if (structure[i][j][k].layerType == ConvLayerTypes::CalcPools) {
					PoolFunctionTypes& type = calcPoolList[structure[i][j][k].respectiveIndex].settings.functionType;
					std::string message;
					(type == PoolFunctionTypes::AVG) ? message = "AVG" : message = "MAX";
					std::cout << "Pooling layer: " << message << std::endl;
				}
				else if (structure[i][j][k].layerType == ConvLayerTypes::ActivationLayer) {
					ActivationFunctionTypes& type = activationLayerList[structure[i][j][k].respectiveIndex].settings.functionType;
					std::string message;
					(type == ActivationFunctionTypes::RELU) ? message = "RELU" : message = "SIGMOID";
					std::cout << "activation layer: " << message << std::endl;
				}
			}
		}
	}
}
