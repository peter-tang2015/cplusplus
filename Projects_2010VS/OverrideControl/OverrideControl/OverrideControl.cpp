// OverrideControl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>

struct Base {
    virtual void Foo(int) {
        std::cout << "Base::Foo(int)" << std::endl;
    }

    virtual void Bar(float) {
        std::cout << "Base::Bar(float)" << std::endl;
    }

    virtual std::string GetName() const {
        std::cout << "Base" << std::endl;
        return "Base";
    }

    virtual void Hat() {
        std::cout << "Base::Hat()" << std::endl;
    }


};

struct Derived : public Base {
    virtual void Foo(int) {
        std::cout << "Derived::Foo(int)" << std::endl;
    }

    virtual void Bar(int) {
        std::cout << "Derived::Bar(int)" << std::endl;
    }


    virtual std::string GetName() {
        std::cout << "Derived" << std::endl;
        return "Derived";
    }

    /*
    virtual int Hat() {
        std::cout << "Derived::Hat()" << std::endl;
        return 1;
    } 
    */
};

class DerivedCplusplus11 : public Base {

};


int _tmain(int argc, _TCHAR* argv[])
{
    Derived d;
    d.Foo(10);
    d.Bar(1);
    d.GetName();

    Base bRef = d;
    bRef.Foo(10);
    bRef.Bar(1);
    bRef.GetName();

	return 0;
}

