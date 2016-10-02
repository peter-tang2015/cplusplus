// MinAbs_Google.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <algorithm>
#include <limits>
#include <unordered_map>

#include <cmath>

struct HashKeyPair
{
    HashKeyPair(size_t i, ptrdiff_t v) :
        index(i), value(v)
    {}
    size_t index; // index of i, |Ai - Bi|
    ptrdiff_t value; // searching value of Bi

    bool operator==(const HashKeyPair& hkp) const {
        return index == hkp.index &&
               value == hkp.value;
    }
};

struct HashKeyPairHashFunc
{
    size_t operator()(const HashKeyPair& hkp) {
        return std::hash<size_t>()(hkp.index) ^
               std::hash<ptrdiff_t>()(hkp.value);
    }

    bool operator()(const HashKeyPair& hkp1, const HashKeyPair& hkp2) const {
        return hkp1 == hkp2;
    }

};
typedef size_t MinSigmaOfAbsDiff;
typedef std::unordered_map<HashKeyPair, MinSigmaOfAbsDiff, 
                           HashKeyPairHashFunc, HashKeyPairHashFunc> HashMap;

ptrdiff_t GetMinAbsValue(const ptrdiff_t ai, const ptrdiff_t target, const ptrdiff_t val)
{
    if (ai > (val + target)) {
        return ai - val - target;
    }
    else if (ai < (val - target)) {
        return val - target - ai;
    }

    return 0;
}

ptrdiff_t MinAbsDiff_DP(const std::vector<ptrdiff_t>& AI,
                     const ptrdiff_t target,
                     const ptrdiff_t minAi,
                     const ptrdiff_t maxAi,
                     const size_t curIndex,
                     const ptrdiff_t value,
                     HashMap& cache)
{
    if (curIndex == (AI.size() - 1)) {
        return GetMinAbsValue(*AI.rbegin(), target, value);
    }

    const HashKeyPair key = { curIndex, value };
    {
        // cached already?
        HashMap::const_iterator foundCIter = cache.find(key);
        if (foundCIter != cache.end()) {
            return foundCIter->second;
        }
    }

    // DP
    auto minSigmaOfAbsDiff = std::numeric_limits<ptrdiff_t>::max();
    ptrdiff_t tempMinSigmaOfAbsDiff;
    for (ptrdiff_t tempVal = value - target; tempVal <= (value + target); ++tempVal) {
        if (tempVal <= maxAi && tempVal >= minAi) {
            tempMinSigmaOfAbsDiff = abs(tempVal - AI[curIndex])
                    + MinAbsDiff_DP(AI, target, minAi, maxAi, curIndex + 1, tempVal, cache);
            if (minSigmaOfAbsDiff > tempMinSigmaOfAbsDiff) {
                minSigmaOfAbsDiff = tempMinSigmaOfAbsDiff;
            }
        }
    }

    // Cache it
    cache.insert(std::make_pair(key, minSigmaOfAbsDiff));

    return minSigmaOfAbsDiff;
}

ptrdiff_t MinAbsDiff(const std::vector<ptrdiff_t>& AI, const ptrdiff_t target)
{
    auto minVal = *(std::min_element(AI.begin(), AI.end()));
    auto maxVal = *(std::max_element(AI.begin(), AI.end()));

    if ((maxVal - minVal) <= target) {
        return 0;
    }

    HashMap cache;
    auto minSigmaOfAbsDiff = std::numeric_limits<ptrdiff_t>::max();
    ptrdiff_t temp;
    for (ptrdiff_t val = minVal; val <= maxVal; ++val) {
        temp = abs(AI[0] - val) +
               MinAbsDiff_DP(AI, target, minVal, maxVal, 1, val, cache);
        if (minSigmaOfAbsDiff > temp) {
            minSigmaOfAbsDiff = temp;
        }
        if (minSigmaOfAbsDiff == 0) {
            return 0;
        }
    }

    return minSigmaOfAbsDiff;
}

#include <cassert>
void TestCases()
{
    {
        std::vector<ptrdiff_t> testVec = { 50, 50, 50, 50, 50, 50, 50, 50, 50, 50};
        ptrdiff_t target = 5;
        assert(MinAbsDiff(testVec, target) == 0);
    }

    {
        std::vector<ptrdiff_t> testVec = { 48, 53, 51, 50, 49, 53, 52, 48, 49, 50 };
        ptrdiff_t target = 5;
        assert(MinAbsDiff(testVec, target) == 0);
    }

    {
        std::vector<ptrdiff_t> testVec = { 56, 50};
        ptrdiff_t target = 5;
        assert(MinAbsDiff(testVec, target) == 1);
    }

    {
        std::vector<ptrdiff_t> testVec = { 56, 50, 50 };
        ptrdiff_t target = 5;
        assert(MinAbsDiff(testVec, target) == 1);
    }

    {
        std::vector<ptrdiff_t> testVec = { 56, 50, 50, 56 };
        ptrdiff_t target = 5;
        assert(MinAbsDiff(testVec, target) == 2);
    }

    {
        std::vector<ptrdiff_t> testVec = { 55, 77, 52, 61, 39, 6, 25, 60, 49, 47 };
        ptrdiff_t target = 10;
        assert(MinAbsDiff(testVec, target) == 75);
    }

    {
        std::vector<ptrdiff_t> testVec = { 94, 35, 29, 55 };
        ptrdiff_t target = 10;
        assert(MinAbsDiff(testVec, target) == 65);
    }

    {
        std::vector<ptrdiff_t> testVec = { 97, 73, 56, 56, 93, 55, 29, 47, 90, 36 };
        ptrdiff_t target = 3;
        assert(MinAbsDiff(testVec, target) == 157);
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestCases();
    return 0;
}

