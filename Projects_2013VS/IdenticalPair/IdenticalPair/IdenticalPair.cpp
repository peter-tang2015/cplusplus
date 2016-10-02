// IdenticalPair.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "HeapSort.h"

int FindIdenticalPairs(int values[], int N)
{
	HeapSort hs;

	int count = 0;
	int freq = 1;
	for (int temp = values[0], i = 1; i < N; ++i) {
		if (temp == values[i]) {
			++freq;
		}
		else {
			count += freq * (freq - 1) / 2;
			temp = values[i];
			freq = 1;
		}
	}

	count += freq * (freq - 1) / 2;

	return count;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int A[] = { 3, 5, 6, 3, 3, 5 };
	// int A[] = { 9, 6, 7, 8, 8, 9 };
	// int A[] = { 5, 5, 5, 5, 5, 5 };
	FindIdenticalPairs(A, 6);

	return 0;
}

