#include "HiddenCellCLS.hpp"

HiddenCellCLS::HiddenCellCLS(uint16_t backLayercellCount) : connectionCount(backLayercellCount) {
	backConnections = std::make_unique<cellConnection[]>(backLayercellCount);
	for (int i = 0; i < backLayercellCount; i++)
	{
		backConnections[i].cellIndex = i;
		backConnections[i].weight = randValueneg1to1();
	}

	biasWeight = randValueneg1to1();
}

HiddenCellCLS::~HiddenCellCLS() {
	backConnections.reset();
	backConnections = nullptr;
}

HiddenCellCLS HiddenCellCLS::operator=(const HiddenCellCLS& dataToCopy) {
	this->biasWeight = dataToCopy.biasWeight;
	this->connectionCount = dataToCopy.connectionCount;
	this->backConnections.reset();
	this->backConnections = std::make_unique < cellConnection[] >(this->connectionCount);
	for (int i = 0; i < this->connectionCount; i++)
	{
		this->backConnections[i] = dataToCopy.backConnections[i];
	}
}