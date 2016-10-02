// FindTheMedianOfTwoSortedArray_Google.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <algorithm>
#include <vector>

#include <cassert>

template<typename T>
double FindNthValOfTwoSortedArray(const std::vector<T>& array1,
                             const std::vector<T>& array2,
                             size_t nth)
{
    if (array1.empty() && array2.empty()) {
        return std::numeric_limits<double>::max();
    }
    if (array1.empty()) {
        return array2[nth];
    }
    if (array2.empty()) {
        return array1[nth];
    }

    size_t startIndex = 0;
    size_t endIndex = array1.size();
    size_t index = (startIndex + endIndex) >> 1;
    std::vector<T>::const_iterator startIter = array2.begin();
    std::vector<T>::const_iterator endIter = array2.end();
    std::lower_bound(startIter, endIter, array1[index]);
}

template<typename T>
double FindTheMedianOfTwoSortedArray(const std::vector<T>& array1,
                                     const std::vector<T>& array2)
{
    if (array1.empty() && array2.empty()) {
        return std::numeric_limits<double>::max();
    }

    size_t sizeOfArray1 = array1.size();
    size_t sizeOfArray2 = array2.size();

    if ((sizeOfArray1 + sizeOfArray2) & 1) {
        return FindNthValOfTwoSortedArray(array1, array2, (sizeOfArray1 + sizeOfArray2) >> 1);
    }
    else {
        size_t midIndex = (sizeOfArray1 + sizeOfArray2) >> 1;
        return (FindNthValOfTwoSortedArray(array1, array2, midIndex) +
                FindNthValOfTwoSortedArray(array1, array2, midIndex - 1)) / 2;
    }

}

void TestCases()
{
    std::vector<int> array1 = { 1, 3, 6, 8 };
    std::vector<int> array2 = { 2, 2, 4, 7, 9 };
    assert(FindTheMedianOfTwoSortedArray(array1, array2) == 0.0);
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestCases();
    return 0;
}

