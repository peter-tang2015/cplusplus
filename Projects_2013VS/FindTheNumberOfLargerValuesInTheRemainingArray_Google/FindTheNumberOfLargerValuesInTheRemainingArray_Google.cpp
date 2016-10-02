// FindTheNumberOfLargerValuesInTheRemainingArray_Google.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <set>
#include <list>
#include <vector>

template <typename T>
std::vector<T> FindTheNumberOfLargerValuesInTheRemainingArray(std::vector<T> const& input)
{
    std::set<T> sortedArray;
    std::list<T> result;
    auto iterEnd = input.rend();
    for (auto iter = input.rbegin(); iter != iterEnd; ++iter) {
        auto ub = sortedArray.upper_bound(*iter);
        result.push_front(std::distance(ub, sortedArray.end()));
        sortedArray.insert(*iter);
    }

    return std::vector<T>(result.begin(), result.end());
}


#include <cassert>
void TestFindTheNumberOfLargerValuesInTheRemainingArray()
{
    {
        std::vector<int> input;
        std::vector<int> output = FindTheNumberOfLargerValuesInTheRemainingArray(input);
        assert(output.empty() == true);

        input.push_back(0);
        output = FindTheNumberOfLargerValuesInTheRemainingArray(input);
        assert(output.size() == 1);
        assert(output[0] == 0);
    }

    {
        std::vector<int> input = { 3, 4, 5, 9, 2, 1, 3 };
        const std::vector<int> result = { 3, 2, 1, 0, 1, 1, 0 };
        std::vector<int> output = FindTheNumberOfLargerValuesInTheRemainingArray(input);
        assert(result == output);
    }

    {
        std::vector<int> input = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        const std::vector<int> result = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
        std::vector<int> output = FindTheNumberOfLargerValuesInTheRemainingArray(input);
        assert(result == output);
    }

    {
        std::vector<int> input = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
        const std::vector<int> result = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        std::vector<int> output = FindTheNumberOfLargerValuesInTheRemainingArray(input);
        assert(result == output);
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestFindTheNumberOfLargerValuesInTheRemainingArray();
    return 0;
}

