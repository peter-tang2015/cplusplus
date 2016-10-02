// OrderArrayIntoNegativePositiveSeries.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>

#include <cassert>

template<typename type>
void OrderArrayIntoNegativePositiveSeries(std::vector<type>& arr)
{
    if (arr.empty()){ 
        return;
    }

    const size_t SizeOfArr = arr.size();
    if (SizeOfArr < 3) {
        return;
    }

    // if first value is negative, then find a positive value next
    bool positiveValToFind = arr[0] < 0;
    type nextValue;
    for (size_t outOfOrderPos = 1, curIndex = 1; curIndex < SizeOfArr; ++curIndex) {
        if ((arr[curIndex] > 0 && positiveValToFind) ||
            (arr[curIndex] < 0 && !positiveValToFind)) {
            if (outOfOrderPos == curIndex) {
                positiveValToFind = !positiveValToFind;
                ++outOfOrderPos;
            }
            else {
                nextValue = arr[curIndex];
                memcpy(&arr[outOfOrderPos + 1], &arr[outOfOrderPos], (curIndex - outOfOrderPos) * sizeof(type));
                arr[outOfOrderPos] = nextValue;
                outOfOrderPos += 2;
            }
        }
    }
}

void TestCornerCases()
{
    std::vector<int> testArr;

    OrderArrayIntoNegativePositiveSeries(testArr);

    assert(testArr.empty());

    testArr = { 1 };
    OrderArrayIntoNegativePositiveSeries(testArr);
    assert(testArr.size() == 1);
    assert(testArr[0] = 1);

    testArr = { 1, -1 };
    OrderArrayIntoNegativePositiveSeries(testArr);
    assert(testArr.size() == 2);
    assert(testArr[0] == 1);
    assert(testArr[1] == -1);
}

void TestCase1()
{
    std::vector<int> testArr = { 2, -1, -3, -7, -8, 9, 5, -5, -7 };
    const std::vector<int> result = { 2, -1, 9, -3, 5, -7, -8, -5, -7 };

    OrderArrayIntoNegativePositiveSeries(testArr);

    assert(testArr == result);
}

void TestCase2()
{
    std::vector<int> testArr = { 2, 9, 5, 3, 2, 1, -1, -3, -7, -8, -5, -7 };
    const std::vector<int> result = { 2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7 };

    OrderArrayIntoNegativePositiveSeries(testArr);

    assert(testArr == result);
}

void TestCase3()
{
    std::vector<int> testArr = { 2, -1, -3, - 7, -8, -5, -7, 9, 5, 3, 2, 1 };
    const std::vector<int> result = { 2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7 };

    OrderArrayIntoNegativePositiveSeries(testArr);

    assert(testArr == result);
}

void TestCase4()
{
    std::vector<int> testArr = { 2, -1, -3, - 7, 9, 5, 3, 2, 1, -8, -5, -7 };
    const std::vector<int> result = { 2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7 };

    OrderArrayIntoNegativePositiveSeries(testArr);

    assert(testArr == result);
}

void TestCase5()
{
    std::vector<int> testArr = { -1, -3, - 7, 2, 9, 5, 3, 2, 1, -8, -5, -7 };
    const std::vector<int> result = { -1, 2, -3, 9, -7, 5, -8, 3, -5, 2, -7, 1};

    OrderArrayIntoNegativePositiveSeries(testArr);

    assert(testArr == result);
}

void TestCase6()
{
    std::vector<int> testArr = { -1, -3, - 7, -8, -5, -7, 2, 9, 5, 3, 2, 1 };
    const std::vector<int> result = { -1, 2, -3, 9, -7, 5, -8, 3, -5, 2, -7, 1 };

    OrderArrayIntoNegativePositiveSeries(testArr);

    assert(testArr == result);
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestCornerCases();
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    TestCase5();
    TestCase6();

    return 0;
}

/*
    * : out of order place index
    ^ : the current index of this array
    positiveValToFind = false
        *
    2, -1, -3, -7, -8, 9, 5, -5, -7
        ^
    positiveValToFind = true
            *
    2, -1, -3, -7, -8, 9, 5, -5, -7
            ^
            *
    2, -1, -3, -7, -8, 9, 5, -5, -7
                       ^
    Increment * by 2 and ^ by 1
                   *
    2, -1, 9, -3, -7, -8, 5, -5, -7
                          ^
    Increment * by 2 and ^ by 1
                          *
    2, -1, 9, -3, 5, -7, -8, -5, -7
                              ^
                          *
    2, -1, 9, -3, 5, -7, -8, -5, -7
                                    ^
*/

/*
11110
11101

11100
11011

11000
10111

10000
01111

0
/////////////////
1111
1110

1110
1101

1100
1011

1000
0111

0
/////////////////

4, 1, K, J, 2, 10, 6, 7, 3, 5, Q, 9, 8

K, J, 2, 10, 6, 7, 3, 5, Q, 9, 8, 4 -> 1
10, 6, 7, 3, 5, Q, 9, 8, 4, K, J -> 2
5, Q, 9, 8, 4, K, J, 10, 6, 7 -> 3
K, J, 10, 6, 7, 5, Q, 9, 8 -> 4 
Q, 9, 8, K, J, 10, 6, 7 -> 5
7, Q, 9, 8, K, J, 10 -> 6
Q, 9, 8, K, J, 10 -> 7
K, J, 10, Q, 9 -> 8
K, J, 10, Q -> 9
Q, K, J -> 10
Q, K -> J
K -> Q
-> K
*/
