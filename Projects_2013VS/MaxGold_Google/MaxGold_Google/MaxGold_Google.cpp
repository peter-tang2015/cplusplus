// MaxGold_Google.cpp : Defines the entry point for the console application..
//

#include "stdafx.h"

#include <numeric>
#include <unordered_map>
#include <vector>

#include <cassert>

size_t MaxGoldCooperativeAndUnknown(const std::vector<size_t>& goldPots)
{
    if (goldPots.empty()) {
        return 0;
    }

    size_t endIndex = goldPots.size() - 1;
    if (endIndex == 0) {
        return goldPots[0];
    }

    size_t gold = 0;
    size_t whoseTurn = 0; // Even: first player; Odd: second player
    for (size_t startIndex = 0; startIndex < endIndex;) {
        if (goldPots[startIndex] > goldPots[endIndex]) {
            if (whoseTurn & 1) {
                --endIndex; // the second player pick up smaller one
            }
            else {
                gold += goldPots[startIndex];
                ++startIndex; // the first player pick up bigger pot
            }
        }
        else
        {
            if (whoseTurn & 1) {
                ++startIndex; // the second player pick up smaller one
            }
            else {
                gold += goldPots[endIndex];
                --endIndex; // // the first player pick up bigger pot
            }
        
        }
        ++whoseTurn;
    }
    
    return gold;
}

size_t MaxGoldCompetitiveAndUnknown(const std::vector<size_t>& goldPots)
{
    if (goldPots.empty()) {
        return 0;
    }

    size_t endIndex = goldPots.size() - 1;
    if (endIndex == 0) {
        return goldPots[0];
    }

    size_t gold = 0;
    size_t whoseTurn = 0; // Even: first player; Odd: second player
    for (size_t startIndex = 0; startIndex < endIndex;) {
        if (goldPots[startIndex] > goldPots[endIndex]) {
            if (whoseTurn & 1) {
                ++startIndex; // the second player pick up bigger one
            }
            else {
                gold += goldPots[startIndex];
                ++startIndex; // the first player pick up bigger pot
            }
        }
        else
        {
            if (whoseTurn & 1) {
                --endIndex; // the second player pick up bigger one
            }
            else {
                gold += goldPots[endIndex];
                --endIndex; // the first player pick up bigger pot
            }

        }
        ++whoseTurn;
    }

    return gold;
}

struct GoldPotKey {
    size_t startIndex;
    size_t endIndex;

    GoldPotKey(size_t s, size_t e)
        : startIndex(s), endIndex(e)
    {}

    bool operator==(const GoldPotKey& rhs) const {
        return startIndex == rhs.startIndex &&
               endIndex == rhs.endIndex;
    }
};

struct GoldPotKeyHash {
    size_t operator()(const GoldPotKey& key) const {
        return std::hash<double>()(key.startIndex) ^ std::hash<size_t>()(key.endIndex);
    }

    bool operator()(const GoldPotKey& k1, const GoldPotKey& k2) const {
        return k1 == k2;
    }
};

typedef size_t REWARD;
typedef std::unordered_map<GoldPotKey, REWARD, GoldPotKeyHash, GoldPotKeyHash> GoldPotRewardHashMap;

size_t MaxGoldCompetitiveAndKnown_DP(const std::vector<size_t>& goldPots,
                                     const size_t startIndex,
                                     const size_t endIndex,
                                     const size_t sum,
                                     GoldPotRewardHashMap& gprhm)
{
    if (startIndex == (endIndex - 1)) {
        return 0;
    }

    const GoldPotKey gpk{ startIndex, endIndex };
    {
        GoldPotRewardHashMap::const_iterator foundIter = gprhm.find(gpk);
        if (foundIter != gprhm.end()) {
            return foundIter->second;
        }
    }

    size_t returnOfOpponentIfTakeTheLeftPot = goldPots[startIndex] + MaxGoldCompetitiveAndKnown_DP(goldPots,
        startIndex + 1, endIndex, sum - goldPots[startIndex], gprhm);
    size_t returnOfOpponentIfTakeTheRightPot = goldPots[endIndex - 1] + MaxGoldCompetitiveAndKnown_DP(goldPots,
        startIndex, endIndex - 1, sum - goldPots[endIndex - 1], gprhm);
    // the second player tries to maximize his/her gold, and take the bigger
    // return and the left is for the first player
    REWARD expectedReward;
    if (returnOfOpponentIfTakeTheLeftPot < returnOfOpponentIfTakeTheRightPot) {
        expectedReward = sum - returnOfOpponentIfTakeTheRightPot;
    }
    else {
        expectedReward = sum - returnOfOpponentIfTakeTheLeftPot;
    }

    gprhm.insert(std::make_pair(gpk, expectedReward));

    return expectedReward;
}

size_t MaxGoldCompetitiveAndKnown(const std::vector<size_t>& goldPots)
{
    if (goldPots.empty()) {
        return 0;
    }

    size_t totalPots = goldPots.size();
    if (totalPots == 1) {
        return goldPots[0];
    }

    GoldPotRewardHashMap gprhm;
    size_t sum = std::accumulate(goldPots.begin(), goldPots.end(), 0);
    size_t returnOfTakeTheLeft = goldPots[0] + 
        MaxGoldCompetitiveAndKnown_DP(goldPots, 1, totalPots, sum - goldPots[0], gprhm);
    size_t reutrnOfTakeTheRight = goldPots[totalPots - 1] +
        MaxGoldCompetitiveAndKnown_DP(goldPots, 0, totalPots - 1, sum - goldPots[totalPots - 1], gprhm);
    size_t maxGold = returnOfTakeTheLeft > reutrnOfTakeTheRight ? 
            returnOfTakeTheLeft : reutrnOfTakeTheRight;
    return maxGold;
}


size_t MaxGoldCooperativeAndKnown_DP(const std::vector<size_t>& goldPots,
                                     const size_t startIndex,
                                     const size_t endIndex,
                                     const bool isFirstPlayer,
                                     GoldPotRewardHashMap& gprhm)
{
    if (startIndex == (endIndex - 1)) {
        if (isFirstPlayer) {
            return goldPots[startIndex];
        }
        return 0;
    }

    const GoldPotKey gpk{ startIndex, endIndex };
    {
        GoldPotRewardHashMap::const_iterator foundIter = gprhm.find(gpk);
        if (foundIter != gprhm.end()) {
            return foundIter->second;
        }
    }

    size_t returnOfOpponentIfTakeTheLeftPot;
    size_t returnOfOpponentIfTakeTheRightPot;
    if (isFirstPlayer)
    {
        returnOfOpponentIfTakeTheLeftPot = goldPots[startIndex] + MaxGoldCooperativeAndKnown_DP(goldPots,
                                                startIndex + 1, endIndex, false, gprhm);
        returnOfOpponentIfTakeTheRightPot = goldPots[endIndex - 1] + MaxGoldCooperativeAndKnown_DP(goldPots,
                                                startIndex, endIndex - 1, false, gprhm);
    }
    else {
        returnOfOpponentIfTakeTheLeftPot = MaxGoldCooperativeAndKnown_DP(goldPots, startIndex + 1,
                                                endIndex, true, gprhm);
        returnOfOpponentIfTakeTheRightPot = MaxGoldCooperativeAndKnown_DP(goldPots,
                                                startIndex, endIndex - 1, true, gprhm);
    }
    // the second player tries to maximize his/her gold, and take the bigger
    // return and the left is for the first player
    size_t expectedReward = returnOfOpponentIfTakeTheLeftPot > returnOfOpponentIfTakeTheRightPot ?
                            returnOfOpponentIfTakeTheLeftPot : returnOfOpponentIfTakeTheRightPot;

    gprhm.insert(std::make_pair(gpk, expectedReward));

    return expectedReward;
}

size_t MaxGoldCooperativeAndKnown(const std::vector<size_t>& goldPots)
{
    if (goldPots.empty()) {
        return 0;
    }

    size_t totalPots = goldPots.size();
    if (totalPots == 1) {
        return goldPots[0];
    }

    GoldPotRewardHashMap gprhm;
    size_t maxGold = MaxGoldCooperativeAndKnown_DP(goldPots, 0, goldPots.size(), true, gprhm);
    return maxGold;
}


void TestCases()
{
    std::vector<size_t> goldPots = { 1, 2 };
    assert(MaxGoldCompetitiveAndKnown(goldPots) == 2);
    assert(MaxGoldCooperativeAndKnown(goldPots) == 2);

    goldPots = { 1, 3, 2 };
    assert(MaxGoldCompetitiveAndKnown(goldPots) == 3);
    assert(MaxGoldCooperativeAndKnown(goldPots) == 5);

    goldPots = { 1, 2, 10, 3 };
    assert(MaxGoldCompetitiveAndKnown(goldPots) == 11);
    assert(MaxGoldCooperativeAndKnown(goldPots) == 13);

    goldPots = { 4, 1, 2, 10 };
    assert(MaxGoldCompetitiveAndKnown(goldPots) == 12);
    assert(MaxGoldCooperativeAndKnown(goldPots) == 14);

    goldPots = { 4, 1, 2, 10, 3 };
    assert(MaxGoldCompetitiveAndKnown(goldPots) == 9);
    assert(MaxGoldCooperativeAndKnown(goldPots) == 17);

    goldPots = { 5, 4, 1, 2, 10 };
    assert(MaxGoldCompetitiveAndKnown(goldPots) == 15);
    assert(MaxGoldCooperativeAndKnown(goldPots) == 19);

    goldPots = { 5, 4, 1, 2, 10, 3 };
    assert(MaxGoldCompetitiveAndKnown(goldPots) == 16);
    assert(MaxGoldCooperativeAndKnown(goldPots) == 19);
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestCases();

    return 0;
}                                                                                                                                                                                                                                                                               
