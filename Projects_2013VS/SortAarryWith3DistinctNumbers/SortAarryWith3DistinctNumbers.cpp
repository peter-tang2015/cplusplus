// SortAarryWith3DistinctNumbers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>

void SortArrayWith3DistinctNumbers(std::vector<int>& arr,
                                   const int low,
                                   const int mid,
                                   const int high)
{
    if (arr.empty()) {
        return;
    }

    const size_t len = arr.size();
    long posToHoldHigh = len - 1;
    while (posToHoldHigh >= 0 && arr[posToHoldHigh] == high) {
        --posToHoldHigh;
    }

    long posOfFirstOne = -1;
    for (long idx = 0; idx <= posToHoldHigh; ++idx) {
        if (arr[idx] == high) {
            arr[idx] = arr[posToHoldHigh];
            arr[posToHoldHigh] = high;
            while (posToHoldHigh >= 0 && arr[posToHoldHigh] == high) {
                --posToHoldHigh;
            }
        }
        if (arr[idx] == mid && posOfFirstOne < 0) {
            posOfFirstOne = idx;
        }
        if (arr[idx] == low && posOfFirstOne >= 0) {
            arr[idx] = mid;
            arr[posOfFirstOne] = low;
            ++posOfFirstOne;
        }
    }
}

#include <cassert>
void TestSortArrayWithThreeDistinctNumbers()
{
    std::vector<int> arr;
    SortArrayWith3DistinctNumbers(arr, 0, 1, 2);
    assert(arr.empty() == true);

    arr = { 2, 2, 2, 0, 0, 0, 1, 1, 1 };
    SortArrayWith3DistinctNumbers(arr, 0 , 1, 2);
    assert(arr == std::vector<int>({ 0, 0, 0, 1, 1, 1, 2, 2, 2 }));

    arr = { 0, 1, 1, 0, 1, 2, 1, 2, 0, 0, 0, 1 };
    SortArrayWith3DistinctNumbers(arr, 0, 1, 2);
    assert(arr == std::vector<int>({ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2 }));
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestSortArrayWithThreeDistinctNumbers();
    return 0;
}

