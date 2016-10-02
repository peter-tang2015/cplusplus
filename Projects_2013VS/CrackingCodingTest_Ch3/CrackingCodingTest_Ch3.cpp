// CrackingCodingTest_Ch3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <array>
#include <stack>
#include <vector>

class ThreeStacks
{
public:

    ThreeStacks(size_t individualSize)
        : mData(individualSize*NUM_OF_STACKS, 0),
        mSize(individualSize)
    {
        mPointersStart[0] = 0;
        mPointersStart[1] = individualSize;
        mPointersStart[2] = individualSize << 1;
        mPointers[0] = -1;
        mPointers[1] = -1;
        mPointers[2] = -;;
    }
    ~ThreeStacks() = default;

    void Push(size_t whichStack, int val) {
        if (!IsValidStack(whichStack)) {
            throw "Invalid stack";
        }

        if (mPointers[whichStack] < 0) {
            mPointers[whichStack] = mPointersStart[whichStack];
            mData[mPointers[whichStack]] = val;
        }
        else {
            if (mPointers[whichStack] - mPointersStart[whichStack] >= mSize) {
                throw "Out of space";
            }
            mData[mPointers[whichStack]] = val;
            ++mPointers[whichStack];
        }
    }

    void Pop(size_t whichStack) {
        if (!IsValidStack(whichStack)) {
            throw "Invalid stack";
        }

        if (mPointers[whichStack] < 0) {
            throw "Empty stack";
        }

        --mPointers[whichStack];
    }

    int Top(size_t whichStack) {
        if (!IsValidStack(whichStack)) {
            throw "Invalid stack";
        }

        if (mPointers[whichStack] < 0) {
            throw "Empty stack";
        }

        return mData[mPointers[whichStack]];
    }

private:
    const int mSize;
    const static size_t NUM_OF_STACKS = 3;
    std::array<int, NUM_OF_STACKS> mPointersStart;
    std::array<int, NUM_OF_STACKS> mPointers;
    bool IsValidStack(size_t whichStack) {
        return whichStack < NUM_OF_STACKS;
    }
    std::vector<int> mData;
};

class Stack_O1Min
{
public:
    Stack_O1Min() = default;
    ~Stack_O1Min() = default;

    void Push(int x) {
        mVal.push(x);
        if (mMin.empty()) {
            mMin.push(x);
        }
        else {
            if (x <= mMin.top()) {
                mMin.push(x);
            }
        }
    }

    int Pop() {
        int x = mVal.top();
        if (x <= mMin.top()) {
            mMin.pop();
        }
        mVal.pop();
        return x;
    }

    int Min() {
        return mMin.top();
    }

private:
    std::stack<int> mVal;
    std::stack<int> mMin;
};

class PileOfStacks
{
public:
    PileOfStacks(int numOfStack, size_t stackSize)
        :mStack(numOfStack), mStackSize(stackSize)
    {
        mCurStack = mStack.begin();
    }

    void Push(int x) {
        if (mCurStack->size() < mStackSize) {
            mCurStack->push(x);
        }
        else {
            ++mCurStack;
            if (mCurStack == mStack.end()) {
                throw "Stack is full";
            }
            else {
                mCurStack->push(x);
            }
        }
    }

    int Pop() {
        if (mCurStack->empty()) {
            if (mCurStack == mStack.begin()) {
                throw "Stack is empty";
            }
            else {
                --mCurStack;
            }
        }
        int val = mCurStack->top();
        mCurStack->pop();
        return val;
    }

private:
    const size_t mStackSize;
    std::vector<std::stack<int>> mStack;
    std::vector<std::stack<int>>::iterator mCurStack;
};

void Hanoi()
{

}

class MyQUeueViaTwoStacks
{
public:
    MyQUeueViaTwoStacks() = default;
    ~MyQUeueViaTwoStacks() = default;

    void Push(int x) {
        mInbound.push(x);
    }

    int Pop() {
        if (mOutbound.empty()) {
            while (!mInbound.empty()) {
                int val = mInbound.top();
                mOutbound.push(val);
                mInbound.pop();
            }
        }
        int value = mOutbound.top();
        mOutbound.pop();
        return value;
    }
private:
    std::stack<int> mInbound;
    std::stack<int> mOutbound;
};

void SortStackInAscendingOrder(std::stack<int>& stk)
{
    if (stk.empty()) {
        return;
    }
    std::stack<int> temp;
    while (!stk.empty()) {
        int val = stk.top();
        stk.pop();
        if (temp.empty()) {
            temp.push(val);
        }
        else {
            while (val > temp.top()) {
                int tempVal = temp.top();
                stk.push(tempVal);
            }
            temp.push(val);
        }
    }

    temp.swap(stk);
}



int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

