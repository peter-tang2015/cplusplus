// FuntionTryBlock.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <exception>
#include <iostream>
#include <string>

class MyException : public std::exception {
public:
    MyException(const std::string& msg) : m_Msg(msg)
    {}

    virtual ~MyException() {}

    virtual const char* what() const throw() {
        return m_Msg.c_str();
    }

    void AppendMessage(const std::string& msg) {
        m_Msg.append(msg);
    }

protected:
    std::string m_Msg{ "" };
};

class CreationException : public MyException {
public:
    CreationException(const std::string& msg)
        : MyException("CreationException: ")
    {
        m_Msg.append(msg);
    }
};

class DestructionException : public MyException {
public:
    DestructionException(const std::string& msg)
        : MyException("DestructionException: ")
    {
        m_Msg.append(msg);
    }
};

class MyNonEmptyString {
public:
    MyNonEmptyString(const std::string& str)
        : m_Str(str) {
        if (m_Str.empty()) {
            throw CreationException("MyNonEmptyString");
        }
    }

    ~MyNonEmptyString() {
        std::cout << "~MyNonEmptyString()" << std::endl;
    }

private:
    std::string m_Str;
};

class MyString {
public:
    MyString(const std::string& str)
        : m_Str(str) {
    }

    ~MyString() {
        std::cout << "~MyString()" << std::endl;
    }

private:
    std::string m_Str;
};

class Base {
public:
    Base(const std::string& name, const int* val)
        try : m_Name(name), m_ValPtr(val) {
        if (m_ValPtr == nullptr) {
            throw CreationException("Base");
        }
    }
    catch (CreationException& ce){
        std::cout << ce.what() << std::endl;
    }

    virtual ~Base() {
        std::cout << "~Base()" << std::endl;
    }
private:
    MyNonEmptyString m_Name;
    const int* m_ValPtr;
};

class Derived : public Base {
public:
    Derived(const std::string& name, const int* valPtr, const double* data)
        try : Base(name, valPtr), m_Data(data) {
        if (m_Data == nullptr) {
            throw CreationException("Derived");
        }
    }
    catch (CreationException& ce) {
        std::cout << ce.what() << std::endl;
    }

    ~Derived() {
        std::cout << "~Derived()" << std::endl;
    }

private:
    MyString m_Version{ "1.0" };
    const double* m_Data;
};

class BaseEx {
public:
    BaseEx(const std::string& name, const int* val)
        : m_Name(name), m_ValPtr(val) {
        if (m_ValPtr == nullptr) {
            throw CreationException("BaseEx");
        }
    }

    BaseEx(const int* val)
        try : BaseEx("BaseEx", val) {

        }
    catch (CreationException& ce) {
        ce.AppendMessage("-Invalid pointer");
        std::cout << ce.what() << std::endl;
    }

    virtual ~BaseEx() {
        std::cout << "~BaseEx()" << std::endl;
    }
private:
    MyNonEmptyString m_Name;
    const int* m_ValPtr;
};

class DerivedEx : public BaseEx {
public:
    DerivedEx(const std::string& name, const int* valPtr, const double* data)
        : BaseEx(name, valPtr), m_Data(data) {
        if (m_Data == nullptr) {
            throw CreationException("DerivedEx");
        }
    }

    ~DerivedEx() {
        std::cout << "~Derived()Ex" << std::endl;
    }

private:
    MyString m_Version{ "1.0" };
    const double* m_Data;
};

#if 0
int _tmain(int argc, _TCHAR* argv[])
{
    //try {
    //    Base b1(std::string(""), nullptr);
    //}
    //catch (CreationException& ce) {
    //    std::cout << "Exception caught in creating Base b1: "
    //        << ce.what()
    //        << std::endl
    //        << std::endl;
    //}
    //catch (...) {
    //    std::cout << "Exception caught in creating Base b1: " << "unknown" << std::endl;
    //}
    
    try {
        BaseEx bex1(nullptr);
    }
    catch (CreationException& ce) {
        std::cout << "Exception caught in creating BaseEx bex1: "
            << ce.what()
            << std::endl
            << std::endl;
    }
    catch (...) {
        std::cout << "Exception caught in creating BaseEx bex1: " << "unknown" << std::endl;
    }
    
    //try {
    //    Base b2(std::string("Base"), nullptr);
    //}
    //catch (CreationException& ce) {
    //    std::cout << "Exception caught in creating Base b2: "
    //        << ce.what()
    //        << std::endl
    //        << std::endl;
    //}
    //catch (...) {
    //    std::cout << "Exception caught in creating Base b2: " << "unknown" << std::endl;
    //}

    //try {
    //    Derived d1(std::string(""), nullptr, nullptr);
    //}
    //catch (CreationException& ce) {
    //    std::cout << "Exception caught in creating Derived d1: "
    //        << ce.what()
    //        << std::endl
    //        << std::endl;
    //}
    //catch (...) {
    //    std::cout << "Exception caught in creating Derived d1: " << "unknown" << std::endl;
    //}

    try {
        DerivedEx dex1(std::string(""), nullptr, nullptr);
    }
    catch (CreationException& ce) {
        std::cout << "Exception caught in creating DerivedEx dex1: "
            << ce.what()
            << std::endl
            << std::endl;
    }
    catch (...) {
        std::cout << "Exception caught in creating DerivedEx dex1: " << "unknown" << std::endl;
    }

    //try {
    //    Derived d2(std::string("Derived"), nullptr, nullptr);
    //}
    //catch (CreationException& ce) {
    //    std::cout << "Exception caught in creating Derived d2: "
    //        << ce.what()
    //        << std::endl
    //        << std::endl;
    //}
    //catch (...) {
    //    std::cout << "Exception caught in creating Derived d2: " << "unknown" << std::endl;
    //}

    try {
        DerivedEx dex2(std::string("DerivedEx"), nullptr, nullptr);
    }
    catch (CreationException& ce) {
        std::cout << "Exception caught in creating DerivedEx dex2: "
            << ce.what()
            << std::endl
            << std::endl;
    }
    catch (...) {
        std::cout << "Exception caught in creating DerivedEx dex2: " << "unknown" << std::endl;
    }

    //try {
    //    int intBuf[2];
    //    Derived d3(std::string("Derived"), intBuf, nullptr);
    //}
    //catch (CreationException& ce) {
    //    std::cout << "Exception caught in creating Derived d3: "
    //        << ce.what()
    //        << std::endl
    //        << std::endl;
    //}
    //catch (...) {
    //    std::cout << "Exception caught in creating Derived d3: " << "unknown" << std::endl;
    //}

    try {
        int intBuf[2];
        DerivedEx dex3(std::string("DerivedEx"), intBuf, nullptr);
    }
    catch (CreationException& ce) {
        std::cout << "Exception caught in creating DerivedEx dex3: "
            << ce.what()
            << std::endl
            << std::endl;
    }
    catch (...) {
        std::cout << "Exception caught in creating DerivedEx dex3: " << "unknown" << std::endl;
    }

    return 0;
}
#else

/*
MyNonEmptyString globalStr("");
namespace MySocpe {
    MyNonEmptyString globalStr("");
    static MyNonEmptyString staticStr("");
}

int _tmain(int argc, _TCHAR* argv[]) try {
    std::cout << "Main()" << std::endl;
    static MyNonEmptyString localStr("");
    return 0;
}
catch (CreationException& ce){
    std::cout << "Exception caught in global variables: "
              << ce.what()
              << std::endl;
}
*/

int Foo() try {
    static MyNonEmptyString localString("");
    //MyNonEmptyString localString("");
    return 2;
}
catch (CreationException& ce) {
    std::cout << "Exception caught in local static variables: "
        << ce.what()
        << std::endl;
}

class Bar {
public:
    Bar()
        try {
        // 1. Ok
        // static MyNonEmptyString localStaticStr("xx");
        // 2. Not Ok crash if instance of Bar is created
        static MyNonEmptyString localStaticStr("");
    }
    catch (CreationException& ce) {
        std::cout << ce.what() << std::endl;
    }

private:
    MyString m_ID{ "Bar" };
    // 3. Crash at beginning of the programm, no matter
    //    if any insatnce of Bar is created or not.
    // static MyNonEmptyString m_NEStr;
};

// 3
// MyNonEmptyString Bar::m_NEStr{ "" };

class BadInt {
public:
    BadInt(int val) : m_val(val)
    {}

    ~BadInt() {
        throw DestructionException("BadInt");
    }
private:
    int m_val;
};

class BaseFool {
public:
    virtual ~BaseFool() {
        std::cout << "~BaseFool()" << std::endl;
    }
private:
    MyString m_Version{ "1.0" };
};
class Fool1 : public BaseFool {
public:
    ~Fool1() {
        std::cout << "~Fool1()" << std::endl;
    }
public:
    BadInt m_val{ 0 };
    MyNonEmptyString m_ID{ "Fool1" };
};

class Fool2 : public BaseFool{
public:
    ~Fool2() try {
        std::cout << "~Fool2()" << std::endl;
    }
    catch (DestructionException& de) {
        std::cout << "Exception throwin in ~Fool2(): " << de.what() << std::endl;
    }
public:
    BadInt m_val{ 0 };
    MyNonEmptyString m_ID{ "Fool2" };
};

int _tmain(int argc, _TCHAR* argv[])
{
    Foo();

    std::cout << std::endl;

    try {
        Bar b;
    }
    catch (CreationException& ce) {
        std::cout << "Exception caught in Bar b: " << ce.what() << std::endl;
    }
    return 0;
}

/*
int _tmain(int argc, _TCHAR* argv[])
{
    try {
        Fool1 f;
    }
    catch (DestructionException& de){
        std::cout << "Exception caught: "
            << de.what()
            << std::endl
            << std::endl;
    }

    try {
        Fool2 f;
    }
    catch (DestructionException& de){
        std::cout << "Exception caught: "
            << de.what()
            << std::endl
            << std::endl;
    }
    return 0;
}*/


#endif



/*
1. Life time of objects
Base class and non-static memmber variabels are destoryed before hitting any catch clause. The behavior of accessing base class 
or non-static member variables is undefined.
The parameters are valid anywhare in function/constructor/destructor. Hence accessing the arguments in catch clause is valid
operation.

2. Legitimate use
For most C++ applications encountering exceptions seems innevitable, because some of most fundemental operations are embedded with
exceptions, such as std::bad_alloc when allocating memory in heap and std::bad_cast in dynamic casting, not even mentioning Standard
Template Library. Complete removing C++ exception and using error code only seems not a valid option any more for most occassion.

As try-block and funciton-try-block is to co-exist. So let's take a look at in what occassions it is good to use funciton-try-block.
In theory function-try-block can be used with any functions: any static/non-static function includeing main, constructors and
destructors. However 
*/