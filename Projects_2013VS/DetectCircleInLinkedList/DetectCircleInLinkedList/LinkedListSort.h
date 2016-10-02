#ifndef LINKED_LIST_SORT_H
#define LINKED_LIST_SORT_H

#pragma once

#include "LinkedListAlgo.h"
#include "LinkedListElement.h"

template<typename T>
void LL_MergeSort(LinkedListElement<T>** head)
{
    if (head == nullptr || *head == nullptr || (*head)->next == nullptr) {
        return;
    }

    LinkedListElement<T>* front = nullptr;
    LinkedListElement<T>* back = nullptr;
    LL_FrontBackSplit(*head, &front, &back);
    LL_MergeSort(&front);
    LL_MergeSort(&back);
    *head = LL_SortedMerge(front, back);
}

template<typename T>
void LL_FrontBackSplit(LinkedListElement<T>* src,
                       LinkedListElement<T>** front,
                       LinkedListElement<T>** back)
{
    if (src == nullptr) {
        return;
    }

    LinkedListElement<T>* slow = src;
    LinkedListElement<T>* fast = src->next;
    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = src;
    *back = slow->next;
    slow->next = nullptr;
}

template<typename T>
LinkedListElement<T>* LL_SortedMerge(LinkedListElement<T>* l1,
                                     LinkedListElement<T>* l2)
{
    LinkedListElement<T> temp;
    LinkedListElement<T>* cur = &temp;

    while (l1 != nullptr || l2 != nullptr) {
        if (l1 == nullptr) {
            cur->next = l2;
            return temp.next;
        }
        if (l2 == nullptr) {
            cur->next = l1;
            return temp.next;
        }
        if (l1->data <= l2->data) {
            cur->next = l1;
            cur = cur->next;
            l1 = l1->next;
        }
        else {
            cur->next = l2;
            cur = cur->next;
            l2 = l2->next;
        }
    }

    return temp.next;
}

template<typename T>
LinkedListElement<T>* LL_SortedMergeRecursively(LinkedListElement<T>* l1,
                                                LinkedListElement<T>* l2)
{
    if (l1 == nullptr) {
        return l2;
    }
    if (l2 == nullptr) {
        return l1;
    }

    LinkedListElement<T>* result = nullptr;
    if (l1->data <= l2->data) {
        result = l1;
        result->next = LL_SortedMergeRecursively(l1->next, l2);
    }
    else {
        result = l2;
        result->next = LL_SortedMergeRecursively(l1, l2->next);
    }

    return result;
}

template<typename T>
void LL_RemoveDuplicates(LinkedListElement<T>** head)
{
    if (head == nullptr || *head == nullptr || (*head)->next == nullptr) {
        return;
    }

    LinkedListElement<T>* curValPtr = *head;
    LinkedListElement<T>* nextValPtr = (*head)->next;
    while (nextValPtr != nullptr) {
        if (nextValPtr->data == curValPtr->data) {
            curValPtr->next = nextValPtr->next;
            delete nextValPtr;
            nextValPtr = curValPtr->next;
        }
        else {
            curValPtr = nextValPtr;
            nextValPtr = nextValPtr->next;
        }
    }

    return;
}

/*
 * create a new list which is intersection of two lists
 * no duplicate in this list
 * l1 and l2: has to be sorted linked list
 */
template<typename T>
LinkedListElement<T>* LL_SortedIntersect(LinkedListElement<T>* l1,
                                         LinkedListElement<T>* l2)
{
    if (l1 == nullptr || l2 == nullptr) {
        return nullptr;
    }

    LinkedListElement<T>* head = nullptr;
    ptrdiff_t found;
    size_t pos = 0;
    LinkedListElement<T>* curValPtr = nullptr;
    while (l1 != nullptr) {
        if (curValPtr == nullptr || curValPtr->data != l1->data) {
            curValPtr = l1;

            found = LL_Find(l2, pos, curValPtr->data);
            if (found >= 0) {
                LL_PushFront(&head, curValPtr->data);
                pos = static_cast<size_t>(found + 1);
            }
        }
        l1 = l1->next;
    }

    return head;
}

template<typename T>
bool LL_SortedInsert(LinkedListElement<T>**head, const T& val)
{
    if (head == nullptr) {
        return false;
    }

    if (*head == nullptr) {
        LL_PushFront(head, val);
        return true;
    }

    if (val <= (*head)->data) {
        LL_PushFront(head, val);
        return true;
    }

    LinkedListElement<T>* prev = *head;
    LinkedListElement<T>* cur = (*head)->next;

    while (cur != nullptr) {
        if (cur->data >= val) {
            prev->next = new LinkedListElement<T>(val);
            prev->next->next = cur;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }

    // hit here not found the position
    // LL_PushBack(head, val);
    prev->next = new LinkedListElement<T>(val);
    return true;
}

#endif
