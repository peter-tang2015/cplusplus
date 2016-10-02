// PickMaximalCoins_Facebook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Position
{
    Position()
        : x(0.0)
        , y(0.0)
    {}
    Position(double _x, double _y)
        : x(_x)
        , y(_y)
    {}
    double x;
    double y;
    bool operator >(const Position &rhs) const {
        return x > rhs.x && y > rhs.y;
    }

    bool operator <(const Position &rhs) const {
        return x < rhs.x && y < rhs.y;
    }

    bool operator ==(const Position &rhs) const {
        return x == rhs.x && y == rhs.y;
    }
};

struct PositionHashFunc
{
    size_t operator()(const Position &p) {
        return std::hash<double>()(p.x) ^ std::hash<double>()(p.y);
    }

    bool operator ()(const Position &lhs, const Position &rhs) const {
        return lhs == rhs;
    }
};

struct PositionPtrHashFunc
{
    size_t operator()(const Position *p) {
        return std::hash<double>()(p->x) ^ std::hash<double>()(p->y);
    }

    bool operator ()(const Position *lhs, const Position *rhs) const {
        return lhs->operator==(*rhs);
    }
};

struct PositionCmpLess
{
    bool operator()(const Position *lhs, const Position *rhs) const {
        return lhs->operator<(*rhs);
    }
};

std::vector<size_t> FindLargerPositions(const std::vector<Position> &input,
                                        const Position &pivotal)
{
    auto itEnd = input.end();
    size_t index = 0;
    std::vector<size_t> result;
    result.reserve(input.size());
    for (auto it = input.begin(); it != itEnd; ++it, ++index) {
        if (it->operator>(pivotal)) {
            result.push_back(index);
        }
    }

    return result;
}

std::vector<size_t> FindLargerPositions(const std::vector<Position> &input,
                                        const std::vector<size_t> &searchIn,
                                        const Position &pivotal)
{
    std::vector<size_t> result;
    result.reserve(searchIn.size());
    auto itEnd = searchIn.end();
    for (auto it = searchIn.begin(); it != itEnd; ++it) {
        auto&& tempPos = input[*it];
        if (tempPos.operator>(pivotal)) {
            result.emplace_back(*it);
        }
    }
    return result;
}

using HashMap = std::unordered_map<Position, size_t, PositionHashFunc, PositionHashFunc>;

size_t PickMaximalCoins_R(const std::vector<Position> &coins,
                          const std::vector<size_t> &subProbelm,
                          const Position &pivotal,
                          HashMap &hash)
{
    if (subProbelm.empty()) {
        return 0;
    }

    auto it = hash.find(pivotal);
    if (it != hash.end()) {
        return it->second;
    }

    size_t maximal = 0;
    auto itEnd = subProbelm.end();
    for (auto it = subProbelm.begin(); it != itEnd; ++it) {
        auto& position = coins[*it];
        const std::vector<size_t> subproblem = FindLargerPositions(coins, subProbelm, position);
        const size_t temp = 1 + PickMaximalCoins_R(coins, subproblem, position, hash);
        if (maximal < temp) {
            maximal = temp;
        }
    }
    hash[pivotal] = maximal;

    return maximal;
}

size_t PickMaximalCoins_R(const std::vector<Position> &coins)
{
    if (coins.empty()) {
        return 0;
    }

    HashMap hm;
    size_t maximal = 0;
    auto itEnd = coins.end();
    for (auto it = coins.begin(); it != itEnd; ++it) {
        size_t temp;
        auto itFound = hm.find(*it);
        if (itFound != hm.end()) {
            temp = 1 + itFound->second;
        }
        else {
            const std::vector<size_t> subProblem = FindLargerPositions(coins, *it);
            temp = 1 + PickMaximalCoins_R(coins, subProblem, *it, hm);
            hm.insert(std::make_pair(*it, temp));
        }
        if (maximal < temp) {
            maximal = temp;
        }
    }

    return maximal;
}

size_t PickMaximalCoins(const std::vector<Position> &coins)
{
    if (coins.empty()) {
        return 0;
    }
    using PositionMSet = std::multiset<const Position*, PositionCmpLess>;
    using PositionSet = std::set<const Position*, PositionCmpLess>;
    using PositionTreeMap = std::vector<PositionSet>;
    std::vector<const Position*> sortedCoins;
    {
        PositionMSet sortedCoinsSet;
        {
            auto itEnd = coins.end();
            for (auto it = coins.begin(); it != itEnd; ++it) {
                sortedCoinsSet.insert(&(*it));
            }
        }
        sortedCoins.reserve(sortedCoinsSet.size());
        sortedCoins.assign(sortedCoinsSet.begin(), sortedCoinsSet.end());
    }

    auto itEnd = sortedCoins.end();
    PositionTreeMap posTM;
    for (auto it = sortedCoins.begin(); it != itEnd; ++it) {
        if (!posTM.empty()) {
            const size_t CUR_SIZE = posTM.size();
            for (size_t idx = 0; idx < CUR_SIZE; ++idx) {
                auto&& curPTM = posTM[idx];
                if (!curPTM.empty()) {
                    auto eqRange = curPTM.equal_range(*it);
                    if (eqRange.second == curPTM.end()) {
                        if ((*curPTM.rbegin())->operator<(**it)) {
                            curPTM.insert(*it);
                        }
                        else {
                            PositionSet posSet(curPTM.begin(), eqRange.first);
                            posSet.insert(*it);
                            posTM.push_back(posSet);
                        }
                    }
                    else if (eqRange.second == curPTM.begin()) {
                        curPTM.insert(*it);
                    }
                    else {
                        --eqRange.second;
                        if ((*eqRange.second)->operator<(**it)) {
                            curPTM.insert(*it);
                        }
                        else {
                            PositionSet posSet(curPTM.begin(), eqRange.first);
                            posSet.insert(++eqRange.second, curPTM.end());
                            posSet.insert(*it);
                            posTM.push_back(posSet);
                        }
                    }
                }
            }
        }
        else {
            PositionSet posSet;
            posSet.insert(*it);
            posTM.push_back(posSet);
        }
    }

    size_t maximalCoins = 0;
    auto itTMEnd = posTM.end();
    for (auto it = posTM.begin(); it != itTMEnd; ++it) {
        if (maximalCoins < it->size()) {
            maximalCoins = it->size();
        }
    }

    return maximalCoins;
}

struct TreeMapNode
{
    TreeMapNode()
        : val(0)
    {}

    TreeMapNode(const Position *val_)
        : val(val_)
    {}
    const Position* val;
    std::vector<const Position*> children;
    void Insert(const Position* pos) {

    }
};

using PosPtrHashSet = std::unordered_set<const Position*,
                                         PositionPtrHashFunc,
                                         PositionPtrHashFunc>;
size_t PickMaximalCoins_1(const std::vector<Position> &coins)
{
    if (coins.empty()) {
        return 0;
    }
    using PositionSet = std::set<const Position*, PositionCmpLess>;
    PosPtrHashSet posHS;
    auto itEnd = coins.end();
    for (auto it = coins.begin(); it != itEnd; ++it) {
        posHS.insert(&(*it));
    }

    size_t maximalCoins = 0;
    PositionSet posSet;
    while (!posHS.empty()) {
        posSet.clear();
        PosPtrHashSet tempHS;
        auto itHSEnd = posHS.end();
        for (auto it = posHS.begin(); it != itHSEnd; ++it) {
            auto itInsert = posSet.insert(*it);
            if (!itInsert.second) {
                tempHS.insert(*it);
            }
        }
        if (maximalCoins < posSet.size()) {
            maximalCoins = posSet.size();
        }
        posHS.swap(tempHS);
    }

    return maximalCoins;
}

#include <cassert>

void TestPickMaximalCoins()
{
    {
        const std::vector<Position> coins;
        assert(PickMaximalCoins_R(coins) == 0);
        assert(PickMaximalCoins(coins) == 0);
    }

    {
        const std::vector<Position> coins = { { 5, 5 }, { 1.5, 3.5 }, { 2, 2 }, { 2.0, 4.0 }, 
                                { 4, 4 }, { 5.0, 2.0 }, { 3, 3 }, { 4.0, 1.0 }, { 1, 1 }};
        assert(PickMaximalCoins_R(coins) == 5);
        assert(PickMaximalCoins(coins) == 5);
        assert(PickMaximalCoins_1(coins) == 5);
    }

    {
        const std::vector<Position> coins = {
                      { 6.1, 2.1 }, { 2.2, 6.2 }, { 5.2, 5.2 }, { 6.2, 2.2 },
            { 2.3, 6.3 }, { 5.3, 5.3 }, { 6.3, 2.3 }, { 5.4, 5.4 },
            { 1.0, 1.0 }, { 2.0, 6.0 }, { 5.0, 5.0 }, { 6.0, 2.0 },
            { 2.1, 6.1 }, { 5.1, 5.1 } };
        assert(PickMaximalCoins_R(coins) == 6);
        assert(PickMaximalCoins(coins) == 6);
        assert(PickMaximalCoins_1(coins) == 6);
    }

    {
        const std::vector<Position> coins = {
            { 6.1, 2.1 }, { 2.2, 6.2 }, { 5.2, 5.2 }, { 6.2, 2.2 },
            { 2.3, 6.3 }, { 5.3, 5.3 }, { 6.3, 2.3 }, { 4.0, 5.3 },
            { 5.4, 5.4 }, { 1.0, 1.0 }, { 2.0, 6.0 }, { 5.0, 5.0 },
            { 6.0, 2.0 }, { 2.1, 6.1 }, { 5.1, 5.1 }, { 5.3, 4.0 } };
        assert(PickMaximalCoins_R(coins) == 6);
        assert(PickMaximalCoins(coins) == 6);
        assert(PickMaximalCoins_1(coins) == 6);
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestPickMaximalCoins();
    return 0;
}
