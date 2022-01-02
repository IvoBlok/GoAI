#pragma once

#include "HiddenCellCLS.hpp"
#include "../convolution/arr_3d_data.hpp"

#include <vector>
#include <memory>
#include <random>

class HiddenLayerCLS
{
private:
public:
	std::unique_ptr<HiddenCellCLS[]> cells;
	uint16_t cellCount;
	float bias;

	HiddenLayerCLS(uint16_t layerSize, uint16_t backLayerSize);
	~HiddenLayerCLS();

	void run(arr_3d_data& previousLayerData, float bias = 0);

	void activationFunc(float& value); 

	void mutate(float severity);
};

