#ifndef LINKED_LIST_CONTAINER_H
#define LINKED_LIST_CONTAINER_H

#include "LinkedListAlgo.h"
#include "LinkedListElement.h"
#include "LinkedListSort.h"

template <typename T>
class LinkedListContainer
{
    typedef LinkedListElement<T>* NodePtr;
    typedef LinkedListElement<T> Node;
public:
    LinkedListContainer()
    {}

    ~LinkedListContainer()
    {
        DeleteList();
    }

    void PushBack(const T& data)
    {
        LL_PushBack(&m_Tail, data);
        if (m_Head == nullptr) {
            // empty list before push
            m_Head = m_Tail;
        }
        else {
            m_Tail = m_Tail->next;
        }
        ++m_Size;
    }

    void PushFront(const T& data)
    {
        LL_PushFront(&m_Head, data);

        if (m_Tail == nullptr) {
            // empty list before push
            m_Tail = m_Head;
        }
        ++m_Size;
    }

    void PopBack()
    {
        if (m_Head == nullptr) {
            return;
        }

        if (m_Head == m_Tail) {
            // empty list after pop
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
                temp = temp->next;
            }
            delete m_Tail;
            m_Tail = temp;
            m_Tail->next = nullptr;
        }
        --m_Size;
    }

    void PopFront()
    {
        if (m_Head == nullptr) {
            return;
        }
        LL_PopFront(&m_Head);
        if (m_Head == nullptr) {
            // empty list after pop
            m_Tail = nullptr;
        }
        --m_Size;
    }

    bool Insert(size_t pos, const T& data)
    {
        if (pos > m_Size) {
            return false;
        }

        if (pos == 0) {
            PushFront(data);
        }
        else if (pos == m_Size) {
            PushBack(data);
        }
        else {
            LL_Insert(&m_Head, pos, data);
            ++m_Size;
        }
        return true;
    }

    bool Insert(const NodePtr posPtr, const T& data)
    {
        if (m_Head == nullptr || posPtr == nullptr) {
            return false;
        }

        if (!LL_Insert(&m_Head, posPtr, data)) {
            return false;
        }
        ++m_size;
        return true;
    }

    bool Erase(const size_t pos)
    {
        if (m_Head == nullptr || pos >= m_Size) {
            return false;
        }

        if (pos == 0) {
            PopFront();
        }
        else if (pos == (m_Size - 1)) {
            PopBack();
        }
        else {
            // in this case no need to update m_Tail
            if (!LL_Erase(&m_Head, pos)) {
                return false;
            }
            --m_Size;
        }

        return true;
    }

    // after this functin, posPtr becomes invalid
    bool Erase(const NodePtr posPtr)
    {
        if (posPtr == m_Head) {
            PopFront();
        }
        else if (posPtr == m_Tail) {
            PopBack();
        }
        else {
            // in this case no need to update m_Tail
            if (!LL_Erase(&m_Head, posPtr)) {
                return fasle;
            }
            --m_Size;
        }

        return true;
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
        m_Tail = m_Head;
        LL_Reverse(&m_Head);
    }

    size_t GetSize() const {
        return m_Size;
    }

    void MergeSort()
    {
        LL_MergeSort(&m_Head);

        // reset m_Tail
        ResetTail();
    }

    /*
     * After this opertaion, &other will lose the ownership
     */
    void SortedMerge(LinkedListContainer<T>& other)
    {
        m_Size += other.m_Size;
        if (m_Tail->data < other.m_Tail->data) {
            m_Tail = other.m_Tail;
        }
        m_Head = LL_SortedMerge(m_Head, other.m_Head);

        // "other" has to lose the ownership, otherwise
        // may cuase double free
        other.m_Head = nullptr;
        other.m_Tail = nullptr;
        other.m_Size = 0;
    }

    void SortedMerge_Recursive(LinkedListContainer<T>& other)
    {
        m_Size += other.m_Size;

        // m_Tail points the largest element
        if (m_Tail->data > other.m_Tail->data) {
            m_Tail = other.m_Tail;
        }
        m_Head = LL_SortedMergeRecursively(m_Head, other.m_Head);
    }


    /*
    * Has to work on a sorted linkedlist
    */
    void RemoveDuplicates()
    {
        if (m_Head == nullptr){
            return;
        }

        // Do not call LL_RemoveDuplicates()
        // otherwise has to update m_Tail and m_Size
        // cause worse performance
        NodePtr curValPtr = m_Head;
        NodePtr nextValPtr = m_Head->next;
        while (nextValPtr != nullptr) {
            if (nextValPtr->data == curValPtr->data) {
                curValPtr->next = nextValPtr->next;
                delete nextValPtr;
                nextValPtr = curValPtr->next;
                --m_Size;
            }
            else {
                curValPtr = nextValPtr;
                nextValPtr = nextValPtr->next;
            }
        }

        m_Tail = curValPtr;
        return;
    }

    void DeleteList()
    {
        LL_Delete(&m_Head);
        // m_Head should set as nullptr already
        m_Tail = nullptr;
        m_Size = 0;
    }

    bool GetNth(size_t n, T& t)
    {
        return LL_GetNth(m_Head, n, t);
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
    void ResetTail()
    {
        NodePtr prev = m_Head;
        m_Tail = m_Head;
        while (m_Tail != nullptr) {
            prev = m_Tail;
            m_Tail = m_Tail->next;
        }

        m_Tail = prev;
    }

    NodePtr m_Head = nullptr;
    NodePtr m_Tail = nullptr;
    size_t m_Size = 0;
};

#endif
