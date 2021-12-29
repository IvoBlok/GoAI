#include "ActivationLayerCLS.hpp"

#include <iostream>
#include <cassert>
#include <cmath>

std::vector<std::vector<std::vector<float>>> ActivationLayerCLS::run(std::vector<std::vector<std::vector<float>>>& data, ActivationLayerSettings settings_) {
	std::vector<std::vector<std::vector<float>>> result(data.size(), std::vector<std::vector<float>>(data[0].size(), std::vector<float>(data[0][0].size(), 0)));
	for (size_t i = 0; i < data.size(); i++)
	{
		for (size_t j = 0; j < data[0].size(); j++)
		{
			for (size_t k = 0; k < data[0][0].size(); k++)
			{
				if (settings_.functionType == ActivationFunctionTypes::RELU) {
					result[i][j][k] = this->ReLuActivationFunction(data[i][j][k]);
				}
				else if (settings_.functionType == ActivationFunctionTypes::SIGMOID) {
					result[i][j][k] = this->SigmoidActivationFunction(data[i][j][k]);
				}
				else {
					std::cout << "ERROR::NO_VALID_ACTIVATION_FUNCTION_NAME_GIVEN" << std::endl;
					assert(false);
				}
			}
		}
	}

	return result;
}

float ActivationLayerCLS::ReLuActivationFunction(float value) {
	return (value > 0) ? value : 0;
}

float ActivationLayerCLS::SigmoidActivationFunction(float value) {
	return std::tanh(value);
}

