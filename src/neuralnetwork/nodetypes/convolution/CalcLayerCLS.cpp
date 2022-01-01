#include "CalcLayerCLS.hpp"

#include <cassert>
#include <math.h>
#include <iostream>
#include <random>

bool CalcLayerCLS::setSettings(CalcLayerSettings settings_) {
	settings = settings_;
	return true;
}

arr_3d_data& CalcLayerCLS::run(arr_3d_data& data, arr_3d_data& filter) {
	// check given inputs
	/*
	assert(filter.maxWidth % 2 == 1);
	assert(filter.maxHeight % 2 == 1);
	assert(filter.maxDepth % 2 == 1);

	int filterHalfWidth = (int)floor(filter.maxWidth / 2);
	int filterHalfHeight = (int)floor(filter.maxHeight / 2);
	int filterHalfDepth = (int)floor(filter.maxDepth / 2);

	int resultDepthSize;
	if (!settings.compensateDepthBorder) { assert(data.maxDepth >= filter.maxDepth); resultDepthSize = data.maxDepth - 2 * filterHalfDepth; }
	else { resultDepthSize = data.maxDepth; }

	// TODO: optimize this by calculating all values first, then summing them all up per point. (more memory intensive, but probably faster)
	if (!settings.compensateBorder) {
		
		arr_3d_data result{data.maxWidth - 2 * filterHalfWidth, data.maxHeight - 2 * filterHalfHeight, resultDepthSize};
		// Go over each of the points in the resulting 2d vector
		
		for (int i = 0; i < result.maxWidth; i++)
		{
			for (int j = 0; j < result.maxHeight; j++)
			{
				for (int k = 0; k < result.maxDepth; k++)
				{
					float value = 0;
					// calculate the value by multiplying the filter with the region around the chosen point
					for (int x = -filterHalfWidth; x <= filterHalfWidth; x++)
					{
						for (int y = -filterHalfHeight; y <= filterHalfHeight; y++)
						{
							for (int z = -filterHalfDepth; z <= filterHalfDepth; z++)
							{
								value += data.getValue(i + filterHalfWidth + x, j + filterHalfHeight + y, k + filterHalfDepth + z)
									* filter.getValue(x + filterHalfWidth, y + filterHalfHeight, z + filterHalfDepth);
							}
						}
					}
					result.setValue(i, j, k, value);
				}
			}
		}
		data.replaceDataAndDestroyOld(result);
		result.~arr_3d_data();
		return data;
	}
	else {
		
		arr_3d_data result{data.maxWidth, data.maxHeight, resultDepthSize};

		// Go over each of the points in the resulting 2d vector
		for (int i = 0; i < result.maxWidth; i++)
		{
			for (int j = 0; j < result.maxHeight; j++)
			{
				for (int k = 0; k < result.maxDepth; k++)
				{
					float value = 0;
					// calculate the value by multiplying the filter with the region around the chosen point
					for (int x = -filterHalfWidth; x <= filterHalfWidth; x++)
					{
						for (int y = -filterHalfHeight; y <= filterHalfHeight; y++)
						{
							for (int z = -filterHalfDepth; z <= filterHalfDepth; z++)
							{
								if (i + x >= 0 && i + x < result.maxWidth &&
									j + y >= 0 && j + y < result.maxHeight &&
									k + z >= 0 && k + z < result.maxDepth) {

									value += data.getValue(i + x, j + y, k + z)
												* filter.getValue(x + filterHalfWidth, y + filterHalfHeight, z + filterHalfDepth);
								}
								else {
									value += settings.borderCompensationValue * filter.getValue(x + filterHalfWidth, y + filterHalfHeight, z + filterHalfDepth);
								}
							}
						}
					}
					result.setValue(i, j, k, value);
				}
			}
		}
		data.replaceDataAndDestroyOld(result);
		return data;
	}
	*/
	arr_3d_data result{ data.maxWidth, data.maxHeight, data.maxDepth };
	data.copy(result);
	result.~arr_3d_data();
	return data;
}

void CalcLayerCLS::mutateFilter(float severity) {
	std::normal_distribution<float> d;
	std::random_device rd;
	std::mt19937 gen(rd());

	for (int i = 0; i < settings.initialFilter.maxValueCount; i++)
	{
		float value = settings.initialFilter.getValue(i);
		// Proportional component
		settings.initialFilter.setValue(i, value * (float)(1 + d(gen) * severity));
		// Independent component
		settings.initialFilter.setValue(i, value + (float)(((randValue0to1() - 0.5) * 2) * severity));

		// keeping the value within intended range
		if (std::abs(value) > settings.maxFilterValueSize) {
			(value > 0) ? settings.initialFilter.setValue(i, settings.maxFilterValueSize) : settings.initialFilter.setValue(i, -settings.maxFilterValueSize);
		}
	}
}

