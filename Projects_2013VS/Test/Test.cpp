// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <exception>

int Solution(int A, int B)
{
    if (A < 0 || B < 0) {
        throw std::exception("Invalid parameter");
    }

    if (A == 0 || B == 0) {
        return 0;
    }

    unsigned long long copyA = A;
    unsigned long long copyB = B;
    unsigned long long multi = copyA * copyB;
    int result = 0;
    while (multi) {
        result += (multi & 1);
        multi = multi >> 1;
    }

    return result;
}

#include <vector>
#include <unordered_set>

using namespace std;
int solution(vector<int> &A) {
    // write your code in C++11 (g++ 4.8.2)
    if (A.empty()) {
        return 0; // indicates failure;
    }

    using VisitedMap = std::unordered_set<int>;
    VisitedMap vm;
    const int upper = A.size() - 1;
    int result = 0;
    int idx = A[0];
    while (true) {
        if (idx > upper || idx < -1) {
            return 0; // indicates failure
        }
        ++result;
        if (idx == -1) {
            break;
        }
        if (vm.find(idx) != vm.end()) {
            return 0; // detected loop
        }
        vm.insert(idx);
        idx = A[idx];
    }

    return result;
}

struct Point3D {
    int x;
    int y;
    int z;
};

int solution(vector<Point3D> &A) {
    // write your code in C++11 (g++ 4.8.2)
    if (A.empty()) {
        return 0;// indicates failure
    }
    using RadisSet = std::unordered_set<unsigned long long>;
    RadisSet result;
    int resultCount = 0;
    auto itEnd = A.end();
    for (auto it = A.begin(); it != itEnd; ++it) {
        unsigned long long copyX = it->x;
        unsigned long long copyY = it->y;
        unsigned long long copyZ = it->z;
        unsigned long long val = copyX*copyX + copyY*copyY + copyZ*copyZ;
        if (result.find(val) == result.end()) {
            result.insert(val);
            ++resultCount;
        }
    }

    return resultCount;
}

int _tmain(int argc, _TCHAR* argv[])
{
    Solution(100000000, 100000000);
    vector<int> input = { 0, 1, 2, 3, 4, 10 };
    solution(input);
    input = { 1, 0 };
    solution(input);
	return 0;
}

