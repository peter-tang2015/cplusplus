// StringPatternSearch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <vector>

ptrdiff_t StringPatternSearch_Naive(const std::string& text,
									 const std::string& pattern)
{
	if (text.empty() || pattern.empty()) {
		return -1;
	}

	for (size_t pos_t = 0, pos_p = 0; (pos_t + pos_p) < text.size();) {
		if (text[pos_t + pos_p] == pattern[pos_p]) {
			++pos_p;
			if (pos_p == pattern.size()) {
				return static_cast<ptrdiff_t>(pos_t);
			}
		}
		else {
			++pos_t;
			pos_p = 0;
		}
	}

	return -1;
}

void BuildUpKMPTable(const std::string& pattern, std::vector<ptrdiff_t>& table)
{
	if (pattern.empty()) {
		return;
	}

	table.clear();
	table.reserve(pattern.size());
	table.push_back(-1);

	ptrdiff_t matchCount = 0;
	for (size_t pos = 1; pos < pattern.size(); ++pos) {
		table.push_back(matchCount);
		if (pattern[pos] == pattern[matchCount]) {
			++matchCount;
		}
		else {
			matchCount = 0;
		}
	}
}

ptrdiff_t StringPatternSearch_KMP(const std::string& text,
								  const std::string& pattern)
{
	if (text.empty() || pattern.empty()) {
		return -1;
	}

	std::vector<ptrdiff_t> kmpTable;
	BuildUpKMPTable(pattern, kmpTable);

	for (size_t pos_t = 0, pos_p = 0; (pos_t + pos_p) < text.size();) {
		if (text[pos_t + pos_p] == pattern[pos_p]) {
			++pos_p;
			if (pos_p == pattern.size()) {
				return static_cast<ptrdiff_t>(pos_t);
			}
		}
		else {
			if (kmpTable[pos_p] < 0) {
				++pos_t;
				pos_p = 0;
			}
			else {
				pos_t = pos_t + pos_p - kmpTable[pos_p];
				pos_p = kmpTable[pos_p];
			}
		}
	}

	return -1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::string pattern1 = "ABCDABD";
	std::vector<ptrdiff_t> kmpTable1;
	BuildUpKMPTable(pattern1, kmpTable1);

	std::string pattern2 = "PARTICIPATE IN PARACHUTE";
	std::vector<ptrdiff_t> kmpTabl2;
	BuildUpKMPTable(pattern2, kmpTabl2);

	std::string text = "Description of pseudocode for the table - building algorithm";
	std::string ptn = "code";
	ptrdiff_t pos_native = StringPatternSearch_Naive(text, ptn);
	ptrdiff_t pos_kmp = StringPatternSearch_KMP(text, ptn);

	text = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
	ptn = "aaaaaaaaaaaaaaaaaaaaaaaab";
	pos_native = StringPatternSearch_Naive(text, ptn);
	pos_kmp = StringPatternSearch_KMP(text, ptn);

	ptn = "cccedcdecece";
	pos_native = StringPatternSearch_Naive(text, ptn);
	pos_kmp = StringPatternSearch_KMP(text, ptn);

	return 0;
}

