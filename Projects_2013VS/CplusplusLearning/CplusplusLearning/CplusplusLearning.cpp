// CplusplusLearning.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <array>
#include <fstream>
#include <vector>

void TestOfstream()
{
    std::ofstream fileHandle;
    fileHandle.open("HelloWorld.log", std::ofstream::app);
    //if (fileHandle.good())
    if (fileHandle.is_open())
    {
        fileHandle << "XYZ" << std::endl;
        fileHandle.flush();
    }

    fileHandle.close();
}

class Base
{
    int m_x = 0;
};

class Derived
{

    int m_y = 0;
};

struct Foo
{
    virtual std::string GetName()
    {
        return "Foo";
    }

    int m_x = 0;
};

class Bar
{
    Bar(int x) : m_x(x)
    {}

    int m_x = 0;
};

struct MyFoo
{
    int mX;
    double mY;
};

struct Comparator
{
    static bool CompareMyFooWithInt(const MyFoo& mf, int x)
    {
        return mf.mX < x;
    }
};
int _tmain(int argc, _TCHAR* argv[])
{
    std::array<int, 3> myArr = { 1, 2, 3 };
    // std::array<Base, 3> myBaseArr = { Base(), Base(), Derived() };
    std::array<Foo, 3> myFooArr = { Foo(), Foo(), Foo() };
    //std::array<Bar, 3> myBarArr = { 1, 2, 3 };

    if (myFooArr[0].m_x == 0) {
        myFooArr[0].m_x = 1;
    }

    std::vector<MyFoo> myFooVec = { { 1, 1.0 }, { 2, 2.0 }, { 3, 3.0 }, { 4, 4.0 }, {5, 5.0} };
    auto it = std::lower_bound(myFooVec.begin(), myFooVec.end(), 3, Comparator::CompareMyFooWithInt);
    return 0;
}

/*
std::array

std::array has the memory footprint of c-style array, but with std::vector's interface. Like the c-style array and
unlike std::vector, std::arrary allocates the objects on the stack. The underline objects exists within the object
of std::array. The motivation behind std::array I think has at least 3 significant benifits
    - Save the memory comparing with std::vector
    - Provide STL interface
    - Performance optimization
        * Memory allocated on stack as c-style array
        * No memory fragment as on stack
        * No performance panelty of dynamic malloc/free lock between threads

1. std::array vs. c-style array
The major difference between might be that std::array provides STL interface. One of worthing mentioning is that
it has rbegin() and rend() to reversely travese the array.

Excpet this difference std::array takes all the advantage and disadvantage of c-style array. 
Advantages like:
    - memory allocated on stack
    - no performance panelty from memory and multi-threading application

Disadvantage (of c-style array):
    - The typename it take should not have polymophisim
        * std::array<Base, 3> myBaseArr = {Derived(), Base(), Derived()};
        * Compilation errors and object slicing
    - The typename should be POD type
        * Data type provides default constructor
        * Or intialized with intialzier-list
    - Worse syntax than c-style of array in multi-dimensional array
        * int threeDimArr[5][6][7]
        * std::array<std::array<std::array<int, 7>, 6>, 5> threeDimStdArr;

2. std::array vs. std::vector
The key difference between std::array and std::vector is that the underline objects on std::array is with the object of
std::array, however on std::array is dynamic allocated on the heap. The potential performance issues are the memory
fragment and the malloc/free lock between threads. (The threads have separated stacks but may or may not have separated
heaps, which depends on OS. Unix and Windows share the heap and Symbian doesn't.)

So in order to have out-of-scope life, std::array objects have to be created on the heap. However std::vector objects on
thhe stack can be easily moved around with const complexity to have out-of-scope life in C++11. Becuase the underline
objects are allocated on heap in std::vector. The operations like std::move and std::swap takes const complexity. However
std::array will take linear complexity to do these two operations, which are as expensive as std::copy.

3. User cases

* Replace the state-machine transition c-style array
This is one of the cases I think that std::array could come into use. Delcared as constexp and directly get the size for
std::array for defensive programming, which takes const time and therefore there is no performance penality comparing with
c-style but with better code. (In std::vecotr empty() takes constant time but size() may take line time. So std::vector()
may take performance penalty)

* Replace c-style array when reverse traverse

* Replace std::vector when the size is known beforehand

* Replace std::vector in the performance hotspots



1. No polymophism
2. POD data type
3. Replace with vector with known size
    vector::reserver() / vector.resize()
4. Used in Fortran or C API
5. Circlar buffer implementation
    Speed, safety and memory usage

*/

/*
reference operator[](size_type _Pos)
{	// subscript mutable sequence
#if _ITERATOR_DEBUG_LEVEL == 2
if (_Size <= _Pos)
_DEBUG_ERROR("array subscript out of range");

#elif _ITERATOR_DEBUG_LEVEL == 1
_SCL_SECURE_VALIDATE_RANGE(_Pos < _Size);
#endif /* _ITERATOR_DEBUG_LEVEL */

_Analysis_assume_(_Pos < _Size);

return (_Elems[_Pos]);
        }

        const_reference operator[](size_type _Pos) const
        {	// subscript nonmutable sequence
#if _ITERATOR_DEBUG_LEVEL == 2
            if (_Size <= _Pos)
                _DEBUG_ERROR("array subscript out of range");

#elif _ITERATOR_DEBUG_LEVEL == 1
            _SCL_SECURE_VALIDATE_RANGE(_Pos < _Size);
#endif /* _ITERATOR_DEBUG_LEVEL */

            _Analysis_assume_(_Pos < _Size);

            return (_Elems[_Pos]);
        }

*/

// http://www.careercup.com/question?id=5207197178920960
// http://www.careercup.com/question?id=5669013872967680
