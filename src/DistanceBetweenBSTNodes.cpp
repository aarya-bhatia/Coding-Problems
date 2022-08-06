/**
 * Given a binary tree, determine the distance between given pairs of nodes in it.
 * The distance between two nodes is defined as the total number of edges in the shortest
 * path from one node to other.
 *
 *
 * Distance(n1, n2) = Distance(n1, LCA(n1, n2)) + Distance(n2, LCA(n1, n2))
 */

#include <bits/stdc++.h>
#include "TreeNode.hpp"
#include "Tree.hpp"

TreeNode<int> *lca(TreeNode<int> *root, TreeNode<int> *n1, TreeNode<int> *n2)
{
    // Base Case 1: Tree is empty
    if(!root) return nullptr;

    // Base Case 2: Either node is found.
    if(root == n1 || root == n2) return root;

    // Check if n1 or n2 exists in the left subtree
    TreeNode<int> *left = lca(root->left, n1, n2);

    // Check if n1 or n2 exists in the right subtree
    TreeNode<int> *right = lca(root->right, n1, n2);

    // n1 is found in one subtree and n2 in the other subtree.
    if(left && right)
    {
        return root;
    }

    // n1 and n2 exist in the left subtree
    if(left)
    {
        return left;
    }

    // n1 and n2 exist in the right subtree
    if(right)
    {
        return right;
    }

    // n1 or n2 does not exist
    return nullptr;
}

int findLevel(TreeNode<int> *root, TreeNode<int> *target, int level)
{
    if(!root) return -1;

    if(root == target) return level;

    int left = findLevel(root->left, target, level + 1);

    if(left != -1)
    {
        return left;
    }

    int right = findLevel(root->right, target, level + 1);

    if(right != -1)
    {
        return right;
    }

    return -1;
}

int distanceBetweenNodes(TreeNode<int> *root, TreeNode<int> *n1, TreeNode<int> *n2)
{
    TreeNode<int> *lcaNode = lca(root, n1, n2);
    if(!lcaNode) return -1;
    return findLevel(lcaNode, n1, 0) + findLevel(lcaNode, n2, 0);
}

TreeNode<int> *insertLeft(TreeNode<int> *root, int data)
{
    TreeNode<int> *node = new TreeNode<int>();
    node->data = data;
    node->left = root->left;
    root->left = node;
    return node;
}

TreeNode<int> *insertRight(TreeNode<int> *root, int data)
{
    TreeNode<int> *node = new TreeNode<int>();
    node->data = data;
    node->right = root->right;
    root->right = node;
    return node;
}

void deleteTree(TreeNode<int> *root)
{
    if(!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main()
{
    TreeNode<int> *root = new TreeNode<int>();
    root->data = 1;

    auto *n2 = insertLeft(root, 2);
    auto *n3 = insertRight(root, 3);
    auto *n4 = insertRight(n2, 4);
    auto *n5 = insertLeft(n3, 5);
    auto *n6 = insertRight(n3, 6);
    auto *n7 = insertLeft(n5, 7);
    auto *n8 = insertRight(n5, 8);

    Tree<int> *tree = new Tree<int>(root);

    tree->print();

    printf("Distance between node %d and %d is %d.\n", 7, 6, 
            distanceBetweenNodes(root, n7, n6));

    delete tree;

    return 0;
}
