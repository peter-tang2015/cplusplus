// NullPtr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

void foo(int i)
{
    std::cout << "foo(int)" << std::endl;
}

/*
void foo(char* chPtr)
{
    std::cout << "foo(char*)" << std::endl;
}
*/

template<class T> void bar(T* t) 
{
    std::cout << "Bar(T*)" << std::endl;
}

template<class T> void hel(T t)
{
    std::cout << "hel(T)" << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
    char* chPtr = NULL;
    short* shPtr = NULL;
    char x = NULL;
    int* iPtr = nullptr;
    //char y = nullptr;
    bool z = nullptr;
    char* chPtr1 = nullptr;
    short* shPtr1 = nullptr;
    if (chPtr == chPtr1) {
        
    }

    if (x == NULL) { }
    if (chPtr == NULL) {}
    if (chPtr == nullptr) {}
    if (chPtr1 == nullptr) {}
    if (chPtr1 == NULL) {}

    if (nullptr == 0) {}
//    if (chPtr1 == shPtr1)
    /*
    if (chPtr!=shPtr) {

    }
    std::cout << "chPtr == shPtr" << chPtr==shPtr << std::endl;
      */
    if (NULL) {
    } else {
        std::cout << "NULL is evaluated as false" << std::endl;
    }

    if (!NULL) {

    }
    /*
    if (nullptr) {
    } else {
        std::cout<< "nullptr is evaluated as false" << std::endl;
    }
    */
    foo(0);
    foo(NULL);
    foo(1);
    //foo((char*)1);
    //foo((char*)0);
    //foo((char*)NULL);
     
    foo(false);
    foo(true);
    //foo((char*)true);

    //foo(nullptr);

    bar((int*)nullptr);
    hel((int*)nullptr);

    char* chPtr5 = 1? 0 : nullptr;

    if (NULL==nullptr) {}

	return 0;
}

