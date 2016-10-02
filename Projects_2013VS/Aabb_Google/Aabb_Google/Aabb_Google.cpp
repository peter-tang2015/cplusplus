// Aabb_Google.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>

#include <cassert>

struct AabbResult {
    AabbResult(int s, int e)
        : start(s), end(e)
    {}

    int start;
    int end;
};

/*
abbbaaabbbbbbaaa
aaaabbbbbbbbbaaa
aaaabbbbbbaaabbb

abbaaabbbbbbaaa
aaaabbbbbbbbaaa
aaaabbbbbbaaabb

abbaaababbbbaaa
aaaabbbabbbbaaa
aaaabbbbabaaabb

a...ab...b

a...absssssbaaaabxxxxxxbaaaabzzzzz

reverse(xxxxxxxx) = yyyyyyyyy
reverse(ssssss) = tttttt
a...aaaaabtttttbbxxxxxxbaaaabzzzzz
a...aaaaabyyyyyybaaaabsssssbbzzzzz
 
aaabbaabbbbaabbbaabbbaabbbbbbbbaabbbbb

aaabbaabbbabbaabbbaabbbbabbaabbbbbabbbaabbbb

a babaaa babaaa babaaa babaaa babaaa

1. Find first 'a' in the reverse direction,
   Save the index of first 'a' in the reverse direction, "rFirstA", 
        the number of 'a', "maxNumOfContinuousA"
        the index of second 'a' in the reverse direction , "rNextA"
        the lenght until the next 'a' starts, "lengthOfSubStr = rFirstA - rNextA"
2. starts from rNext to fristB
   count the number of continuous 'a', "numOfContinuousA"
   Compare if numOfContinuousA >/=/< maxNumOfContinuousA
        if >, rFirstA = the start index of this continuous 'a'
           <, do nothing
           =, found the same length continous 'a', foundSanmeLengthContinousA = true

 */
// http://www.careercup.com/page?pid=google-interview-questions
AabbResult AabbSolution(const std::string& str)
{
    if (str.empty()) {
        return AabbResult{ -1, -1 };
    }

    size_t firstB = str.find_first_of('b');
    if (firstB == std::string::npos) {
        // all are 'a', so need to reverse
        return AabbResult{ 0, 0 };
    }

    bool foundA = false;
    size_t rFirstA = 0;
    size_t rNextA = 0;
    size_t MaxNumOfContinousA = 0;
    for (size_t index = str.length() - 1; index > firstB; --index)
    {
        if (!foundA && rFirstA == 0 && str[index] == 'a') {
            foundA = true;
            rFirstA = index;
            continue;
        }

        if (foundA && str[index] != 'a') {
            // find the first continuous 'a' in the reverse order 
            // and record its length
            foundA = false;
            MaxNumOfContinousA = rFirstA - index;
        }

        if (!foundA && rFirstA > 0 && str[index] == 'a') {
            // find the start of the 2nd continuous 'a' in the
            // reverse order
            rNextA = index;
            break;
        }
    }

    if (rFirstA == 0) {
        // not found any 'a' after first 'b'
        // eg: aaabbbb
        return AabbResult{ 0, 0 };
    }

    if (rNextA == 0) {
        // only one continuous 'a' between firstB and rFirstA
        // aaabbbaaaabb
        return AabbResult( static_cast<int>(firstB),
                           static_cast<int>(rFirstA) );
    }

    // There are multiplie multipile continuous 'a' after firstB
    // eg: aaabbbaaabbaaabbaabb
    size_t strLenBetweenLongestA = 0;
    size_t rLongestAIndex = rFirstA;
    size_t numOfContinuousA = 0;
    bool   sameMaxLengthContinousAFound = false;
    size_t numToContinueComparing = rFirstA - rNextA;
    foundA = false;
    size_t tempIndex = 0;
    for (size_t index = rNextA + 1; index > firstB; --index, ++tempIndex) {
        if (sameMaxLengthContinousAFound) {
            if (numToContinueComparing > 0) {
                if (str[index - 1] > str[rLongestAIndex - MaxNumOfContinousA - tempIndex]) {
                    sameMaxLengthContinousAFound = false;
                }
                else if (str[index - 1] < str[rLongestAIndex - MaxNumOfContinousA - tempIndex]) {
                    // Update the record
                    // take the one close to the start
                    rLongestAIndex = rFirstA;
                }

                --numToContinueComparing;
            }
            else {
                // take the one close to the end
                sameMaxLengthContinousAFound = false;
            }
        }

        if (!foundA && str[index - 1] == 'a') {
            strLenBetweenLongestA = rLongestAIndex - (index - 1);
            rNextA = index - 1;
            numOfContinuousA = 1;
            foundA = true;
            continue;
        }

        if (foundA) {
            if (str[index - 1] == 'a') {
                ++numOfContinuousA;
                if (numOfContinuousA > MaxNumOfContinousA) {
                    sameMaxLengthContinousAFound = false;
                }
            }
            else {
                if (numOfContinuousA > MaxNumOfContinousA) {
                    rLongestAIndex = rNextA;
                    MaxNumOfContinousA = numOfContinuousA;
                    sameMaxLengthContinousAFound = false;
                }
                else if (numOfContinuousA == MaxNumOfContinousA) {
                    sameMaxLengthContinousAFound = true;
                    numToContinueComparing = strLenBetweenLongestA - MaxNumOfContinousA;
                    tempIndex = 0;
                    rFirstA = rNextA;
                }

                foundA = false;
            }
        }

    }

    if (sameMaxLengthContinousAFound) {
        assert(numToContinueComparing > 0);
        // not finished yet. conitnue to the reversed part
        for (size_t index = 0; index < numToContinueComparing; ++index, ++tempIndex) {
            if (str[rFirstA + index + 1] > str[rLongestAIndex - MaxNumOfContinousA - tempIndex]) {
                return AabbResult{ static_cast<int>(firstB),
                                   static_cast<int>(rLongestAIndex) };
            }
            else if (str[rFirstA + index + 1] < str[rLongestAIndex - MaxNumOfContinousA - tempIndex]) {
                return AabbResult{ static_cast<int>(firstB),
                                   static_cast<int>(rFirstA) };
            }
        }
    }

    return AabbResult{ static_cast<int>(firstB),
                       static_cast<int>(rLongestAIndex) };
}

void TestCaseFromCareerup()
{
    AabbResult result = AabbSolution("");
    assert(result.start == -1 && result.end == -1);
        
    result = AabbSolution("abab");
    assert(result.start == 1 && result.end == 2);

    result = AabbSolution("abba");
    assert(result.start == 1 && result.end == 3);
    
    result = AabbSolution("bbaa");
    assert(result.start == 0 && result.end == 3);
    
    result = AabbSolution("aaaa");
    assert(result.start == 0 && result.end == 0);
    
    result = AabbSolution("bbbbbbbbbbbbbbbb");
    assert(result.start == 0 && result.end == 0);

    result = AabbSolution("aaaaaaaaaaaaaa");
    assert(result.start == 0 && result.end == 0);
}

void TestCasesSingleHighestContinousA()
{
    AabbResult result = AabbSolution("babaabba");
    assert(result.start == 0 && result.end == 4);

    result = AabbSolution("babaabbaaaaabbbbaaaaaaabbbaabbaabababab");
    assert(result.start == 0 && result.end == 22);

    result = AabbSolution("aababaabbaaaaabbbbaaaaaaabbbaabbaabababab");
    assert(result.start == 2 && result.end == 24);
}

void TestCasesMultipleHighestContinuousAs()
{
    AabbResult result = AabbSolution("abbaaabbbbbbaaa"); // abbbaaabbbbbbaaa
    assert(result.start == 1 && result.end == 14);
    result = AabbSolution("abbbaaabbbbbbaaa");
    assert(result.start == 1 && result.end == 15);
    result = AabbSolution("abbaaababbbbaaa");
    assert(result.start == 1 && result.end == 5);
    result = AabbSolution("baabaabbaa");
    assert(result.start == 0 && result.end == 5);

    // a babaaa babaaa babaaa babaaa babaaa
    result = AabbSolution("ababaaababaaa");
    assert(result.start == 1 && result.end == 12);
    result = AabbSolution("ababaaababaaababaaa");
    assert(result.start == 1 && result.end == 18);
    result = AabbSolution("ababaaababaaababaaababaaa");
    assert(result.start == 1 && result.end == 24);
    result = AabbSolution("ababaaababaaababaaababaaababaaa");
    assert(result.start == 1 && result.end == 30);
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestCaseFromCareerup();
    TestCasesSingleHighestContinousA();
    TestCasesMultipleHighestContinuousAs();

    return 0;
}

