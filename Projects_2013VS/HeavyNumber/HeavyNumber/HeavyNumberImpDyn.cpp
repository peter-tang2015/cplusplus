#include "stdafx.h"
#include "HeavyNumberImpDyn.h"


HeavyNumberImpDyn::HeavyNumberImpDyn()
{
}


HeavyNumberImpDyn::~HeavyNumberImpDyn()
{
}

bool HeavyNumberImpDyn::IsHeavyNumber(size_t num)
{
	if (num < 8) {
		return false;
	}

	size_t numOfDigits = GetNumOfDigitsAgainstNumber(num);

	return IsHeavyNumberInternal(num, numOfDigits * 7 + 1);

}

void HeavyNumberImpDyn::GetHeavyNumber(const size_t start,
									   const size_t end,
									   std::vector<size_t>& hv)
{
	hv.clear();
	if (start > end) {
		return;
	}

	size_t numOfDigitsAgainstStart = GetNumOfDigitsAgainstNumber(start);
	size_t numOfDigitsAgainstEnd = GetNumOfDigitsAgainstNumber(end);

	if (numOfDigitsAgainstStart == numOfDigitsAgainstEnd) {
		for (size_t num = start; num <= end; ++num) {
			if (IsHeavyNumberInternal(num, numOfDigitsAgainstStart * 7 + 1)) {
				hv.push_back(num);
			}
		}
	}
	else if (numOfDigitsAgainstStart == (numOfDigitsAgainstEnd - 1)) {
		for (size_t num = start; num < pow(10, numOfDigitsAgainstStart); ++num) {
			if (IsHeavyNumberInternal(num, numOfDigitsAgainstStart * 7 + 1)) {
				hv.push_back(num);
			}
		}

		for (size_t num = pow(10, numOfDigitsAgainstStart); num <= end; ++num) {
			if (IsHeavyNumberInternal(num, numOfDigitsAgainstStart * 7 + 1)) {
				hv.push_back(num);
			}
		}
	}
	else {
		for (size_t num = start; num < pow(10, numOfDigitsAgainstStart); ++num) {
			if (IsHeavyNumberInternal(num, numOfDigitsAgainstStart * 7 + 1)) {
				hv.push_back(num);
			}
		}

		for (size_t digits = numOfDigitsAgainstStart + 1; digits < numOfDigitsAgainstEnd; ++digits) {
			GetAllHeavyNumbersOfNdigits(digits, hv);
		}

		for (size_t num = pow(10, numOfDigitsAgainstEnd - 1); num <= end; ++num) {
			if (IsHeavyNumberInternal(num, numOfDigitsAgainstStart * 7 + 1)) {
				hv.push_back(num);
			}
		}
	}
}

void HeavyNumberImpDyn::GetAllHeavyNumbersOfNdigits(size_t n, std::vector<size_t>& hv)
{
	for (size_t num = pow(10, n - 1); num < pow(10, n); ++num) {
		if (IsHeavyNumberInternal(num, 7 * n + 1)) {
			hv.push_back(num);
		}
	}
}

bool HeavyNumberImpDyn::IsHeavyNumberInternal(size_t num,
											  size_t sum)
{
	if (sum > num * 9) {
		return false;
	}

	size_t rem = num % 10;
	if (rem >= sum) {
		return true;
	}

	return IsHeavyNumberInternal(num / 10, sum - rem);
}

size_t HeavyNumberImpDyn::GetNumOfDigitsAgainstNumber(size_t num)
{
	if (num < 10) {
		return 1;
	}

	size_t numOfDigits = 0;
	while (num) {
		num /= num;
		++numOfDigits;
	}

	return numOfDigits;
}
