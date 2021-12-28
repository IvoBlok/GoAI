#pragma once

#include <vector>
#include <cassert>

enum class PoolFunctionTypes {
	AVG,
	MAX
};

struct CalcPoolsSettings {
	void set2Dstride(int stride_[]) {
		stride2D[0] = stride_[0];
		stride2D[1] = stride_[1];
	}
	int stride2D[2] = { 2, 2 };
	int stride3D[3] = { 2, 2, 2 };
	PoolFunctionTypes functionType = PoolFunctionTypes::MAX;
};

class CalcPoolsCLS
{
private:
	float poolFuncAvg(std::vector<std::vector<float>>& values);
	float poolFuncMax(std::vector<std::vector<float>>& values);

public:
	CalcPoolsSettings settings;
	
	CalcPoolsCLS(CalcPoolsSettings settings = CalcPoolsSettings()) { this->settings = settings; }
	
	std::vector<std::vector<float>> run(
		std::vector<std::vector<float>>& data,
		const int stride[2],
		PoolFunctionTypes functionType
		);

	std::vector<std::vector<float>> run(
		std::vector<std::vector<float>>& data
		) {
		return run(data, settings.stride2D, settings.functionType);
	}
};

