#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#pragma once

#include "LinkedListElement.h"

#include <ostream>

template <typename T>
class LinkedList
{
	typedef LinkedListElement<T>* NodePtr;
	typedef LinkedListElement<T> Node;
public:
	LinkedList()
	{}

	~LinkedList()
	{ 
		DeleteList();
	}

    LinkedListElement<T>** Release()
    {
        return &m_Head;
    }
    LinkedListElement<T>** ReleaseTail()
    {
        return &m_Tail;
    }

	void PushBack(const T& data) 
	{
		if (m_Head == nullptr) {
			m_Head = new Node(data);
			m_Tail = m_Head;
		}
		else {
			m_Tail->next = new Node(data);
			m_Tail = m_Tail->next;
		}
	}

	void PushFront(const T& data)
	{
		if (m_Head == nullptr) {
			m_Head = new Node(data);
			m_Tail = m_Head;
		}
		else {
			NodePtr curHead = m_Head;
			m_Head = new Node(data);
			m_Head->next = curHead;
		}
	}

	void PopBack()
	{
		if (m_Head == nullptr) {
			return;
		}

		if (m_Head == m_Tail) {
			delete m_Tail;
			m_Head = nullptr;
			m_Tail = nullptr;
		}
		else {
			NodePtr temp = m_Head;
			while (temp) {
				if (temp->next == m_Tail) {
					break;
				}
			}
			delete m_Tail;
			m_Tail = temp;
			m_Tail->next = nullptr;
		}
	}

	void PopFront()
	{
		if (m_Head == nullptr) {
			return;
		}

		if (m_Head == m_Tail) {
			delete m_Head;
			m_Head = nullptr;
			m_Tail = nullptr;
		}
		else {
			NodePtr temp = m_Head;
			m_Head = m_Head->next;
			delete temp;
		}
	}

	bool Insert(size_t pos, const T& data)
	{
		if (pos == 0) {
			PushFront(data);
		} 
		else {
			if (m_Head == nullptr) {
				return false;
			}

			NodePtr temp = m_Head;
			while (--pos && temp != nullptr) {
				temp = temp->next;
			}

			if (pos > 0) {
				return false;
			}
			
			if (pos == 0 && temp == nullptr) {
				// pos in the last of list
				PushBack(data);
			}
			else {
				// pos is in the middle of the list
				NodePtr tempNext = temp->next;
				temp->next = new Node(data);
				temp->next->next = tempNext;
			}
		}

		return true; 
	}

	bool Insert(const NodePtr posPtr, const T& data)
	{
		NodePtr temp = m_Head;
		NodePtr prev;
		while (temp != nullptr && temp != posPtr) {
			prev = temp;
			temp = temp->next;
		}

		if (temp == nullptr) {
			return false;
		}

		prev->next = new Node(data);
		prev->next = temp;

		return true;
	}

	bool Erase(const size_t pos)
	{
		if (m_Head == nullptr) {
			return false;
		}
	
		if (pos == 0) {
			PopFront();
			return true;
		}

		NodePtr temp = m_Head;
		NodePtr prev;
		while (pos && temp != nullptr) {
			--pos;
			prev = temp;
			temp = temp->next;
		}

		if (pos) {
			return false;
		}

		if (temp == m_Tail) {
			PopBack();
		}
		else
		{
			prev->next = temp->next;
			delete temp;
		}

		return true;
	}

	// after this functin, posPtr becomes invalid
	bool Erase(const NodePtr posPtr)
	{
		if (posPtr == m_Head) {
			PopFront();
			return true;
		}

		if (posPtr == m_Tail) {
			PopBack();
			return true;
		}

		NodePtr temp = m_Head;
		while (temp) {
			if (temp->next == posPtr) {
				temp->next = temp->next->next;
				delete posPtr;
				return true;
			}
		}

		return false;
	}

	ptrdiff_t Find(const T& data)
	{
		NodePtr temp = m_Head;
		ptrdiff_t pos = 0;

		while (temp) {
			if (temp->data == data) {
				return pos;
			}
			++pos;
			temp = temp->next;
		}

		return -1;
	}

	void Reverse()
	{
		NodePtr tempHead = nullptr;
		NodePtr temp;
		m_Tail = m_Head;
		while (m_Head != nullptr) {
			temp = m_Head->next;
			m_Head->next = tempHead;
			tempHead = m_Head;
			m_Head = temp;
		}

		m_Head = tempHead;
		return;
	}

	void Reverse_Recursive()
	{

	}

	void MergeSort()
	{
		if (m_Head == nullptr) {
			return;
		}

		// sort
		MergeSortInternal(&m_Head);

		// reset m_Tail
		m_Tail = m_Head;
		while (m_Tail->next != nullptr) {
			m_Tail = m_Tail->next;
		}

		return;
	}

	NodePtr SortedMerge(NodePtr l1, NodePtr l2)
	{
		Node temp;
		NodePtr result = &temp;
		while (l1 != nullptr || l2 != nullptr) {
			if (l1 == nullptr) {
				result->next = l2;
				return temp.next;
			}
			if (l2 == nullptr) {
				result->next = l1;
				return temp.next;
			}

			if (l1->data <= l2->data) {
				result->next = l1;
				l1 = l1->next;
				result = result->next;
			}
			else {
				result->next = l2;
				l2 = l2->next;
				result = result->next;
			}
		}

		return temp.next;
	}

	NodePtr SortedMerge_Recursive(NodePtr l1, NodePtr l2)
	{
		if (l1 == nullptr) {
			return l2;
		}
		if (l2 == nullptr) {
			return l1;
		}

		// otherwise merge them together
		NodePtr result;
		if (l1->data <= l2->data) {
			result = l1;
			result->next = SortedMerge_Recursive(l1->next, l2);
		}
		else
		{
			reslut = l2;
			result->next = SortedMerge_Recursive(l1, l2->next);
		}

		return result;
	}


	/*
	 * Has to work on a sorted linkedlist
	 */
	void RemoveDuplicates()
	{
		if (m_Head == nullptr){
			return;
		}
		
		NodePtr curVal = m_Head;
		NodePtr nextVal = curVal->next;
		NodePtr temp;
		while (nextVal) {
			if (curVal->data == nextVal->data) {
				temp = nextVal;
				curVal->next = nextVal->next;
				nextVal = nextVal->next;
				delete temp;
			}
			else {
				curVal = nextVal;
				nextVal = nextVal->next;
			}
		}
	}

	void DeleteList()
	{
		NodePtr cur = m_Head;
		NodePtr temp;

		while (cur) {
			temp = cur;
			cur = cur->next;
			delete temp;
		}

		m_Head = m_Tail = nullptr;
	}

	bool GetNth(size_t n, T& t) 
	{
		NodePtr temp = m_Head;
		while (n > 0 && temp != nullptr) {
			temp = temp->next;
			--n;
		}

		if (n > 0 || temp == nullptr) {
			return false;
		}
		t = temp->data;
		return true;
	}

	void Print(std::ostream& os)
	{
		NodePtr temp = m_Head;
		while (temp != nullptr) {
			os << temp->data;
			temp = temp->next;
		}
	}

private:

	void MergeSortInternal(NodePtr* src)
	{
		NodePtr tempSrc = *src;
		if (tempSrc == nullptr || tempSrc->next == nullptr) {
			return;
		}

		NodePtr front = nullptr;
		NodePtr back = nullptr;
		FrontBackSplit(tempSrc, &front, &back);
		MergeSortInternal(&front);
		MergeSortInternal(&back);
		*src = SortedMerge(front, back);
	}

	
	
	void FrontBackSplit(NodePtr src, NodePtr* front, NodePtr* back)
	{
		if (src == nullptr) {
			*front = nullptr;
			*back = nullptr;
			return;
		}

		NodePtr slow = src;
		NodePtr fast = src->next;
		while (fast) {
			fast = fast->next;
			if (fast != nullptr) {
				fast = fast->next;
				slow = slow->next;
			}
		}

		// break into two linkedlists
		*front = src;
		*back = slow->next;
		slow->next = nullptr;
	}

	NodePtr* Reverse_Recursive_Internal(NodePtr* ll)
	{

	}

	NodePtr m_Head = nullptr;
	NodePtr m_Tail = nullptr;
};

#endif


