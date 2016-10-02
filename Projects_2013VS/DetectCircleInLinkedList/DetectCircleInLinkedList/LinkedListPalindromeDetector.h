#ifndef LINKED_LIST_PALINDROME_DETECTOR_H
#define LINKED_LIST_PALINDROME_DETECTOR_H

#pragma once

#include "LinkedListAlgo.h"
#include "LinkedListElement.h"


class LinkedListPalindromeDetector
{
public:
    LinkedListPalindromeDetector() = default;
    ~LinkedListPalindromeDetector() = default;
    LinkedListPalindromeDetector(const LinkedListPalindromeDetector& other) = delete;
    LinkedListPalindromeDetector(const LinkedListPalindromeDetector&& other) = delete;
    LinkedListPalindromeDetector& operator=(const LinkedListPalindromeDetector& rhs) = delete;
    LinkedListPalindromeDetector& operator=(const LinkedListPalindromeDetector&& rhs) = delete;

    template<typename T>
    static bool IsPalindrome(LinkedListElement<T>* head)
    {
        if (head == nullptr) {
            return false;
        }

        LinkedListElement<T>* slow = head;
        LinkedListElement<T>* fast2x = head->next;

        if (fast2x == nullptr) {
            return true;
        }

        while (fast2x != nullptr) {
            if (fast2x->next != nullptr) {
                fast2x = fast2x->next->next;
                slow = slow->next;
            }
            else {
                break;
            }
        }

        // split the LinkedList
        LinkedListElement<T>* firstHalf = head;
        LinkedListElement<T>* secondHalf = slow->next;
        slow->next = nullptr;

        // reverse the second half and compare with the first half
        LL_Reverse(&secondHalf);
        // firstHalf shoud have either the amount of elments as secondHalf
        // or have one more element.
        bool isPalindrome = LL_StartWith(firstHalf, secondHalf);

        // recover to the original LinkedList
        LL_Reverse(&secondHalf);
        slow->next = secondHalf;

        return isPalindrome;
    }


    //http://www.careercup.com/question?id=4826931360956416
    template<>
    static bool IsPalindrome(LinkedListElement<std::string>* head)
    {
        // 1. empty list
        if (head == nullptr) {
            return false;
        }

        using LinkedListString = LinkedListElement<std::string>*;
        LinkedListString cur = head;

        // 2. not empty list
        size_t totalCharacters = 0;
        while (cur != nullptr) {
            totalCharacters += cur->data.size();
            cur = cur->next;
        }

        cur = head;
        LinkedListString prev = cur;
        size_t numOfCharactersToPrev = 0;
        size_t numOfCharactersToCur = 0;
        auto oddNumOfCharacters = (totalCharacters & 1) > 0;
        size_t halfSize = oddNumOfCharacters? 
                          ((totalCharacters >> 1) + 1) : (totalCharacters >> 1);
        while (numOfCharactersToCur < halfSize) {
            numOfCharactersToPrev = numOfCharactersToCur;
            numOfCharactersToCur += cur->data.size();
            prev = cur;
            cur = cur->next;
        }

        // split the LinkedList
        prev->next = nullptr;
        auto leftHalf = head;
        auto rightHalf = cur;

        // reverse the 2nd half
        LL_Reverse(&leftHalf);

        std::string* leftStr = &(leftHalf->data);
        leftHalf = leftHalf->next;
        std::string* rightStr = leftStr;
        size_t leftStrIndex = halfSize - numOfCharactersToPrev;
        size_t rightStrIndex = leftStrIndex;
        oddNumOfCharacters ? leftStrIndex -= 1 : leftStrIndex = leftStrIndex;

        bool match = true;
        do{
            if (rightStrIndex >= rightStr->size()) {
                if (rightHalf == nullptr) {
                    match = false;
                    break;
                }
                rightStr = &(rightHalf->data);
                rightHalf = rightHalf->next;
                rightStrIndex = 0;
            }

            if (leftStrIndex == 0) {
                if (leftHalf == nullptr) {
                    match = false;
                    break;
                }
                leftStr = &(leftHalf->data);
                leftHalf = leftHalf->next;
                leftStrIndex = leftStr->size();
            }

            while (leftStrIndex > 0 && rightStrIndex < rightStr->size()) {
                if ((*leftStr)[leftStrIndex - 1] != (*rightStr)[rightStrIndex]) {
                    match = false;
                    break;
                }

                --leftStrIndex;
                ++rightStrIndex;
            }

            if (!match) {
                break;
            }
        } while (leftHalf != nullptr || rightHalf != nullptr);

        // reverse first half
        auto prevCopy = prev;
        LL_Reverse(&prev);
        // merge two halfs
        prevCopy->next = cur;

        return match;
    }

};

#endif
