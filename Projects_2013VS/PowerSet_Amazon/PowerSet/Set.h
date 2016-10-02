#pragma once

#include <vector>

class Set
{
public:
    using SET = std::vector<int>;
    using INDICE = std::vector<size_t>;

    Set(const SET& input);
    ~Set();

    size_t PrintSubSetOfSummOfAllElementsEqualZero_Heuristic();
private:
    void SplitInputData();
    size_t PrintSubSetOfSummOfAllElementsEqualZero_Heuristic_DP(const size_t curNegativeIndex,
                                                                bool alreadyCounted);
    size_t FindSubsetWithPostitiveElements_Heuristic();
    size_t FindSubsetWithPostitiveElements_Heuristic_DP(const size_t curPositiveIndex);

    void PrintSubset();

    const SET& mInputRef;
    SET mSortedZeroElements;
    SET mSortedNegativeElements;
    SET mSortedPositiveElements;

    int mSumOfAllPositiveElements;
    size_t SIZE_OF_POSITIVE;
    size_t SIZE_OF_NEGATIVE;

    INDICE mNegativeSubsetIndices;
    int mNegativeSum;
    size_t mSizeOfNegativeSubsetIndices;
    INDICE mPositiveSubsetIndices;
    int mPositiveSum;
    size_t mSizeOfPositiveSubsetIndices;
};

