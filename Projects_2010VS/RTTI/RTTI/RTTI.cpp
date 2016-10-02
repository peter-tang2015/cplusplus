// RTTI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <typeinfo>

class Foo {
};

class Bar {
};

class Base {
};

class Derived : public Base {
};

class Base1 {
public:
    virtual std::string GetName() {
        return "Base1";
    }
};

class Derived1 : public Base1 {
public:
    virtual std::string GetName() {
        return "Derived1";
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    /*
    Foo foo;
    const Foo fooConst;
    volatile Foo fooVolatile;
    const Foo& fooRef = fooConst;
    Foo* fooPtr = &foo;
    Bar bar;
    std::cout << (typeid(foo) == typeid(fooConst)) << std::endl;
    std::cout << (typeid(foo) == typeid(fooVolatile)) << std::endl;
    std::cout << (typeid(foo) == typeid(fooRef)) << std::endl;
    std::cout << (typeid(foo) == typeid(fooPtr)) << std::endl;
    std::cout << (typeid(foo) == typeid(*fooPtr)) << std::endl;
    std::cout << (typeid(fooPtr) == typeid(fooRef)) << std::endl;
    std::cout << (typeid(*fooPtr) == typeid(fooRef)) << std::endl;
    std::cout << (typeid(foo) == typeid(bar)) << std::endl;
    */

    /*
    Base b;
    Derived d;
    Base& bRef = d;
    Base* bPtr = &d;
    std::cout << (typeid(b) == typeid(d)) << std::endl;
    std::cout << (typeid(bRef) == typeid(d)) << std::endl;
    std::cout << (typeid(bPtr) == typeid(d)) << std::endl;
    std::cout << (typeid(*bPtr) == typeid(d)) << std::endl;
    std::cout << (typeid(bRef) == typeid(bPtr)) << std::endl;
    std::cout << (typeid(bRef) == typeid(*bPtr)) << std::endl;
    */

    Base1 b1;
    Derived1 d1;
    Base1& b1Ref = d1;
    Base1* b1Ptr = &d1;
    std::cout << (typeid(b1) == typeid(d1)) << std::endl;  
    std::cout << (typeid(b1Ref) == typeid(d1)) << std::endl;
    std::cout << (typeid(b1Ptr) == typeid(d1)) << std::endl;
    std::cout << (typeid(*b1Ptr) == typeid(d1)) << std::endl;
    std::cout << (typeid(b1Ref) == typeid(b1Ptr)) << std::endl;
    std::cout << (typeid(b1Ref) == typeid(*b1Ptr)) << std::endl;
    

    const int& cRef = 2;
    //int& vRef = cRef;

    return 0;
}

