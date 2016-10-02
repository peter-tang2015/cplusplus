// HeavyNumber.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cassert>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "HeavyNumberImpSimple.h"
#include "HeavyNumberImpPermutation.h"
#include "HeavyNumberImpPolynomial.h"

const size_t AVERAGE_VALUE_OF_HEAVY_NUM = 7;

size_t GetHowManyDigitsOfNumber(size_t x)
{
	if (x < 10) {
		return 1;
	}

	size_t digits = 0;
	while (x) {
		x = x / 10;
		++digits;
	}

	return digits;
}

bool IsHeavyNumber(size_t x, size_t digits, size_t sum)
{
	if (sum > 9 * digits || sum == 0) {
		return false;
	}

	if (digits == 1 && x >= sum) {
		return true;
	}

	size_t lastDigit = x % 10;
	x /= 10;
	return IsHeavyNumber(x, digits - 1, sum - lastDigit);
}

bool IsHeavyNumber(size_t x)
{
	if (x == 0) {
		return false;
	}

	size_t digitsOfx = GetHowManyDigitsOfNumber(x);
	return IsHeavyNumber(x, digitsOfx, digitsOfx*AVERAGE_VALUE_OF_HEAVY_NUM + 1);
}

/*
* n = 1, return 8
* n = 2, return 69
* n = 3, return 499
* n = 4, return 2999
* n = 5, return 18999
* n = 6, return 169999
* Start to broke when n is big for instance 12 in Win32
* because overflow will happen
*/
size_t GetSmallestHeavyNumGivenNdigits(size_t n)
{
	if (n == 0 || n >= 11) {
		// Invalid parameter
		return -1;
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


void GetHeavyNumbersOfRange(size_t start, size_t end, std::vector<size_t>& result)
{
	if (start > end) {
		return;
	}

	result.clear();
	for (size_t num = start; num < end; ++num) {
		if (IsHeavyNumber(num)) {
			result.push_back(num);
		}
	}
}

void GetHeavyNumbersOfRange_OpStartIndex(size_t start, size_t end, std::vector<size_t>& result)
{
	if (start > end) {
		return;
	}

	size_t numOfDigitsOfStart = GetHowManyDigitsOfNumber(start);
	size_t numOfDigitsOfEnd = GetHowManyDigitsOfNumber(end);

	for (size_t digits = numOfDigitsOfStart; digits <= numOfDigitsOfEnd; ++digits) {
		size_t theLeastHeavyNumberGivenNDigits = GetSmallestHeavyNumGivenNdigits(digits);
		size_t theHeaviestNumberGivenDigits = pow(10, digits) - 1;
		size_t startIndex = start > theLeastHeavyNumberGivenNDigits ? start : theLeastHeavyNumberGivenNDigits;
		size_t endIndex = end < theHeaviestNumberGivenDigits ? end : theHeaviestNumberGivenDigits;
		GetHeavyNumbersOfRange(startIndex, endIndex, result);
	}
}

void WriteVectorIntoFile(const std::vector<size_t>& data, const std::string fileName)
{
	std::ofstream outputFile;
	outputFile.open(fileName.c_str());
	
	for (size_t idx = 0; idx < data.size(); ++idx) {
		outputFile << data[idx] << std::endl;
	}

	outputFile << "Total: " << data.size() << std::endl;

	outputFile.close();
}

void ReadFileIntoVector(std::vector<std::vector<int>>& digitsCombination) {
	std::ifstream inputFile("HeavyNumberImpSimple_5Digits.txt");
	std::string line;
	int number, rem;
	std::vector<int> digits;
	bool found;
	while (std::getline(inputFile, line)) {
		std::istringstream iss(line);
		digits.assign(10, 0);
		if (!(iss >> number)) {
			break;
		}
		while (number) {
			rem = number % 10;
			number /= 10;
			++digits[rem];
		}

		found = false;
		for (size_t index = 0; index < digitsCombination[0].size(); ++index)
		{
			if (digitsCombination[0].at(index) == digits[0] &&
				digitsCombination[1].at(index) == digits[1] &&
				digitsCombination[2].at(index) == digits[2] &&
				digitsCombination[3].at(index) == digits[3] &&
				digitsCombination[4].at(index) == digits[4] &&
				digitsCombination[5].at(index) == digits[5] &&
				digitsCombination[6].at(index) == digits[6] &&
				digitsCombination[7].at(index) == digits[7] &&
				digitsCombination[8].at(index) == digits[8] &&
				digitsCombination[9].at(index) == digits[9]) {
				found = true;
			}
		}


		if (!found) {
			for (size_t digit = 0; digit < 10; ++digit){
				digitsCombination[digit].push_back(digits[digit]);
			}
		}
	}

	size_t val0Against9 = std::count(digitsCombination[9].begin(), digitsCombination[9].end(), 0);
	size_t val1Against9 = std::count(digitsCombination[9].begin(), digitsCombination[9].end(), 1);
	size_t val2Against9 = std::count(digitsCombination[9].begin(), digitsCombination[9].end(), 2);
	size_t val3Against9 = std::count(digitsCombination[9].begin(), digitsCombination[9].end(), 3);
	size_t val4Against9 = std::count(digitsCombination[9].begin(), digitsCombination[9].end(), 4);
	size_t val5Against9 = std::count(digitsCombination[9].begin(), digitsCombination[9].end(), 5);

	return;
}


int _tmain(int argc, _TCHAR* argv[])
{
	/*
	size_t leastHN;
	leastHN = GetSmallestHeavyNumGivenNdigits(0);
	leastHN = GetSmallestHeavyNumGivenNdigits(1);
	leastHN = GetSmallestHeavyNumGivenNdigits(2);
	leastHN = GetSmallestHeavyNumGivenNdigits(3);
	leastHN = GetSmallestHeavyNumGivenNdigits(4);
	leastHN = GetSmallestHeavyNumGivenNdigits(5);
	leastHN = GetSmallestHeavyNumGivenNdigits(6);
	leastHN = GetSmallestHeavyNumGivenNdigits(7);
	leastHN = GetSmallestHeavyNumGivenNdigits(8);
	leastHN = GetSmallestHeavyNumGivenNdigits(9);
	leastHN = GetSmallestHeavyNumGivenNdigits(10);
	leastHN = GetSmallestHeavyNumGivenNdigits(11);
	leastHN = GetSmallestHeavyNumGivenNdigits(12);
	*/
	/*
	std::vector<size_t> result1, result2;

	GetHeavyNumbersOfRange(100000, 1000000, result1);

	GetHeavyNumbersOfRange_OpStartIndex(100000, 1000000, result2);

	for (size_t i = 0; i < 12; ++i) {
		std::cout 
			<< "Number of digits: " << i
			<< ", The least heavy number: "
			<< GetSmallestHeavyNumGivenNdigits(i)
			<< std::endl;
	}
	*/
	
	/*
	HeavyNumberImpSimple hnis;
	std::vector<size_t> hnis_vec;
	hnis.GetHeavyNumber(0, 9, hnis_vec);
	WriteVectorIntoFile(hnis_vec, "HeavyNumberImpSimple_1Digit.txt");
	hnis.GetHeavyNumber(10, 99, hnis_vec);
	WriteVectorIntoFile(hnis_vec, "HeavyNumberImpSimple_2Digits.txt");
	hnis.GetHeavyNumber(100, 999, hnis_vec);
	WriteVectorIntoFile(hnis_vec, "HeavyNumberImpSimple_3Digits.txt");
	hnis.GetHeavyNumber(1000, 9999, hnis_vec);
	WriteVectorIntoFile(hnis_vec, "HeavyNumberImpSimple_4Digits.txt");
	hnis.GetHeavyNumber(10000, 99999, hnis_vec);
	WriteVectorIntoFile(hnis_vec, "HeavyNumberImpSimple_5Digits.txt");
	hnis.GetHeavyNumber(100000, 999999, hnis_vec);
	WriteVectorIntoFile(hnis_vec, "HeavyNumberImpSimple_6Digits.txt");
	hnis.GetHeavyNumber(1000000, 9999999, hnis_vec);
	WriteVectorIntoFile(hnis_vec, "HeavyNumberImpSimple_7Digits.txt");
	hnis.GetHeavyNumber(10000000, 99999999, hnis_vec);
	WriteVectorIntoFile(hnis_vec, "HeavyNumberImpSimple_8Digits.txt");
	hnis.GetHeavyNumber(100000000, 999999999, hnis_vec);
	WriteVectorIntoFile(hnis_vec, "HeavyNumberImpSimple_9Digits.txt");
	*/

	/*
	HeavyNumberImpPolynomial hnp;
	size_t numOfHN;
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstNdigits(0);
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstNdigits(1);
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstNdigits(2);
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstNdigits(3);
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstNdigits(4);
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstNdigits(5);
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstNdigits(6);
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstNdigits(7);
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstNdigits(8);
	*/

	HeavyNumberImpSimple hnis;
	std::vector<size_t> hnis_vec;
	HeavyNumberImpPolynomial hnp;
	size_t numOfHN;
	/*
	hnis.GetHeavyNumber(0, 0, hnis_vec);
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstRange(0, 0);
	hnis.GetHeavyNumber(0, 10, hnis_vec);
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstRange(0, 10);
	hnis.GetHeavyNumber(0, 100, hnis_vec);
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstRange(0, 100);
	hnis.GetHeavyNumber(0, 1000, hnis_vec);
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstRange(0, 1000);
	hnis.GetHeavyNumber(0, 10000, hnis_vec);
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstRange(0, 10000);
	hnis.GetHeavyNumber(0, 100000, hnis_vec);
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstRange(0, 100000);
	hnis.GetHeavyNumber(0, 1000000, hnis_vec);
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstRange(0, 1000000);
	hnis.GetHeavyNumber(0, 10000000, hnis_vec);
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstRange(0, 10000000);
	hnis.GetHeavyNumber(0, 100000000, hnis_vec);
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstRange(0, 100000000);
	*/
	/*
	hnis.GetHeavyNumber(10000, 10000, hnis_vec);
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstRange(10000, 10000);
	hnis.GetHeavyNumber(789, 788, hnis_vec);
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstRange(789, 788);
	hnis.GetHeavyNumber(789, 56788765, hnis_vec);
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstRange(789, 56788765);
	hnis.GetHeavyNumber(0, 200000000, hnis_vec);
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstRange(0, 200000000);
	*/
	std::vector<std::vector<int>> digitsCombination(10);
	ReadFileIntoVector(digitsCombination);
	HeavyNumberImpPermutation hnipe;
	/*
	numOfHN = hnipe.GetNumOfHeavyNumbersAgainstNdigits(1);
	numOfHN = hnipe.GetNumOfHeavyNumbersAgainstNdigits(2);
	numOfHN = hnipe.GetNumOfHeavyNumbersAgainstNdigits(3);
	numOfHN = hnipe.GetNumOfHeavyNumbersAgainstNdigits(4);
	numOfHN = hnipe.GetNumOfHeavyNumbersAgainstNdigits(5);
	numOfHN = hnipe.GetNumOfHeavyNumbersAgainstNdigits(6);
	numOfHN = hnipe.GetNumOfHeavyNumbersAgainstNdigits(7);
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstNdigits(8);
	numOfHN = hnipe.GetNumOfHeavyNumbersAgainstNdigits(8);
	*/
	clock_t startTime = clock();
	/*
	numOfHN = hnis.GetHeavyNumberCount(100000000, 999999999);
	double duration = clock() - startTime;
	std::cout << "HeavyNumberImpSimple 9 digits: " << numOfHN << ", " << duration << std::endl;
	startTime = clock();
	*/
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstNdigits(9);
	std::cout << "HeavyNumberImpPolynomial   9 digits: " << numOfHN << ", " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;
	startTime = clock();
	numOfHN = hnipe.GetNumOfHeavyNumbersAgainstNdigits(9);
	std::cout << "HeavyNumberImpPermutation  9 digits: " << numOfHN << ", " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;
	/*
	startTime = clock();
	numOfHN = hnis.GetHeavyNumberCount(1000000000, 9999999999);
	std::cout << "HeavyNumberImpSimple 10 digits: " << numOfHN << ", " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;
	*/
	startTime = clock();
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstNdigits(10);
	std::cout << "HeavyNumberImpPolynomial  10 digits: " << numOfHN << ", " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;
	startTime = clock();
	numOfHN = hnipe.GetNumOfHeavyNumbersAgainstNdigits(10);
	std::cout << "HeavyNumberImpPermutation 10 digits: " << numOfHN << ", " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;
	startTime = clock();
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstNdigits(11);
	std::cout << "HeavyNumberImpPolynomial  11 digits: " << numOfHN << ", " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;
	startTime = clock();
	numOfHN = hnipe.GetNumOfHeavyNumbersAgainstNdigits(11);
	std::cout << "HeavyNumberImpPermutation 11 digits: " << numOfHN << ", " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;
	startTime = clock();
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstNdigits(12);
	std::cout << "HeavyNumberImpPolynomial  12 digits: " << numOfHN << ", " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;
	startTime = clock();
	numOfHN = hnipe.GetNumOfHeavyNumbersAgainstNdigits(12);
	std::cout << "HeavyNumberImpPermutation 12 digits: " << numOfHN << ", " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;
	startTime = clock();
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstNdigits(13);
	std::cout << "HeavyNumberImpPolynomial  13 digits: " << numOfHN << ", " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;
	startTime = clock();
	numOfHN = hnipe.GetNumOfHeavyNumbersAgainstNdigits(13);
	std::cout << "HeavyNumberImpPermutation 13 digits: " << numOfHN << ", " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;
	startTime = clock();
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstNdigits(14);
	std::cout << "HeavyNumberImpPolynomial  14 digits: " << numOfHN << ", " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;
	startTime = clock();
	numOfHN = hnipe.GetNumOfHeavyNumbersAgainstNdigits(14);
	std::cout << "HeavyNumberImpPermutation 14 digits: " << numOfHN << ", " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;
	startTime = clock();
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstNdigits(15);
	std::cout << "HeavyNumberImpPolynomial  15 digits: " << numOfHN << ", " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;
	startTime = clock();
	numOfHN = hnipe.GetNumOfHeavyNumbersAgainstNdigits(15);
	std::cout << "HeavyNumberImpPermutation 15 digits: " << numOfHN << ", " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;
	startTime = clock();
	numOfHN = hnp.GetNumOfHeavyNumbersAgainstNdigits(16);
	std::cout << "HeavyNumberImpPolynomial  16 digits: " << numOfHN << ", " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;
	startTime = clock();
	numOfHN = hnipe.GetNumOfHeavyNumbersAgainstNdigits(16);
	std::cout << "HeavyNumberImpPermutation 16 digits: " << numOfHN << ", " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;

	
	return 0;
}

