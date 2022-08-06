#pragma once

template<class T>
struct ListNode
{
    ListNode<T> *prev;
    ListNode<T> *next;
    T data;

    ListNode *insertAfter(const T &data)
    {
        ListNode<T> *node = new ListNode<T> { this, next, data };
        if(next) next->prev = node;
        next = node;
        return node;
    }

    ListNode *insertBefore(const T &data)
    {
        ListNode<T> *node = new ListNode<T> { prev, this, data };
        if(prev) prev->next = node;
        prev = node;
        return node;
    }

    void removeBefore()
    {
        if(!prev) return;

        ListNode<T> *newPrev = prev->prev;
        if(newPrev) newPrev->next = this;

        delete prev;
        prev = newPrev;
    }

    void removeAfter()
    {
        if(!next) return;

        ListNode<T> *newNext = next->next;
        if(newNext) newNext->prev = this;

        delete next;
        next = newNext;
    }

    ListNode(): prev(nullptr), next(nullptr), data(T()) {}

    ListNode(const T &data): prev(nullptr), next(nullptr), data(data) {}

    ListNode(ListNode<T> *prev, ListNode<T> *next, const T& data):
        prev(prev), next(next), data(data) {}

    ~ListNode() {}
};
 
template <class T> unsigned int size(ListNode<T> *node)
{
    unsigned int size = 0;

    while(node)
    {
        node = node->next;
        size++;
    }

    return size;
}
