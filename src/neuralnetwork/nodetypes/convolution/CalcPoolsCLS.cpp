#include "CalcPoolsCLS.hpp"

#include <cmath>

std::vector<std::vector<std::vector<float>>> CalcPoolsCLS::run(
	std::vector<std::vector<std::vector<float>>>& data,
	const int stride[3],
	PoolFunctionTypes functionType
) {
	//in the 2d data structure, the data[0] gives the first row, data[0][n] gives the n - 1 value in the first row

	std::vector<std::vector<std::vector<float>>> result(std::ceil(data.size() / stride[0]), std::vector<std::vector<float>>(std::ceil(data[0].size() / stride[1]), std::vector<float>(std::ceil(data[0][0].size() / stride[2]), 0)));

	for (size_t i = 0; i < std::ceil(data.size() / stride[0]); i++)
	{
		for (size_t j = 0; j < std::ceil(data[0].size() / stride[1]); j++)
		{
			for (size_t k = 0; k < std::ceil(data[0][0].size() / stride[2]); k++)
			{
				std::vector<std::vector<std::vector<float>>> values(stride[0], std::vector<std::vector<float>>(stride[1], std::vector<float>(stride[2], 0)));

				for (size_t x = 0; x < stride[0]; x++)
				{
					for (size_t y = 0; y < stride[1]; y++)
					{
						for (size_t z = 0; z < stride[2]; z++)
						{
							if (i * stride[0] + x >= data.size() || j * stride[1] + y >= data[0].size() || k * stride[2] + z >= data[0][0].size()) {
								values[x][y][z] = NULL;
							}
							else {
								values[x][y][z] = data[i * stride[0] + x][j * stride[1] + y][k * stride[2] + z];
							}
						}
					}
				}
				if (functionType == PoolFunctionTypes::AVG) {
					result[i][j][k] = this->poolFuncAvg(values);
				}
				else if (functionType == PoolFunctionTypes::MAX) {
					result[i][j][k] = this->poolFuncMax(values);
				}
				else {
					result[i][j][k] = NULL;
				}
			}
		}
	}
	return result;
}

float CalcPoolsCLS::poolFuncAvg(std::vector<std::vector<std::vector<float>>>& values) {
	float sum = 0;
	uint16_t count = 0;
	for (size_t i = 0; i < values.size(); i++)
	{
		for (size_t j = 0; j < values[0].size(); j++)
		{
			for (size_t k = 0; k < values[0][0].size(); k++)
			{
				if (values[i][j][k] != NULL)
				{
					count++;
					sum += values[i][j][k];
				}
			}
		}
	}
	return sum / count;
}

float CalcPoolsCLS::poolFuncMax(std::vector<std::vector<std::vector<float>>>& values) {
	float max = values[0][0][0];
	for (size_t i = 0; i < values.size(); i++)
	{
		for (size_t j = 0; j < values[0].size(); j++)
		{
			for (size_t k = 0; k < values[0][0].size(); k++)
			{
				if (values[i][j][k] != NULL && values[i][j][k] > max) {
					max = values[i][j][k];
				}
			}
		}
	}
	return max;
}
