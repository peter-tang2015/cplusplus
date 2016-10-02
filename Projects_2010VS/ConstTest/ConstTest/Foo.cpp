#include "StdAfx.h"
#include "Foo.h"


Foo::Foo(void)
{
}


Foo::~Foo(void)
{
}

const int& Foo::GetX() const
{
	static int i;
	++i;
	return x;
}

int& Foo::GetX()
{
	return x;
}

