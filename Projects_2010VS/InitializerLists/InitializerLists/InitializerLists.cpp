// InitializerLists.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>

struct Foo {
    double x;
    double y;
};

struct Bar {
    int a;
    int b;
    Foo f;
};

class Test {
public:
    Test(int x, int y) : m_x(x), m_y(y) {}
    int m_x;
    int m_y;
};

int _tmain(int argc, _TCHAR* argv[])
{
    Foo f = {1.0, 2.0};
    Foo fDefault = {};
    Bar b = {1, 1, {10.0, 20.0}};
    Bar bDefault = {};

    int i = {0};
    //std::vector<int> myVec= {1, 2, 3};
	return 0;
}

