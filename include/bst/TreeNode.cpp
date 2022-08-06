#include "TreeNode.hpp"

template<class T>
TreeNode<T>::TreeNode(const T &data): data(data)
{
    left = nullptr;
    right = nullptr;
} 

template<class T>
TreeNode<T>::TreeNode(TreeNode<T> *left, TreeNode<T> *right, const T &data)
{
    this->left = left;
    this->right = right;
    this->data = T(data);
}

template<class T> TreeNode<T>::~TreeNode() {}

template<class T> TreeNode<T> *TreeNode<T>::clone() const
{
    TreeNode<T> *node = new TreeNode<T>(data);
    node->left = left ? left->clone() : nullptr;
    node->right = right ? right->clone() : nullptr;
    return node;
}
