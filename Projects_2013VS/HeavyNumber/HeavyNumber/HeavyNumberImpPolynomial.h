#ifndef HEAVY_NUMBER_IMP_POLYNOMIAL_H
#define HEAVY_NUMBER_IMP_POLYNOMIAL_H

#pragma once

#include <unordered_map>

class HeavyNumberImpPolynomial
{
public:
	HeavyNumberImpPolynomial();
	~HeavyNumberImpPolynomial();

	virtual size_t GetNumOfHeavyNumbersAgainstNdigits(long nDigits);
	size_t GetNumOfHeavyNumbersAgainstRange(size_t start, size_t end);

	const static size_t AVERAGE_VALUE_OF_HEAVY_NUM = 7;

private:
	struct HV_KEY{
		long nDigits;
		long SUM;
		bool operator()(const HV_KEY& right) const {
			return right.nDigits == nDigits && right.SUM == SUM;
		}
	};
	struct HV_KEY_HASH{
		size_t operator()(const HV_KEY& key) const {
			return std::hash<long>()(key.nDigits) ^
				   std::hash<long>()(key.SUM);
		}

		bool operator()(const HV_KEY& k1, const HV_KEY& k2) const {
			return k1.operator()(k2);
		}
	};
	typedef std::unordered_map<HV_KEY, size_t, HV_KEY_HASH, HV_KEY_HASH> HV_CACHE;
	size_t CountCombinatonsGivenSumOfNdigits(long nDigits, long nSides, long sum, HV_CACHE& hvCache);
	void GetDigitsOfNumber(size_t num, std::vector<unsigned int>& digits);
	size_t GetNumOfHeavyNumbersGivenListOfNum(const std::vector<unsigned int>& digits);
	size_t GetLeastHeavyNumGivenNdigits(size_t n);
};

#endif

