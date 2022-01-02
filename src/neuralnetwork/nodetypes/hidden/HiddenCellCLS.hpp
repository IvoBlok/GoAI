#pragma once

#include "../../../helperFunctions.hpp"

#include <vector>
#include <memory>

struct cellConnection {
	uint16_t cellIndex;
	float weight;
};

class HiddenCellCLS
{
private:

public:
	std::unique_ptr<cellConnection[]> backConnections;
	uint16_t connectionCount;

	float biasWeight;

	HiddenCellCLS(HiddenCellCLS&&) = default;
	HiddenCellCLS(const HiddenCellCLS&) = default;
	HiddenCellCLS operator=(const HiddenCellCLS&);

	HiddenCellCLS(uint16_t backLayercellCount);
	~HiddenCellCLS();
};

