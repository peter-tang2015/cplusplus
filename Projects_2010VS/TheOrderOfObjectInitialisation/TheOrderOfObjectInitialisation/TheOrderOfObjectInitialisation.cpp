// TheOrderOfObjectInitialisation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>


struct A{
    A() {std::cout << "A()" << std::endl;}
    ~A() {std::cout << "~A()" << std::endl;}
};

struct B{
    B() {std::cout << "B()" << std::endl;}
    ~B() {std::cout << "~B()" << std::endl;}
};

struct C{
    C() {std::cout << "C()" << std::endl;}
    ~C() {std::cout << "~C()" << std::endl;}
};

struct D{
    D() {std::cout << "D()" << std::endl;}
    ~D() {std::cout << "~D()" << std::endl;}
};

struct E{
    E() {std::cout << "E()" << std::endl;}
    ~E() {std::cout << "~E()" << std::endl;}
};

struct F{
    F():m_Count(s_Count) {
        std::cout << "F(" << m_Count << ")" << std::endl;
        ++s_Count;
    }

    F(const F& f) : m_Count(s_Count) {
        std::cout << "copy to F(" << m_Count << ")" << std::endl;
        ++s_Count;        
    }

    ~F() {std::cout << "~F(" << m_Count << ")" << std::endl;}

    static int s_Count;
    int m_Count;
};

int F::s_Count = 0;

struct Base{
    Base() {std::cout << "Base()" << std::endl;}
    ~Base() {std::cout << "~Base()" << std::endl;}

    A a;
    B b;
    C c;
};

struct Foo : public Base{
    Foo() {std::cout << "Foo()" << std::endl;}
    ~Foo() {std::cout << "~Foo()" << std::endl;}

    D d;
    E e;
};

struct G{
    G() : m_X(0) {
        std::cout << "G()" << std::endl;
    }
    G(int i) : m_X(i) {
        std::cout << "G(int)" << std::endl;
    }
    ~G() {
        std::cout << "~G()" << std::endl;
    }

    int m_X;
};

struct Bar{
    Bar(int i) : m_G(i) {
        std::cout << "Bar(int)" << std::endl;
    }
    ~Bar() {std::cout << "~Bar()" << std::endl;}

    G m_G;
};

int _tmain(int argc, _TCHAR* argv[])
{
    {
        //Base b;
        /*
        A()
        B()
        C()
        Base()
        ~Base()
        ~C()
        ~B()
        ~A()
        */
    }
    
    {
        //Foo foo;
        /*                
        A()
        B()
        C()
        Base()
        D()
        E()
        Foo()
        ~Foo()
        ~E()
        ~D()
        ~Base()
        ~C()
        ~B()
        ~A()
        */
    }
    
    {
        //F fArr[5];
        /*
        F(0)
        F(1)
        F(2)
        F(3)
        F(4)
        ~F(4)
        ~F(3)
        ~F(2)
        ~F(1)
        ~F(0)
        */
    }
  
    {
        //std::vector<F> fVec(5, F());
        /*
        F(0)
        copy to F(1)
        copy to F(2)
        copy to F(3)
        copy to F(4)
        ~F(0)
        ~F(1)
        ~F(2)
        ~F(3)
        ~F(4)
        */
        //std::vector<F> fVec(5);
        /*
        F(0)
        copy to F(1)
        F(2)
        copy to F(3)
        F(4)
        copy to F(5)
        F(6)
        copy to F(7)
        F(8)
        copy to F(9)
        ~F(1)
        ~F(3)
        ~F(5)
        ~F(7)
        ~F(9)
        */
    }
    {
        Bar b(1);
    }
    
    return 0;
}

