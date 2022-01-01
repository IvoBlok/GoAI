#pragma once

#include "arr_3d_data.hpp"

#include <vector>
#include <map>
#include <random>
#include <ctime>

static float randValue0to1() {
	return (float)(std::rand()) / (float)RAND_MAX;
}

struct CalcLayerSettings {
	bool compensateBorder = true;
	bool compensateDepthBorder = false;
	float borderCompensationValue = 0;
	arr_3d_data initialFilter;
	float maxFilterValueSize = 1;
};

class CalcLayerCLS
{
public:
	CalcLayerSettings settings;
	CalcLayerCLS(CalcLayerSettings settings_ = CalcLayerSettings{}) {
		settings = settings_;
	}
	bool setSettings(CalcLayerSettings settings_);

	arr_3d_data& run(arr_3d_data& data) { return this->run(data, settings.initialFilter); }
	arr_3d_data& run(arr_3d_data& data, arr_3d_data& filter);

	void mutateFilter(float severity);
};

