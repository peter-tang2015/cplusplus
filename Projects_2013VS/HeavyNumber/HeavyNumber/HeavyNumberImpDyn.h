#ifndef HEAVY_NUMBER_IMP_DYN_H
#define HEAVY_NUMBER_IMP_DYN_H

#pragma once

#include "HeavyNumberImpSimple.h"

class HeavyNumberImpDyn
{
public:
	HeavyNumberImpDyn();
	~HeavyNumberImpDyn();

	bool IsHeavyNumber(size_t num);

	void GetHeavyNumber(const size_t start,
						const size_t end,
						std::vector<size_t>& hv);
	
private:
	bool IsHeavyNumberInternal(size_t numOfDigits,
							   size_t sum);
	size_t GetNumOfDigitsAgainstNumber(size_t num);

	void GetAllHeavyNumbersOfNdigits(size_t n, std::vector<size_t>& hv);
};

#endif


