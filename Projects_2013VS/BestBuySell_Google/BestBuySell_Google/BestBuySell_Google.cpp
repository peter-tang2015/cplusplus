// BestBuySell_Google.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <limits>
#include <numeric>
#include <unordered_map>
#include <vector>

struct BuySellEntry
{
    BuySellEntry()
    {}

    BuySellEntry(size_t buy, size_t sell) :
        ticksToBuy(buy), ticksToSell(sell)
    {}

    BuySellEntry(const BuySellEntry& other) :
        ticksToBuy(other.ticksToBuy),
        ticksToSell(other.ticksToSell)
    {}

    BuySellEntry(const BuySellEntry&& other) :
        ticksToBuy(std::move(other.ticksToBuy)),
        ticksToSell(std::move(other.ticksToSell))
    {}

    size_t ticksToBuy = 0;
    size_t ticksToSell = 0;
};

struct HashKeyPair
{
    HashKeyPair(size_t i, size_t k) :
        index(i), kAttemp(k)
    {}

    bool operator==(const HashKeyPair& rhs) const {
        return index == rhs.index && kAttemp == rhs.kAttemp;
    }

    size_t index{ std::numeric_limits<size_t>::max() };
    size_t kAttemp{ std::numeric_limits<size_t>::min() };
};

struct HashKeyPairHashFunc
{
    size_t operator()(const HashKeyPair& hKey) const {
        return std::hash<size_t>()(hKey.index) ^ 
               std::hash<size_t>()(hKey.kAttemp);
    }

    bool operator()(const HashKeyPair& lhs, const HashKeyPair& rhs) const {
        return lhs == rhs;
    }
};

using HashMap = std::unordered_map<HashKeyPair, size_t, HashKeyPairHashFunc, HashKeyPairHashFunc>;

std::vector<BuySellEntry> DetectBuySellEntries(const std::vector<size_t> ticks, 
                                               std::vector<size_t>& profit)
{
    const auto sizeOfData = ticks.size();
    std::vector<BuySellEntry> BSE;
    if (sizeOfData == 0) {
        return BSE;
    }

    BSE.reserve(sizeOfData);
    profit.clear();
    profit.reserve(sizeOfData);
    size_t buy;
    for (size_t index = 1; index < sizeOfData; ++index) {
        if (ticks[index] > ticks[index - 1]) {
            buy = ticks[index - 1];
            for (; index < sizeOfData; ++index) {
                if (index == (sizeOfData - 1) || ticks[index] > ticks[index + 1]) {
                    BSE.push_back(BuySellEntry{ buy, ticks[index] });
                    profit.push_back(ticks[index] - buy);
                    break;
                }
            }
        }
    }

    return BSE;
}

size_t BestBuySell_DP(const std::vector<BuySellEntry>& BSE,
                      const std::vector<size_t>& profit,
                      const size_t startIndex,
                      const size_t kAttemps,
                      HashMap& cache)
{
    if (BSE.empty() || kAttemps == 0 || startIndex == BSE.size()) {
        return 0;
    }

    if (kAttemps >= (BSE.size() - startIndex)) {
        return std::accumulate(profit.begin() + startIndex, profit.end(), 0);
    }

    // cached?
    const HashKeyPair key = { startIndex, kAttemps };
    {
        auto foundCIter = cache.find(key);
        if (foundCIter != cache.end()) {
            return foundCIter->second;
        }
    }

    // DP
    auto minBuyTick = std::numeric_limits<size_t>::max();
    auto maxSellTick = std::numeric_limits<size_t>::min();
    auto totalProfit = std::numeric_limits<size_t>::min();
    size_t tempProfit;
    for (auto index = startIndex; index < BSE.size(); ++index) {
        if (BSE[index].ticksToBuy < minBuyTick) {
            minBuyTick = BSE[index].ticksToBuy;
        }
        if (BSE[index].ticksToSell > maxSellTick) {
            maxSellTick = BSE[index].ticksToSell;
        }

        tempProfit = maxSellTick - minBuyTick +
            BestBuySell_DP(BSE, profit, index + 1, kAttemps - 1, cache);
        if (tempProfit > totalProfit) {
            totalProfit = tempProfit;
        }
    }

    // cache it
    cache.insert(HashMap::value_type(key, totalProfit));

    return totalProfit;
}

size_t BestBuySell(const std::vector<size_t>& ticks, const size_t kAttemps)
{
    if (ticks.empty() || kAttemps == 0) {
        return 0;
    }

    std::vector<size_t> profit;
    auto BSE = DetectBuySellEntries(ticks, profit);
    HashMap cache;

    return BestBuySell_DP(BSE, profit, 0, kAttemps, cache);
}

#include <cassert>
void TestCases()
{
    {
        std::vector<size_t> ticks = { 1, 2, 3, 4, 5, 6, 7 };
        // BuySellEntries: (1, 7)
        assert(BestBuySell(ticks, 0) == 0);
        assert(BestBuySell(ticks, 1) == 6);
        assert(BestBuySell(ticks, 2) == 6);
    }
    
    {
        std::vector<size_t> ticks = { 1, 2, 3, 4, 2, 6, 7 };
        // BuySellEntries: (1, 4), (2, 7)
        assert(BestBuySell(ticks, 0) == 0);
        assert(BestBuySell(ticks, 1) == 6);
        assert(BestBuySell(ticks, 2) == 8);
        assert(BestBuySell(ticks, 3) == 8);
    }

    {
        std::vector<size_t> ticks = { 1, 2, 3, 4, 2, 6, 7, 2, 4, 6};
        // BuySellEntries: (1, 4), (2, 7), (2, 6)
        assert(BestBuySell(ticks, 0) == 0);
        assert(BestBuySell(ticks, 1) == 6);
        assert(BestBuySell(ticks, 2) == 10);
        assert(BestBuySell(ticks, 3) == 12);
        assert(BestBuySell(ticks, 4) == 12);
    }

    {
        std::vector<size_t> ticks = { 1, 2, 3, 4, 2, 6, 7, 2, 4, 6 , 1, 5, 9};
        // BuySellEntries: (1, 4), (2, 7), (2, 6), (1, 9)
        assert(BestBuySell(ticks, 0) == 0);
        assert(BestBuySell(ticks, 1) == 8);
        assert(BestBuySell(ticks, 2) == 14);
        assert(BestBuySell(ticks, 3) == 18);
        assert(BestBuySell(ticks, 4) == 20);
        assert(BestBuySell(ticks, 5) == 20);
    }

    {
        std::vector<size_t> ticks = { 4, 3, 2, 5, 4, 6, 7, 1, 7, 8, 5, 6 };
        // BuySellEntries: (2, 5), (4, 7), (1, 8), (5, 6)
        assert(BestBuySell(ticks, 0) == 0);
        assert(BestBuySell(ticks, 1) == 7);
        assert(BestBuySell(ticks, 2) == 12);
        assert(BestBuySell(ticks, 3) == 13);
        assert(BestBuySell(ticks, 4) == 14);
        assert(BestBuySell(ticks, 5) == 14);
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestCases();
    return 0;
}

