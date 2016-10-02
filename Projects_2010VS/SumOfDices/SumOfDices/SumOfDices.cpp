// SumOfDices.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <map>
#include <utility>


typedef std::pair<size_t, size_t> DiceKey;
typedef std::map<DiceKey, size_t> DiceCacheMap;

size_t SumOfDiceAlg(long s, long n, long k, DiceCacheMap &dcm)
{
	if (k < n || k > (n*s)) {
		return 0;
	}
	if (n == 1 && k > 0 && k <= s) {
		return 1;
	}

	const DiceKey key = std::make_pair(n, k);

	if (dcm.find(key) != dcm.end()) {
		return dcm[key];
	}
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

int _tmain(int argc, _TCHAR* argv[])
{
	SumOfDice(6, 6, 23);
	return 0;
}

