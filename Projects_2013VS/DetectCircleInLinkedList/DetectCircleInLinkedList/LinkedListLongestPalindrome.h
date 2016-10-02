#pragma once

#include "LinkedListAlgo.h"
#include "LinkedListElement.h"

#include <vector>

#include <cassert>

template<typename T>
class LinkedListLongestPalindrome
{
public:
    LinkedListLongestPalindrome() = default;
    LinkedListLongestPalindrome(LinkedListLongestPalindrome&) = delete;
    LinkedListLongestPalindrome(LinkedListLongestPalindrome&&) = delete;
    LinkedListLongestPalindrome& operator=(LinkedListLongestPalindrome&) = delete;
    LinkedListLongestPalindrome& operator=(LinkedListLongestPalindrome&&) = delete;
    ~LinkedListLongestPalindrome() = default;

    struct LL_PalindromeResult
    {
        LL_PalindromeResult()
            : LL_PalindromeResult(nullptr, 0)
        {}

        LL_PalindromeResult(LinkedListElement<T> *ptr, size_t l)
            : startPtr(ptr), len(l)
        {
        }
        LL_PalindromeResult(LL_PalindromeResult&) = default;
        ~LL_PalindromeResult() = default;
        LinkedListElement<T> *startPtr;
        size_t len;
    };

    LL_PalindromeResult operator()(LinkedListElement<T>* head)
    {
        LL_PalindromeResult result;
        if (head == nullptr) {
            return result;
        }

        result = LL_PalindromeResult(head, 1);
        if (head->next == nullptr) {
            return result;
        }

        // find the middle node
        LinkedListElement<T> *middleNode;
        size_t firstHalfCount;
        size_t totalCount;
        SplitLinkedListIntoTwo(head, middleNode, firstHalfCount, totalCount);
        
        // split the node
        LinkedListElement<T> *firstHalf;
        LinkedListElement<T> *secondHalf;
        SplitAndReverseTheFirstHalf(head, middleNode, firstHalf, secondHalf);

        // find the longest palindrome in the 1st run
        LL_PalindromeResult tempResult = FindLongestPalindrome(firstHalf,
                                                               secondHalf,
                                                               result.len,
                                                               firstHalfCount,
                                                               false);
        if (tempResult.len > result.len) {
            result = tempResult;
        }

        // recover the linked list;
        RecoverFromSplitting(firstHalf, secondHalf);
        assert(firstHalf == head);

        // split the node again
        SplitAndReverseTheFirstHalf(head, middleNode, firstHalf, secondHalf);

        // find the longest palindrom in the second run
        tempResult = FindLongestPalindrome(firstHalf,
                                           secondHalf,
                                           result.len,
                                           totalCount - firstHalfCount,
                                           true);
        if (tempResult.len > result.len) {
            result = tempResult;
        }

        // recover the linked list
        RecoverFromSplitting(firstHalf, secondHalf);

        return result;
    }

private:
    LL_PalindromeResult FindLongestPalindrome(LinkedListElement<T>* &firstHalf,
                                              LinkedListElement<T>* &secondHalf,
                                              size_t curMax,
                                              size_t halfCount,
                                              bool reversed)
    {
        LinkedListElement<T> *temp;
        LL_PalindromeResult result(nullptr, curMax);
        LL_PalindromeResult tempResult;
        while ((halfCount * 2 + 1) > result.len && firstHalf != nullptr && secondHalf != nullptr) {
            tempResult = GetCommon(firstHalf, secondHalf, reversed);
            // track the longest palindrome 
            if (tempResult.len > result.len) {
                result = tempResult;
            }

            // update the node and count for the next loop
            if (reversed) {
                temp = secondHalf->next;
                secondHalf->next = firstHalf;
                firstHalf = secondHalf;
                secondHalf = temp;
            }
            else {
                temp = firstHalf->next;
                firstHalf->next = secondHalf;
                secondHalf = firstHalf;
                firstHalf = temp;
            }
            --halfCount;
        }
        return result;
    }

    LL_PalindromeResult GetCommon(LinkedListElement<T> *x, LinkedListElement<T> *y, bool reversed)
    {
        if (x == nullptr || y == nullptr) {
            return LL_PalindromeResult();
        }

        // compare firstHalf with secondHalf
        LL_PalindromeResult result1 = CompareCommon(x, y, 0);
        // depends on which run
        //    - compare firstHalf->next with secondHalf
        //    - compare firstHalf with secondHalf->next
        LL_PalindromeResult result2 = reversed ? 
            CompareCommon(x->next, y, 1) : CompareCommon(x, y->next, 1);

        // return the longer palindrome
        return result1.len > result2.len ? result1 : result2;
    }

    LL_PalindromeResult CompareCommon(LinkedListElement<T> *x, LinkedListElement<T> *y, size_t start)
    {
        // compare two nodes until the first diverge appears
        LL_PalindromeResult result(nullptr, start);
        while (x != nullptr && y != nullptr) {
            if (x->data == y->data) {
                result.len += 2;
                result.startPtr = x;
                x = x->next;
                y = y->next;
            }
            else {
                break;
            }
        }

        return result;
    }

    void SplitLinkedListIntoTwo(LinkedListElement<T>* head,
                                LinkedListElement<T>* &middleNode,
                                size_t &firstHalfCount,
                                size_t &totalCount)
    {
        if (head == nullptr) {
            middleNode = nullptr;
            firstHalfCount = totalCount = 0;
            return;
        }
        // a, b, c, d, e, f, g, h
        // a, a
        // b, c
        // c, e
        // d, g
        // d, nullptr

        // a, b, c, d, e, f, g, h, i
        // a, a
        // b, c
        // c, e
        // d, g
        // e, i
        // e, nullptr
        LinkedListElement<T> *slowPtr = head;
        {
            LinkedListElement<T> *fasterX2 = head;
            while (fasterX2 != nullptr) {
                if (fasterX2->next != nullptr) {
                    ++totalCount;
                    fasterX2 = fasterX2->next;
                    if (fasterX2->next != nullptr) {
                        ++totalCount;
                        ++firstHalfCount;
                        slowPtr = slowPtr->next;
                    }
                }
                fasterX2 = fasterX2->next;
            }
        }
        middleNode = slowPtr;
    }

    void SplitAndReverseTheFirstHalf(LinkedListElement<T> *head,
                                   LinkedListElement<T> *middleNode,
                                   LinkedListElement<T>* &firstHalf,
                                   LinkedListElement<T>* &secondHalf)
    {
        if (middleNode == nullptr) {
            firstHalf = secondHalf = nullptr;
            return;
        }

        secondHalf = middleNode->next;
        middleNode->next = nullptr;
        firstHalf = head;
        LL_Reverse(&firstHalf);
    }

    void RecoverFromSplitting(LinkedListElement<T>* &firstHalf,
                              LinkedListElement<T>* &secondHalf)
    {
        LinkedListElement<T>* temp;
        if (firstHalf != nullptr) {
            temp = firstHalf;
            LL_Reverse(&firstHalf);
            temp->next = secondHalf;
        }
        else {
            firstHalf = secondHalf;
        }
    }
};
