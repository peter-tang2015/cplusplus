#include "stdafx.h"
#include "QuickSort.h"


QuickSort::QuickSort()
{
}

QuickSort::~QuickSort()
{
}

void QuickSort::Sort(std::vector<int>& data)
{
	if (data.empty()) {
		return;
	}

	Sort(&data[0], data.size());
}

void QuickSort::Sort(int data[], int size)
{
	SortInternal(data, 0, size);
}

void QuickSort::SortInternal(int data[], int start, int end)
{
	if (start < end) {
		int pivotalIndex = Partition(data, start, end);
		SortInternal(data, start, pivotalIndex);
		SortInternal(data, pivotalIndex + 1, end);
	}
}

int QuickSort::Partition(int data[], int start, int end)
{
	// take the last element as the pivotal value
#if 0
	int midpoint = (start + end) >> 1;
	int pivotalVal = data[midpoint];
	// swap it to rightest value
	data[midpoint] = data[end - 1];
	data[end - 1] = pivotalVal;
	int pivotalIndex = end - 1;
#else 
	int pivotalVal = data[end - 1];
	int pivotalIndex = end - 1;
#endif
	for (int temp, index = pivotalIndex - 1; index >= start; --index) {
		if (data[index] > pivotalVal) {
			temp = data[pivotalIndex - 1];
			data[pivotalIndex] = data[index];
			data[index] = temp;
			data[pivotalIndex - 1] = pivotalVal;
			--pivotalIndex;
		}
	}
	/*
	for (int temp, index = start; index < pivotalIndex; ++index) {
		if (data[index] > pivotalVal) {
			temp = data[pivotalIndex - 1];
			data[pivotalIndex] = data[index];
			data[index] = temp;
			data[pivotalIndex - 1] = pivotalVal;
			--pivotalIndex;
		}
	}
	*/

	return pivotalIndex;
}
