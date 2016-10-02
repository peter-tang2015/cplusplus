// VectorVsArray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>

/*
#ifndef _DEBUG
#define _SECURE_SCL 0
#define _ITERATOR_DEBUG_LEVEL 0
#endif
*/

int _tmain(int argc, _TCHAR* argv[])
{
	int x = 0, y = 1, z = 2;
	std::vector<int> myVec(3, 1);
	int myArr[3];
	myArr[0] = x;
	myArr[1] = y;
	myArr[2] = 2;

	if (myVec[2]) {
		goto RETURN_FUNC;
	}

	if (myArr[2]) {
		goto RETURN_FUNC;
	}

RETURN_FUNC:
	return 0;
}

