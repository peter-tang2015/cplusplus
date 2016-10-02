#include "stdafx.h"
#include "HeavyNumberImpPermutation.h"


HeavyNumberImpPermutation::HeavyNumberImpPermutation()
{
}


HeavyNumberImpPermutation::~HeavyNumberImpPermutation()
{
}


size_t HeavyNumberImpPermutation::GetNumOfHeavyNumbersAgainstNdigits(long nDigits)
{
	if (nDigits < 0) {
		return 0;
	}

	const size_t PRE_COMPUTED_NUM_OF_HV[9] = { 0, 2, 10, 56, 330, 2001, 12313, 76470, 478302 };
	if (nDigits <= 8) {
		return PRE_COMPUTED_NUM_OF_HV[nDigits];
	}

	const size_t heaviness = nDigits * AVERAGE_VALUE_OF_HEAVY_NUM + 1;
	const long nSidesUpperBound = 9;
	const size_t nSideLowerBound = 7;
	std::deque<int> digits;
	std::vector<std::vector<int>> digitsCombinations(10);
	for (size_t topDigits = nSidesUpperBound; topDigits > nSideLowerBound; --topDigits) {
		digits.clear();
		digits.push_back(topDigits);
		GetDigitsCombinatonsGivenSumOfNdigits(nDigits - 1, topDigits, heaviness - topDigits,
											  digits, digitsCombinations);
	}

	return GetNumOfHeavyNumberGivenDigitsCombinations(nDigits, digitsCombinations);
}

void HeavyNumberImpPermutation::GetDigitsCombinatonsGivenSumOfNdigits(
	long nDigits,
	long nSides,
	long sum,
	std::deque<int>& digits,
	std::vector<std::vector<int>>& digitsCombination)
{
	if (sum > nSides * nDigits) {
		return;
	}

	if (sum <= 0 && nDigits == 0) {
		for (size_t index = 0; index < digitsCombination.size(); ++index) {
			digitsCombination[index].push_back(0);
		}
		size_t size = digitsCombination[0].size();
		for (size_t val, index = 0; index < digits.size(); ++index) {
			val = digits[index];
			++digitsCombination[val].at(size - 1);
		}
		return;
	}


	size_t count = 0;
	for (long val = nSides; val >= 0; --val) {
		digits.push_back(val);
		GetDigitsCombinatonsGivenSumOfNdigits(nDigits - 1, val, sum - val, digits, digitsCombination);
		digits.pop_back();
	}
}

size_t HeavyNumberImpPermutation::GetNumOfHeavyNumberGivenDigitsCombinations(
	long nDigits,
	const std::vector<std::vector<int>>& digitsCombination)
{
	double factorailNDigits = Factorial(nDigits);
	size_t numOfHM = 0;
	double permutation;
	for (size_t index = 0; index < digitsCombination[0].size(); ++index) {
		permutation = digitsCombination[0].at(index) == 0? 
						factorailNDigits : (nDigits - digitsCombination[0].at(index)) * Factorial(nDigits - 1);
		for (size_t digit = 0; digit < 10; ++digit) {
			permutation /= Factorial(digitsCombination[digit].at(index));
		}
		numOfHM += permutation;
	}

	return numOfHM;
}

double HeavyNumberImpPermutation::Factorial(int val)
{
	if (val <= 1) {
		return 1.0;
	}

	double factorial = 1.0;
	while (val) {
		factorial *= val;
		--val;
	}

	return factorial;
}