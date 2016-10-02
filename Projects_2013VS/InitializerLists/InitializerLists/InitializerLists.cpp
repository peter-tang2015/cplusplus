// InitializerLists.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <initializer_list>
#include <iostream>
#include <vector>

struct Base {
	int x[8];
};

struct Derived : public Base {
	int y[8];
};

struct Foo{
	Foo() = default;
	Foo(int x, int y) : m_x{ x }, m_y{ y } {}

	int m_x{ 1 };
	int m_y{ 2 };

	virtual int GetValue() const { return m_x + m_y; }
};

struct MyFoo : public Foo {
	MyFoo() = default;
	MyFoo(int x, int y, int z) : Foo{ x, y }, m_z{ z } {}
	int m_z;

	virtual int GetValue() const { return Foo::GetValue() + m_z; }
};

struct YourFoo {
	YourFoo(std::initializer_list<int>) {}
	YourFoo(std::initializer_list<double>) {}
};

struct HisFoo {
	HisFoo(std::initializer_list<double>) {}
};

int ReturnTwo() {
	std::cout << "Two" << std::endl;
	return 2;
}

int ReturnFour() {
	std::cout << "Four" << std::endl;
	return 4;
}

int ReturnEight() {
	std::cout << "Eight" << std::endl;
	return 8;
}

int IncrementByTwo(int& x) {
	x += 2;
	return x;
}

int IncrementByFour(int& x) {
	x += 4;
	return x;
}

int IncrementByEight(int& x) {
	x += 8;
	return x;
}

int SumXYZ(int x, int y, int z) {
	std::cout << "x = " << x << std::endl;
	std::cout << "y = " << y << std::endl;
	std::cout << "z = " << z << std::endl;
	return x + y + z;
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<int> myVector = { 1, 2, 3 };

	std::cout << myVector.size() << std::endl;

	std::cout << sizeof(Base) << std::endl;
	std::cout << sizeof(Derived) << std::endl;

	Base myBaseArr[] = { Base{}, Derived{} };
	//Derived myDerivedArr[] = { Derived{}, Base{} };

	Foo f{ 2, 3 };
	MyFoo mf{ 4, 5, 6 };

	Foo fArr[4] = { Foo(1, 2), Foo{ 2, 3 }, Foo{ 4, 5 }, MyFoo{ 1, 2, 3 } };
	// MyFoo mfArr[3] = { Foo{ 1, 2 } };

	std::vector<std::vector<int>> myVec = { { 1, 2, 3 },
											{ 3, 4, 5, 6, 7 } };

	int* intPtr = new int[4] {1, 2, 3, 4};

	auto MyVecFoo = { Foo(1, 2), Foo(2, 3), Foo(4, 5) };
	for (auto iter = MyVecFoo.begin(); iter != MyVecFoo.begin(); ++iter) {

	}

	YourFoo yf1{ 1, 2 };
	YourFoo yf2{ 1.0, 2.0 };
	// YourFoo yf3{ 1, 2.0 };
	// YourFoo yf4{};
	YourFoo yf5{ std::initializer_list<double> {1, 2.0} };
	//YourFoo yf6{ std::initializer_list<int> {1, 2.0} };

	auto intIL = { 1, 2, 3 };
	//auto errorIL = { 1, 2.0, 3.0 };
	//auto okIL = { 1.0, 2, 3 };

	HisFoo hf{ 1, 2.0, 3.0 };

	const int& x{ 1 };
	// int& y{ 2 };

	int xx = 2.0;
	int xxx(2.0);

	int eoTest1[] = { ReturnTwo(), ReturnFour(), ReturnEight() };
	int eoInitVal{ 0 };
	int eoTest2[] = { IncrementByTwo(eoInitVal),
					  IncrementByFour(eoInitVal),
					  IncrementByEight(eoInitVal) };
	eoInitVal = { 0 };
	std::cout << IncrementByTwo(eoInitVal)
			  << IncrementByFour(eoInitVal) 
			  << IncrementByEight(eoInitVal)
			  << std::endl;
	eoInitVal = { 0 };
	SumXYZ(IncrementByTwo(eoInitVal),
		   IncrementByFour(eoInitVal),
		   IncrementByEight(eoInitVal));
	return 0;
}

