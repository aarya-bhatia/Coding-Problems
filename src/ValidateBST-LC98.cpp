#include "TreeNode.hpp"

template<class T>
class Solution
{
public:
    bool isValidBST(TreeNode<T> *root, TreeNode<T> *minNode, TreeNode<T> *maxNode)
    {
        if (!root)
            return true;
        if (minNode && root->data <= minNode->data)
            return false;
        if (maxNode && root->data >= maxNode->data)
            return false;
        return isValidBST(root->left, minNode, root) &&
               isValidBST(root->right, root, maxNode);
    }

    bool isValidBST(TreeNode<T> *root)
    {
        if (!root)
            return true;
        return isValidBST(root, nullptr, nullptr);
    }
};

int main()
{
    Solution<int> s;
    s.isValidBST(nullptr);
}