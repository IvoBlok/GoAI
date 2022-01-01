#pragma once

#include "arr_3d_data.hpp"

#include <vector>
#include <string>
#include <iostream>

enum class ActivationFunctionTypes {
	RELU,
	SIGMOID
};

struct ActivationLayerSettings {
	ActivationLayerSettings(ActivationFunctionTypes functionType_ = ActivationFunctionTypes::RELU) {
		this->functionType = functionType_;
	}
	ActivationFunctionTypes functionType;
};

class ActivationLayerCLS
{
private:
	float ReLuActivationFunction(float value);
	float SigmoidActivationFunction(float value);

public:
	ActivationLayerSettings settings;

	ActivationLayerCLS(ActivationLayerSettings settings_) {
		settings = settings_;
	}
	void run(arr_3d_data& data) {
		return run(data, settings);
	}
	void run(arr_3d_data& data, ActivationLayerSettings settings_);
};

