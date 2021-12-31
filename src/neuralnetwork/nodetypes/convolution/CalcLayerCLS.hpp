#pragma once

#include <vector>
#include <map>
#include <random>
#include <ctime>

static float randValue0to1() {
	return (float)(std::rand()) / (float)RAND_MAX;
}

struct CalcLayerSettings {
	static std::vector<std::vector<std::vector<float>>> createRandomFilter(int width, int height, int depth) {
		std::vector<std::vector<std::vector<float>>> temp(width, std::vector<std::vector<float>>(height, std::vector<float>(depth, 0)));
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				for (int k = 0; k < depth; k++)
				{
					temp[i][j][k] = randValue0to1() * 2 - 1;
				}
			}
		}
		return temp;
	}
	bool compensateBorder = true;
	bool compensateDepthBorder = false;
	float borderCompensationValue = 0;
	std::vector<std::vector<std::vector<float>>> initialFilter = createRandomFilter(3, 3, 1);
	float maxFilterValueSize = 1;
};

class CalcLayerCLS
{
public:
	CalcLayerSettings settings;
	CalcLayerCLS(CalcLayerSettings settings = CalcLayerSettings()) {
		this->settings = settings;
	}
	bool setSettings(CalcLayerSettings settings_);

	std::vector<std::vector<std::vector<float>>> run(std::vector<std::vector<std::vector<float>>>& data) { return this->run(data, settings.initialFilter); }
	std::vector<std::vector<std::vector<float>>> run(std::vector<std::vector<std::vector<float>>>& data, const std::vector<std::vector<std::vector<float>>> filter);

	void mutateFilter(float severity);
};

