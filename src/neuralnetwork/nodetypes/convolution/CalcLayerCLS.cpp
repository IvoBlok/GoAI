#include "CalcLayerCLS.hpp"

#include <cassert>
#include <math.h>
#include <iostream>
#include <random>

bool CalcLayerCLS::setSettings(CalcLayerSettings settings_) {
	settings = settings_;
	return true;
}

std::vector<std::vector<std::vector<float>>> CalcLayerCLS::run(std::vector<std::vector<std::vector<float>>>& data, const std::vector<std::vector<std::vector<float>>> filter) {
	
	// check given inputs
	assert(filter.size() % 2 == 1);
	assert(filter[0].size() % 2 == 1);
	assert(filter[0][0].size() % 2 == 1);

	// TODO: allow filters with different depth then the data, resulting in an output with a potential depth more then 1
	//assert(filter[0][0].size() == data[0][0].size());

	// calculate usefull variables to more easily get the filter values around a point

	// convert the 3d vector to a 1d array
	int filterXSize = (int)filter.size();
	int filterYSize = (int)filter[0].size();
	int filterZSize = (int)filter[0][0].size();

	int filterHalfWidth = (int)floor(filterXSize / 2);
	int filterHalfHeight = (int)floor(filterYSize / 2);
	int filterHalfDepth = (int)floor(filterZSize / 2);

	int resultDepthSize;
	if (!settings.compensateDepthBorder) { assert((int)data[0][0].size() >= filterZSize); resultDepthSize = (int)data[0][0].size() - 2 * filterHalfDepth; }
	else { resultDepthSize = (int)data[0][0].size(); }

	// TODO: optimize this by calculating all values first, then summing them all up per point. (more memory intensive, but probably faster)
	if (!settings.compensateBorder) {
		

		std::vector<std::vector<std::vector<float>>> result((int)data.size() - 2 * filterHalfWidth, std::vector<std::vector<float>> ((int)data[0].size() - 2 * filterHalfHeight, std::vector<float>(resultDepthSize, 0)));
		std::cout << "result depth: " << (int)data[0][0].size() - 2 * filterHalfDepth << std::endl;
		// Go over each of the points in the resulting 2d vector
		
		for (size_t i = 0; i < result.size(); i++)
		{
			for (size_t j = 0; j < result[0].size(); j++)
			{
				for (size_t k = 0; k < result[0][0].size(); k++)
				{
					float value = 0;
					// calculate the value by multiplying the filter with the region around the chosen point
					for (int x = -filterHalfWidth; x <= filterHalfWidth; x++)
					{
						for (int y = -filterHalfHeight; y <= filterHalfHeight; y++)
						{
							for (int z = -filterHalfDepth; z <= filterHalfDepth; z++)
							{
								value += data[i + filterHalfWidth + x][j + filterHalfHeight + y][k + filterHalfDepth + z]
									* filter[x + filterHalfWidth][y + filterHalfHeight][z + filterHalfDepth];
							}
						}
					}
					result[i][j][k] = value;
				}
			}
		}
		return result;
	}
	else {
		
		int dataWidthSize = (int)data.size();
		int dataHeightSize = (int)data[0].size();
		int dataDepthSize = (int)data[0][0].size();

		std::vector<std::vector<std::vector<float>>> result(dataWidthSize, std::vector<std::vector<float>>(dataHeightSize, std::vector<float>(resultDepthSize, 0)));

		// Go over each of the points in the resulting 2d vector
		for (size_t i = 0; i < result.size(); i++)
		{
			for (size_t j = 0; j < result[0].size(); j++)
			{
				for (size_t k = 0; k < result[0][0].size(); k++)
				{
					float value = 0;
					// calculate the value by multiplying the filter with the region around the chosen point
					for (int x = -filterHalfWidth; x <= filterHalfWidth; x++)
					{
						for (int y = -filterHalfHeight; y <= filterHalfHeight; y++)
						{
							for (int z = -filterHalfDepth; z <= filterHalfDepth; z++)
							{
								if (i + filterHalfWidth + x >= 0 && i + filterHalfWidth + x < dataWidthSize &&
									j + filterHalfHeight + y >= 0 && j + filterHalfHeight + y < dataHeightSize &&
									k + filterHalfDepth + z >= 0 && k + filterHalfDepth + z < dataDepthSize) {

									value += data[i + filterHalfWidth + x][j + filterHalfHeight + y][k + filterHalfDepth + z] * filter[x + filterHalfWidth][y + filterHalfHeight][z + filterHalfDepth];
								}
								else {
									value += settings.borderCompensationValue * filter[x + filterHalfWidth][y + filterHalfHeight][z + filterHalfDepth];
								}
							}
						}
					}
					result[i][j][k] = value;
				}
			}
		}
		return result;
	}
	
	return std::vector<std::vector<std::vector<float>>>(0);
}


void CalcLayerCLS::mutateFilter(float severity) {
	std::normal_distribution<float> d;
	std::random_device rd;
	std::mt19937 gen(rd());

	for (size_t i = 0; i < settings.initialFilter.size(); i++)
	{
		for (size_t j = 0; j < settings.initialFilter[0].size(); j++)
		{
			for (size_t k = 0; k < settings.initialFilter[0][0].size(); k++)
			{
				// Proportional component
				settings.initialFilter[i][j][k] *= (float)(1 + d(gen) * severity);
				// Independent component
				settings.initialFilter[i][j][k] += (float)(((randValue0to1() - 0.5) * 2) * severity);

				// keeping the value within intended range
				if (std::abs(settings.initialFilter[i][j][k]) > settings.maxFilterValueSize) {
					(settings.initialFilter[i][j][k] > 0) ? settings.initialFilter[i][j][k] = settings.maxFilterValueSize : settings.initialFilter[i][j][k] = -settings.maxFilterValueSize;
				}
			}
		}
	}
}

