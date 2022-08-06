/**
 * Given two binary search trees t1 and t2. t1 is bigger than t2.
 * Determine whether t2 is a subtree of t1.
 */

#include "TreeNode.hpp"
#include <assert.h>
#include <stdio.h>

template<class T>
bool containsTreeHelper(TreeNode<T> *t1, TreeNode<T> *t2)
{
    if(!t1 && !t2) return true;
    if(!t1 || !t2) return false;

    printf("t1: %d, t2: %d\n", t1->data, t2->data);

    if(t1->data != t2->data) return false;

    bool checkLeft = containsTreeHelper(t1->left, t2->left);

    if(!checkLeft) return false;

    bool checkRight = containsTreeHelper(t1->right, t2->right);

    if(!checkRight) return false;

    return checkLeft && checkRight;
}

template<class T>
bool containsTree(TreeNode<T> *t1, TreeNode<T> *t2)
{
    if(!t2) return true;
    if(!t1) return false;

    // Find the root node of t2 in t1
    TreeNode<T> *itr = t1;
    while(itr!=nullptr)
    {
        if(itr->data==t2->data)
        {
            break;
        }
        else if(itr->data>t2->data)
        {
            itr=itr->left;
        }
        else
        {
            itr=itr->right;
        }
    }

    if(!itr) 
    {
        printf("Failed to find root t2:%d in t1:%d\n", t2->data, t1->data);
        return false;
    }

    // check if rest of the tree exists
    // recursively check if the left and right subtrees of both trees match
    return containsTreeHelper(itr, t2);
}

template<class T> void deleteTree(TreeNode<T> *root)
{
    if(root)
    {
        deleteTree<T>(root->left);
        deleteTree<T>(root->right);
    }

    delete root;
}

int main()
{
    TreeNode<int> two(2);
    TreeNode<int> one(1);
    TreeNode<int> five(5);
    TreeNode<int> four(4);
    TreeNode<int> seven(7);

    two.left = &one;
    two.right = &five;
    five.left = &four;
    five.right = &seven;

    assert(containsTree<int>(nullptr, &five) == false);
    assert(containsTree<int>(nullptr, nullptr) == true);
    assert(containsTree<int>(&one, nullptr) == true);

    assert(containsTree<int>(&two, &two) == true);
    assert(containsTree<int>(&two, &five) == true);
    assert(containsTree<int>(&five, &five) == true);
    assert(containsTree<int>(&four, &five) == false);
    assert(containsTree<int>(&five, &four) == true);
    assert(containsTree<int>(&seven, &four) == false);
    assert(containsTree<int>(&two, &one) == true);

    TreeNode<int> *fiveClone = five.clone();
    fiveClone->left = nullptr;
    assert(containsTree<int>(&two, fiveClone) == false);

    deleteTree<int>(fiveClone);
    return 0;
}

