// CharCompare.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/**
* GCC on Linux: (c== 0x80) || (c == 0xC0)
* warning: comparison is always false due to limited range of data type
* Always be careful with signed/unsigned comparisons.
*/

int _tmain(int argc, _TCHAR* argv[])
{
    char nba[] = {
        0x4D, 0x5A, 0x80, 0xC0
    };

    int len = (sizeof nba) / sizeof(char);
    int ii;
    for (ii = 0; ii < len; ++ii) {
        char c = nba[ii];
        if (c == 0x80) {
            printf("%#x\n", c);
        }
        else if (c == (char)0xC0) {
            printf("%c\n", c);
        }
    }

    return 0;
}

