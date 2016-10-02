#ifndef BINARY_SERACH_H
#define BINARY_SERACH_H

#pragma once

#include <vector>

class BinarySearch
{
public:
	BinarySearch();
	~BinarySearch();

	bool Search(const std::vector<int>& data, int key, int& pos);
	bool Search(const int data[], int start, int end, int key, int& pos);

	bool Search_recursive(const std::vector<int>& data, int key, int& pos);
	bool Search_recursive(const int data[], int start, int end, int key, int& pos);
};

#endif


