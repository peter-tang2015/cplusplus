#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#pragma once

#include <vector>

class QuickSort
{
public:
	QuickSort();
	~QuickSort();

	void Sort(std::vector<int>& data);
	void Sort(int data[], int size);

private:
	void SortInternal(int data[], int start, int end);
	int Partition(int data[], int start, int end);
};

#endif

