#include "stdafx.h"
#include "HeapSort.h"


HeapSort::HeapSort()
{
}


HeapSort::~HeapSort()
{
}


void HeapSort::Sort(std::vector<int>& data)
{
	if (!data.empty()) {
		Sort(&data[0], data.size());
	}
}

void HeapSort::Sort(int data[], int size)
{
	if (size < 1) {
		return;
	}

	Heapify(data, 0, size);

	int tempSize = size - 1;
	int tempVal;
	while (tempSize > 0) {
		// the biggest value alwasy stays at index of "0"
		tempVal = data[tempSize];
		data[tempSize] = data[0];
		data[0] = tempVal;

		ShiftRight(data, 0, tempSize);
		--tempSize;
	}
}

void HeapSort::Sort_Recursive(int data[], int size)
{
	if (size < 1) {
		return;
	}
	Heapify_Recursive(data, 0, size);

	int tempSize = size - 1;
	int tempVal;
	while (tempSize > 0) {
		// the biggest value alwasy stays at index of "0"
		tempVal = data[tempSize];
		data[tempSize] = data[0];
		data[0] = tempVal;

		ShiftRight_Recursive(data, 0, tempSize);
		--tempSize;
	}
}

void HeapSort::Heapify(int data[], int start, int end)
{
	int midpoint = (start + end) >> 1;
	while (midpoint >= 0) {
		ShiftRight(data, midpoint, end);
		--midpoint;
	}
}

void HeapSort::Heapify_Recursive(int data[], int start, int end)
{
	int midpoint = (start + end) >> 1;
	while (midpoint >= 0) {
		ShiftRight_Recursive(data, midpoint, end);
		--midpoint;
	}
}

void HeapSort::ShiftRight(int data[], int start, int end)
{
	int root = start;
	int leftChild = 2 * root + 1;
	int rightChild;
	int max;
	int tempRoot;
	while (leftChild < end) {
		max = data[root];
		tempRoot = root;
		if (data[leftChild] > data[root]) {
			max = data[leftChild];
			tempRoot = leftChild;
		}
		rightChild = leftChild + 1;
		if (rightChild < end) {
			if (data[rightChild] > max) {
				max = data[rightChild];
				tempRoot = rightChild;
			}
		}

		if (tempRoot != root) {
			data[tempRoot] = data[root];
			data[root] = max;
			root = tempRoot;
			leftChild = 2 * root + 1;
		}
		else{
			break;
		}
	}
}

void HeapSort::ShiftRight_Recursive(int data[], int start, int end)
{
	int root = start;
	int leftChild = 2 * root + 1;
	int rightChild;
	int max;
	int tempRoot;
	if (leftChild < end) {
		max = data[root];
		tempRoot = root;
		if (data[leftChild] > data[root]) {
			max = data[leftChild];
			tempRoot = leftChild;
		}
		rightChild = leftChild + 1;
		if (rightChild < end) {
			if (data[rightChild] > max) {
				max = data[rightChild];
				tempRoot = rightChild;
			}
		}

		if (tempRoot != root) {
			data[tempRoot] = data[root];
			data[root] = max;
			root = tempRoot;
			ShiftRight_Recursive(data, tempRoot, end);
		}
	}
}