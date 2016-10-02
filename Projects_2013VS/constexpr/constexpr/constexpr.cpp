// constexpr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

constexpr int PreIncrement1(int x) {
	return ++x;
}

constexpr int PostIncrement1(int x) {
	return x++;
}

constexpr int Increment2(int x) {
	return x + 2;
}

int _tmain(int argc, _TCHAR* argv[])
{
	constexpr x = PreIncrement1(1);
	return 0;
}

