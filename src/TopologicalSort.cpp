#include <bits/stdc++.h>

/**
 * Input: [(target, dependency)...]
 */
template<class T>
std::vector<T> topologicalSort(std::vector<std::pair<T, T> > &edges)
{
    std::unordered_map<T, std::set<T> > dependencyGraph;
    std::vector<T> sortOrder;
    std::queue<T> buildQueue;

    for(auto &edge: edges)
    {
        if(dependencyGraph.find(edge.second) == dependencyGraph.end()) 
        {
            dependencyGraph[edge.second] = std::set<T>();
        }

        dependencyGraph[edge.first].insert(edge.second);
    }

    // Add nodes with no dependencies to the queue
    for(auto itr = dependencyGraph.begin(); itr != dependencyGraph.end(); itr++)
    {
        auto &key = itr->first;
        auto &set = itr->second;

        if(set.empty()) { buildQueue.push(key); }
    }

    for(auto itr = dependencyGraph.begin(); itr != dependencyGraph.end(); itr++)
    {
        std::cout << itr->first << ": ";
        for(auto &x: itr->second) std::cout << x << " ";
        std::cout << "\n";
    }

    while(!buildQueue.empty())
    {
        T current = buildQueue.front();
        sortOrder.push_back(current);
        buildQueue.pop();

        dependencyGraph.erase(current);

        for(auto itr = dependencyGraph.begin(); itr != dependencyGraph.end(); itr++)
        {
            auto &key = itr->first;
            auto &set = itr->second;

            set.erase(current);

            if(set.empty()) 
            {
                buildQueue.push(key);
            }
        }
    }

    return sortOrder;
}

int main()
{
    std::vector<std::pair<int, int> > edges;

    edges.push_back(std::make_pair(4, 3));
    edges.push_back(std::make_pair(4, 2));
    edges.push_back(std::make_pair(3, 2));
    edges.push_back(std::make_pair(2, 1));
    edges.push_back(std::make_pair(4, 1));

    // expect: [1, 2, 3, 4]

    std::vector<int> order = topologicalSort<int>(edges);

    for(int i: order) std::cout << i << " ";

    return 0;
}
