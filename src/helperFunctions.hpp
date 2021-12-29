#pragma once

#include <sstream>
#include <vector>

float tempCalcScore(std::vector<std::vector<float>> data) {
    float sum = 0;
    for (size_t i = 0; i < data.size(); i++)
    {
        for (size_t j = 0; j < data[0].size(); j++)
        {
            sum += data[i][j];
        }
    }
    return sum;
}

float tempCalcScore(std::vector<std::vector<std::vector<float>>> data) {
    float sum = 0;
    for (size_t i = 0; i < data.size(); i++)
    {
        for (size_t j = 0; j < data[0].size(); j++)
        {
            for (size_t k = 0; k < data[0][0].size(); k++)
            {
                sum += data[i][j][k];
            }
        }
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