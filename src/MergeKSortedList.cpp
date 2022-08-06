
/*
Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted list:
1->1->2->3->4->4->5->6
*/

#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct List
{
    ListNode *head;
    ListNode *tail;

    List()
    {
        head = tail = nullptr;
    }

    void push_back(int val)
    {
        push_back(new ListNode(val, nullptr));
    }

    void push_back(ListNode *node)
    {
        if (!head && !tail)
        {
            head = tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }
    }

    void print()
    {
        ListNode *itr = head;
        while (itr)
        {
            cout << itr->val << " ";
            itr = itr->next;
        }
        cout << endl;
    }
};

class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *u, ListNode *v)
    {
        if (!u) return v;
        if (!v) return u;
       
        if (u->val < v->val)
        {
            u->next = mergeTwoLists(u->next, v);
            return u;
        }
        else
        {
            v->next = mergeTwoLists(u, v->next);
            return v;
        }
    }

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        cout << "lists size: " << lists.size() << endl;

        if (lists.empty())
            return nullptr;
        if (lists.size() == 1)
            return lists[0];

        int n = lists.size();

        vector<ListNode *> v;

        for (int i = 0; i < n; i += 2)
        {
            ListNode *l1 = i < n ? lists[i] : nullptr;
            ListNode *l2 = i + 1 < n ? lists[i + 1] : nullptr;
            ListNode *merged = mergeTwoLists(l1, l2);
            if(merged) v.push_back(merged);
        }

        return mergeKLists(v);
    }
};

int main()
{
    List l1, l2, l3;
    for (int i : vector<int>{1, 4, 5})
        l1.push_back(i);
    for (int i : vector<int>{1, 3, 6})
        l2.push_back(i);
    for (int i : vector<int>{2, 6})
        l3.push_back(i);

    vector<ListNode *> v{l1.head, l2.head, l3.head};
    ListNode *result = Solution().mergeKLists(v);

    List l;
    l.head = result;
    l.print();

    while (result)
    {
        ListNode *tmp = result->next;
        delete result;
        result = tmp;
    }

    return 0;
}