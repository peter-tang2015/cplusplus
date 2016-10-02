#ifndef HEAVY_NUMBER_IMP_PERMUTATION_H
#define HEAVY_NUMBER_IMP_PERMUTATION_H

#pragma once

#include "HeavyNumberImpPolynomial.h"

#include <deque>

class HeavyNumberImpPermutation : public HeavyNumberImpPolynomial
{
public:
	HeavyNumberImpPermutation();
	~HeavyNumberImpPermutation();

	size_t GetNumOfHeavyNumbersAgainstNdigits(long nDigits);

private:
	void GetDigitsCombinatonsGivenSumOfNdigits(long nDigits,
											   long nSides,
											   long sum,
											   std::deque<int>& digits,
											   std::vector<std::vector<int>>& digitsCombination);
	size_t GetNumOfHeavyNumberGivenDigitsCombinations(long nDigits,
		const std::vector<std::vector<int>>& digitsCombination);
	double Factorial(int val);
};

#endif


