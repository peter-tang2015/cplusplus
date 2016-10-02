// FindTheFirstAndLastOfGivenNumberInSortedArray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>

template <typename T>
void FindTheFirstOfGivenNumberInSortedArray(const std::vector<T>& sortedArray,
                                            const T& val,
                                            const long start,
                                            const long end,
                                            size_t& first)
{
    if (start > end) {
        return;
    }

    const size_t mid = (start + end) >> 1;
    auto iter = sortedArray.begin();
    if (*(iter + mid) == val) {
        if (mid == 0 || *(iter + mid - 1) < val) {
            first = mid;
        }
        else {
            FindTheFirstOfGivenNumberInSortedArray(sortedArray, 
                                                   val,
                                                   start,
                                                   mid - 1,
                                                   first);
        }
    }
    else {
        FindTheFirstOfGivenNumberInSortedArray(sortedArray,
                                               val,
                                               mid + 1,
                                               end,
                                               first);
    }
}

template <typename T>
void FindTheLastOfGivenNumberInSortedArray(const std::vector<T>& sortedArray,
                                           const T& val,
                                           const size_t arr_len,
                                           const long start,
                                           const long end,
                                           size_t& last)
{
    if (start > end) {
        return;
    }

    const size_t mid = (start + end) >> 1;
    auto iter = sortedArray.begin();
    if (*(iter + mid) == val) {
        if (mid == (arr_len - 1) || *(iter + mid + 1) > val) {
            last = mid;
        }
        else {
            FindTheLastOfGivenNumberInSortedArray(sortedArray,
                                                  val,
                                                  arr_len,
                                                  mid + 1,
                                                  end,
                                                  last);
        }
    }
    else {
        FindTheLastOfGivenNumberInSortedArray(sortedArray,
                                              val,
                                              arr_len,
                                              start,
                                              mid - 1,
                                              last);
    }
}

template <typename T>
bool FindTheFirstAndLastOfGivenNumberInSortedArray(const std::vector<T>& sortedArray,
                                                   const T& val,
                                                   const size_t arr_len,
                                                   const long start,
                                                   const long end,
                                                   size_t& first,
                                                   size_t& last)
{
    if (start > end) {
        return false;
    }

    const size_t mid = (start + end) >> 1;
    auto iter = sortedArray.begin();
    if (*(iter + mid) == val)
    {
        if (mid == 0 || *(iter + mid - 1) < val) {
            first = mid;
        }
        else {
            FindTheFirstOfGivenNumberInSortedArray(sortedArray,
                                                   val,
                                                   start,
                                                   mid - 1,
                                                   first);
        }

        if (mid == (arr_len - 1) || *(iter + mid + 1) > val) {
            last = mid;
        }
        else {
            FindTheLastOfGivenNumberInSortedArray(sortedArray,
                                                  val,
                                                  arr_len,
                                                  mid + 1,
                                                  end,
                                                  last);
        }

        return true;
    }
    else if (*(iter + mid) > val) {
        return FindTheFirstAndLastOfGivenNumberInSortedArray(sortedArray,
                                                             val,
                                                             arr_len,
                                                             start,
                                                             mid - 1,
                                                             first,
                                                             last);
    }
    else
    {
        return FindTheFirstAndLastOfGivenNumberInSortedArray(sortedArray,
                                                             val,
                                                             arr_len,
                                                             mid + 1,
                                                             end,
                                                             first,
                                                             last);
    }
}

template <typename T>
bool FindTheFirstAndLastOfGivenNumberInSortedArray(const std::vector<T>& sortedArray,
                                                   const T& val,
                                                   size_t& first,
                                                   size_t& last)
{
    if (sortedArray.empty()) {
        return false;
    }

    const size_t len = sortedArray.size();
    return FindTheFirstAndLastOfGivenNumberInSortedArray(sortedArray,
                                                         val,
                                                         len,
                                                         0,
                                                         len - 1,
                                                         first,
                                                         last);
}

#include <cassert>
void TestFindTheFistAndLastOfGivenNumberInSortedArray()
{
    std::vector<int> sortedArray;
    size_t first, last;
    {
        assert(FindTheFirstAndLastOfGivenNumberInSortedArray(sortedArray,
                                                             1,
                                                             first,
                                                             last) == false);
    }

    {
        sortedArray = { 5 };
        assert(FindTheFirstAndLastOfGivenNumberInSortedArray(sortedArray,
            1,
            first,
            last) == false);
        assert(FindTheFirstAndLastOfGivenNumberInSortedArray(sortedArray,
            5,
            first,
            last) == true);
        assert(first == 0 && last == 0);
    }

    {
        sortedArray = { 5, 6 };
        assert(FindTheFirstAndLastOfGivenNumberInSortedArray(sortedArray,
                                                             5,
                                                             first,
                                                             last) == true);
        assert(first == 0 && last == 0);

        assert(FindTheFirstAndLastOfGivenNumberInSortedArray(sortedArray,
                                                             6,
                                                             first,
                                                             last) == true);
        assert(first == 1 && last == 1);
    }

    {
        sortedArray = { 5, 5, 5, 5, 5 };
        assert(FindTheFirstAndLastOfGivenNumberInSortedArray(sortedArray,
            5,
            first,
            last) == true);
        assert(first == 0 && last == 4);

        assert(FindTheFirstAndLastOfGivenNumberInSortedArray(sortedArray,
            6,
            first,
            last) == false);
    }

    {
        sortedArray = { 1, 2, 3, 5, 5, 5, 5, 5, 6, 7, 8 };
        assert(FindTheFirstAndLastOfGivenNumberInSortedArray(sortedArray,
            5,
            first,
            last) == true);
        assert(first == 3 && last == 7);
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestFindTheFistAndLastOfGivenNumberInSortedArray();
    return 0;
}

