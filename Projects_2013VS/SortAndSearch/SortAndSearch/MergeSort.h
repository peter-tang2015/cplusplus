#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#pragma once

#include <vector>

class MergeSort
{
public:
	MergeSort();
	~MergeSort();

	void Sort(std::vector<int>& data);
	void Sort(int data[], int size);
	void Sort_Recursive(int data[], int size);

private:
	void BottomUpMerge(int data[], int start, int mid, int end, int copy[]);
	void TopDownSplit(int data[], int start, int end, int copy[]);
	void CopyArray(int src[], int dst[], int start, int end);

};

#endif
