// MaxSumOfElemTimesIdxViaRotation_Yahoo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>

size_t MaxSumOfElementsTimeIndicesViaRotation(const std::vector<size_t> input)
{
    size_t fPrev = 0;
    size_t sum = 0;
    size_t index = 1;
    for (auto x : input) {
        fPrev += x*index;
        sum += x;
        ++index;
    }

    size_t maxVal = fPrev;
    const size_t SizeOfInput = input.size();
    size_t fCur;
    for (index = 1; index < SizeOfInput; ++index) {
        fCur = fPrev + input[index - 1] * SizeOfInput - sum;
        if (fCur > maxVal) {
            maxVal = fCur;
        }
        fPrev = fCur;
    }

    return maxVal;
}

#include <cassert>
void TestCases()
{
    {
        std::vector<size_t> input = { 1, 2, 3, 4, 5, 6, 7 };
        assert(MaxSumOfElementsTimeIndicesViaRotation(input) ==
            (1 * 1 + 2 * 2 + 3 * 3 + 4 * 4 + 5 * 5 + 6 * 6 + 7 * 7));
    }

    {
        std::vector<size_t> input = { 2, 3, 4, 5, 6, 7, 1 };
        assert(MaxSumOfElementsTimeIndicesViaRotation(input) ==
            (1 * 1 + 2 * 2 + 3 * 3 + 4 * 4 + 5 * 5 + 6 * 6 + 7 * 7));
    }

    {
        std::vector<size_t> input = { 3, 4, 5, 6, 7, 1, 2 };
        assert(MaxSumOfElementsTimeIndicesViaRotation(input) ==
            (1 * 1 + 2 * 2 + 3 * 3 + 4 * 4 + 5 * 5 + 6 * 6 + 7 * 7));
    }

    {
        std::vector<size_t> input = { 4, 5, 6, 7, 1, 2, 3 };
        assert(MaxSumOfElementsTimeIndicesViaRotation(input) ==
            (1 * 1 + 2 * 2 + 3 * 3 + 4 * 4 + 5 * 5 + 6 * 6 + 7 * 7));
    }

    {
        std::vector<size_t> input = { 5, 6, 7, 1, 2, 3, 4 };
        assert(MaxSumOfElementsTimeIndicesViaRotation(input) ==
            (1 * 1 + 2 * 2 + 3 * 3 + 4 * 4 + 5 * 5 + 6 * 6 + 7 * 7));
    }

    {
        std::vector<size_t> input = { 6, 7, 1, 2, 3, 4, 5 };
        assert(MaxSumOfElementsTimeIndicesViaRotation(input) ==
            (1 * 1 + 2 * 2 + 3 * 3 + 4 * 4 + 5 * 5 + 6 * 6 + 7 * 7));
    }

    {
        std::vector<size_t> input = { 7, 1, 2, 3, 4, 5, 6, };
        assert(MaxSumOfElementsTimeIndicesViaRotation(input) ==
            (1 * 1 + 2 * 2 + 3 * 3 + 4 * 4 + 5 * 5 + 6 * 6 + 7 * 7));
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    void TestCases();
    return 0;
}
/*
S = {S1, S2, S3, ..., Sn}
SUM = S1 + S2 + ... + Sn
F(1) = 1*S1 + 2*S2 + ... + n*Sn
// shift left 
F(2) = n*S1 + 1*S2 + ... + (n-1)*Sn

F(2) - F(1) = (n-1)*S1 - S2 - ... - Sn
            = (n-1)*S1 - (S2 + S3 + ... + Sn)
            = n*S1 - (S1 + S2 + ... + Sn)
            = n*S1 - SUM
F(3) = (n-1)*S1 + n*S2 + 1*S3 + ... + (n-2)*Sn
F(3) - F(2) = (n-1)*S2 - (S1 + S3 + ... + Sn)
            = n*S2 - (S1 + S2 + S3 + ... + Sn)
            = nS2 - SUM

According to the induction theory,
F(n) - F(n-1) = n*Sm-1 - SUM

Ans this slution has coompuation complexity of O(N) and space complexity of O(1).
/*
After downloading and installing the program, you can launch Visual Studio 2013 and switch to use the new compiler in your C++ projects. We recommend that you create a separate project configuration and modify it for projects that utilize the CTP compiler. To do so: 1. Open the "Build" menu and then select the "Configuration Manager" option. 2. In the Configuration Manager, duplicate your existing configuration. 3. Open the project's Property Pages by pressing F7 or right clicking the project in Solution Explorer and selecting "Properties". 4. In the "General" tab, change "Platform Toolset" from "Visual Studio 2013 (v120)" to "Visual C++ Compiler Nov 2013 CTP (CTP_Nov2013)". 5. Rebuild your project.
*/
