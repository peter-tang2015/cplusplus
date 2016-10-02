#pragma once
#ifndef FOO_H
#define FOO_H
class Foo
{
public:
	Foo(void);
	~Foo(void);
	const int& GetX() const;
	int& GetX();
private:
	int x;
};

#endif


