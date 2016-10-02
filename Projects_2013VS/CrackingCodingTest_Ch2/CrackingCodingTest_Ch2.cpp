// CrackingCodingTest_Ch2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <unordered_set>

struct Node
{
    int value = 0;
    Node* next = nullptr;
    Node()
        : value(0), next(nullptr)
    {}
    Node(int v)
        : value(v), next(nullptr)
    {}
    ~Node()
    {
        delete next;
        next = nullptr;
    }
};

void RemoveDuplicate(Node* head)
{
    using HashSet = std::unordered_set<int>;
    if (head == nullptr) {
        return;
    }

    HashSet visitedValues;
    Node* curNode = head;
    Node* prevNode;
    while (curNode != nullptr) {
        if (visitedValues.find(curNode->value) == visitedValues.end()) {
            visitedValues.insert(curNode->value);
            prevNode = curNode;
            curNode = curNode->next;
        }
        else {
            // duplicate
            prevNode->next = curNode->next;
            delete curNode;
            curNode = prevNode->next;
        }
    }
}

void RemoveDuplicateInPlace(Node* head)
{
    using HashSet = std::unordered_set<int>;
    if (head == nullptr) {
        return;
    }

    HashSet visitedValues;
    Node* curNode = head->next;
    Node* uniqueNodeTail = head->next;
    while (curNode != nullptr) {
        Node* tempNode = head;
        while (tempNode != uniqueNodeTail) {
            if (tempNode->value == curNode->value) {
                // duplicate
                curNode = curNode->next;
                break;
            }
        }
        if (tempNode == uniqueNodeTail) {
            // unique node
            uniqueNodeTail->value = curNode->value;
            uniqueNodeTail = uniqueNodeTail->next;
            curNode = curNode->next;
        }
    }

    while (uniqueNodeTail != nullptr) {
        Node* tempNode = uniqueNodeTail;
        uniqueNodeTail = uniqueNodeTail->next;
        delete tempNode;
    }
}

Node* FingNthLastElement(Node* head, size_t n)
{
    Node* nthBehind = nullptr;
    Node* curNode = head;
    while (--n > 0 && curNode != nullptr) {
        curNode = curNode->next;
    }

    if (curNode != nullptr) {
        nthBehind = head;
        curNode = curNode->next;
        while (curNode != nullptr) {
            nthBehind = nthBehind->next;
            curNode = curNode->next;
        }
    }

    return nthBehind;
}

void DeleteNodeInMiddle(Node** toDelete)
{
    Node* curNode = *toDelete;
    if (curNode == nullptr) {
        return;
    }

    Node* nextNode = curNode->next;
    while (nextNode != nullptr && nextNode->next != nullptr) {
        curNode->value = nextNode->value;
        curNode = nextNode;
        nextNode = nextNode->next;
    }

    // free up the memory
    if (nextNode == nullptr) {
        delete curNode;
        curNode = nullptr;
    }
    else if (nextNode->next == nullptr) {
        curNode->value = nextNode->value;
        curNode->next = nullptr;
        delete nextNode;
    }
}

Node* AddOperation(Node* a1, Node* a2)
{
    // value [0, 9]
    if (a1 == nullptr && a2 == nullptr) {
        return nullptr;
    }

    Node* result = nullptr;
    Node* tailOfResult = nullptr;
    int num1, num2, carrier = 0, temp;
    while (a1 != nullptr || a2 != nullptr)
    {
        num1 = num2 = 0;
        if (a1 != nullptr) {
            num1 = a1->value;
            a1 = a1->next;
        }
        if (a2 != nullptr) {
            num2 = a2->value;
            a2 = a2->next;
        }
        temp = num1 + num2 + carrier;
        carrier = temp / 10;
        temp = temp - 10 * carrier;
        if (tailOfResult == nullptr) {
            tailOfResult = new Node(temp);
            result = tailOfResult;
        }
        else {
            tailOfResult->next = new Node(temp);
            tailOfResult = tailOfResult->next;
        }
    }

    return result;
}

Node* FindTopOfCircularNode(Node* head)
{
    if (head == nullptr) {
        return nullptr;
    }

    Node* slow = head;
    Node* fast = head;
    while (fast != nullptr) {
        if (fast->next != nullptr && fast->next->next != nullptr) {
            fast = fast->next->next;
        }
        else {
            return nullptr;
        }
        if (fast == slow) {
            // there is a loop
            break;
        }
        slow = slow->next;
    }

    // find the circular len
    size_t circularLen = 1;
    fast = fast->next;
    while (fast != slow) {
        ++circularLen;
        fast = fast->next;
    }

    // find out the node
    slow = head;
    fast = head;
    while (circularLen) {
        fast = fast->next;
        --circularLen;
    }
    while (fast != slow) {
        fast = fast->next;
        slow = slow->next;
    }

    return slow;
}

Node* FindTopOfCircularNode2(Node* head)
{
    using HashMap = std::unordered_set<Node*>;
    if (head == nullptr) {
        return nullptr;
    }

    HashMap appearedNodes;
    Node* curNode = head;
    while (curNode != nullptr) {
        if (appearedNodes.find(curNode) == appearedNodes.end()) {
            appearedNodes.insert(curNode);
            curNode = curNode->next;
        }
        else {
            break;
        }
    }

    return curNode;
}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

