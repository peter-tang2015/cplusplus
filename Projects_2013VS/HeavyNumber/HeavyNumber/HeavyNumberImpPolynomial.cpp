#include "stdafx.h"

#include "HeavyNumberImpPolynomial.h"

#include <assert.h>
#include <numeric>

HeavyNumberImpPolynomial::HeavyNumberImpPolynomial()
{
}


HeavyNumberImpPolynomial::~HeavyNumberImpPolynomial()
{
}


size_t HeavyNumberImpPolynomial::GetNumOfHeavyNumbersAgainstRange(size_t start, size_t end)
{
	if (start > end) {
		return 0;
	}
	std::vector<unsigned int> digitsOfStart;
	GetDigitsOfNumber(start, digitsOfStart);
	std::vector<unsigned int> digitsOfEnd;
	GetDigitsOfNumber(end, digitsOfEnd);

	size_t count = std::accumulate(digitsOfEnd.begin(), digitsOfEnd.end(), 0.0) / digitsOfEnd.size() 
					> AVERAGE_VALUE_OF_HEAVY_NUM ? 1 : 0;

	for (size_t digit = digitsOfStart.size(); digit < digitsOfEnd.size(); ++digit) {
		count += GetNumOfHeavyNumbersAgainstNdigits(digit);
	}

	if (end >= GetLeastHeavyNumGivenNdigits(digitsOfEnd.size())) {
		count += GetNumOfHeavyNumbersGivenListOfNum(digitsOfEnd);
	}
	if (start >= GetLeastHeavyNumGivenNdigits(digitsOfStart.size())) {
		count -= GetNumOfHeavyNumbersGivenListOfNum(digitsOfStart);
	}

	return count;
}

size_t HeavyNumberImpPolynomial::GetNumOfHeavyNumbersAgainstNdigits(long nDigits)
{
	if (nDigits < 0) {
		return 0;
	}
	
	const static size_t PRE_COMPUTED_NUM_OF_HV[9] = { 0, 2, 10, 56, 330, 2001, 12313, 76470, 478302 };

	if (nDigits <= 8) {
		return PRE_COMPUTED_NUM_OF_HV[nDigits];
	}

	size_t numOfHN = 0;
	HV_CACHE hvCache;
	const size_t heaviness = nDigits * AVERAGE_VALUE_OF_HEAVY_NUM + 1;
	const long nSides = 9;
	for (size_t topDigits = 1; topDigits <= nSides; ++topDigits) {
		numOfHN += CountCombinatonsGivenSumOfNdigits(nDigits - 1, nSides, heaviness - topDigits, hvCache);
	}

	return numOfHN;
}

size_t HeavyNumberImpPolynomial::CountCombinatonsGivenSumOfNdigits(long nDigits, long nSides, long sum, HV_CACHE& hvCache)
{
	if (sum > nSides * nDigits) {
		return 0;
	}

	if (sum <= 0 && nDigits == 0) {
		return 1;
	}

	const HV_KEY key{ nDigits, sum };
	HV_CACHE::const_iterator cachedIter = hvCache.find(key);
	if (cachedIter != hvCache.end()) {
		return cachedIter->second;
	}

	size_t count = 0;
	for (size_t val = 0; val <= nSides; ++val) {
		count += CountCombinatonsGivenSumOfNdigits(nDigits - 1, nSides, sum - val, hvCache);
	}

	hvCache.insert(std::make_pair(key, count));

	return count;
}

void HeavyNumberImpPolynomial::GetDigitsOfNumber(size_t num, std::vector<unsigned int>& digits)
{
	digits.clear();
	if (num == 0) {
		digits.push_back(0);
		return;
	}

	while (num) {
		digits.push_back(num % 10);
		num /= 10;
	}
	return;
}

size_t HeavyNumberImpPolynomial::GetNumOfHeavyNumbersGivenListOfNum(const std::vector<unsigned int>& digits)
{
	if (digits.empty()) {
		return 0;
	}

	long numOfDigits = digits.size();
	assert(digits[numOfDigits - 1] > 0);
	long sum = numOfDigits * AVERAGE_VALUE_OF_HEAVY_NUM + 1;
	size_t start;
	size_t count = 0;
	HV_CACHE hvCache;
	const long nSides = 9;
	while (numOfDigits) {
		start = numOfDigits == digits.size() ? 1 : 0;
		for (size_t digit = start; digit < digits[numOfDigits - 1]; ++digit) {
			count += CountCombinatonsGivenSumOfNdigits(numOfDigits - 1, nSides, sum - digit, hvCache);
		}
		sum -= digits[numOfDigits - 1];
		--numOfDigits;
	}

	return count;
}

/*
* n = 1, return 8
* n = 2, return 69
* n = 3, return 499
* n = 4, return 2999
* n = 5, return 18999
* n = 6, return 169999
* Start to broke when n is too big for Win32
* because overflow will happen (n < 11)
*
*/
size_t HeavyNumberImpPolynomial::GetLeastHeavyNumGivenNdigits(size_t n)
{
	const size_t PRE_COMPUTED_LEAST_HN[] = { 8,
											 69,
											 499,
											 2999,
											 18999,
											 169999,
											 1499999,
											 12999999,
											 109999999,
											 1079999999 };
	if (n == 0) {
		return -1;
	}

	if (n < 11) {
		return PRE_COMPUTED_LEAST_HN[n - 1];
	}

	size_t sum = n*AVERAGE_VALUE_OF_HEAVY_NUM + 1;
	size_t num = 0;
	size_t tempDigits = 0;
	while (sum) {
		if (sum > 9) {
			num += 9 * pow(10, tempDigits);
			++tempDigits;
			sum -= 9;
		}
		else {
			break;
		}
	}


	if ((n - tempDigits) == 1) {
		num += sum * pow(10, tempDigits);
	}
	else {
		num += (sum - 1) * pow(10, tempDigits);
		num += pow(10, n - 1);
	}

	return num;
}