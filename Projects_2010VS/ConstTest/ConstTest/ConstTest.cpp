// ConstTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Foo.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Foo foo;
	const Foo constfoo;

	foo.GetX() = 5;
	const int& x = foo.GetX();
	constfoo.GetX();

	return 0;
}

