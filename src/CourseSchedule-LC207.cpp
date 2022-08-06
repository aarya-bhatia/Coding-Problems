/** Leetcode Problem No. 207 - Course Schedule
 * 
 * 
 * 
 * Need to do a topological sort on dependency graph of courses
 * y must be taken before x for all [x,y] in prerequisites
 * Build graph
 * Nodes are courses
 * Edges are x to y for all [x,y] in prerequisites
 * Run topological sort till failure
 * Check if enough courses were found = numCourses
 * 
 * 
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites);

    unordered_map<int, list<int>> inbound; // maps node to list of inbound nodes
    unordered_map<int, set<int>> outbound; // maps node to list of outbound nodes
    queue<int> processing;
};

bool Solution::canFinish(int numCourses, vector<vector<int>> &prerequisites)
{
    for (int i = 0; i < numCourses; i++)
        outbound.insert({i, {}});

    for (vector<int> &prerequisite : prerequisites)
    {
        int from = prerequisite[0];
        int to = prerequisite[1];

        inbound[to].push_back(from);
        outbound[from].insert(to);
    }

    for (auto &itr : outbound)
    {
        if (itr.second.empty())
            processing.push(itr.first);
    }

    int count = 0;

    while (!processing.empty())
    {
        int next = processing.front();
        processing.pop();

        count++;
        if (count >= numCourses)
            break;

        for (int adj : inbound[next])
        {
            outbound[adj].erase(next);
            if (outbound[adj].empty())
                processing.push(adj);
        }
    }

    return count >= numCourses;
}

int main()
{
    vector<vector<int>> v{ {1, 0} };
    cout << Solution().canFinish(1, v);
}