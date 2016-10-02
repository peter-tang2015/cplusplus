// auto_feature.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

struct Foo {
	int x;
	double y;
};

class Base {
public:
	virtual const std::string GetName() const {
		return "Base";
	}

};

class Derived : public Base {
public:
	virtual const std::string GetName() const {
		return "Derived";
	}
};

static Derived gDervied;

Base GetBase() {
	return gDervied;
}

Base& GetBaseRef() {
	return gDervied;
}


int _tmain(int argc, _TCHAR* argv[])
{
	auto i = 3, j = 4;
	//auto x = 1, y = 2.0;
	//auto x = 1, &y = i, *z = &j;

	auto aFoo1 = Foo{ 1, 2.0 };
	// auto aFoo2{ Foo{ 1, 2.0 } };
	auto aFoo3(Foo{ 1, 2.0 });
	auto* aFoo4 = new Foo{ 1, 2.0 };
	auto* aFoo5(new Foo{ 1, 2.0 });
	// auto* aFoo6{ new Foo{ 1, 2.0 } };

	auto* intPtr = new int { 10 };
	auto* intPtr1 = new auto{12};
	auto* intPtr2 = new auto(1);
	auto* dblPtr1 = new auto{1.0};
	// auto* fooPtr = new auto {Foo(1, 2.0)};

	auto gb = GetBase();
	std::cout << gb.GetName() << std::endl;
	auto &gbr = GetBaseRef();
	std::cout << gbr.GetName() << std::endl;

	return 0;
}

