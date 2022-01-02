#include "HiddenLayerCLS.hpp"

#include <cmath>

void HiddenLayerCLS::activationFunc(float& value) {
	value = std::tanh(value); // sigmoid
}

void HiddenLayerCLS::run(arr_3d_data& previousLayerData, float bias = 0) {
	arr_3d_data layerData{cellCount};

	for (int i = 0; i < cellCount; i++)
	{
		float value = bias * cells[i].biasWeight;
		for (int j = 0; j < cells[i].connectionCount; j++)
		{
			value += previousLayerData.getValue(cells[i].backConnections[j].cellIndex) * cells[i].backConnections[j].weight;
		}
		activationFunc(value);
		layerData.setValue(i, value);
	}

	previousLayerData = layerData;
	layerData.~arr_3d_data();
}

HiddenLayerCLS::HiddenLayerCLS(uint16_t layerSize, uint16_t backLayerSize ) : cellCount(layerSize) {
	if (cellCount && cellCount > 0) {
		cells = std::make_unique < HiddenCellCLS[] > (cellCount);
		for (int i = 0; i < cellCount; i++)
		{
			cells[i] = HiddenCellCLS{ backLayerSize };
		}
		bias = randValueneg1to1();
	}
	std::cout << "ERROR:INVALID_LAYER_SIZE_GIVEN" << std::endl;
	abort();
}

HiddenLayerCLS::~HiddenLayerCLS() {
	for (int i = 0; i < cellCount; i++)
	{
		cells[i].~HiddenCellCLS();
	}
	cells.reset();
	cells = nullptr;
}

void HiddenLayerCLS::mutate(float severity) {
	std::normal_distribution<float> d;
	std::random_device rd;
	std::mt19937 gen(rd());

	bias *= (float)(1 + d(gen) * severity);
	
	for (int i = 0; i < cellCount; i++)
	{
		for (int j = 0; j < cells[i].connectionCount; j++)
		{
			cells[i].backConnections[j].weight *= (float)(1 + d(gen) * severity);
		}
	}
}