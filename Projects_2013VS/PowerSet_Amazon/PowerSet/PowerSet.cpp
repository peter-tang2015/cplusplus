// PowerSet.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

using SET = std::vector<int>;
using POWERSET = std::vector<SET>;

void RelationshipOfProblemAndSubproblem(POWERSET& result, int Mn)
{
    size_t len = result.size();
    
    for (size_t i = 0; i < len; ++i) {
        result.push_back(result[i]);
    }
    
    for (size_t i = len; i < result.size(); ++i) {
        SET& curSet = result[i];
        curSet.push_back(Mn);
    }
    result.push_back(SET(1, Mn));
}

void PowerSetR(const SET& s, size_t pos, POWERSET& result)
{
    if (pos == s.size()) {
        return;
    }

    PowerSetR(s, pos + 1, result);
    RelationshipOfProblemAndSubproblem(result, s[pos]);
}

POWERSET PowerSetNR(const SET& s)
{
    POWERSET result;
    
    for (size_t i = 0; i < s.size(); ++i) {
        RelationshipOfProblemAndSubproblem(result, s[i]);
    }

    return result;
}

void PrintOutSubSet(const SET& input,
                    const std::vector<size_t>& indicesOfSubset,
                    const size_t sizeOfSubset)
{
    if (sizeOfSubset == 0) {
        return;
    }

    std::cout << "{ " << input[indicesOfSubset[0]];
    for (size_t index = 1; index < sizeOfSubset; ++index) {
        std::cout << "; " << input[indicesOfSubset[index]];
    }
    std::cout << " }" << std::endl;
}

size_t PrintSubSetOfSummOfAllElementsEqualZero_DP(const SET& input,
                                                  const size_t indexOfNext,
                                                  std::vector<size_t>& indicesOfSubset,
                                                  const int sumOfSubset,
                                                  const size_t sizeOfSubset,
                                                  bool alreadyCounted)
{
    size_t count = 0;
    if (sumOfSubset == 0 && !alreadyCounted) {
        PrintOutSubSet(input, indicesOfSubset, sizeOfSubset);
        alreadyCounted = true;
        ++count;
    }

    if (indexOfNext < input.size()) {
        count += PrintSubSetOfSummOfAllElementsEqualZero_DP(input,
                                                            indexOfNext + 1,
                                                            indicesOfSubset,
                                                            sumOfSubset,
                                                            sizeOfSubset,
                                                            alreadyCounted);
 
        indicesOfSubset[sizeOfSubset] = indexOfNext;
        count += PrintSubSetOfSummOfAllElementsEqualZero_DP(input,
                                                            indexOfNext + 1,
                                                            indicesOfSubset,
                                                            sumOfSubset + input[indexOfNext],
                                                            sizeOfSubset + 1,
                                                            false);
    }
    return count;
}

size_t PrintSubSetOfSummOfAllElementsEqualZero(const SET& input)
{
    auto SIZE_OF_INPUT = input.size();
    std::vector<size_t> indicesOfSubset(SIZE_OF_INPUT, 0);
    size_t count = 0;
    for (size_t index = 0; index < SIZE_OF_INPUT; ++index) {
        indicesOfSubset[0] = index;
        count += PrintSubSetOfSummOfAllElementsEqualZero_DP(input,
                                                            index + 1,
                                                            indicesOfSubset,
                                                            input[index],
                                                            1,
                                                            false);
    }

    return count;
}

void TestPOWERSet()
{
    SET s;
    s.push_back(1);
    s.push_back(4);
    s.push_back(6);

    POWERSET resultR;
    PowerSetR(s, 0, resultR);

    POWERSET resultNR = PowerSetNR(s);

}

#include <cassert>
void TestPrintSubSetOfSummOfAllElementsEqualZero()
{
    {
        const SET testSet = { 5, 3, 1, 8, -8, -4 };
        assert(PrintSubSetOfSummOfAllElementsEqualZero(testSet) == 4);
    }

    {
        const SET testSet = { 0, 0, 0 , 0 };
        assert(PrintSubSetOfSummOfAllElementsEqualZero(testSet) == 15);
    }

    {
        const SET testSet = { -1, 1 };
        assert(PrintSubSetOfSummOfAllElementsEqualZero(testSet) == 1);
    }

    {
        const SET testSet = { -1, 1, -3, 3 };
        assert(PrintSubSetOfSummOfAllElementsEqualZero(testSet) == 3);
    }

    {
        const SET testSet = { -1, 1, -3, 3, -4, 4 };
        assert(PrintSubSetOfSummOfAllElementsEqualZero(testSet) == 9);
    }

    {
        const SET testSet = { -1, 1, -2, 2, -3, 3, -4, 4 };
        assert(PrintSubSetOfSummOfAllElementsEqualZero(testSet) == 25);
    }

    {
        const SET testSet = { -1, 1, -2, 2, -3, 3, -4, 4, -5, 5 };
        assert(PrintSubSetOfSummOfAllElementsEqualZero(testSet) == 75);
    }
}

#include "Set.h"
void TestPrintSubSetOfSummOfAllElementsEqualZero_Heuristic()
{
    {
        const SET testSet = { 1, 3, 5, 7};
        assert(Set(testSet).PrintSubSetOfSummOfAllElementsEqualZero_Heuristic() == 0);
    }

    {
        const SET testSet = { -1, -3, -5, -7 };
        assert(Set(testSet).PrintSubSetOfSummOfAllElementsEqualZero_Heuristic() == 0);
    }

    {
        const SET testSet = { -7, -8, -9, -10, 1, 2, 3 };
        assert(Set(testSet).PrintSubSetOfSummOfAllElementsEqualZero_Heuristic() == 0);
    }

    {
        const SET testSet = { 7, 8, 9, 10, -1, -2, -3 };
        assert(Set(testSet).PrintSubSetOfSummOfAllElementsEqualZero_Heuristic() == 0);
    }

    {
        const SET testSet = { 0, 0, 0, 0};
        assert(Set(testSet).PrintSubSetOfSummOfAllElementsEqualZero_Heuristic() == 15);
    }

    {
        const SET testSet = { 5, 3, 1, 8, -8, -4 };
        assert(Set(testSet).PrintSubSetOfSummOfAllElementsEqualZero_Heuristic() == 4);
    }

    {
        const SET testSet = { 0, 0, 0, 0 };
        assert(Set(testSet).PrintSubSetOfSummOfAllElementsEqualZero_Heuristic() == 15);
    }

    {
        const SET testSet = { -1, 1 };
        assert(Set(testSet).PrintSubSetOfSummOfAllElementsEqualZero_Heuristic() == 1);
    }

    {
        const SET testSet = { -1, 1, -3, 3 };
        assert(Set(testSet).PrintSubSetOfSummOfAllElementsEqualZero_Heuristic() == 3);
    }

    {
        const SET testSet = { -1, 1, -3, 3, -4, 4 };
        assert(Set(testSet).PrintSubSetOfSummOfAllElementsEqualZero_Heuristic() == 9);
    }

    {
        const SET testSet = { -1, 1, -2, 2, -3, 3, -4, 4 };
        assert(Set(testSet).PrintSubSetOfSummOfAllElementsEqualZero_Heuristic() == 25);
    }

    {
        const SET testSet = { -1, 1, -2, 2, -3, 3, -4, 4, -5, 5 };
        assert(Set(testSet).PrintSubSetOfSummOfAllElementsEqualZero_Heuristic() == 75);
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    // TestPrintSubSetOfSummOfAllElementsEqualZero();
    TestPrintSubSetOfSummOfAllElementsEqualZero_Heuristic();
	return 0;
}

