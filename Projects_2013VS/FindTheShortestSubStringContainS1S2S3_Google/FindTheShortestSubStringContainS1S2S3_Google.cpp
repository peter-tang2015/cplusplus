// FindTheShortestSubStringContainS1S2S3_Google.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

void FindSubString(std::string const &input,
                   std::string const &sub,
                   std::vector<size_t> &foundPos)
{
    if (input.empty() || sub.empty()) {
        return;
    }
    size_t pos = 0;
    while (true)
    {
        pos = input.find(sub, pos);
        if (pos == std::string::npos) {
            break;
        }
        foundPos.push_back(pos);
        ++pos;
    }
}

struct SubString {
    SubString(size_t idx, size_t length)
        : startIndex(idx)
        , len(length)
    {}

    size_t startIndex;
    size_t len;

    size_t EndIndex() const {
        return startIndex + len;
    }

    bool operator > (SubString const & rhs) {
        return this->len > rhs.len;
    }
};

SubString FindSubStringContainS1S2S3(SubString const &s1,
                                     SubString const &s2,
                                     SubString const &s3)
{
    size_t startIndex = std::min(std::min(s1.startIndex, s2.startIndex), s3.startIndex);
    size_t endIndex = std::max(std::max(s1.EndIndex(), s2.EndIndex()), s3.EndIndex());
    return SubString(startIndex, endIndex - startIndex);
}

void FindShortestSubString(int idxS1, int idxS2, int idxS3,
                          size_t len1, size_t len2, size_t len3,
                          SubString& bestResult)
{
    if (idxS1 < 0 || idxS2 < 0 || idxS3 < 0) {
        return;
    }

    SubString temp = FindSubStringContainS1S2S3(SubString(idxS1, len1),
                                                SubString(idxS2, len2),
                                                SubString(idxS3, len3));
    if (bestResult.operator>(temp)) {
        bestResult = temp;
    }
}

std::string FindTheShortestSubStringContainS123(std::string const &input,
                                                std::string const &S1,
                                                std::string const &S2,
                                                std::string const &S3)
{
    if (input.empty() || S1.empty() || S2.empty() || S3.empty()) {
        return std::string();
    }

    const size_t len1 = S1.size();
    const size_t len2 = S2.size();
    const size_t len3 = S3.size();
    const size_t minLen = std::min(std::min(len1, len2), len3);
    const size_t maxLen = std::max(std::max(len1, len2), len3);
    const size_t lenInput = input.size();
    const char* cstrInput = input.c_str();
    const char* cstrS1 = S1.c_str();
    const char* cstrS2 = S2.c_str();
    const char* cstrS3 = S3.c_str();

    int idxS1 = -1;
    int idxS2 = -1;
    int idxS3 = -1;
    SubString bestResult(0, lenInput);
    for (size_t index = 0; (index + minLen) < lenInput; ++index) {
        if (strncmp(cstrInput + index, cstrS1, len1) == 0) {
            idxS1 = index;
            FindShortestSubString(idxS1, idxS2, idxS3, len1, len2, len3, bestResult);
        }
        if (strncmp(cstrInput + index, cstrS2, len2) == 0) {
            idxS2 = index;
            FindShortestSubString(idxS1, idxS2, idxS3, len1, len2, len3, bestResult);
        }
        if (strncmp(cstrInput + index, cstrS3, len3) == 0) {
            idxS3 = index;
            FindShortestSubString(idxS1, idxS2, idxS3, len1, len2, len3, bestResult);
        }

        if (bestResult.len == maxLen) {
            break;
        }
    }

    if (idxS1 < 0 || idxS2 < 0 || idxS3 < 0) {
        return std::string();
    }

    return input.substr(bestResult.startIndex, bestResult.len);
}

std::string FindTheShortestSubStringContainS1S2S3(std::string const &input,
                                                  std::string const &s1,
                                                  std::string const &s2,
                                                  std::string const &s3)
{
    std::vector<size_t> foundPos1;
    FindSubString(input, s1, foundPos1);

    std::vector<size_t> foundPos2;
    FindSubString(input, s2, foundPos2);

    std::vector<size_t> foundPos3;
    FindSubString(input, s3, foundPos3);

    if (foundPos1.empty() || foundPos2.empty() || foundPos3.empty()) {
        return std::string();
    }

    const size_t len1 = s1.size();
    const size_t len2 = s2.size();
    const size_t len3 = s3.size();
    
    SubString bestResult(0, input.size());
    for (auto iter1 = foundPos1.begin(); iter1 != foundPos1.end(); ++iter1) {
        // iter1, iter2NotGreater, iter3NotGreater
        // iter1, iter2NotGreater, iter3Greater
        // iter1, iter2Greater, iter3NotGreater
        // iter1, iter2Greater, iter3Greater
        auto range2 = std::equal_range(foundPos2.begin(), foundPos2.end(), *iter1);
        auto range3 = std::equal_range(foundPos3.begin(), foundPos3.end(), *iter1);
        if (range2.first == range2.second && range2.first != foundPos2.begin()) {
            --range2.first;
        }
        if (range3.first == range3.second && range3.first != foundPos3.begin()) {
            --range3.first;
        }

        SubString s1(*iter1, len1);
        if (range2.first != foundPos2.end() && range3.first != foundPos3.end()) {
            SubString temp = FindSubStringContainS1S2S3(
                s1,
                SubString(*range2.first, len2),
                SubString(*range3.first, len3));
            if (bestResult.operator>(temp)) {
                bestResult = temp;
            }
        }
        if (range2.first != foundPos2.end() && range3.second != foundPos3.end()) {
            SubString temp = FindSubStringContainS1S2S3(
                s1,
                SubString(*range2.first, len2),
                SubString(*range3.second, len3));
            if (bestResult.operator>(temp)) {
                bestResult = temp;
            }
        }
        if (range2.second != foundPos2.end() && range3.first != foundPos3.end()) {
            SubString temp = FindSubStringContainS1S2S3(
                s1,
                SubString(*range2.second, len2),
                SubString(*range3.first, len3));
            if (bestResult.operator>(temp)) {
                bestResult = temp;
            }
        }
        if (range2.second != foundPos2.end() && range3.second != foundPos3.end()) {
            SubString temp = FindSubStringContainS1S2S3(
                s1,
                SubString(*range2.second, len2),
                SubString(*range3.second, len3));
            if (bestResult.operator>(temp)) {
                bestResult = temp;
            }
        }
    }

    return input.substr(bestResult.startIndex, bestResult.len);
}

#include <cassert>
void TestFindTheShortestSubStringContainS1S2S3()
{
    {
        const std::string input("abc0123456789aksdfjasd");
        const std::string s1("0123");
        const std::string s2("3456");
        const std::string s3("");
        std::string result = FindTheShortestSubStringContainS123(input, s1, s2, s3);
        assert(result.empty() == true);
    }

    {
        const std::string input("abc0123456789aksdfjasd");
        const std::string s1("0123456");
        const std::string s2("3456");
        const std::string s3("1234");
        std::string result = FindTheShortestSubStringContainS123(input, s1, s2, s3);
        assert(result == std::string("0123456"));
    }

    {
        const std::string input("abc0123456789aksdfjasd");
        const std::string s1("0123");
        const std::string s2("3456");
        const std::string s3("6789");
        std::string result = FindTheShortestSubStringContainS123(input, s1, s2, s3);
        assert(result == std::string("0123456789"));
    }

    {
        const std::string input("sdfa01234ad23456dfad6789abc0123456789aksdfjasd");
        const std::string s1("0123");
        const std::string s2("3456");
        const std::string s3("6789");
        std::string result = FindTheShortestSubStringContainS123(input, s1, s2, s3);
        assert(result == std::string("0123456789"));
    }

    {
        const std::string input("sdfa01234ad23456dfad6789abc0123456789aksdfjasd0123skd3456kjsd6789jhs");
        const std::string s1("0123");
        const std::string s2("3456");
        const std::string s3("6789");
        std::string result = FindTheShortestSubStringContainS123(input, s1, s2, s3);
        assert(result == std::string("0123456789"));
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestFindTheShortestSubStringContainS1S2S3();
    return 0;
}

