// DiceGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <math.h>
#include <numeric>
#include <time.h>
#include <unordered_map>
#include <utility>
#include <vector>


struct DiceKey {
    size_t nDice;
    size_t curSum;
    bool operator()(const DiceKey& right) const {
        return nDice == right.nDice && curSum == right.curSum;
    }
};

struct DiceKey_Hash {
    size_t operator()(const DiceKey& key) const {
        return std::hash<size_t>()(key.nDice) ^ std::hash<size_t>()(key.curSum);
    }

    bool operator()(const DiceKey& k1, const DiceKey& k2) const {
        return k1.operator()(k2);
    }
};
typedef std::unordered_map<DiceKey, size_t, DiceKey_Hash, DiceKey_Hash> DiceCacheMap;

size_t SumOfDiceAlg(long s, long n, long k, DiceCacheMap &dcm)
{
    if (k < n || k >(n*s)) {
        // no solution found in this case
        return 0;
    }
    if (n == 1 && k > 0 && k <= s) {
        // found a solution here
        return 1;
    }

    const DiceKey key{ n, k };

    if (dcm.find(key) != dcm.end()) {
        return dcm[key];
    }

    // this loop is the sub-problem illustration
    //  f(S, N, K) = sigma(f(S, N-1, K-Si))
    size_t count = 0;
    for (long j = 1; j <= s; ++j) {
        count += SumOfDiceAlg(s, n - 1, k - j, dcm);
    }

    dcm.insert(std::make_pair(key, count));

    return count;
}

size_t SumOfDice(long s, long n, long k)
{
    DiceCacheMap dcm;

    size_t count = SumOfDiceAlg(s, n, k, dcm);

    return count;
}

void CalculateQiAndPiOfSums(size_t s,
    size_t n,
    std::vector<size_t>& counts,
    std::vector<double>& probablity)
{
    if (s == 0 || n == 0) {
        return;
    }

    counts.clear();
    counts.reserve(s*n - n + 1);
    probablity.clear();
    probablity.reserve(s*n - n + 1);

    double allCombinations = pow((double)s, (double)n);
    for (size_t count, sum = n; sum <= n*s; ++sum) {
        count = SumOfDice(s, n, sum);
        counts.push_back(count);
        probablity.push_back((double)count / allCombinations);
    }
}

size_t CalculateSigmaQiKi(size_t sides,
    size_t nDices,
    const std::vector<size_t>& counts)
{
    size_t sigma = 0;
    for (size_t sum = nDices; sum < sides*nDices + 1; ++sum) {
        sigma += sum * counts[sum - nDices];
    }

    return sigma;
}

void CalculateStrategyAndPiOfSums(size_t sides,
    size_t nDices,
    std::vector<double>& strategyVals,
    std::vector<double>& probablity)
{
    std::vector<size_t> counts;
    CalculateQiAndPiOfSums(sides,
        nDices,
        counts,
        probablity);

    size_t sigma = CalculateSigmaQiKi(sides,
        nDices,
        counts);

    strategyVals.clear();
    strategyVals.reserve(counts.size());
    double strategyVal;
    for (size_t indx = 0, sum = nDices; indx < counts.size(); ++indx, ++sum) {
        strategyVal = (double)sigma / (double)counts[indx] - sum;
        strategyVals.push_back(strategyVal);
    }
}

struct CurrentState{
    double reward;
    size_t curSum;
    CurrentState(double r, size_t s)
        : reward(r), curSum(s)
    {}
    bool operator()(const CurrentState& right) const {
        return reward == right.reward && curSum == right.curSum;
    }
};

struct CurrentState_HASH{
    size_t operator()(const CurrentState& key) const {
        return std::hash<double>()(key.reward) ^ std::hash<size_t>()(key.curSum);
    }

    bool operator()(const CurrentState& k1, const CurrentState& k2) const {
        return k1.operator()(k2);
    }
};

typedef std::unordered_map<CurrentState, double, CurrentState_HASH, CurrentState_HASH> CS_CACHE;

double DiceGameStrategy(size_t sides,
    size_t nDices,
    const std::vector<double>& strategyVals,
    const std::vector<double>& probablity,
    double reward,
    size_t curSum,
    CS_CACHE& cache)
{
    if (reward >= strategyVals[curSum - nDices]) {
        return reward;
    }

    const CurrentState key{ reward, curSum };
    {
        CS_CACHE::const_iterator cachedIter = cache.find(key);
        if (cachedIter != cache.end()) {
            return cachedIter->second;
        }
    }

    double expectedReward = 0;
    double p;
    for (size_t sum = nDices; sum < sides*nDices + 1; ++sum) {
        if (sum != curSum) {
            p = probablity[sum - nDices];
            expectedReward += p* DiceGameStrategy(sides,
                nDices,
                strategyVals,
                probablity,
                reward + sum,
                sum,
                cache);
        }
    }

    cache.insert(std::make_pair(key, expectedReward));

    return expectedReward;
}

double DiceGame(size_t sides, size_t nDices)
{
    std::vector<double> strategyVals;
    std::vector<double> probablity;

    CalculateStrategyAndPiOfSums(sides,
        nDices,
        strategyVals,
        probablity);

    CS_CACHE cache;
    double gameValue = 0;
    // std::vector<double> gameValues;
    for (size_t sum = nDices; sum < (sides * nDices + 1); ++sum) {
        double val = DiceGameStrategy(sides,
            nDices,
            strategyVals,
            probablity,
            0,
            sum,
            cache);
        gameValue += probablity[sum - nDices] * val;
        //gameValues.push_back(val);
    }

    return gameValue;
}

size_t RangedRandomVal(size_t lowerBound, size_t upperBound)
{
    // return [lowerBound, upperBound)
    // srand((unsigned int)time(nullptr));
    size_t random = (double)rand() / (RAND_MAX + 1) * (upperBound - lowerBound) + lowerBound;
    return random;
}

size_t RollDices(size_t sides, size_t nDices)
{
    size_t sum = 0;

    for (size_t dice = 0; dice < nDices; ++dice) {
        sum += RangedRandomVal(1, sides + 1);
    }

    return sum;
}

size_t SimulateOneGame_MC(size_t sides, size_t nDices)
{
    size_t reward = 0;
    size_t preSum = 0;
    size_t curSum = RollDices(sides, nDices);

    while (preSum != curSum) {
        reward += curSum;
        preSum = curSum;
        curSum = RollDices(sides, nDices);
    }

    return reward;
}

double DiceGame_MC(size_t sides, size_t nDices, size_t simulationSize)
{
    srand((unsigned int)time(nullptr));

    std::vector<size_t> simResult;
    simResult.reserve(simulationSize);

    for (size_t sim = 0; sim < simulationSize; ++sim) {
        simResult.push_back(SimulateOneGame_MC(sides, nDices));
    }

    size_t sum = std::accumulate(simResult.begin(), simResult.end(), 0);
    double gameValue = (double)sum / (double)(simResult.size());

    return gameValue;
}

int _tmain(int argc, _TCHAR* argv[])
{
    DiceGame(6, 2); // gameValue    22.224974509843324  double
    DiceGame(6, 3); // gameValue    40.471468665548528  double
    DiceGame(6, 4); // gameValue    61.969998311984483  double

    return 0;
}
