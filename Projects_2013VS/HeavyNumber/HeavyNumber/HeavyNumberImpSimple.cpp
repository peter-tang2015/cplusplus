#include "stdafx.h"
#include "HeavyNumberImpSimple.h"


HeavyNumberImpSimple::HeavyNumberImpSimple()
{
}


HeavyNumberImpSimple::~HeavyNumberImpSimple()
{
}

bool HeavyNumberImpSimple::IsHeavyNumber(size_t num)
{
	if (num < 8) {
		return false;
	}

	double sum = 0;
	double numOfDigits = 0;

	while (num) {
		sum += num % 10;
		num /= 10;
		++numOfDigits;
	}

	if (sum / numOfDigits > 7) {
		return true;
	}

	return false;
}

void HeavyNumberImpSimple::GetHeavyNumber(const size_t start,
										  const size_t end,
										  std::vector<size_t>& hv)
{
	hv.clear();
	if (start > end) {
		return;
	}

	for (size_t num = start; num <= end; ++num) {
		if (IsHeavyNumber(num)) {
			hv.push_back(num);
		}
	}
}

size_t HeavyNumberImpSimple::GetHeavyNumberCount(const size_t start, const size_t end)
{
	if (start > end) {
		return 0;
	}

	size_t count = 0;
	for (size_t num = start; num <= end; ++num) {
		if (IsHeavyNumber(num)) {
			++count;
		}
	}
	return count;
}
