========================================================================
    CONSOLE APPLICATION : NullPtr Project Overview
========================================================================

AppWizard has created this NullPtr application for you.

This file contains a summary of what you will find in each of the files that
make up your NullPtr application.


NullPtr.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

NullPtr.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

NullPtr.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named NullPtr.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////


void foo(int i)
{
    std::cout << "foo(int)" << std::endl;
}

void foo(char* chPtr)
{
    std::cout << "foo(char*)" << std::endl;
}
					  
foo(0);		 // foo(int)
foo((char*)0);	 // foo(char*)
foo(NULL);		 // foo(int)
foo((char*)NULL);	// foo(char*)
foo(1);	 // foo(int)
foo(true); // foo(int)
foo((char*)1);// foo(char*);
foo((char*)true);// foo(char*);
foo(false); // foo(int);
foo(nullptr); // foo(char*)

--------------------------------------------------------------------
void foo(char* chPtr)
{
    std::cout << "foo(char*)" << std::endl;
}

foo(0);	// error
foo((char*)0);	// foo(char*)
foo(NULL); // error
foo((char*)NULL); // foo(char*)
foo(1);	 // error
foo(true); // error
foo((char*)1);//ok
foo((char*)true);//foo(char*)
foo(false); // foo(char*)
foo(nullptr);

--------------------------------------------------------------------
void foo(int i)
{
    std::cout << "foo(int)" << std::endl;
}


foo(0);	  // foo(int)
foo((char*)0); // error
foo(NULL);	   // foo(int)
foo((char*)NULL); // error
foo(1);	// foo(int)
foo(true); // foo(int)
foo((char*)1);//error
foo((char*)true);//eoor
foo(false); // ok
foo(nullptr); // error
---------------------------------------------------------------------
if (NULL) eqvalenet as if (0), evaluated as false
if (!NULL) // true
if (nullptr) // error
if (!nullptr) // error
if (nullptr == 0) // ok evaluated as true; supposed to be false accroding to HS's proposal
if (NULL==nullptr) 	// ok evaluated as true; supposed to be false accroding to HS's proposal
---------------------------------------------------------------------
char* chPtr = NULL;
char* chPtr1= nullptr;
int* iPtr = NULL;
int* iPtr1 = nullptr;

char x = NULL;
char x1 = nullptr;//error
bool z = NULL;
bool z1 = nullptr;//ok evaluted as false

if (chPtr == iPtr) // error
if (chPtr1 == iPtr1) // error
if (chPtr == chPtr1) // ok

if (x == NULL)
if (x == nullptr) // error

if (chPtr == NULL) {}
if (chPtr == nullptr) {}
if (chPtr1 == nullptr) {}
if (chPtr1 == NULL) {}

-------------------------------------------------------------
size_t s = sizeof(nullptr);
typeid(nullptr);
throw nullptr;

char* chPtr2 = 1? nullptr : nullptr;
char* chPtr3 = 1? NULL : nullptr;	// ok, supposed to error according to HS's proposal
char* chPtr3 = 1? 0 : nullptr;	// ok, supposed to error according to HS's proposal

int xx = 1? nullptr : nullptr;	 // error
int xxx = 1? NULL : nullptr; // error

----------------------------------------------------------------
template<class T> void bar(T* t) 
{
    std::cout << "Bar(T*)" << std::endl;
}

template<class T> void hel(T t)
{
    std::cout << "hel(T)" << std::endl;
}

    bar(nullptr);// error
    hel(nullptr); // nullptr_t
	bar((int*)nullptr);
    hel((int*)nullptr);