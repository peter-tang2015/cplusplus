// CodingPractice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <map>
#include <vector>

template<typename K, typename V>
V& FindFromMap(std::map<K, V>& input, const K& key, const V& val)
{
    auto lu = input.equal_range(key);
    if (lu.first == lu.second) {
        input.insert(lu.second, std::make_pair(key, val));
        --lu.second;
        return lu.second->second;
    }

    return lu.first->second;
}

class Base
{
public:
    Base() {
        std::cout << "Base()" << std::endl;
    }
};

class DerivedA : public Base
{
public:
    DerivedA() {
        std::cout << "DerivedA()" << std::endl;
    }
};

class DerivedB : public Base
{
public:
    DerivedB() {
        std::cout << "DerivedB()" << std::endl;
    }

};

class Derived : public DerivedA, public DerivedB
{
public:
    Derived() {
        std::cout << "Derived()" << std::endl;
    }

};

class Foo
{
public:
    Foo() {
        std::cout << "Foo" << std::endl;
    }

private:
    ~Foo() {
        std::cout << "~Foo()" << std::endl;
    }

};

class Bar
{
public:
    Bar()
        : Bar(-1)
    {}
    Bar(int x)
        : mX(x)
    {}

private:
    int mX = 0;
};

int _tmain(int argc, _TCHAR* argv[])
{
    // Derived d;
    // DerivedB db;

    // Foo* fPtr = new Foo();
    // std::vector<Foo> vecFoo;

    std::map<int, Bar> barMap;
    barMap[1] = Bar(1);
    Bar xBar = FindFromMap(barMap, 1, Bar());
    xBar = FindFromMap(barMap, 2, Bar(2));
    return 0;
}

