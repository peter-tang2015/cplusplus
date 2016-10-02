// FindLongestUniqueCharacterSerial_Amazon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <queue>
#include <string>
#include <unordered_set>

std::string FindLongestUniqueCharacterSerial(const std::string& input)
{
    if (input.empty()) {
        return std::string();
    }

    std::unordered_set<char> appearedCharacters;
    std::string uniqueCharacters;
    std::string result;
    auto iterEnd = input.end();
    for (auto iter = input.begin(); iter != iterEnd; ++iter) {
        if (appearedCharacters.find(*iter) != appearedCharacters.end()) {
            // repetitive character
            if (uniqueCharacters.size() > result.size()) {
                result = uniqueCharacters;
            }

            auto iterUC = uniqueCharacters.begin();
            auto iterUCEnd = uniqueCharacters.end();
            for (; iterUC != iterUCEnd; ++iterUC) {
                if (*iterUC == *iter) {
                    break;
                }
                appearedCharacters.erase(*iterUC);
            }
            std::string(++iterUC, iterUCEnd).swap(uniqueCharacters);
        }

        appearedCharacters.insert(*iter);
        uniqueCharacters.push_back(*iter);
    }

    if (uniqueCharacters.size() > result.size()) {
        result.swap(uniqueCharacters);
    }

    return result;
}

#include <cassert>
void TestCasesOfFindLongestUniqueCharacterSerial()
{
    std::string testString;
    assert(FindLongestUniqueCharacterSerial(testString).empty());

    testString = "aaaaaaaaaaaaaaaaaaaa";
    assert(FindLongestUniqueCharacterSerial(testString) == "a");

    testString = "abcdefghijklmn";
    assert(FindLongestUniqueCharacterSerial(testString) == testString);

    testString = "aabcbcdbca";
    assert(FindLongestUniqueCharacterSerial(testString) == "dbca");

    testString = "bcccf";
    assert(FindLongestUniqueCharacterSerial(testString) == "bc");
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestCasesOfFindLongestUniqueCharacterSerial();
    return 0;
}

