// DivideArrayIntoTwoPartWithEqualSum_Google.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <algorithm>
#include <numeric>
#include <stack>
#include <vector>

using DataArray = std::vector<unsigned int>;
using ResultStack = std::stack<size_t>;

enum class Action
{
    STOP,
    CONTINUE,
    FOUND
};

Action DivideTwoPartsWithEqualSum(const DataArray& input,
                                const size_t last_index,
                                const double sum_of_part,
                                const size_t size_of_part,
                                const size_t size_of_all,
                                ResultStack& result,
                                size_t& result_size,
                                double& sumOfResult,
                                ResultStack& curBestResult,
                                double& sumOfCurBestResult)
{
    if (result_size == size_of_part) {
        if (fabs(sumOfResult - sum_of_part) < fabs(sumOfCurBestResult - sum_of_part)) {
            curBestResult = result;
            sumOfCurBestResult = sumOfResult;
        }
 
        if (fabs(sumOfCurBestResult - sum_of_part) < 1.0) {
            // found the best result;
            return Action::FOUND;
        }
        else if (sumOfResult > sum_of_part) {
            return Action::STOP;
        }

        return Action::CONTINUE;
    }

    Action act = Action::CONTINUE;
    const size_t startIndex = result.top() + 1;
    const size_t endIndex = size_of_all - (size_of_part - result_size) + 1;
    for (size_t index = startIndex; index < endIndex; ++index) {
        result.push(index);
        ++result_size;
        sumOfResult += input[index];
        act = DivideTwoPartsWithEqualSum(input, last_index, sum_of_part,
                                         size_of_part, size_of_all,
                                         result, result_size, sumOfResult,
                                         curBestResult, sumOfCurBestResult);

        if (act == Action::FOUND) {
            break;
        }

        result.pop();
        --result_size;
        sumOfResult -= input[index];
        if (act == Action::STOP) {
            act = Action::CONTINUE;
        }
    }

    return act;
}

double DivideToTwoPartsWithEqualSum(const DataArray& input,
                                    DataArray& result)
{
    if (input.empty()) {
        return -1.0;
    }

    const size_t len = input.size();
    const size_t size_of_part = len >> 1;
    const double sum_of_all = std::accumulate(input.begin(), input.end(), 0.0);

    const double sum_of_part = sum_of_all/2;
    const size_t last_index = (len & 1) > 0 ? (size_of_part + 2) : (size_of_part + 1);
    DataArray inputCopy(input);
    ResultStack tempResult;
    size_t size_of_stack;
    double sum_of_stack;
    ResultStack bestResult;
    double sumOfBestResult;
    std::sort(inputCopy.begin(), inputCopy.end());
    for (size_t index = 0; index < last_index; ++index) {
        tempResult.push(index);
        size_of_stack = 1;
        sum_of_stack = inputCopy[index];
        if (DivideTwoPartsWithEqualSum(inputCopy, last_index,
                                       sum_of_part, size_of_part, len,
                                       tempResult, size_of_stack,
                                       sum_of_stack, bestResult, 
                                       sumOfBestResult) == Action::FOUND) {
            break;
        }
        tempResult.pop();
    }

    result.clear();
    result.reserve(size_of_part);
    while (!bestResult.empty())
    {
        result.push_back(inputCopy[bestResult.top()]);
        bestResult.pop();
    }

    return sumOfBestResult;
}


#include <cassert>
int _tmain(int argc, _TCHAR* argv[])
{
    DataArray result;
    assert(DivideToTwoPartsWithEqualSum(DataArray{ 1, 2, 3, 6, 8, 9, 7 }, result) == 18.0);
    assert(DivideToTwoPartsWithEqualSum(DataArray{ 5, 7, 50, 8, 9, 62 }, result) == 74);
    assert(DivideToTwoPartsWithEqualSum(DataArray{ 1, 10, 11, 18, 20 }, result) == 30);
    assert(DivideToTwoPartsWithEqualSum(DataArray{ 1, 7, 8, 9, 10, 13 }, result) == 24);

    return 0;
}

// http://www.careercup.com/question?id=4830599367884800