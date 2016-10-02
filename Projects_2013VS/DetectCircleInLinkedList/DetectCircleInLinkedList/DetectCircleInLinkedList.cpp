// DetectCircleInLinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "LinkedList.h"
#include "LinkedListAlgo.h"
#include "LinkedListAlgoCPP.h"
#include "LinkedListCircleDetect.h"
#include "LinkedListContainer.h"
#include "LinkedListElement.h"
#include "LinkedListLongestPalindrome.h"
#include "LinkedListPalindromeDetector.h"
#include "LinkedListSort.h"

#include <iostream>
#include <cassert>

void TestLinkedList_1()
{
	LinkedList<int> myLL;
	myLL.PushBack(1);
	myLL.PushBack(2);
	myLL.PushFront(3);
	myLL.PushFront(4);
	myLL.PushFront(2);
	myLL.Print(std::cout);

	int x;
	assert(myLL.GetNth(0, x) == true);
	assert(x == 2);
	assert(myLL.GetNth(1, x) == true);
	assert(x == 4);
	assert(myLL.GetNth(2, x) == true);
	assert(x == 3);
	assert(myLL.GetNth(3, x) == true);
	assert(x == 1);
	assert(myLL.GetNth(4, x) == true);
	assert(x == 2);
	assert(myLL.GetNth(5, x) == false);

	// 2, 4, 3, 1, 2
	myLL.MergeSort();
	assert(myLL.GetNth(0, x) == true);
	assert(x == 1);
	assert(myLL.GetNth(1, x) == true);
	assert(x == 2);
	assert(myLL.GetNth(2, x) == true);
	assert(x == 2);
	assert(myLL.GetNth(3, x) == true);
	assert(x == 3);
	assert(myLL.GetNth(4, x) == true);
	assert(x == 4);
	assert(myLL.GetNth(5, x) == false);

	myLL.Reverse();
	assert(myLL.GetNth(0, x) == true);
	assert(x == 4);
	assert(myLL.GetNth(1, x) == true);
	assert(x == 3);
	assert(myLL.GetNth(2, x) == true);
	assert(x == 2);
	assert(myLL.GetNth(3, x) == true);
	assert(x == 2);
	assert(myLL.GetNth(4, x) == true);
	assert(x == 1);
	assert(myLL.GetNth(5, x) == false);
}

void TestLinkedListAlgo()
{
	LinkedListElement<int>* head = nullptr;

	// construct list: 20, 12, 10, 9, 9, 8, 7, 15
	LL_PushFront(&head, 9);
	LL_PushFront(&head, 10);
	LL_PushFront(&head, 12);
	LL_PushBack(&head, 9);
	LL_PushBack(&head, 8);
	LL_PushBack(&head, 7);
	LL_PushBack(&head, 15);
	LL_PushFront(&head, 20);

	assert(LL_GetSize(head) == 8);
	int val;
	assert(LL_GetNth(head, 0, val) == true);
	assert(val == 20);
	assert(LL_GetNth(head, 1, val) == true);
	assert(val == 12);
	assert(LL_GetNth(head, 2, val) == true);
	assert(val == 10);
	assert(LL_GetNth(head, 3, val) == true);
	assert(val == 9);
	assert(LL_GetNth(head, 4, val) == true);
	assert(val == 9);
	assert(LL_GetNth(head, 5, val) == true);
	assert(val == 8);
	assert(LL_GetNth(head, 6, val) == true);
	assert(val == 7);
	assert(LL_GetNth(head, 7, val) == true);
	assert(val == 15);
	assert(LL_GetNth(head, 8, val) == false);

	LL_PopFront(&head);
	assert(LL_GetSize(head) == 7); // 12, 10, 9, 9, 8, 7, 15
	LL_PopBack(&head);
	assert(LL_GetSize(head) == 6); // 12, 10, 9, 9, 8, 7
	LL_Delete(&head);

	// constuct list: 18, 25, 30, 11, 10, 9, 5, 20
	LL_PushBack(&head, 10);
	LL_PushBack(&head, 9);
	LL_PushBack(&head, 5);
	LL_PushBack(&head, 20);
	LL_PushFront(&head, 11);
	LL_PushFront(&head, 30);
	LL_PushFront(&head, 25);
	LL_PushFront(&head, 18);

	assert(LL_GetSize(head) == 8);
	
	assert(LL_Insert(&head, 0, 40) == true); // 40, 18, 25, 30, 11, 10, 9, 5, 20
	assert(LL_GetSize(head) == 9);
	assert(LL_GetNth(head, 0, val) == true);
	assert(val = 40);
	assert(LL_Insert(&head, 10, 50) == false);
	assert(LL_GetSize(head) == 9);
	assert(LL_Insert(&head, 9, 50) == true); // 40, 18, 25, 30, 11, 10, 9, 5, 20, 50
	assert(LL_GetSize(head) == 10);
	assert(LL_GetNth(head, 9, val) == true);
	assert(val == 50);
	assert(LL_Insert(&head, 3, 100) == true); // 40, 18, 25, 100, 30, 11, 10, 9, 5, 20, 50
	assert(LL_GetSize(head) == 11);
	assert(LL_GetNth(head, 3, val) == true);
	assert(val == 100);

	LinkedListElement<int>* elemPtr = LL_GetNth(head, 2); // index starts from 0
	assert(elemPtr != nullptr);
	assert(elemPtr->data == 25);
	assert(LL_GetNth(head, 11) == nullptr);
	elemPtr = LL_GetNth(head, 9);
	assert(elemPtr != nullptr);
	assert(elemPtr->data == 20);
	assert(LL_Insert(&head, elemPtr, 70) == true); // 40, 18, 25, 100, 30, 11, 10, 9, 5, 70, 20, 50
	assert(LL_GetSize(head) == 12);
	elemPtr = LL_GetNth(head, 9);
	assert(elemPtr != nullptr);
	assert(elemPtr->data == 70);
	assert(LL_GetNth(head, 3, val) == true);
	assert(val == 100);
	assert(LL_GetNth(head, 12, val) == false);
	assert(LL_GetSize(head) == 12);

	assert(LL_Erase(&head, 0) == true); // 18, 25, 100, 30, 11, 10, 9, 5, 70, 20, 50
	assert(LL_GetSize(head) == 11);
	elemPtr = LL_GetNth(head, 0);
	assert(elemPtr != nullptr);
	assert(elemPtr->data == 18);
	elemPtr = LL_GetNth(head, 10);
	assert(elemPtr != nullptr);
	assert(elemPtr->data == 50);
	assert(LL_Erase(&head, elemPtr)); // 18, 25, 100, 30, 11, 10, 9, 5, 70, 20
	assert(LL_GetSize(head) == 10);
	assert(LL_GetNth(head, 10, val) == false);
	assert(LL_GetNth(head, 9, val) == true);
	assert(val == 20);

	LL_PopFront(&head); // 25, 100, 30, 11, 10, 9, 5, 70, 20
	assert(LL_GetSize(head) == 9);
	elemPtr = LL_GetNth(head, 0);
	assert(elemPtr != nullptr);
	assert(elemPtr->data == 25);
	LL_PopBack(&head); // 25, 100, 30, 11, 10, 9, 5, 70
	assert(LL_GetSize(head) == 8);
	assert(LL_GetNth(head, 8, val) == false);
	assert(LL_GetNth(head, 7, val) == true);
	assert(val == 70);

	LL_Reverse(&head); // 70, 5, 9, 10, 11, 30, 100, 25
	assert(LL_GetSize(head) == 8);
	assert(LL_GetNth(head, 0, val) == true);
	assert(val == 70);
	assert(LL_GetNth(head, 1, val) == true);
	assert(val == 5);
	assert(LL_GetNth(head, 2, val) == true);
	assert(val == 9);
	assert(LL_GetNth(head, 3, val) == true);
	assert(val == 10);
	assert(LL_GetNth(head, 4, val) == true);
	assert(val == 11);
	assert(LL_GetNth(head, 5, val) == true);
	assert(val == 30);
	assert(LL_GetNth(head, 6, val) == true);
	assert(val == 100);
	assert(LL_GetNth(head, 7, val) == true);
	assert(val == 25);

	assert(LL_Insert(&head, 2, 10) == true); // 70, 5, 10, 9, 10, 11, 30, 100, 25
	ptrdiff_t pos = LL_Find(head, 70);
	assert(pos == 0);
	pos = LL_Find(head, 25);
	assert(pos == 8);
	pos = LL_Find(head, 30);
	assert(pos == 6);
	pos = LL_Find(head, 10);
	assert(pos == 2);
	pos = LL_Find(head, 2, 10);
	assert(pos == 0);
	pos = LL_Find(head, 3, 10);
	assert(pos == 1);
	pos = LL_Find(head, 50);
	assert(pos == -1);


	LL_Delete(&head);
	assert(head == nullptr);
	assert(LL_GetSize(head) == 0);
}

void TestLinkedListSort()
{
    LinkedListElement<int>* head1 = nullptr;
    // construct list: 10, 9, 20, 8, 7, 7, 20, 30, 50, 20, 4, 3,
    LL_PushFront(&head1, 3);
    LL_PushFront(&head1, 4);
    LL_PushFront(&head1, 20);
    LL_PushFront(&head1, 50);
    LL_PushFront(&head1, 30);
    LL_PushFront(&head1, 20);
    LL_PushFront(&head1, 7);
    LL_PushFront(&head1, 7);
    LL_PushFront(&head1, 8);
    LL_PushFront(&head1, 20);
    LL_PushFront(&head1, 9);
    LL_PushFront(&head1, 10);
    assert(LL_GetSize(head1) == 12);

    LinkedListElement<int>* head2 = nullptr;
    // const list: 12, 17, 56, 19, 18, 10, 9, 12, 6, 8, 10
    LL_PushFront(&head2, 10);
    LL_PushFront(&head2, 8);
    LL_PushFront(&head2, 6);
    LL_PushFront(&head2, 12);
    LL_PushFront(&head2, 9);
    LL_PushFront(&head2, 10);
    LL_PushFront(&head2, 18);
    LL_PushFront(&head2, 19);
    LL_PushFront(&head2, 56);
    LL_PushFront(&head2, 17);
    LL_PushFront(&head2, 12);
    assert(LL_GetSize(head2) == 11);

    LL_MergeSort(&head1); // 3, 4, 7, 7, 8, 9, 10, 20, 20, 20, 30, 50

    int val;
    assert(LL_GetNth(head1, 0, val) == true);
    assert(val == 3);
    assert(LL_GetNth(head1, 1, val) == true);
    assert(val == 4);
    assert(LL_GetNth(head1, 2, val) == true);
    assert(val == 7);
    assert(LL_GetNth(head1, 3, val) == true);
    assert(val == 7);
    assert(LL_GetNth(head1, 4, val) == true);
    assert(val == 8);
    assert(LL_GetNth(head1, 5, val) == true);
    assert(val == 9);
    assert(LL_GetNth(head1, 6, val) == true);
    assert(val == 10);
    assert(LL_GetNth(head1, 7, val) == true);
    assert(val == 20);
    assert(LL_GetNth(head1, 8, val) == true);
    assert(val == 20);
    assert(LL_GetNth(head1, 9, val) == true);
    assert(val == 20);
    assert(LL_GetNth(head1, 10, val) == true);
    assert(val == 30);
    assert(LL_GetNth(head1, 11, val) == true);
    assert(val == 50);
    assert(LL_GetNth(head1, 12, val) == false);

    LL_MergeSort(&head2); // 6, 8, 9, 10, 10, 12, 12, 17, 18, 19, 56
    assert(LL_GetNth(head2, 0, val) == true);
    assert(val == 6);
    assert(LL_GetNth(head2, 1, val) == true);
    assert(val == 8);
    assert(LL_GetNth(head2, 2, val) == true);
    assert(val == 9);
    assert(LL_GetNth(head2, 3, val) == true);
    assert(val == 10);
    assert(LL_GetNth(head2, 4, val) == true);
    assert(val == 10);
    assert(LL_GetNth(head2, 5, val) == true);
    assert(val == 12);
    assert(LL_GetNth(head2, 6, val) == true);
    assert(val == 12);
    assert(LL_GetNth(head2, 7, val) == true);
    assert(val == 17);
    assert(LL_GetNth(head2, 8, val) == true);
    assert(val == 18);
    assert(LL_GetNth(head2, 9, val) == true);
    assert(val == 19);
    assert(LL_GetNth(head2, 10, val) == true);
    assert(val == 56);
    assert(LL_GetNth(head2, 11, val) == false);

    LinkedListElement<int>* front = nullptr;
    LinkedListElement<int>* back = nullptr;
    LL_FrontBackSplit(head1, &front, &back);
    assert(front == head1);
    assert(back->data == 10);
    assert(LL_GetSize(front) == 6);
    assert(LL_GetSize(back) == 6);
    head1 = LL_SortedMerge(front, back); // 3, 4, 7, 7, 8, 9, 10, 20, 20, 20, 30, 50
    assert(LL_GetSize(head1) == 12);
    assert(LL_GetNth(head1, 0, val) == true);
    assert(val == 3);
    assert(LL_GetNth(head1, 1, val) == true);
    assert(val == 4);
    assert(LL_GetNth(head1, 2, val) == true);
    assert(val == 7);
    assert(LL_GetNth(head1, 3, val) == true);
    assert(val == 7);
    assert(LL_GetNth(head1, 4, val) == true);
    assert(val == 8);
    assert(LL_GetNth(head1, 5, val) == true);
    assert(val == 9);
    assert(LL_GetNth(head1, 6, val) == true);
    assert(val == 10);
    assert(LL_GetNth(head1, 7, val) == true);
    assert(val == 20);
    assert(LL_GetNth(head1, 8, val) == true);
    assert(val == 20);
    assert(LL_GetNth(head1, 9, val) == true);
    assert(val == 20);
    assert(LL_GetNth(head1, 10, val) == true);
    assert(val == 30);
    assert(LL_GetNth(head1, 11, val) == true);
    assert(val == 50);
    assert(LL_GetNth(head1, 12, val) == false);

    LL_FrontBackSplit(head2, &front, &back); // 6, 8, 9, 10, 10, 12, 12, 17, 18, 19, 56
    assert(front == head2);
    assert(back->data == 12);
    assert(LL_GetSize(front) == 6);
    assert(LL_GetSize(back) == 5);
    head2 = LL_SortedMergeRecursively(front, back);
    assert(LL_GetNth(head2, 0, val) == true);
    assert(val == 6);
    assert(LL_GetNth(head2, 1, val) == true);
    assert(val == 8);
    assert(LL_GetNth(head2, 2, val) == true);
    assert(val == 9);
    assert(LL_GetNth(head2, 3, val) == true);
    assert(val == 10);
    assert(LL_GetNth(head2, 4, val) == true);
    assert(val == 10);
    assert(LL_GetNth(head2, 5, val) == true);
    assert(val == 12);
    assert(LL_GetNth(head2, 6, val) == true);
    assert(val == 12);
    assert(LL_GetNth(head2, 7, val) == true);
    assert(val == 17);
    assert(LL_GetNth(head2, 8, val) == true);
    assert(val == 18);
    assert(LL_GetNth(head2, 9, val) == true);
    assert(val == 19);
    assert(LL_GetNth(head2, 10, val) == true);
    assert(val == 56);
    assert(LL_GetNth(head2, 11, val) == false);

    // 810, 9, 8
    LinkedListElement<int>* intersect = LL_SortedIntersect(head1, head2);
    assert(LL_GetSize(intersect) == 3);
    assert(LL_GetNth(intersect, 0, val) == true);
    assert(val == 10);
    assert(LL_GetNth(intersect, 1, val) == true);
    assert(val == 9);
    assert(LL_GetNth(intersect, 2, val) == true);
    assert(val == 8);
    assert(LL_GetNth(intersect, 3, val) == false);
    LL_Delete(&intersect);
	

    // 3, 4, 6, 7, 7, 8, 8, 9, 9, 10, 10, 10, 12, 12, 17, 18, 19, 20, 20, 20, 30, 50, 56
    LinkedListElement<int>* head = LL_SortedMergeRecursively(head1, head2);
    assert(LL_GetSize(head) == 23);
    assert(LL_GetNth(head, 0, val) == true);
    assert(val == 3);
    assert(LL_GetNth(head, 1, val) == true);
    assert(val == 4);
    assert(LL_GetNth(head, 2, val) == true);
    assert(val == 6);
    assert(LL_GetNth(head, 3, val) == true);
    assert(val == 7);
    assert(LL_GetNth(head, 4, val) == true);
    assert(val == 7);
    assert(LL_GetNth(head, 5, val) == true);
    assert(val == 8);
    assert(LL_GetNth(head, 6, val) == true);
    assert(val == 8);
    assert(LL_GetNth(head, 7, val) == true);
    assert(val == 9);
    assert(LL_GetNth(head, 8, val) == true);
    assert(val == 9);
    assert(LL_GetNth(head, 9, val) == true);
    assert(val == 10);
    assert(LL_GetNth(head, 10, val) == true);
    assert(val == 10);
    assert(LL_GetNth(head, 11, val) == true);
    assert(val == 10);
    assert(LL_GetNth(head, 12, val) == true);
    assert(val == 12);
    assert(LL_GetNth(head, 13, val) == true);
    assert(val == 12);
    assert(LL_GetNth(head, 14, val) == true);
    assert(val == 17);
    assert(LL_GetNth(head, 15, val) == true);
    assert(val == 18);
    assert(LL_GetNth(head, 16, val) == true);
    assert(val == 19);
    assert(LL_GetNth(head, 17, val) == true);
    assert(val == 20);
    assert(LL_GetNth(head, 18, val) == true);
    assert(val == 20);
    assert(LL_GetNth(head, 19, val) == true);
    assert(val == 20);
    assert(LL_GetNth(head, 20, val) == true);
    assert(val == 30);
    assert(LL_GetNth(head, 21, val) == true);
    assert(val == 50);
    assert(LL_GetNth(head, 22, val) == true);
    assert(val == 56);
    assert(LL_GetNth(head, 23, val) == false);

    // 3, 4, 6, 7, 8, 9, 10, 12, 17, 18, 19, 20, 30, 50, 56
    LL_RemoveDuplicates(&head);
    assert(LL_GetSize(head) == 15);
    assert(LL_GetNth(head, 0, val) == true);
    assert(val == 3);
    assert(LL_GetNth(head, 1, val) == true);
    assert(val == 4);
    assert(LL_GetNth(head, 2, val) == true);
    assert(val == 6);
    assert(LL_GetNth(head, 3, val) == true);
    assert(val == 7);
    assert(LL_GetNth(head, 4, val) == true);
    assert(val == 8);
    assert(LL_GetNth(head, 5, val) == true);
    assert(val == 9);
    assert(LL_GetNth(head, 6, val) == true);
    assert(val == 10);
    assert(LL_GetNth(head, 7, val) == true);
    assert(val == 12);
    assert(LL_GetNth(head, 8, val) == true);
    assert(val == 17);
    assert(LL_GetNth(head, 9, val) == true);
    assert(val == 18);
    assert(LL_GetNth(head, 10, val) == true);
    assert(val == 19);
    assert(LL_GetNth(head, 11, val) == true);
    assert(val == 20);
    assert(LL_GetNth(head, 12, val) == true);
    assert(val == 30);
    assert(LL_GetNth(head, 13, val) == true);
    assert(val == 50);
    assert(LL_GetNth(head, 14, val) == true);
    assert(val == 56);
    assert(LL_GetNth(head, 15, val) == false);

    assert(LL_SortedInsert(&head, 1) == true);
    assert(LL_GetSize(head) == 16); // 1, 3, 4, 6, 7, 8, 9, 10, 12, 17, 18, 19, 20, 30, 50, 56
    assert(LL_Find(head, 1) == 0);
    assert(LL_SortedInsert(&head, 60) == true); // 1, 3, 4, 6, 7, 8, 9, 10, 12, 17, 18, 19, 20, 30, 50, 56, 60
    assert(LL_GetSize(head) == 17);
    assert(LL_Find(head, 60) == 16); 
    assert(LL_SortedInsert(&head, 10)); // 1, 3, 4, 6, 7, 8, 9, 10, 10, 12, 17, 18, 19, 20, 30, 50, 56, 60
    ptrdiff_t pos = LL_Find(head, 10);
    assert(pos == 7);
    pos = LL_Find(head, pos + 1, 10);
    assert(pos == 0);

    LL_Delete(&head);
}

void TestLinkedListCircleDetector()
{
    LinkedListElement<int>* head = nullptr;

    // empty list
    assert(LL_GetOneOfNodesInCircleIfExists(head) == nullptr);
    assert(LL_CheckIfCircleExists(head) == false);
    assert(LL_GetCircleSizeIfExists(head) == 0);
    assert(LL_DetectTheLastNodeOfCircleIfExists(head) == nullptr);
    assert(LL_RemoveCircleIfExists(&head) == false);

    LL_PushFront(&head, 11);
    LinkedListElement<int>* tail = head;

    // point to itself
    tail->next = head;
    assert(LL_GetOneOfNodesInCircleIfExists(head) != nullptr);
    assert(LL_CheckIfCircleExists(head) == true);
    assert(LL_GetCircleSizeIfExists(head) == 1);
    assert(LL_DetectTheLastNodeOfCircleIfExists(head) == tail);
    assert(LL_RemoveCircleIfExists(&head) == true);
    assert(head->next == nullptr);
    assert(head->data == 11);

    // construct 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
    LL_PushFront(&head, 10);
    LL_PushFront(&head, 9);
    LL_PushFront(&head, 8);
    LL_PushFront(&head, 7);
    LL_PushFront(&head, 6);
    LL_PushFront(&head, 5);
    LL_PushFront(&head, 4);
    LL_PushFront(&head, 3);
    LL_PushFront(&head, 2);
    LL_PushFront(&head, 1);
    LL_PushFront(&head, 12);

    assert(LL_GetOneOfNodesInCircleIfExists(head) == nullptr);
    assert(LL_CheckIfCircleExists(head) == false);
    assert(LL_GetCircleSizeIfExists(head) == 0);
    assert(LL_DetectTheLastNodeOfCircleIfExists(head) == nullptr);
    assert(LL_RemoveCircleIfExists(&head) == false);

    // setup the circle
    tail->next = head;
    assert(LL_GetOneOfNodesInCircleIfExists(head) != nullptr);
    assert(LL_CheckIfCircleExists(head) == true);
    assert(LL_GetCircleSizeIfExists(head) == 12);
    assert(LL_DetectTheLastNodeOfCircleIfExists(head) == tail);
    assert(LL_RemoveCircleIfExists(&head) == true);
    assert(tail->next == nullptr);
    assert(LL_GetSize(head) == 12);
    int val;
    assert(LL_GetNth(head, 12, val) == false);

    // setup the circle
    tail->next = head;
    LL_PushFront(&head, 20);
    LL_PushFront(&head, 30);
    LL_PushFront(&head, 40);
    LL_PushFront(&head, 50);
    LL_PushFront(&head, 60);
    LL_PushFront(&head, 70);
    assert(LL_GetOneOfNodesInCircleIfExists(head) != nullptr);
    assert(LL_CheckIfCircleExists(head) == true);
    assert(LL_GetCircleSizeIfExists(head) == 12);
    assert(LL_DetectTheLastNodeOfCircleIfExists(head) == tail);
    assert(LL_RemoveCircleIfExists(&head) == true);
    assert(tail->next == nullptr);
    assert(LL_GetSize(head) == 18);
    assert(LL_GetNth(head, 18, val) == false);

    LL_Delete(&head);
}

void TestLinkedListContainer()
{
    LinkedListContainer<int> myLLC;

    myLLC.PushFront(10);
    assert(myLLC.GetSize() == 1);
    myLLC.PushBack(20);
    assert(myLLC.GetSize() == 2);
    int val;
    assert(myLLC.GetNth(0, val) == true);
    assert(val == 10);
    assert(myLLC.GetNth(1, val) == true);
    assert(val == 20);
    myLLC.PushFront(30);
    assert(myLLC.GetSize() == 3);
    assert(myLLC.GetNth(0, val) == true);
    assert(val == 30);
    myLLC.PopFront();
    assert(myLLC.GetSize() == 2);
    assert(myLLC.GetNth(0, val) == true);
    assert(val == 10);
    myLLC.PopBack();
    assert(myLLC.GetSize() == 1);
    assert(myLLC.GetNth(0, val) == true);
    assert(val == 10);
    myLLC.PopFront();
    assert(myLLC.GetSize() == 0);
    assert(myLLC.GetNth(0, val) == false);

    myLLC.PushBack(40);
    assert(myLLC.GetSize() == 1);
    assert(myLLC.GetNth(0, val) == true);
    assert(val == 40);
    myLLC.PushFront(50);
    assert(myLLC.GetSize() == 2);
    assert(myLLC.GetNth(0, val) == true);
    assert(val == 50);
    myLLC.PopFront();
    assert(myLLC.GetNth(0, val) == true);
    assert(val == 40);
    myLLC.PopBack();
    assert(myLLC.GetSize() == 0);

    assert(myLLC.Insert(2, 30) == false);
    assert(myLLC.GetSize() == 0);
    assert(myLLC.Insert((size_t)0, 30) == true);
    assert(myLLC.GetSize() == 1);
    assert(myLLC.GetNth(0, val) == true);
    assert(val == 30);
    myLLC.PushBack(40);
    assert(myLLC.GetSize() == 2);
    assert(myLLC.GetNth(1, val) == true);
    assert(val == 40);
    myLLC.PopFront();
    myLLC.PopFront();
    assert(myLLC.GetSize() == 0);

    // construct 9, 12, 10, 3, 20, 18, 10, 40
    myLLC.PushFront(3);
    myLLC.PushFront(10);
    myLLC.PushFront(12);
    myLLC.PushFront(9);
    myLLC.PushBack(20);
    myLLC.PushBack(18);
    myLLC.PushBack(10);
    myLLC.PushBack(40);

    assert(myLLC.GetSize() == 8);
    assert(myLLC.GetNth(0, val) == true);
    assert(val == 9);
    assert(myLLC.GetNth(1, val) == true);
    assert(val == 12);
    assert(myLLC.GetNth(2, val) == true);
    assert(val == 10);
    assert(myLLC.GetNth(3, val) == true);
    assert(val == 3);
    assert(myLLC.GetNth(4, val) == true);
    assert(val == 20);
    assert(myLLC.GetNth(5, val) == true);
    assert(val == 18);
    assert(myLLC.GetNth(6, val) == true);
    assert(val == 10);
    assert(myLLC.GetNth(7, val) == true);
    assert(val == 40);
    assert(myLLC.GetNth(8, val) == false);

    // construct 9, 12, 10, 3, 20, 18, 10, 40
    // 3, 9, 10, 10, 12, 18,20, 40
    myLLC.MergeSort();
    assert(myLLC.GetSize() == 8);
    assert(myLLC.GetNth(0, val) == true);
    assert(val == 3);
    assert(myLLC.GetNth(1, val) == true);
    assert(val == 9);
    assert(myLLC.GetNth(2, val) == true);
    assert(val == 10);
    assert(myLLC.GetNth(3, val) == true);
    assert(val == 10);
    assert(myLLC.GetNth(4, val) == true);
    assert(val == 12);
    assert(myLLC.GetNth(5, val) == true);
    assert(val == 18);
    assert(myLLC.GetNth(6, val) == true);
    assert(val == 20);
    assert(myLLC.GetNth(7, val) == true);
    assert(val == 40);
    assert(myLLC.GetNth(8, val) == false);

    assert(myLLC.Erase(8) == false);
    // 3, 9, 10, 10, 12, 18, 20
    assert(myLLC.Erase(7) == true);
    // 9, 10, 10, 12, 18, 20
    assert(myLLC.Erase((size_t)0) == true);
    // 9, 10, 10, 18, 20
    assert(myLLC.Erase(3) == true);
    assert(myLLC.GetSize() == 5);
    assert(myLLC.GetNth(0, val) == true);
    assert(val == 9);
    assert(myLLC.GetNth(1, val) == true);
    assert(val == 10);
    assert(myLLC.GetNth(2, val) == true);
    assert(val == 10);
    assert(myLLC.GetNth(3, val) == true);
    assert(val == 18);
    assert(myLLC.GetNth(4, val) == true);
    assert(val == 20);
    assert(myLLC.GetNth(5, val) == false);

    // 9, 10, 18, 20
    myLLC.RemoveDuplicates();
    assert(myLLC.GetSize() == 4);
    assert(myLLC.GetNth(0, val) == true);
    assert(val == 9);
    assert(myLLC.GetNth(1, val) == true);
    assert(val == 10);
    assert(myLLC.GetNth(2, val) == true);
    assert(val == 18);
    assert(myLLC.GetNth(3, val) == true);
    assert(val == 20);
    assert(myLLC.GetNth(5, val) == false);

    // 20, 9, 10, 18, 20
    assert(myLLC.Insert((size_t)0, 20) == true);
    // 20, 9, 10, 18, 9, 20
    assert(myLLC.Insert(4, 9) == true);
    // 20, 9, 10, 18, 9, 20, 18
    assert(myLLC.Insert(6, 18));
    assert(myLLC.GetSize() == 7);
    assert(myLLC.GetNth(0, val) == true);
    assert(val == 20);
    assert(myLLC.GetNth(1, val) == true);
    assert(val == 9);
    assert(myLLC.GetNth(2, val) == true);
    assert(val == 10);
    assert(myLLC.GetNth(3, val) == true);
    assert(val == 18);
    assert(myLLC.GetNth(4, val) == true);
    assert(val == 9);
    assert(myLLC.GetNth(5, val) == true);
    assert(val == 20);
    assert(myLLC.GetNth(6, val) == true);
    assert(val == 18);
    assert(myLLC.GetNth(7, val) == false);

    // 9, 9, 10, 18, 18, 20, 20
    myLLC.MergeSort();
    assert(myLLC.GetSize() == 7);
    assert(myLLC.GetNth(0, val) == true);
    assert(val == 9);
    assert(myLLC.GetNth(1, val) == true);
    assert(val == 9);
    assert(myLLC.GetNth(2, val) == true);
    assert(val == 10);
    assert(myLLC.GetNth(3, val) == true);
    assert(val == 18);
    assert(myLLC.GetNth(4, val) == true);
    assert(val == 18);
    assert(myLLC.GetNth(5, val) == true);
    assert(val == 20);
    assert(myLLC.GetNth(6, val) == true);
    assert(val == 20);
    assert(myLLC.GetNth(7, val) == false);

    // 9, 10, 18, 20
    myLLC.RemoveDuplicates();
    assert(myLLC.GetSize() == 4);
    assert(myLLC.GetNth(0, val) == true);
    assert(val == 9);
    assert(myLLC.GetNth(1, val) == true);
    assert(val == 10);
    assert(myLLC.GetNth(2, val) == true);
    assert(val == 18);
    assert(myLLC.GetNth(3, val) == true);
    assert(val == 20);
    assert(myLLC.GetNth(4, val) == false);

    // const another list 1, 15, 25, 19, 12
    LinkedListContainer<int> myLLC2;
    myLLC2.PushFront(25);
    myLLC2.PushBack(19);
    myLLC2.PushFront(15);
    myLLC2.PushBack(12);
    myLLC2.PushFront(1);
    assert(myLLC2.GetSize() == 5);
    // 1, 12, 15, 19, 25
    myLLC2.MergeSort();
    assert(myLLC2.GetSize() == 5);
    assert(myLLC2.GetNth(0, val) == true);
    assert(val == 1);
    assert(myLLC2.GetNth(1, val) == true);
    assert(val == 12);
    assert(myLLC2.GetNth(2, val) == true);
    assert(val == 15);
    assert(myLLC2.GetNth(3, val) == true);
    assert(val == 19);
    assert(myLLC2.GetNth(4, val) == true);
    assert(val == 25);
    assert(myLLC2.GetNth(5, val) == false);

    // 1, 9, 10, 12, 15, 18, 19, 20, 25
    myLLC.SortedMerge(myLLC2);
    assert(myLLC2.GetSize() == 0);
    assert(myLLC.GetSize() == 9);
    assert(myLLC.GetNth(0, val) == true);
    assert(val == 1);
    assert(myLLC.GetNth(1, val) == true);
    assert(val == 9);
    assert(myLLC.GetNth(2, val) == true);
    assert(val == 10);
    assert(myLLC.GetNth(3, val) == true);
    assert(val == 12);
    assert(myLLC.GetNth(4, val) == true);
    assert(val == 15);
    assert(myLLC.GetNth(5, val) == true);
    assert(val == 18);
    assert(myLLC.GetNth(6, val) == true);
    assert(val == 19);
    assert(myLLC.GetNth(7, val) == true);
    assert(val == 20);
    assert(myLLC.GetNth(8, val) == true);
    assert(val == 25);
    assert(myLLC.GetNth(9, val) == false);
}

void TestLinkedListPalindromeDetectorCase1()
{
    LinkedListElement<char>* head = nullptr;

    assert(LinkedListPalindromeDetector::IsPalindrome(head) == false);
}

void TestLinkedListPalindromeDetectorCase2()
{
    LinkedListElement<char>* head = nullptr;
    LL_PushFront(&head, 'A');

    assert(LinkedListPalindromeDetector::IsPalindrome(head) == true);
}

void TestLinkedListPalindromeDetectorCase3()
{
    LinkedListElement<char>* head = nullptr;
    LL_PushFront(&head, 'A');
    LL_PushFront(&head, 'A');

    assert(LinkedListPalindromeDetector::IsPalindrome(head) == true);
}

void TestLinkedListPalindromeDetectorCase4()
{
    LinkedListElement<char>* head = nullptr;
    LL_PushFront(&head, 'A');
    LL_PushFront(&head, 'B');

    assert(LinkedListPalindromeDetector::IsPalindrome(head) == false);
}

void TestLinkedListPalindromeDetectorCase5()
{
    LinkedListElement<char>* head = nullptr;
    LL_PushFront(&head, 'A');
    LL_PushFront(&head, 'B');
    LL_PushFront(&head, 'C');
    LL_PushFront(&head, 'D');
    LL_PushFront(&head, 'E');
    LL_PushFront(&head, 'E');
    LL_PushFront(&head, 'D');
    LL_PushFront(&head, 'C');
    LL_PushFront(&head, 'B');
    LL_PushFront(&head, 'A');

    assert(LinkedListPalindromeDetector::IsPalindrome(head) == true);
}

void TestLinkedListPalindromeDetectorCase6()
{
    LinkedListElement<char>* head = nullptr;
    LL_PushFront(&head, 'A');
    LL_PushFront(&head, 'B');
    LL_PushFront(&head, 'C');
    LL_PushFront(&head, 'D');
    LL_PushFront(&head, 'E');
    LL_PushFront(&head, 'F');
    LL_PushFront(&head, 'D');
    LL_PushFront(&head, 'C');
    LL_PushFront(&head, 'B');
    LL_PushFront(&head, 'A');

    assert(LinkedListPalindromeDetector::IsPalindrome(head) == false);
}

void TestLinkedListPalindromeDetectorCase7()
{
    LinkedListElement<char>* head = nullptr;
    LL_PushFront(&head, 'A');
    LL_PushFront(&head, 'B');
    LL_PushFront(&head, 'C');
    LL_PushFront(&head, 'D');
    LL_PushFront(&head, 'E');
    LL_PushFront(&head, 'F');
    LL_PushFront(&head, 'E');
    LL_PushFront(&head, 'D');
    LL_PushFront(&head, 'C');
    LL_PushFront(&head, 'B');
    LL_PushFront(&head, 'A');

    assert(LinkedListPalindromeDetector::IsPalindrome(head) == true);
}

void TestLinkedListPalindromeDetectorCase8()
{
    LinkedListElement<char>* head = nullptr;
    LL_PushFront(&head, 'A');
    LL_PushFront(&head, 'B');
    LL_PushFront(&head, 'C');
    LL_PushFront(&head, 'D');
    LL_PushFront(&head, 'E');
    LL_PushFront(&head, 'F');
    LL_PushFront(&head, 'G');
    LL_PushFront(&head, 'D');
    LL_PushFront(&head, 'C');
    LL_PushFront(&head, 'B');
    LL_PushFront(&head, 'A');

    assert(LinkedListPalindromeDetector::IsPalindrome(head) == false);
}

void TestOrderElementsCornerCase()
{
    {
        std::vector<int> testArr;

        LinkedListElement<int>* head = nullptr;
        LL_PushFrontFromStdVector(&head, testArr);
        LL_OrderElementsIntoNegativePositiveSeries(head);

        std::vector<int> result;
        LL_CopyDataToStdVector(head, result);
        assert(result.empty());
    }

    {
        std::vector<int> testArr = { 1 };

        LinkedListElement<int>* head = nullptr;
        LL_PushFrontFromStdVector(&head, testArr);
        LL_OrderElementsIntoNegativePositiveSeries(head);

        std::vector<int> result;
        LL_CopyDataToStdVector(head, result);
        assert(testArr == result);
    }

    {
        std::vector<int> testArr = { 1, -1 };

        LinkedListElement<int>* head = nullptr;
        LL_PushFrontFromStdVector(&head, testArr);
        LL_OrderElementsIntoNegativePositiveSeries(head);

        std::vector<int> result;
        LL_CopyDataToStdVector(head, result);
        assert(testArr == result);
    }
}

void TestOrderElementsCase1()
{
    std::vector<int> testArr = { 2, -1, -3, -7, -8, 9, 5, -5, -7 };
    const std::vector<int> result = { 2, -1, 9, -3, 5, -7, -8, -5, -7 };

    LinkedListElement<int>* head = nullptr;
    LL_PushFrontFromStdVector(&head, testArr);
    LL_OrderElementsIntoNegativePositiveSeries(head);

    std::vector<int> result1;
    LL_CopyDataToStdVector(head, result1);
    assert(result1 == result);
}

void TestOrderElementsCase2()
{
    std::vector<int> testArr = { 2, 9, 5, 3, 2, 1, -1, -3, -7, -8, -5, -7 };
    const std::vector<int> result = { 2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7 };

    LinkedListElement<int>* head = nullptr;
    LL_PushFrontFromStdVector(&head, testArr);
    LL_OrderElementsIntoNegativePositiveSeries(head);

    std::vector<int> result1;
    LL_CopyDataToStdVector(head, result1);
    assert(result1 == result);
}

void TestOrderElementsCase3()
{
    std::vector<int> testArr = { 2, -1, -3, -7, -8, -5, -7, 9, 5, 3, 2, 1 };
    const std::vector<int> result = { 2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7 };

    LinkedListElement<int>* head = nullptr;
    LL_PushFrontFromStdVector(&head, testArr);
    LL_OrderElementsIntoNegativePositiveSeries(head);

    std::vector<int> result1;
    LL_CopyDataToStdVector(head, result1);
    assert(result1 == result);
}

void TestOrderElementsCase4()
{
    std::vector<int> testArr = { 2, -1, -3, -7, 9, 5, 3, 2, 1, -8, -5, -7 };
    const std::vector<int> result = { 2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7 };

    LinkedListElement<int>* head = nullptr;
    LL_PushFrontFromStdVector(&head, testArr);
    LL_OrderElementsIntoNegativePositiveSeries(head);

    std::vector<int> result1;
    LL_CopyDataToStdVector(head, result1);
    assert(result1 == result);
}

void TestOrderElementsCase5()
{
    std::vector<int> testArr = { -1, -3, -7, 2, 9, 5, 3, 2, 1, -8, -5, -7 };
    const std::vector<int> result = { -1, 2, -3, 9, -7, 5, -8, 3, -5, 2, -7, 1 };

    LinkedListElement<int>* head = nullptr;
    LL_PushFrontFromStdVector(&head, testArr);
    LL_OrderElementsIntoNegativePositiveSeries(head);

    std::vector<int> result1;
    LL_CopyDataToStdVector(head, result1);
    assert(result1 == result);
}

void TestOrderElementsCase6()
{
    std::vector<int> testArr = { -1, -3, -7, -8, -5, -7, 2, 9, 5, 3, 2, 1 };
    const std::vector<int> result = { -1, 2, -3, 9, -7, 5, -8, 3, -5, 2, -7, 1 };

    LinkedListElement<int>* head = nullptr;
    LL_PushFrontFromStdVector(&head, testArr);
    LL_OrderElementsIntoNegativePositiveSeries(head);

    std::vector<int> result1;
    LL_CopyDataToStdVector(head, result1);
    assert(result1 == result);
}

using LinkedListString = LinkedListElement<std::string>;
void TestLinkedListPalindromWithStringCase1()
{
    LinkedListString* head = nullptr;
    assert(LinkedListPalindromeDetector::IsPalindrome(head) == false);
}

void TestLinkedListPalindromWithStringCase2()
{
    LinkedListString* head = nullptr;
    LL_PushFront(&head, std::string("ABCDEFGFEDCBA"));

    assert(LinkedListPalindromeDetector::IsPalindrome(head) == true);

    LL_Delete(&head);
}

void TestLinkedListPalindromWithStringCase3()
{
    LinkedListString* head = nullptr;
    LL_PushFront(&head, std::string("AABCDEFGFEDCBBD"));

    assert(LinkedListPalindromeDetector::IsPalindrome(head) == false);

    LL_Delete(&head);
}

void TestLinkedListPalindromWithStringCase4()
{
    LinkedListString* head = nullptr;
    LL_PushFront(&head, std::string("ABCDEFFEDCBA"));

    assert(LinkedListPalindromeDetector::IsPalindrome(head) == true);

    LL_Delete(&head);
}

void TestLinkedListPalindromWithStringCase5()
{
    LinkedListString* head = nullptr;
    LL_PushFront(&head, std::string("AABCDEFFEDCBAB"));

    assert(LinkedListPalindromeDetector::IsPalindrome(head) == false);

    LL_Delete(&head);
}

void TestLinkedListPalindromWithStringCase6()
{
    LinkedListString* head = nullptr;
    LL_PushFront(&head, std::string("GHIJKJIHGFEDCBA"));
    LL_PushFront(&head, std::string("EF"));
    LL_PushFront(&head, std::string("CD"));
    LL_PushFront(&head, std::string("B"));
    LL_PushFront(&head, std::string("A"));

    assert(LinkedListPalindromeDetector::IsPalindrome(head) == true);

    LL_Delete(&head);
}

void TestLinkedListPalindromWithStringCase7()
{
    LinkedListString* head = nullptr;
    LL_PushFront(&head, std::string("GHIJKJIHGFEDCBA"));
    LL_PushFront(&head, std::string("EF"));
    LL_PushFront(&head, std::string("CD"));
    LL_PushFront(&head, std::string("B"));
    LL_PushFront(&head, std::string("B"));

    assert(LinkedListPalindromeDetector::IsPalindrome(head) == false);

    LL_Delete(&head);
}


void TestLinkedListPalindromWithStringCase8()
{
    LinkedListString* head = nullptr;
    LL_PushFront(&head, std::string("GHIJKJIHGFEDCBA"));
    LL_PushFront(&head, std::string("EF"));
    LL_PushFront(&head, std::string("CD"));
    LL_PushFront(&head, std::string("B"));
    LL_PushFront(&head, std::string("A"));
    LL_PushFront(&head, std::string("A"));

    assert(LinkedListPalindromeDetector::IsPalindrome(head) == false);

    LL_Delete(&head);
}

void TestLinkedListPalindromWithStringCase9()
{
    LinkedListString* head = nullptr;
    LL_PushFront(&head, std::string("XYZ"));
    LL_PushFront(&head, std::string("123"));
    LL_PushFront(&head, std::string("MNLOP"));
    LL_PushFront(&head, std::string("789"));
    LL_PushFront(&head, std::string("AABCDEFFEDCBAA"));
    LL_PushFront(&head, std::string("87"));
    LL_PushFront(&head, std::string("9"));
    LL_PushFront(&head, std::string("LNM"));
    LL_PushFront(&head, std::string("PO"));
    LL_PushFront(&head, std::string("321"));
    LL_PushFront(&head, std::string("ZYX"));

    assert(LinkedListPalindromeDetector::IsPalindrome(head) == true);

    LL_Delete(&head);
}

void TestLinkedListPalindromWithStringCase10()
{
    LinkedListString* head = nullptr;
    LL_PushFront(&head, std::string("XYZ"));
    LL_PushFront(&head, std::string("123"));
    LL_PushFront(&head, std::string("MNLOP"));
    LL_PushFront(&head, std::string("789"));
    LL_PushFront(&head, std::string("AABCDEFGFEDCBAA"));
    LL_PushFront(&head, std::string("87"));
    LL_PushFront(&head, std::string("9"));
    LL_PushFront(&head, std::string("LNM"));
    LL_PushFront(&head, std::string("PO"));
    LL_PushFront(&head, std::string("321"));
    LL_PushFront(&head, std::string("ZYX"));

    assert(LinkedListPalindromeDetector::IsPalindrome(head) == true);

    LL_Delete(&head);
}

void TestLinkedListPalindromWithStringCase11()
{
    LinkedListString* head = nullptr;
    LL_PushFront(&head, std::string("XYZ"));
    LL_PushFront(&head, std::string("123"));
    LL_PushFront(&head, std::string("MNLOP"));
    LL_PushFront(&head, std::string("789"));
    LL_PushFront(&head, std::string("AABCDEFFEDCBAA"));
    LL_PushFront(&head, std::string("87"));
    LL_PushFront(&head, std::string("9"));
    LL_PushFront(&head, std::string("LNM"));
    LL_PushFront(&head, std::string("PO"));
    LL_PushFront(&head, std::string("321"));
    LL_PushFront(&head, std::string("zYX"));

    assert(LinkedListPalindromeDetector::IsPalindrome(head) == false);

    LL_Delete(&head);
}

void TestLinkedListPalindromWithStringCase12()
{
    LinkedListString* head = nullptr;
    LL_PushFront(&head, std::string("XYz"));
    LL_PushFront(&head, std::string("123"));
    LL_PushFront(&head, std::string("MNLOP"));
    LL_PushFront(&head, std::string("789"));
    LL_PushFront(&head, std::string("AABCDEFGFEDCBAA"));
    LL_PushFront(&head, std::string("87"));
    LL_PushFront(&head, std::string("9"));
    LL_PushFront(&head, std::string("LNM"));
    LL_PushFront(&head, std::string("PO"));
    LL_PushFront(&head, std::string("321"));
    LL_PushFront(&head, std::string("ZYX"));

    assert(LinkedListPalindromeDetector::IsPalindrome(head) == false);

    LL_Delete(&head);
}

bool IsFibonaciNumber(int val)
{
    int temp = 5 * val*val;
    int root = static_cast<int>(sqrt(temp - 4));
    if (root*root == (temp - 4)) {
        return true;
    }

    root = static_cast<int>(sqrt(temp + 4));
    if (root*root == (temp + 4)) {
        return true;
    }

    return false;
}

void TestSplitLLAgainstFibonaci()
{
    {
        LinkedListElement<int>* head = nullptr;
        LinkedListElement<int>* fibonaciNodes = nullptr;
        LinkedListElement<int>* nonFibonaciNodes = nullptr;
        LL_SpiltLinkedList<int>(&head, &fibonaciNodes, &nonFibonaciNodes, IsFibonaciNumber);

        assert(fibonaciNodes == nullptr);
        assert(nonFibonaciNodes == nullptr);
    }

    {
        std::vector<int> testArr = { 0, 1, 1, 2, 3, 5, 8 };

        LinkedListElement<int>* head = nullptr;
        LL_PushFrontFromStdVector(&head, testArr);

        LinkedListElement<int>* fibonaciNodes = nullptr;
        LinkedListElement<int>* nonFibonaciNodes = nullptr;
        LL_SpiltLinkedList<int>(&head, &fibonaciNodes, &nonFibonaciNodes, IsFibonaciNumber);

        assert(fibonaciNodes != nullptr);
        assert(nonFibonaciNodes == nullptr);
        assert(head == nullptr);

        std::vector<int> result;
        LL_CopyDataToStdVector(fibonaciNodes, result);
        assert(testArr == result);

        LL_Delete(&fibonaciNodes);
    }

    {
        std::vector<int> testArr = { 4, 6, 7, 9, 10 };

        LinkedListElement<int>* head = nullptr;
        LL_PushFrontFromStdVector(&head, testArr);

        LinkedListElement<int>* fibonaciNodes = nullptr;
        LinkedListElement<int>* nonFibonaciNodes = nullptr;
        LL_SpiltLinkedList<int>(&head, &fibonaciNodes, &nonFibonaciNodes, IsFibonaciNumber);

        assert(fibonaciNodes == nullptr);
        assert(nonFibonaciNodes != nullptr);
        assert(head == nullptr);

        std::vector<int> result;
        LL_CopyDataToStdVector(nonFibonaciNodes, result);
        assert(testArr == result);

        LL_Delete(&nonFibonaciNodes);
    }

    {
        std::vector<int> testArr = { 0, 4, 1, 6, 1, 7, 2, 9, 3, 10, 5, 8 };
        std::vector<int> fibonaciArr = { 0, 1, 1, 2, 3, 5, 8 };
        std::vector<int> nonFibonaciArr = { 4, 6, 7, 9, 10 };

        LinkedListElement<int>* head = nullptr;
        LL_PushFrontFromStdVector(&head, testArr);

        LinkedListElement<int>* fibonaciNodes = nullptr;
        LinkedListElement<int>* nonFibonaciNodes = nullptr;
        LL_SpiltLinkedList<int>(&head, &fibonaciNodes, &nonFibonaciNodes, IsFibonaciNumber);

        assert(fibonaciNodes != nullptr);
        assert(nonFibonaciNodes != nullptr);
        assert(head == nullptr);


        std::vector<int> fibonaciResult;
        LL_CopyDataToStdVector(fibonaciNodes, fibonaciResult);
        assert(fibonaciArr == fibonaciResult);

        std::vector<int> nonFibonaciResult;
        LL_CopyDataToStdVector(nonFibonaciNodes, nonFibonaciResult);
        assert(nonFibonaciArr == nonFibonaciResult);

        LL_Delete(&fibonaciNodes);
        LL_Delete(&nonFibonaciNodes);
    }
}

void TestLinkedListLongestPalindrome()
{
    using Result = LinkedListLongestPalindrome<char>::LL_PalindromeResult;
    {
        LinkedListElement<char> *inputLL = nullptr;
        Result r = LinkedListLongestPalindrome<char>().operator()(inputLL);
        assert(r.len == 0);
        assert(r.startPtr == nullptr);
    }
    {
        LinkedListElement<char> *inputLL = nullptr;
        LL_PushFront(&inputLL, 'A');
        Result r = LinkedListLongestPalindrome<char>().operator()(inputLL);
        assert(r.len == 1);
        assert(r.startPtr->data == 'A');
    }
    {
        LinkedListElement<char> *inputLL = nullptr;
        LL_PushFront(&inputLL, 'B');
        LL_PushFront(&inputLL, 'A');
        Result r = LinkedListLongestPalindrome<char>().operator()(inputLL);
        assert(r.len == 1);
        assert(r.startPtr->data == 'A');
    }
    {
        const std::string input("ABCDEFGHIJKLMN");
        LinkedListElement<char> *inputLL = nullptr;
        auto iterREnd = input.rend();
        for (auto iterR = input.rbegin(); iterR != iterREnd; ++iterR) {
            LL_PushFront(&inputLL, *iterR);
        }
        Result r = LinkedListLongestPalindrome<char>().operator()(inputLL);
        assert(r.len == 1);
        assert(r.startPtr->data == 'A');
    }
    {
        const std::string input("AAAAAAAAAAAAAAAAAAAAA");
        LinkedListElement<char> *inputLL = nullptr;
        auto iterREnd = input.rend();
        for (auto iterR = input.rbegin(); iterR != iterREnd; ++iterR) {
            LL_PushFront(&inputLL, *iterR);
        }
        Result r = LinkedListLongestPalindrome<char>().operator()(inputLL);

        std::string palindrome;
        while (r.len) {
            palindrome.push_back(r.startPtr->data);
            r.startPtr = r.startPtr->next;
            --r.len;
        }
        assert(palindrome == input);
    }
    {
        const std::string input("ABABCDEFGFEDCBAXY");
        LinkedListElement<char> *inputLL = nullptr;
        auto iterREnd = input.rend();
        for (auto iterR = input.rbegin(); iterR != iterREnd; ++iterR) {
            LL_PushFront(&inputLL, *iterR);
        }
        Result r = LinkedListLongestPalindrome<char>().operator()(inputLL);

        std::string palindrome;
        while (r.len) {
            palindrome.push_back(r.startPtr->data);
            r.startPtr = r.startPtr->next;
            --r.len;
        }
        assert(palindrome == "ABCDEFGFEDCBA");
    }
    {
        const std::string input("ABABCDEFGFEDCBAXYZUVWXYZ");
        LinkedListElement<char> *inputLL = nullptr;
        auto iterREnd = input.rend();
        for (auto iterR = input.rbegin(); iterR != iterREnd; ++iterR) {
            LL_PushFront(&inputLL, *iterR);
        }
        Result r = LinkedListLongestPalindrome<char>().operator()(inputLL);

        std::string palindrome;
        while (r.len) {
            palindrome.push_back(r.startPtr->data);
            r.startPtr = r.startPtr->next;
            --r.len;
        }
        assert(palindrome == "ABCDEFGFEDCBA");
    }
    {
        const std::string input("UVWXYZABABCDEFGFEDCBAXYZ");
        LinkedListElement<char> *inputLL = nullptr;
        auto iterREnd = input.rend();
        for (auto iterR = input.rbegin(); iterR != iterREnd; ++iterR) {
            LL_PushFront(&inputLL, *iterR);
        }
        Result r = LinkedListLongestPalindrome<char>().operator()(inputLL);

        std::string palindrome;
        while (r.len) {
            palindrome.push_back(r.startPtr->data);
            r.startPtr = r.startPtr->next;
            --r.len;
        }
        assert(palindrome == "ABCDEFGFEDCBA");
    }
    {
        const std::string input("AB01234567899876543210XY");
        LinkedListElement<char> *inputLL = nullptr;
        auto iterREnd = input.rend();
        for (auto iterR = input.rbegin(); iterR != iterREnd; ++iterR) {
            LL_PushFront(&inputLL, *iterR);
        }
        Result r = LinkedListLongestPalindrome<char>().operator()(inputLL);

        std::string palindrome;
        while (r.len) {
            palindrome.push_back(r.startPtr->data);
            r.startPtr = r.startPtr->next;
            --r.len;
        }
        assert(palindrome == "01234567899876543210");
    }
    {
        const std::string input("asfdasdfasAB01234567899876543210XY");
        LinkedListElement<char> *inputLL = nullptr;
        auto iterREnd = input.rend();
        for (auto iterR = input.rbegin(); iterR != iterREnd; ++iterR) {
            LL_PushFront(&inputLL, *iterR);
        }
        Result r = LinkedListLongestPalindrome<char>().operator()(inputLL);

        std::string palindrome;
        while (r.len) {
            palindrome.push_back(r.startPtr->data);
            r.startPtr = r.startPtr->next;
            --r.len;
        }
        assert(palindrome == "01234567899876543210");
    }
    {
        const std::string input("AB01234567899876543210XYkljfkajsdkfasd");
        LinkedListElement<char> *inputLL = nullptr;
        auto iterREnd = input.rend();
        for (auto iterR = input.rbegin(); iterR != iterREnd; ++iterR) {
            LL_PushFront(&inputLL, *iterR);
        }
        Result r = LinkedListLongestPalindrome<char>().operator()(inputLL);

        std::string palindrome;
        while (r.len) {
            palindrome.push_back(r.startPtr->data);
            r.startPtr = r.startPtr->next;
            --r.len;
        }
        assert(palindrome == "01234567899876543210");
    }
    {
        const std::string input("AB01234567899876543210ABCDDCBAxyx");
        LinkedListElement<char> *inputLL = nullptr;
        auto iterREnd = input.rend();
        for (auto iterR = input.rbegin(); iterR != iterREnd; ++iterR) {
            LL_PushFront(&inputLL, *iterR);
        }
        Result r = LinkedListLongestPalindrome<char>().operator()(inputLL);

        std::string palindrome;
        while (r.len) {
            palindrome.push_back(r.startPtr->data);
            r.startPtr = r.startPtr->next;
            --r.len;
        }
        assert(palindrome == "01234567899876543210");
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestLinkedListLongestPalindrome();

    TestSplitLLAgainstFibonaci();

    TestLinkedListAlgo();
    TestLinkedListSort();
    TestLinkedListCircleDetector();
    TestLinkedListContainer();

    TestLinkedListPalindromeDetectorCase1();
    TestLinkedListPalindromeDetectorCase2();
    TestLinkedListPalindromeDetectorCase3();
    TestLinkedListPalindromeDetectorCase4();
    TestLinkedListPalindromeDetectorCase5();
    TestLinkedListPalindromeDetectorCase6();
    TestLinkedListPalindromeDetectorCase7();
    TestLinkedListPalindromeDetectorCase8();

    TestOrderElementsCornerCase();
    TestOrderElementsCase1();
    TestOrderElementsCase2();
    TestOrderElementsCase3();
    TestOrderElementsCase4();
    TestOrderElementsCase5();
    TestOrderElementsCase6();

    TestLinkedListPalindromWithStringCase1();
    TestLinkedListPalindromWithStringCase2();
    TestLinkedListPalindromWithStringCase3();
    TestLinkedListPalindromWithStringCase4();
    TestLinkedListPalindromWithStringCase5();
    TestLinkedListPalindromWithStringCase6();
    TestLinkedListPalindromWithStringCase7();
    TestLinkedListPalindromWithStringCase8();
    TestLinkedListPalindromWithStringCase9();
    TestLinkedListPalindromWithStringCase10();
    TestLinkedListPalindromWithStringCase11();
    TestLinkedListPalindromWithStringCase12();
    return 0;
}

// Upate LL_Erase(**, size_t)
