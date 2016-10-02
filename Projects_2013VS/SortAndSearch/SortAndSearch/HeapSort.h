#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#pragma once

#include <vector>

class HeapSort
{
public:
	HeapSort();
	~HeapSort();

	void Sort(std::vector<int>& data);
	void Sort(int data[], int size);
	void Sort_Recursive(int data[], int size);

private:
	void Heapify(int data[], int start, int end);
	void Heapify_Recursive(int data[], int start, int end);
	void ShiftRight(int data[], int start, int end);
	void ShiftRight_Recursive(int data[], int start, int end);
};

#endif

