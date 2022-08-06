#pragma once

template<class T> 
struct TreeNode{
        TreeNode(const T &data = T());
        TreeNode(TreeNode<T> *left, TreeNode<T> *right, const T &data);
        ~TreeNode();

        TreeNode<T> *clone() const;

        TreeNode<T> *left;
        TreeNode<T> *right;
        T data;
};

#include "TreeNode.cpp"
