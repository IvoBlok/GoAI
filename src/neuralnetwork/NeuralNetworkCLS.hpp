#pragma once

#include "nodetypes/convolution/ConvStructureCLS.hpp"
#include "nodetypes/hidden/HiddenLayerCLS.hpp"

#include "nodetypes/convolution/arr_3d_data.hpp"

#include <vector>

enum class layerTypeOptions {
	CONV,
	HIDDEN
};

struct ANNElement {
	ANNElement(layerTypeOptions layerType_, int index_) : layerType(layerType_),index(index_) {}
	layerTypeOptions layerType;
	int index;
};

class NeuralNetworkCLS
{
private:
	//potential layers
	std::vector<ConvStructureCLS> convLayers;
	std::vector<HiddenLayerCLS> hiddenLayers;

public:
	std::vector<ANNElement> structure;

	float run(arr_3d_data& data, arr_3d_data& bestPossible);

	void addStructureElement(ConvStructureCLS convLayer, int layer = NULL);
	void addStructureElement(HiddenLayerCLS hiddenLayer, int layer = NULL);

	float getScore(arr_3d_data& result, arr_3d_data& bestPossible);

	void mutate(float severity);

	~NeuralNetworkCLS();
};

