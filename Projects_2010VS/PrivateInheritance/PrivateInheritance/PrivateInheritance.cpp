// PrivateInheritance.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Base.h"
#include "Sub1.h"
#include "Sub2.h"

void HandleBase(Base& b) 
{

}

int _tmain(int argc, _TCHAR* argv[])
{
	Base b;
	Sub1 s1;
	Sub2 s2;

	HandleBase(b);
	HandleBase(s1);
	HandleBase(s2);

	return 0;
}

