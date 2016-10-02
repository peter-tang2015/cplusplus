#ifndef LINKED_LIST_ELEMENT_H
#define LINKED_LIST_ELEMENT_H

#pragma once

template <typename T>
struct LinkedListElement {
	T data;
	LinkedListElement<T>* next = nullptr;

	LinkedListElement()
	{}
	LinkedListElement(const T& t) : data(t)
	{}
	~LinkedListElement()
	{}
};

#endif
