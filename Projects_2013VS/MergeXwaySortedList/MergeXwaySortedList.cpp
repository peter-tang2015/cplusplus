// MergeXwaySortedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../DetectCircleInLinkedList/DetectCircleInLinkedList/LinkedListElement.h"
#include "../DetectCircleInLinkedList/DetectCircleInLinkedList/LinkedList.h"

#include <queue>
#include <vector>

template <typename T>
struct LLE_Comparator
{
    bool operator() (LinkedListElement<T>* &lhs, LinkedListElement<T>* &rhs) {
        return lhs->data > rhs->data;
    }
};

template<typename T>
LinkedListElement<T>* AdvanceByX(LinkedListElement<T>* start, unsigned int X)
{
    unsigned int step = 0;
    while (start && step < X) {
        start = start->next;
        ++step;
    }

    return start;
}

template <typename T>
void MergeXwaySortedLL(LinkedList<T> &input, const unsigned int X, LinkedList<T> &result)
{
    using MinHeap = std::priority_queue<LinkedListElement<T>*, std::vector<LinkedListElement<T>*>, LLE_Comparator<T>>;

    LinkedListElement<T> **head = input.Release();
    if (!head || !(*head)) {
        return;
    }

    unsigned int count = 0;
    LinkedListElement<T> *temp = *head;
    MinHeap topNodesOfXways;
    // get first X nodes
    while (count < X && temp) {
        topNodesOfXways.push(temp);
        temp = temp->next;
        ++count;
    }

    while (!topNodesOfXways.empty()) {
        temp = topNodesOfXways.top();
        result.PushBack(temp->data);
        temp = AdvanceByX(temp, X);
        topNodesOfXways.pop();
        if (temp) {
            topNodesOfXways.push(temp);
        }
    }
}

template <typename T>
struct ValueIndexPair{
    ValueIndexPair(const T& val, size_t idx)
        : value(val), index(idx)
    {}
    ValueIndexPair()
    {}

    T value;
    size_t index;
};

template <typename T>
struct ArrE_Comparator
{
    bool operator() (ValueIndexPair<T> &lhs, ValueIndexPair<T> &rhs) {
        return lhs.value > rhs.value;
    }
};

template <typename T>
std::vector<T> MergeXwaySortedArr(const std::vector<T> &arr, const unsigned int X)
{
    using MinHeap = std::priority_queue<ValueIndexPair<T>, std::vector<ValueIndexPair<T>>, ArrE_Comparator<T>>;

    const size_t LEN = arr.size();
    if (X > LEN) {
        return std::vector<T>();
    }

    // push first X into heap
    MinHeap minHeap;
    for (unsigned int count = 0; count < X; ++count) {
        minHeap.push(ValueIndexPair<T>(arr[count], count));
    }

    std::vector<T> result;
    result.reserve(LEN);
    while (!minHeap.empty()) {
        ValueIndexPair<T> &temp = minHeap.top();
        result.push_back(temp.value);
        if ((temp.index + X) < LEN) {
            minHeap.push(ValueIndexPair<T>(arr[temp.index + X], temp.index + X));
        }
        minHeap.pop();
    }

    return result;
}


#include <cassert>
#include <array>
void Test_LL()
{
    {
        LinkedList<int> input;
        LinkedList<int> result;
        input.PushBack(1);
        MergeXwaySortedLL(input, 1, result);
        LinkedListElement<int> *head = *(result.Release());
        LinkedListElement<int> *tail = *(result.ReleaseTail());
        assert(head->data == 1);
        assert(tail->data == 1);
    }

    {
        LinkedList<int> input;
        LinkedList<int> result;
        const std::array<int, 16> data = { 0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15 };
        for (auto iter = data.begin(); iter != data.end(); ++iter) {
            input.PushBack(*iter);
        }

        MergeXwaySortedLL(input, 4, result);
        LinkedListElement<int> *curNode = *(result.Release());
        unsigned int count = 0;
        while (curNode) {
            assert(curNode->data == count);
            curNode = curNode->next;
            ++count;
        }

        assert(count == 16);
    }
}

void Test_Arr()
{
    {
        const std::vector<int> data = { 1, 3, 2, 4 };
        std::vector<int> result = MergeXwaySortedArr(data, 5);
        assert(result.empty() == true);
        result = MergeXwaySortedArr(data, 2);
        assert(result == std::vector<int>({ 1, 2, 3, 4 }));
    }

    {
        const std::vector<int> data = { 0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15 };
        std::vector<int> result = MergeXwaySortedArr(data, 17);
        assert(result.empty() == true);
        result = MergeXwaySortedArr(data, 4);
        assert(result == std::vector<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}));
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    Test_LL();
    Test_Arr();

    return 0;
}

