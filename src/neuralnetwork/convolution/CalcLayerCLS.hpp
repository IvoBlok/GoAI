#pragma once

#include <vector>
#include <map>
#include <random>

static float randValue0to1() {
	return (float)(std::rand()) / (float)RAND_MAX;
}

struct CalcLayerSettings {
	bool compensateBorder = true;
	float borderCompensationValue = 0;
	std::vector<std::vector<float>> initialFilter = { 
		{randValue0to1() * 2 - 1, randValue0to1() * 2 - 1, randValue0to1() * 2 - 1},
		{randValue0to1() * 2 - 1, randValue0to1() * 2 - 1, randValue0to1() * 2 - 1},
		{randValue0to1() * 2 - 1, randValue0to1() * 2 - 1, randValue0to1() * 2 - 1},
	};
};

class CalcLayerCLS
{
private:

public:
	CalcLayerSettings settings;
	CalcLayerCLS(CalcLayerSettings settings = CalcLayerSettings()) {
		this->settings = settings;
	}
	bool setSettings(CalcLayerSettings settings_);

	std::vector<std::vector<float>> run(std::vector<std::vector<float>>& data) { return this->run(data, settings.initialFilter); }
	std::vector<std::vector<float>> run(std::vector<std::vector<float>>& data, const std::vector<std::vector<float>> filter);

	void mutateFilter(float severity);

};

