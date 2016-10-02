// Casting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

class Base{
public:
    virtual const char* GetName() const {
        return "Base";
    }
};

class Derived : Base {
public:
    virtual const char* GetName() const {
        return "Base";
    }
    virtual const char* GetID() const {
        return "ID: Derived";
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    Base b;

    /*
    Derived* dPtr = dynamic_cast<Derived*>(&b);
    if (dPtr) {
        dPtr->GetID();
    }
    */

    Derived* dPtr1 = static_cast<Derived*> (&b);
    dPtr1->GetName();
    dPtr1->GetID();

	return 0;
}

