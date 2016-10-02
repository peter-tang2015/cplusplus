// SumOfTopDices.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <map>
#include <utility>
#include <vector>


typedef std::pair<size_t, size_t> DiceKey;
typedef std::map<DiceKey, size_t> DiceCacheMap;

void SumOfDiceAlg(long s, long n, long k, long leastValue, std::vector<long> &leastValueOfCombs)
{
	if (k < n || k > (n*s)) {
		return;
	}
	if (n == 1 && k > 0 && k <= s) {
		if (k > leastValue) {
			leastValueOfCombs.push_back(leastValue);
		}
		else {
			leastValueOfCombs.push_back(k);
		}
		return;
	}

	size_t count = 0;
	for (long j = 1; j <= s; ++j) {
		long tempLeastValue = leastValue < j ? leastValue : j; 
		count += SumOfDiceAlg(s, n - 1, k - j, tempLeastValue, leastValueOfCombs);
	}
}

size_t SumOfTopDices(long s, long n, long topN, long k)
{
	if (n < topN || k < topN || k > (s * topN)) {
		return 0;
	}

	std::vector<long> leastValueOfCombs;

	SumOfTopDiceAlg(s, topN, k, 0, leastValueOfCombs);

	size_t count = 0;
	for (size_t i = 0; i < leastValueOfCombs.size(); ++i) {
		count += (s - leastValueOfCombs[i]) ^ (n - topN);
	}

	return count;
}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

