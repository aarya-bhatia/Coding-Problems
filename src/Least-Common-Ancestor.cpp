#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "TreeNode.hpp"
#include <queue>
#include <unordered_map>
#include <iostream>

bool get_path(TreeNode<int> *root, TreeNode<int> *target,
        std::unordered_map<TreeNode<int> *, TreeNode<int> *> &path)
{
    // BFS

    std::queue<TreeNode<int> *> q;
    q.push(root);
    path[root] = nullptr;

    while(!q.empty())
    {
        TreeNode<int> *cur = q.front();
        q.pop();

        if(cur == target) return true;

        if(cur->left) 
        {
            path[cur->left] = cur;
            q.push(cur->left);
        }
        if(cur->right) 
        {
            path[cur->right] = cur;
            q.push(cur->right);
        }
    }

    return false;
}

TreeNode<int> *lca_with_list_intersection(TreeNode<int> *root, TreeNode<int> *n1, TreeNode<int> *n2)
{
    if(!n1 || ! n2)
    {
        return nullptr;
    }

    if(n1 == n2)
    {
        return n1;
    }

    if(n1 == root || n2 == root)
    {
        return root;
    }

    // upward paths of the nodes in the tree 
    // path[x] = y => x is a child of y. 
    std::unordered_map<TreeNode<int> *, TreeNode<int> *> path;

    // compute and store paths to n1 and n2 from root in the path map
    // if no path found, node does not exist in tree
    if(!get_path(root, n1, path) || !get_path(root, n2, path)) return nullptr;

    // consider the list root -> .. -> n1 and root -> .. -> n2
    // The list is traversed by moving from itr->path[itr]->..
    // find sizes of both lists
    int size1 = 1;
    int size2 = 1;

    TreeNode<int> *itr = nullptr;

    itr = n1;

    TreeNode<int> *end1 = nullptr;
    TreeNode<int> *end2 = nullptr;

    while(itr != nullptr)
    {
        itr = path[itr];
        size1++;

        if(path[itr] == nullptr) end1 = itr;
    }

    itr = n2;

    while(itr != nullptr)
    {
        itr = path[itr];
        size2++;

        if(path[itr] == nullptr) end2 = itr;
    }

    // the paths of the two nodes do not meet at a common root
    if(end1 != end2) 
    {
        return nullptr;
    }

    // we have the sizes for both lists

    TreeNode<int> *larger = size1 > size2 ? n1 : n2;
    TreeNode<int> *smaller = size1 > size2 ? n2 : n1;

    for(int i = 0; i < std::abs(size1-size2); i++) larger = path[larger];

    // find intersection point 
    while(larger && smaller && larger != smaller) 
    {
        larger = path[larger];
        smaller = path[smaller];
    }

    // Found the LCA
    if(larger == smaller)
    {
        return larger;
    }

    return nullptr;
}

bool contains(TreeNode<int> *root, TreeNode<int> *node)
{
    if(root == node) return true;
    if(!node) return false;

    return (root->left ? contains(root->left, node) : false) 
        || (root->right ? contains(root->right, node) : false);
}

TreeNode<int> *lca(TreeNode<int> *subtree, TreeNode<int> *n1, TreeNode<int> *n2)
{
    if(!n1 || !n2 || !subtree) return nullptr;

    // some node does not exist in tree
    if(!contains(subtree, n1) || !contains(subtree, n2)) return nullptr;

    // root node of subtree is one of the nodes
    if(subtree == n1 || subtree == n2) return subtree;

    // both nodes in left subtree
    if(contains(subtree->left, n1) && contains(subtree->left, n2)) return lca(subtree->left, n1, n2);

    // both nodes in right subtree
    if(contains(subtree->right, n1) && contains(subtree->right, n2)) return lca(subtree->right, n1, n2);

    // one node in left subtree and other node in right subtree
    return subtree;
}

TEST_CASE("Tree::contains works as expected", "[bst]") {
    TreeNode<int> n4 = { nullptr, nullptr, 4 };
    TreeNode<int> n2 = { &n4, nullptr, 2 };
    TreeNode<int> n3 = { nullptr, nullptr, 3 };
    TreeNode<int> n1 = { &n2, &n3, 1 };

    REQUIRE(contains(&n1, &n1));
    REQUIRE(contains(&n1, &n2));
    REQUIRE(contains(&n1, &n3));
    REQUIRE(contains(&n1, &n4));
    REQUIRE(contains(&n2, &n4));
    REQUIRE(!contains(&n3, &n4));
    REQUIRE(!contains(&n2, &n1));
    REQUIRE(!contains(&n1, nullptr));

}

TEST_CASE("lca works as expected", "[bst]") {
    TreeNode<int> n4 = { nullptr, nullptr, 4 };
    TreeNode<int> n2 = { &n4, nullptr, 2 };
    TreeNode<int> n3 = { nullptr, nullptr, 3 };
    TreeNode<int> n1 = { &n2, &n3, 1 };

    REQUIRE(lca(&n1, &n4, &n3) == &n1);
    REQUIRE(lca(&n1, &n2, &n3) == &n1);
    REQUIRE(lca(&n3, &n2, &n1) == nullptr);
    REQUIRE(lca(&n1, &n2, &n4) == &n2);
    REQUIRE(lca(&n1, &n1, &n3) == &n1);
}

TEST_CASE("lca_with_list_intersection works as expected", "[bst]") {
    TreeNode<int> n4 = { nullptr, nullptr, 4 };
    TreeNode<int> n2 = { &n4, nullptr, 2 };
    TreeNode<int> n3 = { nullptr, nullptr, 3 };
    TreeNode<int> n1 = { &n2, &n3, 1 };

    REQUIRE(lca_with_list_intersection(&n1, &n4, &n3) == &n1);
    REQUIRE(lca_with_list_intersection(&n1, &n2, &n3) == &n1);
    REQUIRE(lca_with_list_intersection(&n3, &n2, &n1) == nullptr);
    REQUIRE(lca_with_list_intersection(&n1, &n2, &n4) == &n2);
    REQUIRE(lca_with_list_intersection(&n1, &n1, &n3) == &n1);
}

