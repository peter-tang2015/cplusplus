// FindLargestPalindromeInString.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>

#include <cassert>

struct PalindromeInString
{
    int pos;    // start position in string
    int len;    // length of palindrome
};

PalindromeInString FindLargestPalindromeInString(const std::string& str)
{
    if (str.empty()) {
        return PalindromeInString{ -1, -1 };
    }
    
    if (str.length() == 1) {
        return PalindromeInString{ 0, 1 };
    }

    if (str.length() == 2) {
        if (str[0] == str[1]) {
            return PalindromeInString{ 0, 2 };
        }
        else {
            return PalindromeInString{ 0, 1 };
        }
    }

    PalindromeInString result = { 0, 1 };
    bool found = false;
    size_t tempIndex;
    size_t curIndex;
    for (tempIndex = 0, curIndex = 1; curIndex < str.length(); ++curIndex) {
        if (!found) {
            if (str[curIndex] == str[curIndex - 1]) {
                found = true;
                tempIndex = curIndex - 1;
                while ((curIndex + 1) < str.length()) {
                    if (str[curIndex + 1] != str[tempIndex]) {
                        break;
                    }
                    else {
                        ++curIndex;
                    }
                }
            }
            else if (curIndex > 1 && str[curIndex] == str[curIndex - 2]) {
                found = true;
                tempIndex = curIndex - 2;
            }
            else {
                continue;
            }
        }
        else {
            if (tempIndex > 0 && str[curIndex] == str[tempIndex - 1]) {
                --tempIndex;
            }
            else {
                found = false;
                // save the palindrome with max length found so far
                if (result.len < (curIndex - tempIndex)) {
                    result = { tempIndex, curIndex - tempIndex };
                }
            }
        }
    }

    if (found && result.len < (curIndex - tempIndex)) {
        result = { tempIndex, curIndex - tempIndex };
    }

    return result;
}

void TestCornerCases()
{
    PalindromeInString result = FindLargestPalindromeInString("");
    assert(result.pos == -1 && result.len == -1);

    result = FindLargestPalindromeInString("A");
    assert(result.pos == 0 && result.len == 1);

    result = FindLargestPalindromeInString("AA");
    assert(result.pos == 0 && result.len == 2);

    result = FindLargestPalindromeInString("AB");
    assert(result.pos == 0 && result.len == 1);
}

void TestCase1()
{
    PalindromeInString result = FindLargestPalindromeInString("123ABCDEFGGFEDCBA123");
    assert(result.pos == 3 && result.len == 14);

    result = FindLargestPalindromeInString("123ABCDEFGFEDCBA123");
    assert(result.pos == 3 && result.len == 13);
}

void TestCase2()
{
    PalindromeInString result = FindLargestPalindromeInString("123XYZZYXABCDEFGGFEDCBA123");
    assert(result.pos == 9 && result.len == 14);

    result = FindLargestPalindromeInString("123XYZYXABCDEFGFEDCBA123");
    assert(result.pos == 8 && result.len == 13);
}

void TestCase3()
{
    PalindromeInString result = FindLargestPalindromeInString("123AAAAAAAAAAAA123");
    assert(result.pos == 3 && result.len == 12);

    result = FindLargestPalindromeInString("123AAAAAAAAAAA123");
    assert(result.pos == 3 && result.len == 11);
}

void TestCase4()
{
    PalindromeInString result = FindLargestPalindromeInString("AAA");
    assert(result.pos == 0 && result.len == 3);

    result = FindLargestPalindromeInString("AAAAAAAAAA");
    assert(result.pos == 0 && result.len == 10);

    result = FindLargestPalindromeInString("AAAAAAAAAAA");
    assert(result.pos == 0 && result.len == 11);
}

void TestCase5()
{
    PalindromeInString result = FindLargestPalindromeInString("ABACCDCCAEFBFEACCD");
    assert(result.pos == 5 && result.len == 13);

    result = FindLargestPalindromeInString("abac");
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestCornerCases();
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    TestCase5();

    return 0;
}

