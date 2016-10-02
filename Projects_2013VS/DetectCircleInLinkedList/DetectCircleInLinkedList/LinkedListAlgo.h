#ifndef LINKED_LIST_ALGO_H
#define LINKED_LIST_ALGO_H

#pragma once

#include "LinkedListElement.h"

#include <functional>

template<typename T>
void LL_PushFront(LinkedListElement<T>** head, const T& data)
{
    if (*head == nullptr) {
        *head = new LinkedListElement<T>(data);
    }
    else {
        LinkedListElement<T>* curHead = *head;
        *head = new LinkedListElement<T>(data);
        (*head)->next = curHead;
    }
}

template<typename T>
void LL_PushBack(LinkedListElement<T>** head, const T& data)
{
	if (*head == nullptr) {
		*head = new LinkedListElement<T>(data);
	}
	else {
		LinkedListElement<T>* curHead = *head;
		while (curHead->next != nullptr) {
			curHead = curHead->next;
		}
		curHead->next = new LinkedListElement<T>(data);
	}
}

template<typename T>
void LL_PopFront(LinkedListElement<T>** head)
{
	if (head == nullptr || *head == nullptr) {
		return;
	}

	LinkedListElement<T>* temp = *head;
	*head = (*head)->next;
	delete temp;
}

template<typename T>
void LL_PopBack(LinkedListElement<T>** head)
{
	if (head == nullptr || *head == nullptr) {
		return;
	}
	
	LinkedListElement<T>* prev = *head;
	LinkedListElement<T>* curHead = *head;
	while (curHead->next != nullptr) {
		prev = curHead;
		curHead = curHead->next;
	}

	prev->next = nullptr;
	delete curHead;
}

template<typename T>
bool LL_Insert(LinkedListElement<T>** head, size_t pos, const T& data)
{
	if (pos == 0) {
		LL_PushFront(head, data);
		return true;
	}

	LinkedListElement<T>* curHead = *head;
	while (--pos > 0) {
		curHead = curHead->next;
		if (curHead == nullptr) {
			return false;
		}
	}

	LinkedListElement<T>* next = curHead->next;
	curHead->next = new LinkedListElement<T>(data);
	curHead->next->next = next;
	return true;
}

template<typename T>
bool LL_Insert(LinkedListElement<T>** head, const LinkedListElement<T>* pos_node, const T& data)
{
	if (head == nullptr || *head == nullptr || pos_node == nullptr) {
		return false;
	}

	if (*head == pos_node) {
		LL_PushFront(head, data);
		return true;
	}

	LinkedListElement<T>* prev = nullptr;
	LinkedListElement<T>* curHead = *head;
	while (curHead != pos_node) {
		prev = curHead;
		curHead = curHead->next;
		if (curHead == nullptr) {
			return false;
		}
	}

	prev->next = new LinkedListElement<T>(data);
	prev->next->next = curHead;
	return true;
}

template<typename T>
bool LL_Erase(LinkedListElement<T>** head, size_t pos)
{
	if (head == nullptr || *head == nullptr) {
		return false;
	}

	if (pos == 0) {
		LL_PopFront(head);
		return true;
	}

	LinkedListElement<T>* prev = *head;
	LinkedListElement<T>* curHead = *head;
	while (pos > 0) {
		prev = curHead;
		curHead = curHead->next;
		if (curHead == nullptr) {
			return false;
		}
        --pos;
	}

	prev->next = curHead->next;
	delete curHead;
	return true;
}

template<typename T>
bool LL_Erase(LinkedListElement<T>** head, const LinkedListElement<T>* pos_node)
{
	if (head == nullptr || *head == nullptr || pos_node == nullptr) {
		return false;
	}

	if (*head == pos_node) {
		LL_PopFront(head);
		return true;
	}

	LinkedListElement<T>* prev = nullptr;
	LinkedListElement<T>* curHead = *head;
	while (curHead != pos_node) {
		prev = curHead;
		curHead = curHead->next;
		if (curHead == nullptr) {
			return false;
		}
	}

	prev->next = curHead->next;
	delete curHead;
	return true;
}

template<typename T>
bool LL_GetNth(LinkedListElement<T>* head, size_t pos, T& data)
{
	if (head == nullptr) {
		return false;
	}

	while (pos > 0) {
		head = head->next;
		if (head == nullptr) {
			return false;
		}
		--pos;
	}

	data = head->data;
	return true;
}

template<typename T>
LinkedListElement<T>* LL_GetNth(LinkedListElement<T>* head, size_t pos)
{
	if (head == nullptr) {
		return nullptr;
	}

	while (pos > 0) {
		head = head->next;
		if (head == nullptr) {
			return nullptr;
		}
		--pos;
	}

	return head;
}

template<typename T>
size_t LL_GetSize(LinkedListElement<T>* head)
{
	size_t size = 0;
	while (head != nullptr) {
		head = head->next;
		++size;
	}

	return size;
}

template<typename T>
void LL_Reverse(LinkedListElement<T>** head)
{
	// return if has less than 2 nodes
	if (head == nullptr || *head == nullptr || (*head)->next == nullptr) {
		return;
	}

	LinkedListElement<T>* cur = *head;
	LinkedListElement<T>* next = nullptr;
	LinkedListElement<T>* curHead = nullptr;

	while (cur != nullptr) {
		next = cur->next;
		cur->next = curHead;
		curHead = cur;
		cur = next;
	}

	*head = curHead;
}

template<typename T>
void LL_Delete(LinkedListElement<T>** head)
{
	if (head == nullptr || *head == nullptr) {
		return;
	}

	LinkedListElement<T>* curHead = *head;
	LinkedListElement<T>* temp = nullptr;
	while (curHead != nullptr) {
		temp = curHead;
		curHead = curHead->next;
		delete temp;
	}

	*head = nullptr;
}

/*
 * return -1, if not found
 * 0 - size-1, if found the very first
 */
template<typename T>
ptrdiff_t LL_Find(LinkedListElement<T>* head, const T& val)
{
	if (head == nullptr) {
		return -1;
	}

	ptrdiff_t pos = 0;
	while (head != nullptr) {
		if (head->data == val) {
			return pos;
		}

		head = head->next;
		++pos;
	}

	return -1;
}

template<typename T>
ptrdiff_t LL_Find(LinkedListElement<T>* head, size_t pos, const T& val)
{
    if (head == nullptr) {
        return -1;
	}

	while (pos > 0) {
		head = head->next;
		if (head == nullptr) {
			return -1;
		}
		--pos;
	}

	return LL_Find(head, val);
}

/*
 * Refer to std::string compare
 * Return 0: =
 *        1: >
 *       -1: <
 */
template<typename T>
int LL_Compare(LinkedListElement<T>* lhs, LinkedListElement<T>* rhs)
{
    if (lhs == nullptr && rhs == nullptr) {
        return true;
    }

    while (lhs != nullptr) {
        if (rhs == nullptr) {
            // lhs has more elements
            return 1;
        }

        if (lhs->data > rhs->data) {
            return 1;
        } 
        else if (lhs->data < rhs->data) {
            return -1;
        }

        // if the same, compare the next element
        lhs = lhs->next;
        rhs = rhs->next;
    }

    if (rhs == nullptr) {
        // rhs has the same amount elements as lhs
        // and so fare they are all equal
        return 0;
    }

    // rhs has more elements
    return -1;
}

template<typename T>
bool LL_StartWith(LinkedListElement<T>* source, LinkedListElement<T>* pattern)
{
    if (source == nullptr && pattern == nullptr) {
        return true;
    }

    while (source != nullptr) {
        if (pattern == nullptr) {
            // source has more elements
            return true;
        }

        if (source->data != pattern->data) {
            return false;
        }

        // if the same, compare the next element
        source = source->next;
        pattern = pattern->next;
    }

    // pattern has the same amount elements as source
    // and so fare they are all equal, then return true
    // pattern has more elements, return false
    return pattern == nullptr;
}


/*
 * This function is only for signed arithmatic type
 * double, float, long, int, short, char
 */
template<typename T>
void LL_OrderElementsIntoNegativePositiveSeries(LinkedListElement<T>* head)
{
    if (head == nullptr ||
        head->next == nullptr ||
        head->next->next == nullptr){
        return;
    }

    // if first value is negative, then find a positive value next
    bool positiveValToFind = head->data < 0;
    LinkedListElement<T>* outOfOrderNode = head;
    LinkedListElement<T>* curNode = head;
    LinkedListElement<T>* tempNode;

    while (curNode->next != nullptr) {
        if ((curNode->next->data > 0 && positiveValToFind) ||
            (curNode->next->data < 0 && !positiveValToFind)) {
            if (outOfOrderNode->next == curNode->next) {
                // Scenario 1
                positiveValToFind = !positiveValToFind;
                outOfOrderNode = outOfOrderNode->next;
                curNode = curNode->next;
            }
            else {
                // Scenario 2
                tempNode = curNode->next;
                curNode->next = tempNode->next;
                tempNode->next = outOfOrderNode->next;
                outOfOrderNode->next = tempNode;
                outOfOrderNode = tempNode->next;
            }
        }
        else {
            curNode = curNode->next;
        }
    }
}

template <typename T>
void LL_SpiltLinkedList(LinkedListElement<T>** input,
                        LinkedListElement<T>** splitOnTrue,
                        LinkedListElement<T>** splitOnFalse,
                        std::function<bool (const T&)> func)
{
    if (input == nullptr || *input == nullptr) {
        return;
    }

    LinkedListElement<T>* curNode = *input;
    LinkedListElement<T>* nodesOnTrue = nullptr;
    LinkedListElement<T>* nodesOnFalse = nullptr;
    while (curNode) {
        if (func(curNode->data)) {
            if (*splitOnTrue == nullptr) {
                *splitOnTrue = curNode;
                nodesOnTrue = *splitOnTrue;
            }
            else {
                nodesOnTrue->next = curNode;
                nodesOnTrue = nodesOnTrue->next;
            }
        }
        else {
            if (*splitOnFalse == nullptr) {
                *splitOnFalse = curNode;
                nodesOnFalse = *splitOnFalse;
            }
            else {
                nodesOnFalse->next = curNode;
                nodesOnFalse = nodesOnFalse->next;
            }
        }
        curNode = curNode->next;
    }
    if (nodesOnTrue) {
        nodesOnTrue->next = nullptr;
    }
    if (nodesOnFalse) {
        nodesOnFalse->next = nullptr;
    }
    *input = nullptr;
}

#endif
