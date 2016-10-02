#include "stdafx.h"

#include "LinkListCircleDetector.h"

LinkListCircleDetector::LinkListCircleDetector()
{
}

LinkListCircleDetector::~LinkListCircleDetector()
{
}

template<typename T>
bool LinkListCircleDetector::HasCircle(const T* root)
{
	return GetOneOfElementsIfHasCircle(root) != nullptr;
}


template<typename T>
size_t LinkListCircleDetector::CheckCircleAndReturnCircleSize(const T* root)
{
	if (root == nullptr) {
		return 0;
	}

	const T* circleElement = GetOneOfElementsIfHasCircle(root);
	if (circleElement == nullptr) {
		return 0;
	}

	size_t count = 1;
	const T* tempElement = circleElement;
	while (tempElement) {
		if (tempElement->next != circleElement) {
			++count;
			tempElement = tempElement->next;
		}
		else {
			break;
		}
	}

	return count;
}

template<typename T>
void LinkListCircleDetector::RemoveCircleIfHasCircle(T* root)
{
	if (root == nullptr) {
		return;
	}

	size_t circleSize = CheckCircleAndReturnCircleSize(root);
	if (circleSize == 0) {
		return;
	}

	T* tempNode1 = root;
	T* tempNode2 = root;
	while (size > 0) {
		tempNode2 = tempNode2->next;
	}

	while (tempNode2->next != tempNode1) {
		tempNode2 = tempNode2->next;
		tempNode1 = tempNode1->next;
	}

	// Remove the circle
	tempNode2->next = nullptr;
}


template<typename T>
const T* LinkListCircleDetector::GetOneOfElementsIfHasCircle(const T* root)
{
	const T* slowHand = root;
	const T* fastHand = root;

	while (slowHand != nullptr) {
		slowHand = slowHand->next;
		if (fastHand == nullptr || fastHand->next == nullptr) {
			return nullptr;
		}
		fastHand = fastHand->next->next;
		if (slowHand != nullptr && slowHand == fastHand) {
			return slowHand;
		}
	}

	return nullptr;
}