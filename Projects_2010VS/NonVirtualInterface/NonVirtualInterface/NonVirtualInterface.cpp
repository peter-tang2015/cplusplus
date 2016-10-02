// NonVirtualInterface.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class DerivedNVI;

class NVI {
public:
    typedef enum {
        ITSELF,
        DRIVED_1,
        DRIVED_2
    } NVI_INSTANCE;
    void Foo() {
        FooImp();
    }
    void Bar() {
        BarImp();
    }
    virtual ~NVI() {};

    static NVI* CreateInstance(NVI_INSTANCE in) {
        // Create instance of itself or sub-classes
        switch (in) {
            case ITSELF:
                return new NVI();
            case DRIVED_1:
                //return new DerivedNVI();
            case DRIVED_2:
            default:
                return NULL;
        }
    }

protected:
    NVI() {}

private:
    virtual void FooImp() {
        static int i = 0;
        ++i;
    }
    virtual void BarImp() {
        static int j = 0;
        ++j;
    }
};

class DerivedNVI : public NVI {
public:
    DerivedNVI() : NVI() {}
private:
    void FooImp() {
        static int ii = 0;
        ++ii;
    }

    void BarImp() {
        static int jj = 0;
        ++jj;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    NVI* nviPtr1 = NVI::CreateInstance(NVI::ITSELF);
    nviPtr1->Foo();
    nviPtr1->Bar();

    NVI& nviRef = DerivedNVI();

    /*
    NVI* nviPtr2 = NVI::CreateInstance(NVI::DRIVED_1);
    nviPtr2->Foo();
    nviPtr2->Bar();
      */
    return 0;
}

/*
Non-virtual inerface vs. vitual interface

The main advantage of NVI is that it provides better code sepration and modulization. We oftern come across
VI when having full access to the source code. These codes does not mean to be exsiting alone.

However NVI normally
comes into force when you would like to turn a bunch of codes into a standalone module, dll or shared library.
The C++ api can be implemented via NVI with refereing to the same object type but internally different
behavior instatntiated. 

In the user code
NVI* nvi = NVI::CreateInstance(//option passed here to create different objects to have different behavior )
With the public interface to serve the purpose.

With the modulization a better implemention can be done via NVI by delegating the different behavior/data member
into a delegate class
                             
*/