#include "CalcPoolsCLS.hpp"

#include <cmath>

std::vector<std::vector<float>> CalcPoolsCLS::run(
	std::vector<std::vector<float>>& data,
	const int stride[2],
	PoolFunctionTypes functionType
) {
	//in the 2d data structure, the data[0] gives the first row, data[0][n] gives the n - 1 value in the first row

	std::vector<std::vector<float>> result(std::ceil(data.size() / stride[0]), std::vector<float>(std::ceil(data[0].size() / stride[1]), 0));

	for (size_t i = 0; i < data.size() / stride[0]; i++)
	{
		for (size_t j = 0; j < data[0].size() / stride[1]; j++)
		{
			std::vector<std::vector<float>> values(stride[0], std::vector<float>(stride[1], 0));

			for (size_t k = 0; k < stride[0]; k++)
			{
				for (size_t q = 0; q < stride[1]; q++)
				{
					if (i * stride[0] + k >= data.size() || j * stride[1] + q >= data[0].size()) {
						values[k][q] = NULL;
					}
					else {
						values[k][q] = data[i * stride[0] + k][j * stride[1] + q];
					}
				}
			}
			if (functionType == PoolFunctionTypes::AVG) {
				result[i][j] = this->poolFuncAvg(values);
			}
			else if (functionType == PoolFunctionTypes::MAX) {
				result[i][j] = this->poolFuncMax(values);
			}
			else {
				result[i][j] = NULL;
			}
		}
	}
	return result;
}

float CalcPoolsCLS::poolFuncAvg(std::vector<std::vector<float>>& values) {
	float sum = 0;
	uint16_t count = 0;
	for (size_t i = 0; i < values.size(); i++)
	{
		for (size_t j = 0; j < values[0].size(); j++)
		{
			if (values[i][j] != NULL)
			{
				count++;
				sum += values[i][j];
			}
		}
	}
	return sum / count;
}

float CalcPoolsCLS::poolFuncMax(std::vector<std::vector<float>>& values) {
	float max =  values[0][0];
	for (size_t i = 0; i < values.size(); i++)
	{
		for (size_t j = 0; j < values[0].size(); j++)
		{
			if (values[i][j] != NULL && values[i][j] > max) {
				max = values[i][j];
			}
		}
	}
	return max;
}
