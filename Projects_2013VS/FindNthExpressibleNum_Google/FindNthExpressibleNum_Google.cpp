// FindNthExpressibleNum_Google.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <list>
#include <queue>
#include <unordered_map>
#include <vector>

struct KeyValuePair
{
    KeyValuePair()
    {}

    KeyValuePair(unsigned long val,
                 unsigned long k,
                 size_t index)
        :value(val), key(k), keyIndex(index)
    {}

    KeyValuePair(const KeyValuePair&) = default;
    KeyValuePair& operator=(const KeyValuePair&) = default;

    unsigned long value = 2;
    unsigned long key = 2;
    size_t keyIndex = 0;
};

struct KeyValuePairComparator
{
    bool operator()(const KeyValuePair& lhs, const KeyValuePair& rhs) {
        return lhs.value > rhs.value;
    }
};

using MinHeap = std::priority_queue<KeyValuePair,
                                    std::vector<KeyValuePair>,
                                    KeyValuePairComparator>;
using ValueMap = std::unordered_map<unsigned long, std::list<unsigned long>>;

unsigned long FindNthExpressibleNumGivenSet(const std::vector<unsigned long>& sortedPrimes,
                                            const unsigned long Nth,
                                            MinHeap& topNums,
                                            ValueMap& nums)
{
    unsigned long numCounter = Nth - 1;

    auto iterStart = sortedPrimes.begin();
    auto iterEnd = sortedPrimes.end();
    unsigned long value;
    while (true) {
        const KeyValuePair kvp = topNums.top();
        nums[kvp.key].pop_front();
        // pop out a value from the priority queue
        // count until the Nth
        --numCounter;
        if (numCounter == 0) {
            return kvp.value;
        }
        // Generate the number and push them into the list
        for (auto iter = iterStart + kvp.keyIndex; iter != iterEnd; ++iter) {
            value = *iter * kvp.value;
            nums[*iter].push_back(value);
        }
        // pop out the value from the priority queue
        // and push its successor from the value list into the priority queue
        topNums.pop();
        topNums.push(KeyValuePair(nums[kvp.key].front(), kvp.key, kvp.keyIndex));
    }

    return 0;
}

unsigned long FindNthExpressibleNumGivenSet(const std::vector<unsigned long>& sortedPrimes,
                                            const unsigned long Nth)
{
    if (sortedPrimes.empty() || Nth == 0) {
        // indicates failure
        return 0;
    }

    if (Nth == 1) {
        return 1;
    }

    if (Nth <= sortedPrimes.size() + 1) {
        return sortedPrimes[Nth - 2];
    }

    MinHeap topNums;
    ValueMap nums;
    auto iterEnd = sortedPrimes.end();
    size_t idx = 0;
    // Starting point:
    // the values: each prime number x 1
    // the priority queue is (prime number, prime number) - <value, key> pair
    for (auto iter = sortedPrimes.begin(); iter != iterEnd; ++iter, ++idx) {
        std::list<unsigned long> values;
        values.push_front(*iter);
        nums[*iter] = values;
        topNums.push(KeyValuePair(*iter, *iter, idx));
    }

    return FindNthExpressibleNumGivenSet(sortedPrimes, Nth, topNums, nums);
}

#include <cassert>
void TestFindNthExpressibleNum()
{
    std::vector<unsigned long> sortedPrimes;
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 0) == 0);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 1) == 0);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 5) == 0);

    sortedPrimes.push_back(2);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 0) == 0);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 1) == 1);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 2) == 2);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 3) == 4);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 4) == 8);

    sortedPrimes.push_back(3);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 0) == 0);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 1) == 1);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 2) == 2);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 3) == 3);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 4) == 4);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 5) == 6);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 6) == 8);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 7) == 9);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 8) == 12);

    sortedPrimes = {3, 5, 7};
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 0) == 0);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 1) == 1);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 2) == 3);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 3) == 5);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 4) == 7);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 5) == 9);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 6) == 15);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 7) == 21);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 8) == 25);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 9) == 27);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 10) == 35);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 11) == 45);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 12) == 49);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 13) == 63);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 14) == 75);
    assert(FindNthExpressibleNumGivenSet(sortedPrimes, 15) == 81);
}

struct ValueBasePair
{
    ValueBasePair(unsigned long val, unsigned long b)
        : value(val), base(b)
    {}
    unsigned long value;
    unsigned long base;
};

struct ValueBasePairComparator
{
    bool operator()(const ValueBasePair& lhs, const ValueBasePair& rhs) {
        return lhs.value > rhs.value;
    }
};

using MinHeap2 = std::priority_queue<ValueBasePair,
                                     std::vector<ValueBasePair>,
                                     ValueBasePairComparator>;

unsigned long FindNthMultipleNumGivenSet(const unsigned long Nth,
                                         MinHeap2& topNums)
{
    unsigned long numCounter = Nth;
    unsigned long lastVal = 0;
    while (true) {
        const ValueBasePair kvp = topNums.top();
        // pop out a value from the priority queue
        // count until the Nth
        // But only count if this number is different from the last
        // because common mulitple can only count as once
        // For example {4, 6}, numbers like 12, 24 count only once
        if (kvp.value != lastVal) {
            --numCounter;
            lastVal = kvp.value;
        }
        if (numCounter == 0) {
            return kvp.value;
        }

        // pop out the value from the priority queue
        // and push its successor from the value list into the priority queue
        // Successor: <multiple, base> -> <multiple + base, base>
        topNums.pop();
        topNums.push(ValueBasePair(kvp.value + kvp.base, kvp.base));
    }

    return 0;
}

unsigned long FindNthMultipleNumGivenSet(const std::vector<unsigned long>& sortedPrimes,
    const unsigned long Nth)
{
    if (sortedPrimes.empty() || Nth == 0) {
        // indicates failure
        return 0;
    }

    if (Nth <= sortedPrimes.size()) {
        return sortedPrimes[Nth - 1];
    }

    MinHeap2 topNums;
    auto iterEnd = sortedPrimes.end();
    // Starting point:
    // the values: each number x 1
    // the priority queue is (multiple, base) - <value, base> pair
    for (auto iter = sortedPrimes.begin(); iter != iterEnd; ++iter) {
        topNums.push(ValueBasePair(*iter, *iter));
    }

    return FindNthMultipleNumGivenSet(Nth, topNums);
}




int _tmain(int argc, _TCHAR* argv[])
{
    TestFindNthExpressibleNum();
    TestFindNthMultipleNum();

    return 0;
}

