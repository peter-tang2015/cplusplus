// SetPermutation_Google.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>

// http://www.careercup.com/question?id=5101575825522688

template<typename T>
void PermuteSet(std::vector<T> const &input, size_t len, std::vector<std::vector<T>> &result)
{
    if (len == 0) {
        return;
    }

    const size_t currentSize = result.size();
    auto iter = input.begin();
    auto iterEnd = input.end();
    if (currentSize == 0) {
        // very first time
        for (; iter != iterEnd; ++iter) {
            std::vector<T> initialSet(1, *iter);
            result.push_back(initialSet);
        }
    }
    else {
        auto iterBeginOfResult = result.begin();
        ++iter;
        // Keep F(n-1) and generate the values for F(n)
        for (; iter != iterEnd; ++iter) {
            size_t count = 0;
            for (auto iterOfResult = iterBeginOfResult; count < currentSize; ++iterOfResult, ++count) {
                std::vector<T> copy(*iterOfResult);
                copy.push_back(*iter);
                result.push_back(copy);
            }
        }

        // Update F(n-1) as elements of F(n) 
        size_t count = 0;
        auto firstVal = input.begin();
        for (auto iterOfResult = iterBeginOfResult; count < currentSize; ++iterOfResult, ++count) {
            (*iterOfResult).push_back(*firstVal);
        }
    }

    PermuteSet(input, len - 1, result);
}

template<typename T>
std::vector<std::vector<T>> PermuteSet(std::vector<T> const &input, size_t len)
{
    if (input.empty() || len == 0 || len > input.size()) {
        return std::vector<std::vector<T>>();
    }

    std::vector<std::vector<T>> result;
    result.reserve(static_cast<size_t>(pow(input.size(), len)));
    PermuteSet(input, len, result);

    return result;
}

#include <cassert>
void TestSetPermutation()
{
    {
        const std::vector<int> input;
        auto result = PermuteSet(input, 0);
        assert(result.empty() == true);
        result = PermuteSet(input, 1);
        assert(result.empty() == true);
    }

    {
        const std::vector<int> input = { 1 };
        auto result = PermuteSet(input, 0);
        assert(result.empty() == true);
        result = PermuteSet(input, 2);
        assert(result.empty() == true);
        result = PermuteSet(input, 1);
        assert(result.size() == 1);
        assert(result[0].at(0) == 1);
    }

    {
        const std::vector<int> input = { 2, 3, 4, 5 };
        auto result = PermuteSet(input, 0);
        assert(result.empty() == true);

        result = PermuteSet(input, 1);
        assert(result.size() == 4);
        assert(result[0].size() == 1);
        assert(result[0].at(0) == 2);
        assert(result[1].size() == 1);
        assert(result[1].at(0) == 3);
        assert(result[2].size() == 1);
        assert(result[2].at(0) == 4);
        assert(result[3].size() == 1);
        assert(result[3].at(0) == 5);

        result = PermuteSet(input, 2);
        assert(result.size() == 16);
        for (auto iter = result.begin(); iter != result.end(); ++iter) {
            assert(iter->size() == 2);
        }
        assert((*result.begin()) == std::vector<int>({2, 2}));
        assert((*result.rbegin()) == std::vector<int>({5, 5}));

        result = PermuteSet(input, 3);
        assert(result.size() == 64);
        for (auto iter = result.begin(); iter != result.end(); ++iter) {
            assert(iter->size() == 3);
        }
        assert((*result.begin()) == std::vector<int>({ 2, 2, 2 }));
        assert((*result.rbegin()) == std::vector<int>({ 5, 5, 5 }));

        result = PermuteSet(input, 4);
        assert(result.size() == 256);
        for (auto iter = result.begin(); iter != result.end(); ++iter) {
            assert(iter->size() == 4);
        }
        assert((*result.begin()) == std::vector<int>({ 2, 2, 2, 2 }));
        assert((*result.rbegin()) == std::vector<int>({ 5, 5, 5, 5 }));

        result = PermuteSet(input, 6);
        assert(result.empty() == true);
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestSetPermutation();
    return 0;
}

