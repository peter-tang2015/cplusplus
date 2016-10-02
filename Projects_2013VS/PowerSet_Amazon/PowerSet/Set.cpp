#include "stdafx.h"
#include "Set.h"

#include <algorithm>
#include <iostream>
#include <numeric>

#include <cstdlib>

Set::Set(const std::vector<int>& input)
: mInputRef(input)
{
    SplitInputData();
}

Set::~Set()
{
}

size_t Set::PrintSubSetOfSummOfAllElementsEqualZero_Heuristic()
{
    SIZE_OF_NEGATIVE = mSortedNegativeElements.size();
    size_t count = 0;

    if (SIZE_OF_NEGATIVE > 0) {
        SIZE_OF_POSITIVE = mSortedPositiveElements.size();
        if (SIZE_OF_POSITIVE > 0) {
            const int sumOfNegative = std::accumulate(mSortedNegativeElements.begin(),
                mSortedNegativeElements.end(), 0);
            if (abs(sumOfNegative) >= *mSortedPositiveElements.begin())
            {
                mSumOfAllPositiveElements = std::accumulate(mSortedPositiveElements.begin(),
                    mSortedPositiveElements.end(), 0);
                if (mSumOfAllPositiveElements >= abs(*mSortedNegativeElements.rbegin()))
                {
                    mNegativeSubsetIndices.assign(SIZE_OF_NEGATIVE, 0);
                    mPositiveSubsetIndices.assign(SIZE_OF_POSITIVE, 0);

                    for (size_t index = 0; index < SIZE_OF_NEGATIVE; ++index) {
                        mNegativeSubsetIndices[0] = index;
                        mNegativeSum = mSortedNegativeElements[index];
                        mSizeOfNegativeSubsetIndices = 1;
                        count += PrintSubSetOfSummOfAllElementsEqualZero_Heuristic_DP(index + 1, false);
                    }
                }
            }
        }
    }
    const size_t SIZE_OF_ZERO = mSortedZeroElements.size();
    if (count > 0) {
        return count << SIZE_OF_ZERO;
    }
    
    if (SIZE_OF_ZERO > 0) {
        return (1 << SIZE_OF_ZERO) - 1;
    }

    return 0;
}

size_t Set::PrintSubSetOfSummOfAllElementsEqualZero_Heuristic_DP(const size_t curNegativeIndex,
                                                                 bool alreadyCounted)
{
    size_t count = 0;
    if (!alreadyCounted) {
        count += FindSubsetWithPostitiveElements_Heuristic();
        alreadyCounted = true;
    }

    if (curNegativeIndex < SIZE_OF_NEGATIVE) {
        count += PrintSubSetOfSummOfAllElementsEqualZero_Heuristic_DP(curNegativeIndex + 1,
                                                                      alreadyCounted);

        mNegativeSubsetIndices[mSizeOfNegativeSubsetIndices] = curNegativeIndex;
        mNegativeSum += mSortedNegativeElements[curNegativeIndex];
        ++mSizeOfNegativeSubsetIndices;
        count += PrintSubSetOfSummOfAllElementsEqualZero_Heuristic_DP(curNegativeIndex + 1,
                                                                      false);
        mNegativeSum -= mSortedNegativeElements[curNegativeIndex];
        --mSizeOfNegativeSubsetIndices;
    }
    return count;
}

size_t Set::FindSubsetWithPostitiveElements_Heuristic()
{
    size_t count = 0;
    for (size_t index = 0; index < SIZE_OF_POSITIVE; ++index) {
        mPositiveSubsetIndices[0] = index;
        mPositiveSum = mSortedPositiveElements[index];
        mSizeOfPositiveSubsetIndices = 1;
        count += FindSubsetWithPostitiveElements_Heuristic_DP(index + 1);
    }

    return count;
}

size_t Set::FindSubsetWithPostitiveElements_Heuristic_DP(const size_t curPositiveIndex)
{
    if ((mNegativeSum + mSumOfAllPositiveElements) < 0) {
        return 0;
    }
    
    int result = mNegativeSum + mPositiveSum;
    if (result == 0) {
        PrintSubset();
        return 1;
    }

    if (result > 0) {
        return 0;
    }

    size_t count = 0;
    if (curPositiveIndex < SIZE_OF_POSITIVE) {
        count += FindSubsetWithPostitiveElements_Heuristic_DP(curPositiveIndex + 1);

        mPositiveSubsetIndices[mSizeOfPositiveSubsetIndices] = curPositiveIndex;
        mPositiveSum += mSortedPositiveElements[curPositiveIndex];
        ++mSizeOfPositiveSubsetIndices;
        count += FindSubsetWithPostitiveElements_Heuristic_DP(curPositiveIndex + 1);
        mPositiveSum -= mSortedPositiveElements[curPositiveIndex];
        --mSizeOfPositiveSubsetIndices;
    }

    return count;
}

void Set::SplitInputData()
{
    SET inputCopy(mInputRef);
    const auto SIZE_TO_RESERVE = inputCopy.size();
    mSortedNegativeElements.reserve(SIZE_TO_RESERVE);
    mSortedZeroElements.reserve(SIZE_TO_RESERVE);
    mSortedPositiveElements.reserve(SIZE_TO_RESERVE);

    std::sort(inputCopy.begin(), inputCopy.end());
    auto firstZeroIt = std::lower_bound(inputCopy.begin(), inputCopy.end(), 0);
    auto lastZeroIt = std::upper_bound(inputCopy.begin(), inputCopy.end(), 0);
    mSortedNegativeElements.assign(inputCopy.begin(), firstZeroIt);
    mSortedZeroElements.assign(firstZeroIt, lastZeroIt);
    mSortedPositiveElements.assign(lastZeroIt, inputCopy.end());
}

void Set::PrintSubset()
{
    std::cout << "{ ";
    for (size_t idx = 0; idx < mSizeOfNegativeSubsetIndices; ++idx) {
        std::cout << mSortedNegativeElements[mNegativeSubsetIndices[idx]] << ", ";
    }

    for (size_t idx = 0; idx < mSizeOfPositiveSubsetIndices; ++idx) {
        if ((idx + 1) != mSizeOfPositiveSubsetIndices) {
            std::cout << mSortedPositiveElements[mPositiveSubsetIndices[idx]] << ", ";
        }
        else {
            std::cout << mSortedPositiveElements[mPositiveSubsetIndices[idx]];
        }
    }
    std::cout << " }" << std::endl;
}
