#pragma once
#include "neuralnetwork/nodetypes/convolution/arr_3d_data.hpp"

#include <sstream>
#include <vector>
#include <random>
#include <ctime>

float tempCalcScore(arr_3d_data data) {
    float sum = 0;
    for (int i = 0; i < data.maxValueCount; i++)
    {
        sum += data.getValue(i);
    }
    return sum;
}

std::string getCurrentTimeString() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;

    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    return oss.str();
}

std::string getProjectPath() {
    // get prjPath and remove the string quotes
    std::string prjPath = EXPAND(GOAIPRJPATH);
    prjPath.erase(0, 1); prjPath.erase(prjPath.size() - 2);
    return prjPath;
}

void initRandomnessSeed() {
    std::srand((unsigned int)time(NULL));
}

float randValueneg1to1() {
    return ((float)(std::rand()) / (float)RAND_MAX) * 2 - 1;
}