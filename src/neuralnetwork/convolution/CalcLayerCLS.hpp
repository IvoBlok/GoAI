#pragma once

#include <vector>
#include <map>
#include <random>
#include <ctime>

static float randValue0to1() {
	return (float)(std::rand()) / (float)RAND_MAX;
}

struct CalcLayerSettings {
	std::vector<std::vector<float>> createRandomFilter(int width, int height) {
		std::vector<std::vector<float>> temp(width, std::vector<float>(height, 0));
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				temp[i][j] = randValue0to1() * 2 - 1;
			}
		}
		return temp;
	}
	bool compensateBorder = true;
	float borderCompensationValue = 0;
	std::vector<std::vector<float>> initialFilter = createRandomFilter(3, 3);
	float maxFilterValueSize = 1;
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

