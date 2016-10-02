// CatchingExceptions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>

class IntegerWrapper {
public:
    IntegerWrapper(int i) : m_i(i) 
    {}

private:
    int m_i;
};

class BaseException : std::exception {
public:
    virtual const char* what() const {
        return "BaseException is thrown";
    }

    virtual void ReThrow() {
        throw *this;
    }
};

class DerivedException : public BaseException {
public:
    virtual const char* what() const {
        return "DerivedException is thrown";
    }

    virtual void ReThrow() {
        throw *this;
    }
};

class MyDerivedException : public DerivedException {
public:
    virtual const char* what() const {                                           
        return "MyDerivedException is thrown";
    }
    virtual void ReThrow() {
        throw *this;
    }
};

void HandleExceptionAndRethrow(BaseException& be)
{
    std::cout << be.what() << std::endl;
    throw be;
}

void HandleExceptionAndRethrow1(BaseException& be)
{
    std::cout << be.what() << std::endl;
    be.ReThrow();  
}


void CatchExceptionAndRethrow()
{
    try {
        try {
            throw MyDerivedException();
        } catch (MyDerivedException& mde) {
            //HandleExceptionAndRethrow(mde);
            HandleExceptionAndRethrow1(mde);
        } catch (DerivedException& de) {
            //HandleExceptionAndRethrow(de);
            HandleExceptionAndRethrow1(de);
        } catch (BaseException& be) {
            //HandleExceptionAndRethrow(be);
            HandleExceptionAndRethrow1(be);
        } catch (...) {
            std::cout << "CatchExceptionAndRethrow: anything else in inner try block"
                        << std::endl;
        }
    } catch (MyDerivedException& mde) {
        std::cout << mde.what() << std::endl;
    } catch (DerivedException& de) {
        std::cout << de.what() << std::endl;
    } catch (BaseException& be) {
        std::cout << be.what() << std::endl;
    } catch (...) {
        std::cout << "CatchExceptionAndRethrow: anything else in outer try block"
                  << std::endl;
    }
}

void CatchExceptionClassHiearachyByPointer() 
{
    try {
        throw new DerivedException();
    } catch (void* e) {
        std::cout << "CatchExceptionClassHiearachyByPointer::void *" << std::endl;
    } catch (BaseException* be) {
        std::cout << "CatchExceptionClassHiearachyByPointer::BaseException *" << std::endl;
    } catch (DerivedException* de) {
        std::cout << "CatchExceptionClassHiearachyByPointer::DerivedException *" << std::endl;
    } catch (...) {
        std::cout << "CatchExceptionClassHiearachyByPointer::anything else" << std::endl;
    }    
}

void CatchExceptionClassHiearachyByReference()
{
    try {
        throw DerivedException();
    } catch (BaseException& be) {
        std::cout << "CatchExceptionClassHiearachyByReference::BaseException &" << std::endl;
    } catch (DerivedException* de) {
        std::cout << "CatchExceptionClassHiearachyByReference::DerivedException &" << std::endl;
    } catch (...) {
        std::cout << "CatchExceptionClassHiearachyByReference::anything else" << std::endl;
    }    
}


void CatchExceptionNoTypePromotion()
{
    try {
        throw 1;
    } catch (float) {
        std::cout << "CatchExceptionNoTypePromotion::folat" << std::endl;
    } catch (IntegerWrapper& iw) {
        std::cout << "CatchExceptionNoTypePromotion::IntegerWrapper" << std::endl;
    } catch (...) {
        std::cout << "CatchExceptionNoTypePromotion::anything else" << std::endl;
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    CatchExceptionNoTypePromotion();
    CatchExceptionClassHiearachyByPointer();
    CatchExceptionClassHiearachyByReference();
    CatchExceptionAndRethrow();

	return 0;
}

