#pragma once

#include "ListNode.hpp"

template<class T>
struct List
{
    ListNode<T> *head;
    ListNode<T> *tail;
    unsigned int size;

    List()
    {
        head = new ListNode<T>();
        tail = new ListNode<T>();
        size = 0;
    }

    ~List()
    {
        clear();

        delete head;
        delete tail;
    }

    void clear()
    {
        ListNode *itr = head->next;
        while(itr != tail)
        {
            ListNode *tmp = itr->next;
            delete itr;
            itr = tmp;
        }
    }

    void push_front(const T &data)
    {
        head.insertAfter(data);
        size++;
    }

    void push_back()
    {
        tail.insertBefore(data);
        size++;
    }

    void pop_front()
    {
        head.removeAfter();
        size--;
    }

    void pop_back()
    {
        tail.removeBefore();
        size--;
    }

    bool empty() const
    {
        return size == 0;
    }

    T &front() const
    {
        return head->next->data;
    }

    T &back() const 
    {
        return tail->prev->data;
    }
};
