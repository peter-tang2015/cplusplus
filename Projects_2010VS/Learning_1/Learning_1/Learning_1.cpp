// Learning_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int add(int a, int b)
{
	return a+b;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char cType = 0;
	short sType = 0;
	int iType = 0;
	float fType = 0;
	double dType = 0;
	const char* charType = "Hello, Mom";
	char *cPtr = NULL;

	int a = 3, b = 4;
	int c = add(a, b);

	char astr[20] = "Hello world";
	astr[1] = 't';

	const char aconstStr[20] = "Hello world";
	((char*)aconstStr)[3] = 't';

	char *astrPtr = "Hello world";
	//astrPtr[3] = 't';

	const char* aconststrPtr = "Hellp world";
	//aconststrPtr[3] = 't';

	char astrB[] = "Hello world";
	astrB[3] = 't';

	const char aconststrB[] = "Hello world";
	//aconststrB[3] = 't';
	((char*) aconststrB)[3] = 't';

	return 0;
}

// 32-bit sys
// i byte: 8 bits
// char: 1 byte
// short: 2 bytes
// int: 4 bytes
// long: 4 bytes
// float: 4 bytes -- x    xxxxxxx    xxxx xxxx xxxx xxxx xxxx xxxx
// double: 8 bytes

// 64-bit sys - LP

// 64-bit sys - LLP


// C 89, 98, 99

// C++ 98, 03, 11
// int_8: 1 byte
// int_16: 2 bytes
// int_32: 4 bytes
// int_64: 8 bytes
// uint_8

// operator
// arithmatic: + - * / % 
// logical && || !
// bit &, |, ~  char x = 1 (00000001); ~x (11111110) 
