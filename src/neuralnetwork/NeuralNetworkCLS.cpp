#include "NeuralNetworkCLS.hpp"

float NeuralNetworkCLS::run(arr_3d_data& data, arr_3d_data& bestPossible) {
	float lastLayerBias = 0;
	for (size_t i = 0; i < structure.size(); i++)
	{
		if (structure[i].layerType == layerTypeOptions::HIDDEN) {
			hiddenLayers[structure[i].index].run(data, lastLayerBias);
			lastLayerBias = hiddenLayers[structure[i].index].bias;
		}
		else if (structure[i].layerType == layerTypeOptions::CONV) {
			convLayers[structure[i].index].runConvLayer(data);
			lastLayerBias = 0;
		}
	}
	return getScore(data, bestPossible);
}

void NeuralNetworkCLS::mutate(float severity) {
	for (size_t i = 0; i < convLayers.size(); i++)
	{
		convLayers[i].mutateConvStructure(severity);
	}
	for (size_t i = 0; i < hiddenLayers.size(); i++)
	{
		hiddenLayers[i].mutate(severity);
	}
}

float getScore(arr_3d_data& result, arr_3d_data& bestPossible) {
	// TODO: create proper example scoring function
	return 0;
}

NeuralNetworkCLS::~NeuralNetworkCLS() {
	for (size_t i = 0; i < hiddenLayers.size(); i++)
	{
		hiddenLayers[i].~HiddenLayerCLS();
	}
}

void NeuralNetworkCLS::addStructureElement(ConvStructureCLS convLayer, int layer) {
	int respectiveIndex = (int)convLayers.size();
	convLayers.push_back(convLayer);

	ANNElement element{ layerTypeOptions::CONV, respectiveIndex };
	if (layer == NULL) {
		structure.push_back(element);
	}
	else {
		structure[layer] = element;
	}
}

void NeuralNetworkCLS::addStructureElement(HiddenLayerCLS hiddenLayer, int layer) {
	int respectiveIndex = (int)hiddenLayers.size();
	hiddenLayers.push_back(hiddenLayer);

	ANNElement element{ layerTypeOptions::HIDDEN, respectiveIndex };
	if (layer == NULL) {
		structure.push_back(element);
	}
	else {
		structure[layer] = element;
	}
}