// FindRepeatedSequence_Google.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <unordered_map>
#include <vector>

#include <cassert>

typedef std::unordered_map<size_t, size_t> FrequencyMap;

bool IsPalindrome(const std::string& myStr)
{
    if (myStr.empty()) {
        return false;
    }

    const size_t len = myStr.size();
    if (len == 1) {
        return true;
    }

    for (size_t start = 0, end = len - 1; start < end; ++start, --end) {
        if (myStr[start] != myStr[end]) {
            return false;
        }
    }

    return true;
}

bool DetectFrequencyAndReturnFalseIGreaterThan2(const std::string& myStr, FrequencyMap& freqMap)
{
    for (std::string::const_iterator cIt = myStr.begin(); cIt != myStr.end(); ++cIt) {
        FrequencyMap::iterator found = freqMap.find(*cIt);
        if (found == freqMap.end()) {
            freqMap.insert(std::make_pair(*cIt, 1));
        }
        else {
            ++found->second;
            if (found->second > 2) {
                return true;
            }
        }
    }

    return false;
}

std::string StripCharsAppearingOnlyOnce(const std::string& myStr, const FrequencyMap& freqMap)
{
    std::string result;
    for (std::string::const_iterator cIt = myStr.begin(); cIt != myStr.end(); ++cIt) {
        FrequencyMap::const_iterator found = freqMap.find(*cIt);
        assert(found != freqMap.end());
        if (found->second == 2) {
            result.push_back(*cIt);
        }
    }

    return result;
}

bool FindRepeatedSequence(const std::string& myStr)
{
    FrequencyMap freqMap;
    if (DetectFrequencyAndReturnFalseIGreaterThan2(myStr, freqMap)) {
        return true;
    }

    std::string stringWithCharAppearingTwice = StripCharsAppearingOnlyOnce(myStr, freqMap);
    if (stringWithCharAppearingTwice.empty() || stringWithCharAppearingTwice.size() < 4) {
        return false;
    }

    return !IsPalindrome(stringWithCharAppearingTwice);
}

void TestCases()
{
    assert(FindRepeatedSequence("aaa") == true);
    assert(FindRepeatedSequence("abab") == true);
    assert(FindRepeatedSequence("abba") == false);
    assert(FindRepeatedSequence("acbdaghfb") == true);
    assert(FindRepeatedSequence("abcdacb") == true);
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestCases();
    return 0;
}