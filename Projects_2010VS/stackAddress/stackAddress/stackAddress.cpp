// stackAddress.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


int _tmain(int argc, _TCHAR* argv[])
{
    int i = 0;
    int* iPtr = new int(1);
    int* iPtr1 = new int(2);

    std::cout << &i << std::endl;
    std::cout << &iPtr << std::endl;
    std::cout << iPtr << std::endl;
    std::cout << iPtr1 << std::endl;
	return 0;
}

