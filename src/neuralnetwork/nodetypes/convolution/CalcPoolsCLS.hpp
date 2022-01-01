#pragma once

#include "arr_3d_data.hpp"

#include <vector>
#include <cassert>

enum class PoolFunctionTypes {
	AVG,
	MAX
};

struct CalcPoolsSettings {
	void setStride(int stride_[]) {
		stride[0] = stride_[0];
		stride[1] = stride_[1];
		stride[2] = stride_[2];
	}
	int stride[3] = { 2, 2, 1 };
	PoolFunctionTypes functionType = PoolFunctionTypes::MAX;
};

class CalcPoolsCLS
{
private:
	float poolFuncAvg(arr_3d_data& values);
	float poolFuncMax(arr_3d_data& values);

public:
	CalcPoolsSettings settings;
	
	CalcPoolsCLS(CalcPoolsSettings settings = CalcPoolsSettings()) { this->settings = settings; }
	
	arr_3d_data run(
		arr_3d_data& data,
		const int stride[2],
		PoolFunctionTypes functionType
		);

	arr_3d_data run(
		arr_3d_data& data
		) {
		return run(data, settings.stride, settings.functionType);
	}
};

