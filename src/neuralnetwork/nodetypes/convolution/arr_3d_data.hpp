#pragma once

#include <memory>
#include <cassert>
#include <iostream>
#include <iomanip>

static int arr_counter = 0;

class arr_3d_data
{
private:
	std::unique_ptr<float[]> arr = nullptr;

public:
	int maxWidth;
	int maxHeight;
	int maxDepth;

	int maxValueCount;

	arr_3d_data(int width_ = 0, int height_ = 0, int depth_ = 0);
	~arr_3d_data();

	arr_3d_data& operator=(arr_3d_data&&) = default;

	void allocateSpace(int width_, int height_, int depth_);

	void empty();

	float getValue(int widthIndex_, int heightIndex_, int depthIndex_);
	float getValue(int index_); 

	void setValue(int widthIndex_, int heightIndex_, int depthIndex_, float value);
	void setValue(int index_, float value);

	int getSizeInBytes();

	void copy(arr_3d_data& dataToCopy);
	void copy(arr_3d_data* dataToCopy);
	void replaceDataAndDestroyOld(arr_3d_data& dataToCopy);
	void replaceDataAndDestroyOld(arr_3d_data* dataToCopy);
	void insert(arr_3d_data& dataToCopy);

	void print();

	arr_3d_data& operator=(const arr_3d_data& data);

	arr_3d_data(const arr_3d_data& obj);

	static arr_3d_data createRandomFilter(int width, int height, int depth);
};

