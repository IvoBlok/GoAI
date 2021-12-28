
#pragma once

#include "CalcLayerCLS.hpp"
#include "ActivationLayerCLS.hpp"
#include "CalcPoolsCLS.hpp"

#include <vector>
#include <memory>
#include <iostream>
#include <iomanip>

struct ConvStructureSettings {
	bool printOutput = false;
};

enum class ConvLayerTypes {
	CalcLayer,
	CalcPools,
	ActivationLayer
};

struct ConvStructureElement {
	ConvStructureElement(int respectiveIndex_, ConvLayerTypes layerType_) { this->respectiveIndex = respectiveIndex_; this->layerType = layerType_;  }
	int respectiveIndex;
	ConvLayerTypes layerType;
};

class ConvStructureCLS
{
private:
	// sadly enough we need to define a vector for every conv layer type, because c++ is being stubborn
	std::vector<CalcLayerCLS> CalcLayerList;
	std::vector<CalcPoolsCLS> CalcPoolList;
	std::vector<ActivationLayerCLS> ActivationLayerList;

public:
	ConvStructureSettings settings;
	std::vector<ConvStructureElement> structure;

	ConvStructureCLS(ConvStructureSettings settings = ConvStructureSettings()) { this->settings = settings; }
	
	void addStructureElement(CalcLayerCLS calcLayer_);
	void addStructureElement(CalcPoolsCLS calcPools_);
	void addStructureElement(ActivationLayerCLS ActivationLayer_);

	std::vector<std::vector<float>> runConvStructure(std::vector<std::vector<float>> data);
	void mutateConvStructure(float severity);

	void print2dVector(std::vector<std::vector<float>> data);
	void printFilters(std::string filterName = "");
};

