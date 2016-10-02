// DiamondDeathProblem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>

class Base{
public:
    Base(int x) : m_x(x)
    {}
    virtual std::string GetName() const {
        return "Base";  
    }
    virtual std::string GetID() const {
        return "BASE";
    }
    void SetX(int x) {
        m_x = x;
    }

    int GetX() const {
        return m_x;
    }

public:
    int m_x;
};

class Foo : public Base {
public:
    Foo(int x, int y) : Base(x), m_y(y)
    {}

    virtual std::string GetName() const {
        return "Foo";
    }

    virtual std::string GetID() const {
        return "FOO";
    }

private:
    int m_y;
};

class Bar : public Base {
public:
    Bar(int x, int z) : Base(x), m_z(z)
    {}

    virtual std::string GetName() const {
        return "Bar";
    }

    virtual std::string GetID() const {
        return "BAR";
    }

private:
    int m_z;
};

class FooBar : public Foo, public Bar {
public:
    FooBar(int x, int y, int z, int a) 
        : Foo(x, y), Bar(x, z), m_a(a)
    {}

    virtual std::string GetName() const {
        return "FooBar";
    }
    
    virtual int GetA() const {
        return m_a;
    }
private:
    int m_a;
};

class FooBarDerived : public FooBar
{
public:
    FooBarDerived(int x, int y, int z, int a)
        : FooBar(x, y, z, a)
    {}

    virtual int GetA() const {
        return 1;
    }
};

class FooV : virtual public Base {
public:
    FooV(int x, int y) : Base(x), m_y(y)
    {}

    virtual std::string GetName() const {
        return "FooV";
    }

    virtual std::string GetID() const {
        return "FOOV";
    }

private:
    int m_y;
};

class BarV : virtual public Base {
public:
    BarV(int x, int z) : Base(x), m_z(z)
    {}

    virtual std::string GetName() const {
        return "BarV";
    }

    virtual std::string GetID() const {
        return "BARV";
    }

private:
    int m_z;
};

class FooBarV : public FooV, public BarV {
public:
    FooBarV(int x, int y, int z, int a) 
        : Base(x), FooV(x, y), BarV(x, z), m_a(a)
    {}

    virtual std::string GetName() const {
        return "FooBarV";
    }

    // has to present otherwise compilcaiton error
    virtual std::string GetID() const {
        return "FOOBARV";
    }

private:
    int m_a;
};

int _tmain(int argc, _TCHAR* argv[])
{
    std::cout << "sizeof(Base): " << sizeof(Base) << std::endl;
    std::cout << "sizeof(Foo): " << sizeof(Foo) << std::endl;
    std::cout << "sizeof(Bar): " << sizeof(Bar) << std::endl;
    std::cout << "sizeof(FooBar): " << sizeof(FooBar) << std::endl;
    std::cout << "sizeof(FooBarDerived): " << sizeof(FooBarDerived) << std::endl;

    Base b(0);
    FooBar fb(1, 2, 3, 4);
    fb.GetA();
    FooBarDerived fbd(1, 2, 3, 4);
    fbd.GetA();
    Foo& fooRef = fb;
    fooRef.SetX(20);
    Bar& barRef = fb;
    barRef.SetX(30);
    std::cout << "Foo::m_x = " << fooRef.GetX() << std::endl;
    std::cout << "Bar::m_x = " << barRef.GetX() << std::endl;
    //std::cout << "FooBar::m_x = " << fb.Foo::GetX() << std::endl;
    std::cout << fb.Base::GetX() << std::endl;
    std::cout << fb.Foo::GetX() << std::endl;
    std::cout << fb.Bar::GetX() << std::endl;
    std::cout << fb.Foo::Base::GetX() << std::endl;
    std::cout << fb.Bar::Base::GetX() << std::endl;
    //Base& bRef = fb;
    //bRef.SetX(10);
    //std::cout << "Base::m_x = " << bRef.GetX() << std::endl;
    //std::cout << "FooBar::m_x = " << fb.GetX() << std::endl;

    std::cout << "Foo::name: " << fooRef.GetName() << std::endl;
    std::cout << "Bar::name: " << barRef.GetName() << std::endl;
    std::cout << "FooBar::name: " << fb.GetName() << std::endl;

    std::cout << "Foo::ID: " << fooRef.GetID() << std::endl;
    std::cout << "Bar::ID: " << barRef.GetID() << std::endl;
//    std::cout << "FooBar::ID: " << fb.GetID() << std::endl;


    /*************************************************************************/
    std::cout << "sizeof(Base): " << sizeof(Base) << std::endl;
    std::cout << "sizeof(FooV): " << sizeof(FooV) << std::endl;
    std::cout << "sizeof(BarV): " << sizeof(BarV) << std::endl;
    std::cout << "sizeof(FooBarV): " << sizeof(FooBarV) << std::endl;
    
    FooBarV fbv(1, 2, 3, 4);
    Base& bvRef = fbv;
    FooV& fvRef = fbv;
    BarV& barvRef = fbv;
    std::cout << "Base::m_x = " << bvRef.GetX() << std::endl;
    std::cout << "FooV::m_x = " << fvRef.GetX() << std::endl;
    std::cout << "BarV::m_x = " << barvRef.GetX() << std::endl;
    std::cout << "FooBarV::m_x = " << fbv.GetX() << std::endl;
    bvRef.SetX(10);
    std::cout << "Base::m_x = " << bvRef.GetX() << std::endl;
    std::cout << "FooV::m_x = " << fvRef.GetX() << std::endl;
    std::cout << "BarV::m_x = " << barvRef.GetX() << std::endl;
    std::cout << "FooBarV::m_x = " << fbv.GetX() << std::endl;
    fvRef.SetX(20);
    std::cout << "Base::m_x = " << bvRef.GetX() << std::endl;
    std::cout << "FooV::m_x = " << fvRef.GetX() << std::endl;
    std::cout << "BarV::m_x = " << barvRef.GetX() << std::endl;
    std::cout << "FooBarV::m_x = " << fbv.GetX() << std::endl;
    barvRef.SetX(30);
    std::cout << "Base::m_x = " << bvRef.GetX() << std::endl;
    std::cout << "FooV::m_x = " << fvRef.GetX() << std::endl;
    std::cout << "BarV::m_x = " << barvRef.GetX() << std::endl;
    std::cout << "FooBarV::m_x = " << fbv.GetX() << std::endl;
    fbv.SetX(40);
    std::cout << "Base::m_x = " << bvRef.GetX() << std::endl;
    std::cout << "FooV::m_x = " << fvRef.GetX() << std::endl;
    std::cout << "BarV::m_x = " << barvRef.GetX() << std::endl;
    std::cout << "FooBarV::m_x = " << fbv.GetX() << std::endl;

    	return 0;
}

