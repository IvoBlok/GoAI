#include "ActivationLayerCLS.hpp"

#include <iostream>
#include <cassert>
#include <cmath>

void ActivationLayerCLS::run(arr_3d_data& data, ActivationLayerSettings settings_) {
	for (int i = 0; i < data.maxValueCount; i++)
	{
		if (settings_.functionType == ActivationFunctionTypes::RELU) {
			data.setValue(i, this->ReLuActivationFunction(data.getValue(i)));
		}
		else if (settings_.functionType == ActivationFunctionTypes::SIGMOID) {
			data.setValue(i, this->SigmoidActivationFunction(data.getValue(i)));
		}
		else {
			std::cout << "ERROR::NO_VALID_ACTIVATION_FUNCTION_NAME_GIVEN" << std::endl;
			assert(false);
		}
	}
}

float ActivationLayerCLS::ReLuActivationFunction(float value) {
	return (value > 0) ? value : 0;
}

float ActivationLayerCLS::SigmoidActivationFunction(float value) {
	return std::tanh(value);
}

