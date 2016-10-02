// absSum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <map>
#include <vector>

#include <cassert>
#include <cmath>

struct ResultTuple{
    int val[3];
    size_t absSum;
};

typedef std::multimap<int, char> CombinedArrayMap;
typedef CombinedArrayMap::const_iterator CAMIterator;

void UpdateResult(CAMIterator& abc1,
                  CAMIterator& abc2,
                  CAMIterator& abc3,
                  size_t absSum,
                  ResultTuple& result)
{
    result.absSum = absSum;
    result.val[abc1->second - 'A'] = abc1->first;
    result.val[abc2->second - 'A'] = abc2->first;
    result.val[abc3->second - 'A'] = abc3->first;
}

void CalculateAndUpdateAbsSum(CAMIterator& itEnd,
                              CAMIterator& prev1,
                              CAMIterator& prev2,
                              CAMIterator& curVal,
                              ResultTuple& result)
{
    if (prev1 == itEnd || prev2 == itEnd || curVal == itEnd) {
        return;
    }

    size_t absSum = (prev1->first < prev2->first) ?
        (curVal->first - prev1->first) << 1 :
        (curVal->first - prev2->first) << 1;
    if (absSum < result.absSum) {
        UpdateResult(prev1, prev2, curVal, absSum, result);
    }
}

void FindNextNotXandY(CAMIterator& itEnd,
                      const char x,
                      const char y,
                      CAMIterator& notXYIter)
{
    for (; notXYIter != itEnd; ++notXYIter) {
        if (notXYIter->second != x &&
            notXYIter->second != y) {
            break;
        }
    }
}

void FindNextNotX(CAMIterator& itEnd,
                  const char x,
                  CAMIterator& notXIter)
{
    for (; notXIter != itEnd; ++notXIter) {
        if (notXIter->second != x) {
            break;
        }
    }
}

void CalculateAndUpdateAbsSum(CAMIterator& itEnd,
                              CAMIterator& prevA,
                              CAMIterator& prevB,
                              CAMIterator& prevC,
                              CAMIterator& curABC,
                              ResultTuple& result)
{
    switch (curABC->second){
    case 'A':
        CalculateAndUpdateAbsSum(itEnd, prevB, prevC, curABC, result);
        break;
    case 'B':
        CalculateAndUpdateAbsSum(itEnd, prevA, prevC, curABC, result);
        break;
    case 'C':
        CalculateAndUpdateAbsSum(itEnd, prevA, prevB, curABC, result);
        break;
    default:
        assert(false);
    }
}

void FindLastTwoCombinationsAndUpdate(CAMIterator& itEnd,
                                      CAMIterator& prev1,
                                      CAMIterator& prev2,
                                      CAMIterator& curIter,
                                      ResultTuple& result)
{
    CAMIterator notXIter = curIter;
    FindNextNotX(itEnd, curIter->second, notXIter);
    if (notXIter != itEnd) {
        if (prev1 != itEnd && prev1->second != notXIter->second) {
            CalculateAndUpdateAbsSum(itEnd, prev1, curIter, notXIter, result);
        }
        if (prev2 != itEnd && prev2->second != notXIter->second) {
            CalculateAndUpdateAbsSum(itEnd, prev2, curIter, notXIter, result);
        }

        CAMIterator notXYIter = notXIter;
        FindNextNotXandY(itEnd, curIter->second,
            notXIter->second, notXYIter);
        CalculateAndUpdateAbsSum(itEnd, curIter, notXIter, notXYIter, result);
    }
}

ResultTuple CalculateLeastAbsSum(const std::vector<int>& aVec,
                                 const std::vector<int>& bVec,
                                 const std::vector<int>& cVec)
{
    CombinedArrayMap valueVecMap;

    for (auto val : aVec) {
        valueVecMap.insert(std::make_pair(val, 'A'));
    }

    for (auto val : bVec) {
        valueVecMap.insert(std::make_pair(val, 'B'));
    }

    for (auto val : cVec) {
        valueVecMap.insert(std::make_pair(val, 'C'));
    }

    CAMIterator itStart = valueVecMap.begin();
    CAMIterator itEnd = valueVecMap.end();
    CAMIterator prevA = itEnd;
    CAMIterator prevB = itEnd;
    CAMIterator prevC = itEnd;
    char prevType = 0;
    size_t SizeOfA = aVec.size();
    size_t SizeOfB = bVec.size();
    size_t SizeOfC = cVec.size();
    size_t visitedA = 0;
    size_t visitedB = 0;
    size_t visitedC = 0;

    ResultTuple result = { { INT_MAX, INT_MAX, INT_MAX }, SIZE_MAX }; // SIZE_MAX?
    for (CAMIterator curIter = itStart; curIter != itEnd; ++curIter) {
        if (prevType != curIter->second) {
            CalculateAndUpdateAbsSum(itEnd, prevA, prevB, prevC, curIter, result);
            if (result.absSum == 0) {
                return result;
            }
        }

        if (curIter->second == 'A') {
            prevA = curIter;
            if (++visitedA == SizeOfA) {
                FindLastTwoCombinationsAndUpdate(itEnd, prevB, prevC,
                                                 curIter, result);
                break;
            }
        }
        else if (curIter->second == 'B') {
            prevB = curIter;
            if (++visitedB == SizeOfB) {
                FindLastTwoCombinationsAndUpdate(itEnd, prevA, prevC,
                                                 curIter, result);
                break;
            }
        }
        else if (curIter->second == 'C') {
            prevC = curIter;
            if (++visitedC == SizeOfC) {
                FindLastTwoCombinationsAndUpdate(itEnd, prevA, prevB,
                                                 curIter, result);
                break;
            }
        }
        else {
            assert(false);
        }
        prevType = curIter->second;
    }

    return result;
}

void testCase1()
{
    std::vector<int> aVec = { 9, 7, 5, 7, 4, 8, 12, 30, 50 };
    std::vector<int> bVec = { 30, 5, 9, 20, 35, 70, 50, 12 };
    std::vector<int> cVec = { 8, 10, 30, 21, 6, 3, 6, 10, 0 };

    ResultTuple result = CalculateLeastAbsSum(aVec, bVec, cVec);
    assert(result.absSum == 0);
    assert(result.val[0] == 30);
    assert(result.val[1] == 30);
    assert(result.val[2] == 30);
}

void testCase2()
{
    std::vector<int> aVec = { 9, 7, 6, 8, 4, 5, 3, 1, 2 };
    std::vector<int> bVec = { 20, 10, 19, 12, 15, 17, 14, 12 };
    std::vector<int> cVec = { 30, 31, 21, 40, 25, 23, 36, 40, 50 };

    ResultTuple result = CalculateLeastAbsSum(aVec, bVec, cVec);
    assert(result.absSum == 24);
    assert(result.val[0] == 9);
    assert(result.val[1] == 10);
    assert(result.val[2] == 21);
}

void testCase3()
{
    // 3 vectors has 4 and 9, this case should return 4
    std::vector<int> aVec = { 9, 7, 6, 8, 4, 5, 3, 1, 2 };
    std::vector<int> bVec = { 20, 4, 19, 2, 15, 17, 9, 12 };
    std::vector<int> cVec = { 3, 13, 9, 40, 25, 23, 6, 4, 5 };

    ResultTuple result = CalculateLeastAbsSum(aVec, bVec, cVec);
    assert(result.absSum == 0);
    assert(result.val[0] == 4);
    assert(result.val[1] == 4);
    assert(result.val[2] == 4);
}

void testCase4()
{
    // 3 vectors has two sets result
    // (90, 89, 91) and (3, 4, 5)
    // in this case, it should return (3, 4, 5)
    std::vector<int> aVec = { 90, 3, 16, 28, 45, 35, 63, 71, 82 };
    std::vector<int> bVec = { 89, 4, 19, 26, 48, 37, 69, 72, 86 };
    std::vector<int> cVec = { 91, 5, 15, 29, 43, 33, 66, 74, 85 };

    ResultTuple result = CalculateLeastAbsSum(aVec, bVec, cVec);
    assert(result.absSum == 4);
    assert(result.val[0] == 3);
    assert(result.val[1] == 4);
    assert(result.val[2] == 5);
}

void testCase5()
{
    std::vector<int> aVec = { 90, 83, 16, 28, 45, 35, 63, 71, 3 };
    std::vector<int> bVec = { 95, 88, 19, 26, 48, 37, 69, 72, 1 };
    std::vector<int> cVec = { 91, 85, 15, 29, 43, 33, 66, 74, 2 };

    ResultTuple result = CalculateLeastAbsSum(aVec, bVec, cVec);
    assert(result.absSum == 4);
    assert(result.val[0] == 3);
    assert(result.val[1] == 1);
    assert(result.val[2] == 2);
}


int _tmain(int argc, _TCHAR* argv[])
{
    testCase1();
    testCase2();
    testCase3();
    testCase4();
    testCase5();

    return 0;
}
