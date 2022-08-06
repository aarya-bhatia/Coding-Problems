#pragma once

#include <list>

template<class T>
struct Node
{
    T data;
    std::list<Node<T> *> adj;
    bool visited;
    Node<T> *parent;
    int distance;

    Node(const T &data) : data(data)
    {
        distance = 0;
        visited = false;
        parent = nullptr;
    }

    bool contains(Node<T> *n) const
    {
        for (Node<T> *x : adj)
        {
            if (x == n)
            {
                return true;
            }
        }

        return false;
    }
};

