#include "stdafx.h"
#include "BinarySearch.h"


BinarySearch::BinarySearch()
{
}


BinarySearch::~BinarySearch()
{
}


bool BinarySearch::Search(const std::vector<int>& data, int key, int& pos)
{
	if (data.empty()) {
		return false;
	}
	return Search(&data[0], 0, data.size(), key, pos);
}

bool BinarySearch::Search(const int data[], int start, int end, int key, int& pos)
{
	pos = -1;
	if (data == nullptr) {
		return false;
	}

	int midpoint;
	int tempStart = start;
	int tempEnd = end;
	while (tempStart <= tempEnd) {
		midpoint = (tempStart + tempEnd) >> 1;
		if (data[midpoint] == key) {
			pos = midpoint;
			return true;
		}
		else if (data[midpoint] > key) {
			tempEnd = midpoint - 1;
		}
		else{
			tempStart = midpoint + 1;
		}
	}

	return false;
}

bool BinarySearch::Search_recursive(const std::vector<int>& data, int key, int& pos)
{
	if (data.empty()) {
		return false;
	}
	return Search_recursive(&data[0], 0, data.size(), key, pos);
}

bool BinarySearch::Search_recursive(const int data[], int start, int end, int key, int& pos)
{
	if (start > end || data == nullptr) {
		pos = -1;
		return false;
	}

	int midpoint = (start + end) >> 1;
	if (data[midpoint] == key) {
		pos = midpoint;
		return true;
	}
	else if (data[midpoint] > key) {
		return Search_recursive(data, start, midpoint - 1, key, pos);
	}
	else {
		return Search_recursive(data, midpoint + 1, end, key, pos);
	}
}