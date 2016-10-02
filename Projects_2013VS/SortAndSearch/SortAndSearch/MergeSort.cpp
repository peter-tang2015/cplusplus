#include "stdafx.h"
#include "MergeSort.h"


MergeSort::MergeSort()
{
}


MergeSort::~MergeSort()
{
}

void MergeSort::Sort(std::vector<int>& data)
{
	if (data.empty()) {
		return;
	}

	Sort(&data[0], data.size());
}

void MergeSort::Sort(int data[], int size)
{
	if (size <= 0) {
		return;
	}

	int* tempCopy = new int[size];

	for (int width = 1; width < size; width *= 2) {
		for (int mid, end, start = 0; start < size; start += 2 * width) {
			mid = (start + width) < size ? (start + width) : size;
			end = (start + 2 * width) < size ? (start + width * 2) : size;
			BottomUpMerge(data, start, mid, end, tempCopy);
		}

		// copy back the data
		CopyArray(tempCopy, data, 0, size);
	}

	delete[] tempCopy;
}

void MergeSort::BottomUpMerge(int data[], int start, int mid, int end, int copy[])
{
	int leftStart = start;
	int rightStart = mid;

	for (int index = start; index < end; ++index) {
		if (leftStart < mid && (rightStart >= end || data[leftStart] <= data[rightStart]) ) {
			copy[index] = data[leftStart];
			++leftStart;
		}
		else {
			copy[index] = data[rightStart];
			++rightStart;
		}
	}
}

void MergeSort::Sort_Recursive(int data[], int size)
{
	if (size <= 0) {
		return;
	}

	int* tempCopy = new int[size];
	TopDownSplit(data, 0, size, tempCopy);
	delete[] tempCopy;
}

void MergeSort::TopDownSplit(int data[], int start, int end, int copy[])
{
	if ((end - start) < 2) {
		return;
	}

	int midpoint = (start + end) >> 1;
	TopDownSplit(data, start, midpoint, copy);
	TopDownSplit(data, midpoint, end, copy);
	BottomUpMerge(data, start, midpoint, end, copy);

	CopyArray(copy, data, start, end);
}

void MergeSort::CopyArray(int src[], int dst[], int start, int end)
{
	while (start < end) {
		*(dst + start) = *(src + start);
		++start;
	}
}