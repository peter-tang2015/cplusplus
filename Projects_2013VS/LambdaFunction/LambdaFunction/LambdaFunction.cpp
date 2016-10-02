// LambdaFunction.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <map>

int _tmain(int argc, _TCHAR* argv[])
{
    std::vector<int> myVec = { 1, 2, 3 };
    std::map<int, int> myMap = { { 1, 2 }, { 3, 4 }, { 5, 6 } };

    for (auto& m : myMap) {
        m.second *= 2;
    }

    int i = 0;
    std::ref(i) = 1;
    std::cref(i) = 2;

    return 0;
}

