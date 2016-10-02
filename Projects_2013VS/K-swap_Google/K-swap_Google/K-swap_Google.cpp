/

/ K-swap_Google.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <set>
#include <string>
#include <unordered_map>

#include <cassert>

const int TOTAL_NUM_OF_DIGITS = 10;

struct SwapPair {
    SwapPair(char src, char dst)
    : a(src < dst ? src : dst),
    b(src > dst ? src : dst)
    {}

    bool operator()(const SwapPair& rhs) const {
        return a == rhs.a && b == rhs.b;
    }

    char a;
    char b;
};

struct SwapPairInfo {
    SwapPairInfo(char src, char dst, size_t f)
    : aLessThanb(src < dst), frequency(f)
    {}

    bool aLessThanb;
    size_t frequency;
};

struct SwapPairHash{
    size_t operator()(const SwapPair& key) const {
        return std::hash<long>()(key.a) ^
            std::hash<long>()(key.b);
    }

    bool operator()(const SwapPair& k1, const SwapPair& k2) const {
        return k1.operator()(k2);
    }
};

typedef std::unordered_map<SwapPair, SwapPairInfo, SwapPairHash, SwapPairHash> SwapPairHashMap;

std::string FindLargestNumber(const std::string& numbers, std::vector<size_t> allDigitsMap[TOTAL_NUM_OF_DIGITS])
{
    for (size_t charIdx = numbers.size(); charIdx > 0; --charIdx) {
        assert(numbers[charIdx - 1] >= '0' && numbers[charIdx - 1] <= '9');
        allDigitsMap[numbers[charIdx - 1] - '0'].push_back(charIdx - 1);
    }

    std::string result;
    for (int num = TOTAL_NUM_OF_DIGITS - 1; num >= 0; --num) {
        if (!allDigitsMap[num].empty()) {
            for (size_t index = 0; index < allDigitsMap[num].size(); ++index) {
                result.push_back('0' + num);
            }
        }
    }

    return result;
}

std::string SwapKcharsBySorting(const std::string& numbers, const std::set<size_t>& swapIndices)
{
    size_t digitsCount[TOTAL_NUM_OF_DIGITS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    for (std::set<size_t>::const_iterator cIter = swapIndices.begin(); cIter != swapIndices.end(); ++cIter) {
        ++digitsCount[numbers[*cIter] - '0'];
    }

    std::vector<char> sortedSwapChars;
    for (int num = TOTAL_NUM_OF_DIGITS - 1; num >= 0; --num) {
        if (digitsCount[num] > 0) {
            for (size_t index = 0; index < digitsCount[num]; ++index) {
                sortedSwapChars.push_back('0' + num);
            }
        }
    }

    std::string result(numbers);
    size_t index = 0;
    for (std::set<size_t>::const_iterator cIter = swapIndices.begin(); 
        cIter != swapIndices.end(); ++cIter, ++index) {
        result[*cIter] = sortedSwapChars[index];
    }

    return result;
}

std::string KswapSolution(const std::string& numbers, const size_t k)
{
    if (k == 0 || numbers.empty()) {
        return numbers;
    }

    std::vector<size_t> digitsMap[TOTAL_NUM_OF_DIGITS];
    const std::string largestNum = FindLargestNumber(numbers, digitsMap);
    assert(largestNum.size() == numbers.size());

    if ((k + 1) >= numbers.size()) {
        // special case to reach the maximal value any way
        return largestNum;
    }


    // find the index to swap
    SwapPairHashMap swapPairHM;
    size_t swapCount = k;
    std::set<size_t> swapIndices;
    size_t tempIndexOfDigitsMap[TOTAL_NUM_OF_DIGITS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    for (size_t index = 0; index < numbers.size() && swapCount > 0; ++index) {
        if (largestNum[index] != numbers[index]) {
            const SwapPair sp(numbers[index], largestNum[index]);
            SwapPairHashMap::iterator found = swapPairHM.find(sp);
            if (found == swapPairHM.end()) {
                swapPairHM.insert(std::make_pair(sp,
                    SwapPairInfo(numbers[index], largestNum[index], 1)));
                --swapCount;
                swapIndices.insert(index);
                swapIndices.insert(digitsMap[largestNum[index] - '0'].at(
                    tempIndexOfDigitsMap[largestNum[index] - '0']));
                ++tempIndexOfDigitsMap[largestNum[index] - '0'];
            }
            else {
                bool aLessThanb = numbers[index] < largestNum[index];
                if (found->second.aLessThanb == aLessThanb) {
                    ++found->second.frequency;
                    --swapCount;
                }
                else {
                    if (found->second.frequency > 0) {
                        --found->second.frequency;
                    }
                    else {
                        ++found->second.frequency;
                        found->second.aLessThanb = aLessThanb;
                        --swapCount;
                    }
                }

                swapIndices.insert(index);
                swapIndices.insert(digitsMap[largestNum[index] - '0'].at(
                    tempIndexOfDigitsMap[largestNum[index] - '0']));
                ++tempIndexOfDigitsMap[largestNum[index] - '0'];
            }
        }
    }

    return SwapKcharsBySorting(numbers, swapIndices);
}

void TestCornerCases()
{
    assert(KswapSolution("", 1).empty());
    assert(KswapSolution("9", 1) == "9");
    assert(KswapSolution("19", 1) == "91");
    assert(KswapSolution("19", 0) == "19");
    assert(KswapSolution("1234", 3) == "4321");
    assert(KswapSolution("119798699", 8) == "999987611");
}

void TestCases()
{
    assert(KswapSolution("132", 1) == "312");
    assert(KswapSolution("132", 2) == "321");
    assert(KswapSolution("7899", 2) == "9987");
    assert(KswapSolution("8799", 2) == "9987");
    assert(KswapSolution("1189119999", 5) == "9999981111");
    assert(KswapSolution("191899", 3) == "999811");
    assert(KswapSolution("191899", 2) == "999811");
    assert(KswapSolution("34155", 2) == "55143");
    assert(KswapSolution("12520", 2) == "52210");
    assert(KswapSolution("876959", 3) == "998756");
    assert(KswapSolution("6899459999", 5) == "9999998654");
    assert(KswapSolution("68994579999", 5) == "99999987654");
    assert(KswapSolution("689984599382999", 5) == "999999988382654");
    assert(KswapSolution("68994593999", 5) == "99999986543");
    assert(KswapSolution("68994597999", 5) == "99999987654");
    assert(KswapSolution("689945932999", 5) == "999999862543");
    assert(KswapSolution("876959", 2) == "996857");
    assert(KswapSolution("123456789098765432199998888777777266655", 350) 
                == "999999888888777777776666655554433222110");
    assert(KswapSolution("123456789098765432199998888777777266655", 35)
                == "999999888888777777776666655554433222110");
    assert(KswapSolution("123456789098765432199998888777777266655", 9)
                == "999999888878765432165438210777777266655");
}


int _tmain(int argc, _TCHAR* argv[])
{
    TestCornerCases();
    TestCases();

    return 0;
}

/*
http://www.careercup.com/question?id=5637944224251904
234567891
134567892
124567893
123567894
123467895
123457896
123456897
123456798
123456789
983456721

876959
996857
998765
 
897659
879989 k = 4 999887
999887 found last 4 largest and swasp 

879939
999837 k = 2
9837 k = 2
37 k = 2
73

989978 k = 2
999878

Soultion:
The idea 

The sub-problem:

The solution of the sub-problem


*/
