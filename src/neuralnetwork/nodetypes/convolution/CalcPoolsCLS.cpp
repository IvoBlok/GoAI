#include "CalcPoolsCLS.hpp"

#include <cmath>

arr_3d_data CalcPoolsCLS::run(
	arr_3d_data& data,
	const int stride[3],
	PoolFunctionTypes functionType
) {
	//in the 2d data structure, the data[0] gives the first row, data[0][n] gives the n - 1 value in the first row

	arr_3d_data result{ (int)std::ceil(data.maxWidth / stride[0]), (int)std::ceil(data.maxHeight / stride[1]), (int)std::ceil(data.maxDepth / stride[2]) };

	for (size_t i = 0; i < result.maxWidth; i++)
	{
		for (size_t j = 0; j < result.maxHeight; j++)
		{
			for (size_t k = 0; k < result.maxDepth; k++)
			{
				arr_3d_data values{stride[0], stride[1], stride[2]};

				for (size_t x = 0; x < values.maxWidth; x++)
				{
					for (size_t y = 0; y < values.maxHeight; y++)
					{
						for (size_t z = 0; z < values.maxDepth; z++)
						{
							if (i * stride[0] + x >= data.maxWidth || j * stride[1] + y >= data.maxHeight || k * stride[2] + z >= data.maxDepth) {
								values.setValue(x, y, z, NULL);
							}
							else {
								values.setValue(x, y, z, data.getValue(i * stride[0] + x, j * stride[1] + y, k * stride[2] + z));
							}
						}
					}
				}
				if (functionType == PoolFunctionTypes::AVG) {
					result.setValue(i, j, k, this->poolFuncAvg(values));
				}
				else if (functionType == PoolFunctionTypes::MAX) {
					result.setValue(i, j, k, this->poolFuncMax(values));
				}
				else {
					result.setValue(i, j, k, NULL);
				}
			}
		}
	}
	data.replaceDataAndDestroyOld(result);
	return data;
}

float CalcPoolsCLS::poolFuncAvg(arr_3d_data& values) {
	float sum = 0;
	uint8_t count = 0;

	for (int i = 0; i < values.maxValueCount; i++)
	{
		if (values.getValue(i) != NULL) {
			count++;
			sum += values.getValue(i);
		}
	}

	return sum / count;
}

float CalcPoolsCLS::poolFuncMax(arr_3d_data& values) {
	float max = values.getValue(0);
	for (int i = 0; i < values.maxValueCount; i++)
	{
		if (values.getValue(i) != NULL && values.getValue(i) > max) {
			max = values.getValue(i);
		}
	}

	return max;
}
