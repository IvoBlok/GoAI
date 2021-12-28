#define stringify( name )
#include "ConvStructureCLS.hpp"
#include <cstring>

std::vector<std::vector<float>> ConvStructureCLS::runConvStructure(std::vector<std::vector<float>> data) {
	std::vector<std::vector<float>> dataHolder = data;

	for (size_t i = 0; i < structure.size(); i++)
	{
		if (structure[i].layerType == ConvLayerTypes::CalcLayer) {
			dataHolder = CalcLayerList[structure[i].respectiveIndex].run(dataHolder);
			if (settings.printOutput) { std::cout << "Layer type: CalcLayer" << std::endl; }
		} else if (structure[i].layerType == ConvLayerTypes::ActivationLayer) {
			dataHolder = ActivationLayerList[structure[i].respectiveIndex].run(dataHolder);
			if (settings.printOutput) { std::cout << "Layer type: ActivationLayer" << std::endl; }
		} else if (structure[i].layerType == ConvLayerTypes::CalcPools) {
			dataHolder = CalcPoolList[structure[i].respectiveIndex].run(dataHolder);
			if (settings.printOutput) { std::cout << "Layer type: CalcPoolsLayer" << std::endl; }
		}
		if (settings.printOutput) {
			print2dVector(dataHolder);
		}
	}
	return dataHolder;
}

void ConvStructureCLS::addStructureElement(CalcLayerCLS calcLayer_) {

	int respectiveIndex = (int)CalcLayerList.size();
	structure.push_back(ConvStructureElement(respectiveIndex, ConvLayerTypes::CalcLayer));
	CalcLayerList.push_back(calcLayer_);
}

void ConvStructureCLS::addStructureElement(CalcPoolsCLS calcPools_) {

	int respectiveIndex = (int)CalcPoolList.size();
	structure.push_back(ConvStructureElement(respectiveIndex, ConvLayerTypes::CalcPools));
	CalcPoolList.push_back(calcPools_);
}

void ConvStructureCLS::addStructureElement(ActivationLayerCLS ActivationLayer_) {

	int respectiveIndex = (int)ActivationLayerList.size();
	structure.push_back(ConvStructureElement{respectiveIndex, ConvLayerTypes::ActivationLayer});
	ActivationLayerList.push_back(ActivationLayer_);
}

void ConvStructureCLS::print2dVector(std::vector<std::vector<float>> data) {
	for (size_t i = 0; i < data.size(); i++)
	{
		for (size_t j = 0; j < data[i].size(); j++) std::cout << std::fixed << std::setprecision(2) << data[i][j] << ' ';
		std::cout << std::endl;
	}
	std::cout << "-=-=-=-=-=-=-=-=-=-=-=-" << std::endl;
}

void ConvStructureCLS::mutateConvStructure(float severity) {
	// CalcLayers have filters that can be mutated
	for (size_t i = 0; i < CalcLayerList.size(); i++)
	{
		CalcLayerList[i].mutateFilter(severity);
	}
}

void ConvStructureCLS::printFilters(std::string filterName) {
	for (size_t i = 0; i < CalcLayerList.size(); i++)
	{
		std::cout << "Filter: " << filterName << " " << i << std::endl;
		print2dVector(CalcLayerList[i].settings.initialFilter);
	}
}