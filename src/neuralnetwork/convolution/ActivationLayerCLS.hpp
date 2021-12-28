#pragma once

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
	std::vector<std::vector<float>> run(std::vector<std::vector<float>>& data) {
		return run(data, settings);
	}
	std::vector<std::vector<float>> run(std::vector<std::vector<float>>& data, ActivationLayerSettings settings_);
};

