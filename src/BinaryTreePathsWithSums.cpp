#include <bits/stdc++.h>
#include "TreeNode.hpp"

void update_results(std::list<std::list<int> > *from, int data, std::list<std::list<int> > *to)
{
    if(!from || !to) return;

    for(auto &list: *from)
    {
        list.push_front(data);
        to->push_front(list);
    }
}

/**
 * Find and return alls path in BST whose elements add up to the target sum.
 */
std::list<std::list<int> > *find_all_paths(TreeNode<int> *root, int sum)
{
    if(!root || sum < 0)
    {
        return nullptr;
    }

    std::list<std::list<int> > *results = nullptr;

    if(sum==root->data){
        results = new std::list<std::list<int> >();
        std::list<int> list;
        list.push_front(root->data);
        results->push_front(list);

        return results;
    }
    
    std::list<std::list<int> > *p1 = find_all_paths(root->left, sum - root->data);
    std::list<std::list<int> > *p2 = find_all_paths(root->right, sum - root->data);
    std::list<std::list<int> > *p3 = find_all_paths(root->left, sum);
    std::list<std::list<int> > *p4 = find_all_paths(root->right, sum);

    if(p1 || p2 || p3 || p4) results = new std::list<std::list<int> >();
    if(!results) return nullptr;

    if(p1) update_results(p1, root->data, results);
    if(p2) update_results(p2, root->data, results);
    if(p3) update_results(p3, root->data, results);
    if(p4) update_results(p4, root->data, results);

    return results;
}

/**
 * Find and return shortest path in BST whose elements add up to the target sum.
 */
std::list<int> *find_shortest_path(TreeNode<int>*root,int sum)
{
    if(!root || sum < 0)
    {
        return nullptr;
    }

    if(sum==root->data){
        auto *list = new std::list<int>;
        list->push_front(root->data);
        return list;
    }
    
    std::list<int> *path = nullptr;

    std::list<int> *p1 = find_shortest_path(root->left, sum - root->data);
    std::list<int> *p2 = find_shortest_path(root->right, sum - root->data);
    std::list<int> *p3 = find_shortest_path(root->left, sum);
    std::list<int> *p4 = find_shortest_path(root->right, sum);

    if(p1 || p2 || p3 || p4)
    {
        if(!path || (p1 && path->size() > p1->size())) path = p1;
        if(!path || (p2 && path->size() > p2->size())) path = p2;
        if(!path || (p3 && path->size() > p3->size())) path = p3;
        if(!path || (p4 && path->size() > p4->size())) path = p4;
    }

    if(path != p1) delete p1;
    if(path != p2) delete p2;
    if(path != p3) delete p3;
    if(path != p4) delete p4;
    
    if(path)
    {
        path->push_front(root->data);
        return path;
    }

    return nullptr;
}

int main()
{
    TreeNode<int> one { nullptr, nullptr, 1 };
    TreeNode<int> three { nullptr, &one, 3 };
    TreeNode<int> four { nullptr, nullptr, 4 };
    TreeNode<int> two { &four, &three, 2 };

    //std::list<int> *result = find_shortest_path(&two, 6);

    //if(!result) return 1;

    //for(int i: *result) printf("%d ", i);

    //delete result;
    //

    std::list<std::list<int> > *solutions = find_all_paths(&two, 6);

    for(auto &list: *solutions){
        for(int i: list) {
            printf("%d ", i);
        }
        printf("\n");
    }

    delete solutions;

    return 0;
}
