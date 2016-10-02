#ifndef LINKED_LIST_CIRCLE_DETECT_H
#define LINKED_LIST_CIRCLE_DETECT_H

#pragma once

#include "LinkedListElement.h"

template<typename T>
LinkedListElement<T>* LL_GetOneOfNodesInCircleIfExists(LinkedListElement<T>* head)
{
    if (head == nullptr) {
        return nullptr;
    }

    LinkedListElement<T>* slow = head;
    LinkedListElement<T>* fast = head;

    while (1) {
        for (int speed = 0; speed < 2; ++speed) {
            fast = fast->next;
            if (fast == nullptr) {
                return nullptr;
            }
            if (slow == fast) {
                return slow;
            }
        }

        slow = slow->next;
    }

    return nullptr;
}

template<typename T>
bool LL_CheckIfCircleExists(LinkedListElement<T>* head)
{
    return LL_GetOneOfNodesInCircleIfExists(head) != nullptr;
}

template<typename T>
size_t LL_GetCircleSizeIfExists(LinkedListElement<T>* head)
{
    LinkedListElement<T>* oneNodeInCircle = LL_GetOneOfNodesInCircleIfExists(head);

    if (oneNodeInCircle == nullptr) {
        return 0;
    }

    size_t count = 1;
    LinkedListElement<T>* cur = oneNodeInCircle->next;
    while (cur != oneNodeInCircle) {
        cur = cur->next;
        ++count;
    }

    return count;
}

template<typename T>
LinkedListElement<T>* LL_DetectTheLastNodeOfCircleIfExists(LinkedListElement<T>* head)
{
    size_t circleSize = LL_GetCircleSizeIfExists(head);

    if (circleSize == 0) {
        return nullptr;
    }

    LinkedListElement<T>* cur = head;
    LinkedListElement<T>* tempOffsetByCircleSize = head;

    while (--circleSize > 0) {
        tempOffsetByCircleSize = tempOffsetByCircleSize->next;
    }

    while (cur != tempOffsetByCircleSize->next) {
        cur = cur->next;
        tempOffsetByCircleSize = tempOffsetByCircleSize->next;
    }

    return tempOffsetByCircleSize;
}

/*
 * If circle does not exsit, return false
 * If circle exists, then remove the circle and return true
 */
template<typename T>
bool LL_RemoveCircleIfExists(LinkedListElement<T>** head)
{
    if (head == nullptr) {
        return false;
    }
    LinkedListElement<T>* lastNodeOfCircle = LL_DetectTheLastNodeOfCircleIfExists(*head);
    if (lastNodeOfCircle == nullptr) {
        return false;
    }

    lastNodeOfCircle->next = nullptr;
    return true;
}

#endif
