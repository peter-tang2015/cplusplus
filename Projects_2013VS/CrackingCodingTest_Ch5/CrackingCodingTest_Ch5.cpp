// CrackingCodingTest_Ch5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <cstdlib>

bool ReplaceWith(int& input, size_t start, size_t end, int pattern)
{
    // 0000 1000 0000 0000, 2, 6, 10101, -> 0000 1000 0101 0100
    if (start > end || end > 31) {
        return false;
    }

    int x = input >> (end + 1);
    x = x << (end + 1);
    int y = input << (32 - start);
    y = y >> (32 - start);
    int z = x + y;

    int ptn = pattern << (32 - (end - start + 1));
    ptn = ptn >> (32 - (end - start + 1));
    input = z + ptn;

    return true;
}

bool RepresentableByBinary(const char* decimal)
{
    float num = atof(decimal);

    bool result = false;
    int numOfBinary = 0;
    while (numOfBinary < 32) {
        if (num == 0) {
            result = true;
            break;
        }
        num *= 2;
        ++numOfBinary;
    }

    return result;
}

void GetNextSmallerAndLargerNumWithSame1s(int input,
                                          int& smaller,
                                          int& larger)
{
    if (input == 0) {
        smaller = 0;
        larger = 0;
    }
    else if (input < 0) {
        GetNextSmallerAndLargerNumWithSame1s(-input, smaller, larger);
        int temp = larger;
        larger = -smaller;
        smaller = -temp;
    }
    else {
        int indexOfFirst0 = -1;
        int indexOfFirst1 = -1;
        int indexOfFirst1After0 = -1;
        int indexOfFirst0After1 = -1;
        if (input & 1) {
            indexOfFirst1 = 0;
            int index = 0;
            int temp = input;
            while (temp) {
                if (!(temp & 1)) {
                    indexOfFirst0After1 = index;
                    break;
                }
                temp = temp >> 1;
                ++index;
            }

            // set indexOfFirst1 as 0
            // set indexOfFirst0After1 as 1
            // to get next bigger

            indexOfFirst0 = indexOfFirst0After1;



        }
        else {
            indexOfFirst0 = 0;
            int index = 0;
            int temp = input;
            while (temp) {
                if (temp & 1) {
                    indexOfFirst1After0 = index;
                    break;
                }
                temp = temp >> 1;
                ++index;
            }
            // set bit indexOfFirst0 as 1
            // set bit indexOfFirst1After0 as 0
            // to get next samller

        }
        int index = 0;
        int temp = input;
        while (temp >>) {}
    }
    return;
}


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

