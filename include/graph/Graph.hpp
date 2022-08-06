#pragma once

#include <vector>
#include <list>
#include <unordered_map>

#include "Node.hpp"

template <class T>
struct Graph
{
    bool contains(const T &u) const
    {
        return nodes.find(u) != nodes.end();
    }

    void addNode(const T &u)
    {
        if (!contains(u))
        {
            nodes[u] = new Node<T>(u);
        }
    }

    void addEdge(const T &u, const T &v)
    {
        if (!contains(u))
        {
            addNode(u);
        }
        if (!contains(v))
        {
            addNode(v);
        }

        if (!nodes[u]->contains(nodes[v]))
        {
            nodes[u]->adj.push_back(nodes[v]);
        }
        if (!nodes[v]->contains(nodes[u]))
        {
            nodes[v]->adj.push_back(nodes[u]);
        }
    }

    void construct(const std::vector<std::vector<T>> &edgeList)
    {
        for (auto edgePair : edgeList)
        {
            addEdge(edgePair[0], edgePair[1]);
        }
    }

    ~Graph()
    {
        for(auto itr = nodes.begin(); itr != nodes.end(); itr++)
        {
            Node<T> *node = itr->second;
            delete node;
        }
    }

    std::unordered_map<T, Node<T> *> nodes;
};
