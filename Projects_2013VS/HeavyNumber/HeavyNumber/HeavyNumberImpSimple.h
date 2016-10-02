#ifndef HEAVY_NUMBER_IMP_SIMPLE_H
#define HEAVY_NUMBER_IMP_SIMPLE_H

#pragma once

#include <vector>

class HeavyNumberImpSimple
{
public:
	HeavyNumberImpSimple();
	~HeavyNumberImpSimple();

	bool IsHeavyNumber(size_t num);

	void GetHeavyNumber(const size_t start,
						const size_t end,
						std::vector<size_t>& hv);
	size_t GetHeavyNumberCount(const size_t start, const size_t end);
};

#endif


