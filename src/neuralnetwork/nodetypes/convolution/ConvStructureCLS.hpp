
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
	std::vector<CalcLayerCLS> calcLayerList;
	std::vector<CalcPoolsCLS> calcPoolList;
	std::vector<ActivationLayerCLS> activationLayerList;

public:
	ConvStructureSettings settings;
	std::vector<std::vector<std::vector<ConvStructureElement>>> structure;

	ConvStructureCLS(ConvStructureSettings settings = ConvStructureSettings()) { this->settings = settings; }
	
	void addStructureElement(CalcLayerCLS calcLayer_, int step = NULL, int substep = NULL);
	void addStructureElement(CalcPoolsCLS calcPools_, int step = NULL, int substep = NULL);
	void addStructureElement(ActivationLayerCLS activationLayer_, int step = NULL, int substep = NULL);

	std::vector<std::vector<std::vector<float>>> runConvStructure(std::vector<std::vector<std::vector<float>>> data);
	void mutateConvStructure(float severity);

	static void printVector(std::vector<std::vector<float>>& data);
	static void printVector(std::vector<std::vector<std::vector<float>>>& data);

	void printFilters(std::string filterName = "");

	void printStructure();
};
