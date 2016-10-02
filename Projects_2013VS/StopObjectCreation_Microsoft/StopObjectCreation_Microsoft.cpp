// StopObjectCreation_Microsoft.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

class Abc
{
public:
    Abc(int x)
    {}
};

class Xyz
{
    Xyz() {}
};

class Interface
{
    virtual int GetVersion() = 0;
};

//template <typename T>
class Foo //: public Interface //: public Abc //: public Xyz
{
    //int &m_Val;
    //Abc m_Abc;
    //Xyz m_Xyz;
    Foo() {
        std::cout << "Foo()" << std::endl;
    }
    ~Foo() {
        std::cout << "~Foo()" << std::endl;
    }
public:
    static void Bar() {
        Foo f;
        Foo *fPtr = new Foo();
        delete fPtr;
    }

    // virtual void PrintSelf() = 0;
};


int _tmain(int argc, _TCHAR* argv[])
{
    Foo::Bar();
    return 0;
}

