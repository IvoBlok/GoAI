#include "arr_3d_data.hpp"

#include <vector>
#include <map>
#include <random>
#include <ctime>


static float randValueneg1to1() {
	return ((float)(std::rand()) / (float)RAND_MAX) * 2 - 1;
}

arr_3d_data::arr_3d_data(int width_, int height_, int depth_) {
	allocateSpace(width_, height_, depth_);
}

arr_3d_data::~arr_3d_data() {
	arr.release();
	arr = nullptr;
}

void arr_3d_data::allocateSpace(int width_, int height_, int depth_) {
	maxWidth = width_;
	maxHeight = height_;
	maxDepth = depth_;
	int amount = width_ * height_ * depth_;
	if (maxValueCount != 0) { arr.release(); }
	arr = std::unique_ptr<float[]>(new float[amount]);
	maxValueCount = amount;
	for (int i = 0; i < maxValueCount; i++)
	{
		arr[i] = 0;
	}
}

void arr_3d_data::empty() {
	allocateSpace(0, 0, 0);
}

float arr_3d_data::getValue(int widthIndex_, int heightIndex_, int depthIndex_) {
	if (widthIndex_ >= maxWidth || heightIndex_ >= maxHeight || depthIndex_ >= maxDepth) {
		assert(false, "ERROR::GIVEN_INDEX_IS_OUT_OF_RANGE");
	}
	return arr[maxHeight * (depthIndex_ * maxWidth + widthIndex_) + heightIndex_];
}

float arr_3d_data::getValue(int index_) {
	if (index_ >= 0 && index_ < maxValueCount) {
		return arr[index_];
	}
	else {
		std::cout << "ERROR::GIVEN_INDEX_IS_OUT_OF_RANGE" << std::endl;
		abort();
	}
}

void arr_3d_data::setValue(int widthIndex_, int heightIndex_, int depthIndex_, float value) {
	if (widthIndex_ >= maxWidth || heightIndex_ >= maxHeight || depthIndex_ >= maxDepth) {
		std::cout << maxWidth << " " << maxHeight << " " << maxDepth << std::endl;
		std::cout << widthIndex_ << " " << heightIndex_ << " " << depthIndex_ << std::endl;
		std::cout << "ERROR::GIVEN_INDEX_IS_OUT_OF_RANGE" << std::endl;
		abort();
	}
	setValue(maxHeight * (depthIndex_ * maxWidth + widthIndex_) + heightIndex_, value); // compact 3d to 1d index conversion;
}

void arr_3d_data::setValue(int index_, float value) {
	if (index_ >= 0 && index_ < maxValueCount) {
		arr[index_] = value;
	}
	else {
		std::cout << "ERROR::GIVEN_INDEX_IS_OUT_OF_RANGE" << std::endl;
		abort();
	}
}

int arr_3d_data::getSizeInBytes() {
	return sizeof(float) * maxValueCount;
}

void arr_3d_data::copy(arr_3d_data& dataToCopy) {
	allocateSpace(dataToCopy.maxWidth, dataToCopy.maxHeight, dataToCopy.maxDepth);
	for (int i = 0; i < maxValueCount; i++)
	{
		setValue(i, dataToCopy.getValue(i));
	}
}

void arr_3d_data::copy(arr_3d_data* dataToCopy) {
	allocateSpace(dataToCopy->maxWidth, dataToCopy->maxHeight, dataToCopy->maxDepth);
	for (int i = 0; i < maxValueCount; i++)
	{
		setValue(i, dataToCopy->getValue(i));
	}
}

void arr_3d_data::replaceDataAndDestroyOld(arr_3d_data& dataToCopy) {
	copy(dataToCopy);
	dataToCopy.~arr_3d_data();
}

void arr_3d_data::replaceDataAndDestroyOld(arr_3d_data* dataToCopy) {
	copy(dataToCopy);
	dataToCopy->~arr_3d_data();
}

void arr_3d_data::insert(arr_3d_data& dataToCopy) {
	// absurdly inefficient, but couldn't come up with a better way of doing this
	if ((this->maxWidth != dataToCopy.maxWidth && this->maxWidth != 0) || (this->maxHeight != dataToCopy.maxHeight && this->maxHeight != 0)) {
		std::cout << "ERROR::DATA_TO_INSERT_DOESNT_HAVE_MATCHING_WIDTH_ANDOR_HEIGHT" << std::endl;
		std::cout << "self: " << this->maxWidth << " " << this->maxHeight << " " << this->maxDepth << std::endl;
		std::cout << "copy: " << dataToCopy.maxWidth << " " << dataToCopy.maxHeight << " " << dataToCopy.maxDepth << std::endl;

		abort();
	}

	arr_3d_data dataHolder{};
	dataHolder.copy(*this);

	this->allocateSpace(dataToCopy.maxWidth, dataToCopy.maxHeight, this->maxDepth + dataToCopy.maxDepth);
	for (int i = 0; i < this->maxWidth; i++)
	{
		for (int j = 0; j < this->maxHeight; j++)
		{
			for (int k = 0; k < this->maxDepth; k++)
			{
				if (k < this->maxDepth - dataToCopy.maxDepth) {
					this->setValue(i, j, k, dataHolder.getValue(i, j, k));
				}
				else {
					this->setValue(i, j, k, dataToCopy.getValue(i, j, k - this->maxDepth + dataToCopy.maxDepth));
				}
			}
		}
	}
	dataHolder.~arr_3d_data();
}

void arr_3d_data::print() {
	int depthCount, widthCount, heightCount;
	(maxDepth >= 10) ? depthCount = 10 : depthCount = maxDepth;
	(maxWidth >= 10) ? widthCount = 10 : widthCount = maxWidth;
	(maxHeight >= 10) ? heightCount = 10 : heightCount = maxHeight;

	if (depthCount == 10 || widthCount == 10 || heightCount == 10) { std::cout << std::endl << "3d data too big; only 10x10x10 from zero is shown." << std::endl << std::endl; }

	for (size_t k = 0; k < depthCount; k++)
	{
		for (size_t i = 0; i < widthCount; i++)
		{
			for (size_t j = 0; j < heightCount; j++)
				std::cout << std::fixed << std::setprecision(2) << getValue(i, j, k) << ' ';

			std::cout << std::endl;
		}
		std::cout << "---------" << std::endl;
	}
	std::cout << "-=-=-=-=-=-=-=-=-=-=-=-" << std::endl;
}

arr_3d_data::arr_3d_data(const arr_3d_data& obj) {
	if (this->arr == obj.arr) { return; }

	arr.release();
	arr = std::unique_ptr<float[]>(new float[obj.maxValueCount]);
	maxValueCount = obj.maxValueCount;
	maxWidth = obj.maxWidth;
	maxHeight = obj.maxHeight;
	maxDepth = obj.maxDepth;
	for (int i = 0; i < maxValueCount; i++)
	{
		arr[i] = obj.arr[i];
	}
}

arr_3d_data& arr_3d_data::operator=(const arr_3d_data& data) {
	if (this->arr == data.arr) { return *this; }

	arr.release();
	arr = std::unique_ptr<float[]>(new float[data.maxValueCount]);
	maxValueCount = data.maxValueCount;
	maxWidth = data.maxWidth;
	maxHeight = data.maxHeight;
	maxDepth = data.maxDepth;
	for (int i = 0; i < maxValueCount; i++)
	{
		arr[i] = data.arr[i];
	}

	return *this;
}

arr_3d_data arr_3d_data::createRandomFilter(int width, int height, int depth) {
	arr_3d_data temp{ width, height, depth };
	for (int i = 0; i < temp.maxValueCount; i++)
	{
		temp.setValue(i, randValueneg1to1());
	}
	return temp;
}