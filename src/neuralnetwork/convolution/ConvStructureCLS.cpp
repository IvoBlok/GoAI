#define stringify( name )
#include "ConvStructureCLS.hpp"
#include <cstring>

std::vector<std::vector<std::vector<float>>> ConvStructureCLS::runConvStructure(std::vector<std::vector<std::vector<float>>> data) {
	std::vector<std::vector<std::vector<float>>> dataHolderStep = data;
	std::vector<std::vector<std::vector<float>>> dataHolderSubStep;
	std::vector<std::vector<std::vector<float>>> sumHolder;

	std::cout << std::endl << "===============================" << std::endl << "conv structure has started!" << std::endl;
	// go over every structure step
	// every step can contain multiple substeps to generate the data for the next step
	for (size_t i = 0; i < structure.size(); i++)
	{
		sumHolder.clear();
		// every step can contain multiple series of substeps, which are summed up before going to the next step
		for (size_t j = 0; j < structure[i].size(); j++)
		{
			dataHolderSubStep = dataHolderStep;
			// getting the sum of the series of substeps
			for (size_t k = 0; k < structure[i][j].size(); k++)
			{
				if (structure[i][j][k].layerType == ConvLayerTypes::CalcLayer) {
					dataHolderSubStep = calcLayerList[structure[i][j][k].respectiveIndex].run(dataHolderSubStep);
					if (settings.printOutput) { std::cout << "Layer type: CalcLayer" << std::endl; }
				}
				else if (structure[i][j][k].layerType == ConvLayerTypes::ActivationLayer) {
					dataHolderSubStep = activationLayerList[structure[i][j][k].respectiveIndex].run(dataHolderSubStep);
					if (settings.printOutput) { std::cout << "Layer type: ActivationLayer" << std::endl; }
				}
				else if (structure[i][j][k].layerType == ConvLayerTypes::CalcPools) {
					dataHolderSubStep = calcPoolList[structure[i][j][k].respectiveIndex].run(dataHolderSubStep);
					if (settings.printOutput) { std::cout << "Layer type: CalcPoolsLayer" << std::endl; }
				}
			}
			std::cout << "substep has been run!" << std::endl;
			// check if the data from every series of substeps has the same width and height
			if (sumHolder.size() != 0) {
				if (sumHolder.size() != dataHolderSubStep.size() || sumHolder[0].size() != dataHolderSubStep[0].size()) { assert(false, "ERROR:SUBSTEPS_DONT_ALL_RETURN_DATA_OFF_THE_SAME_WIDTH_AND/OR_HEIGHT"); }
			}
			sumHolder.insert(sumHolder.end(), dataHolderSubStep.begin(), dataHolderSubStep.end());
		}
		dataHolderStep = sumHolder;
		std::cout << "step has been run!" << std::endl;
	}
	return dataHolderStep;
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

void ConvStructureCLS::printVector(std::vector<std::vector<float>>& data) {
	for (size_t i = 0; i < data.size(); i++)
	{
		for (size_t j = 0; j < data[i].size(); j++) std::cout << std::fixed << std::setprecision(2) << data[i][j] << ' ';
		std::cout << std::endl;
	}
	std::cout << "-=-=-=-=-=-=-=-=-=-=-=-" << std::endl;
}

void ConvStructureCLS::printVector(std::vector<std::vector<std::vector<float>>>& data) {
	for (size_t k = 0; k < data[0][0].size(); k++)
	{
		for (size_t i = 0; i < data.size(); i++)
		{
			for (size_t j = 0; j < data[i].size(); j++) std::cout << std::fixed << std::setprecision(2) << data[i][j][k] << ' ';
			std::cout << std::endl;
		}
		std::cout << "---------" << std::endl;
	}
	std::cout << "-=-=-=-=-=-=-=-=-=-=-=-" << std::endl;
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
		ConvStructureCLS::printVector(calcLayerList[i].settings.initialFilter);
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
					std::vector<std::vector<std::vector<float>>>& filter = calcLayerList[structure[i][j][k].respectiveIndex].settings.initialFilter;
					std::cout << "Conv layer: " << " x: " << filter.size() << " y: " << filter[0].size() << " z: " << filter[0][0].size() << std::endl;
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
