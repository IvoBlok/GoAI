#include "CalcLayerCLS.hpp"

#include <cassert>
#include <math.h>
#include <iostream>
#include <random>

bool CalcLayerCLS::setSettings(CalcLayerSettings settings_) {
	settings = settings_;
	return true;
}

std::vector<std::vector<float>> CalcLayerCLS::run(std::vector<std::vector<float>>& data, const std::vector<std::vector<float>> filter) {
	
	// check given inputs
	assert(filter.size() % 2 == 1);
	assert(filter[0].size() % 2 == 1);


	// calculate usefull variables to more easily get the filter values around a point
	int filterHalfWidth = (int)floor(filter.size() / 2);
	int filterHalfHeight = (int)floor(filter[0].size() / 2);

	// TODO: optimize this by calculating all values first, then summing them all up per point. (more memory intensive, but probably faster)
	if (!settings.compensateBorder) {
		
		std::vector<std::vector<float>> result( (int)data.size() - 2, std::vector<float> ((int)data[0].size() - 2, 0));

		// Go over each of the points in the resulting 2d vector
		for (size_t i = 1; i < data.size() - 1; i++)
		{
			for (size_t j = 1; j < data[0].size() - 1; j++)
			{
				float value = 0;

				
				// calculate the value by multiplying the filter with the region around the chosen point
				for (int k = -filterHalfWidth; k <= filterHalfWidth; k++)
				{
					for (int q = -filterHalfHeight; q <= filterHalfHeight; q++)
					{
						value += data[i + k][j + q] * filter[(int)k + filterHalfWidth][(int)q + filterHalfHeight];
					}
				}
				result[i - 1][j - 1] = value;
				std::cout << value << " ";
			}
		}
		return result;
	}
	else if (settings.compensateBorder != NULL) {
		std::vector<std::vector<float>> result((int)data.size(), std::vector<float>((int)data[0].size(), 0));

		// Go over each of the points in the resulting 2d vector
		for (size_t i = 0; i < data.size(); i++)
		{
			for (size_t j = 0; j < data[0].size(); j++)
			{
				float value = 0;

				// calculate the value by multiplying the filter with the region around the chosen point
				for (int k = -filterHalfWidth; k <= filterHalfWidth; k++)
				{
					for (int q = -filterHalfHeight; q <= filterHalfHeight; q++)
					{
						if (i + k >= 0 && i + k < data.size() && j + q >= 0 && j + q < data[0].size()) {
							value += data[i + k][j + q] * filter[(int)k + filterHalfWidth][(int)q + filterHalfHeight];
						}
						else {
							value += settings.borderCompensationValue * filter[(int)k + filterHalfWidth][(int)q + filterHalfHeight];
						}
					}
				}
				result[i][j] = value;
			}
		}

		return result;
	}
	
	return std::vector<std::vector<float>>(0);
}

void CalcLayerCLS::mutateFilter(float severity) {
	std::normal_distribution<float> d;
	std::random_device rd;
	std::mt19937 gen(rd());

	for (size_t i = 0; i < settings.initialFilter.size(); i++)
	{
		for (size_t j = 0; j < settings.initialFilter[0].size(); j++)
		{
			// Proportional component
			//settings.initialFilter[i][j] *= (float)((-0.5 + randValue0to1()) * severity + 1);
			settings.initialFilter[i][j] *= (float)(1 + d(gen) * severity);
			// Independent component
			settings.initialFilter[i][j] += ((randValue0to1() - 0.5) * 2) * severity;
			
			// keeping the value within intended range
			if (std::abs(settings.initialFilter[i][j]) > 1) {
				(settings.initialFilter[i][j] > 0) ? settings.initialFilter[i][j] = 1 : settings.initialFilter[i][j] = -1;
			}
		}
	}
}

