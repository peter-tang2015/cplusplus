// SortAndSearch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "BinarySearch.h"
#include "HeapSort.h"
#include "MergeSort.h"
#include "QuickSort.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int data0[] = {89, 34, 102, 75, 96, 100, 55, 25, 99};
	int data1[] = { 89, 34, 102, 75, 96, 100, 55, 25, 99 };
	HeapSort hs;
	hs.Sort(data0, 9);
	hs.Sort_Recursive(data1, 9);

	int data2[] = { 89, 34, 102, 75, 96, 100, 55, 25, 99 };
	int data3[] = { 89, 34, 102, 75, 96, 100, 55, 25, 99 };
	MergeSort ms;
	ms.Sort(data2, 9);
	ms.Sort_Recursive(data3, 9);

	int data4[] = { 89, 34, 102, 75, 96, 100, 55, 25, 99 };
	QuickSort qs;
	qs.Sort(data4, 9);

	int test1[] = { 3 };
	hs.Sort(test1, 1);
	hs.Sort_Recursive(test1, 1);
	ms.Sort(test1, 1);
	ms.Sort_Recursive(test1, 1);
	qs.Sort(test1, 1);

	int* test2 = nullptr;
	hs.Sort(test2, 0);
	hs.Sort_Recursive(test2, 0);
	ms.Sort(test2, 0);
	ms.Sort_Recursive(test2, 0);
	qs.Sort(test2, 0);


	BinarySearch bs;
	int pos;
	bool found;
	found = bs.Search(data0, 0, 9, 22, pos);
	found = bs.Search(data0, 0, 9, 25, pos);
	found = bs.Search(data0, 0, 9, 97, pos);
	found = bs.Search(data0, 0, 9, 99, pos);
	found = bs.Search(data0, 0, 9, 102, pos);
	found = bs.Search(data0, 0, 9, 200, pos);
	found = bs.Search_recursive(data0, 0, 9, 22, pos);
	found = bs.Search_recursive(data0, 0, 9, 25, pos);
	found = bs.Search_recursive(data0, 0, 9, 97, pos);
	found = bs.Search_recursive(data0, 0, 9, 99, pos);
	found = bs.Search_recursive(data0, 0, 9, 102, pos);
	found = bs.Search_recursive(data0, 0, 9, 200, pos);

	return 0;
}

