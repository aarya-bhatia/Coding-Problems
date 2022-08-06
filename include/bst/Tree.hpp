#pragma once
#include <queue>
#include "TreeNode.hpp"

template<class T> 
class Tree {
    public:
        Tree(TreeNode<T> *root=nullptr);
        ~Tree();

        void insert(const T&data);
        void clear();
        bool erase(const T&data);
        void print() const;
        size_t size() const;
        Tree<T> *clone() const;

        class Iterator
        {
            private:
                TreeNode<T> *_current;
                std::queue<TreeNode<T> *> _queue;
            public:
                Iterator(TreeNode<T> *current);

                const T &operator*() const;
                Iterator &operator++();
                Iterator operator++(int);
                bool operator!=(Iterator other) const;
        };

        Iterator begin() const { return Iterator(_root); }
        Iterator end() const { return Iterator(nullptr); }

    protected:
        void insert(TreeNode<T> *&node, const T&data);
        bool erase(TreeNode<T> *&node, const T&data);
        void clear(TreeNode<T> *node);
        void print(const TreeNode<T> *node, int depth) const;
        Tree<T> *clone(TreeNode<T> *node) const;

    private:
        TreeNode<T> *_root;
        size_t _size;

};

#include "Tree.cpp"
