#ifndef LINKED_LIST_ALGO_CPP_H
#define LINKED_LIST_ALGO_CPPH

#pragma once

#include "LinkedListAlgo.h"

#include <vector>

template<typename T>
void LL_PushFrontFromStdVector(LinkedListElement<T>** head, const std::vector<T>& dataVec)
{
    if (dataVec.empty()) {
        return;
    }

    for (std::vector<T>::const_reverse_iterator cRIter = dataVec.rbegin();
         cRIter != dataVec.rend(); ++cRIter) {
        LL_PushFront(head, *cRIter);
    }
}

template<typename T>
void LL_PushBackFromStdVector(LinkedListElement<T>** head, const std::vector<T>& dataVec)
{
    if (dataVec.empty()) {
        return;
    }

    for (std::vector<T>::const_iterator cIter = dataVec.begin();
        cIter != dataVec.end(); ++cIter) {
        LL_Pushback(head, *cIter);
    }
}

template<typename T>
void LL_CopyDataToStdVector(LinkedListElement<T>* head, std::vector<T>& dataVec)
{
    if (head != nullptr) {
        dataVec.clear();
        dataVec.reserve(LL_GetSize(head));
    }

    LinkedListElement<T>* curNode = head;
    while (curNode != nullptr) {
        dataVec.push_back(curNode->data);
        curNode = curNode->next;
    }
}


#endif
