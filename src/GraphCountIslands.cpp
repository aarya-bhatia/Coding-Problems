#include "Graph.hpp"
#include <stdio.h>

void printGraph(const Graph<int> &graph)
{
    for(auto itr = graph.nodes.begin(); itr != graph.nodes.end(); itr++)
    {
        Node<int> *node = itr->second;
        printf("%d: ", node->data);

        for(auto itr = node->adj.begin(); itr != node->adj.end(); itr++)
        {
            Node<int> *neighbor = *itr;
            printf("%d ", neighbor->data);
        }

        printf("\n");
    }
}

void dfs(Node<int> *node)
{
    for(auto itr = node->adj.begin(); itr != node->adj.end(); itr++)
    {
        Node<int> *neighbor = *itr;

        if(!neighbor->visited)
        {
            neighbor->visited = true;
            neighbor->parent = node;
            dfs(neighbor);
        }
    }
}


int countIslands(std::vector<std::vector<int> > edgeList)
{
    Graph<int> graph;
    graph.construct(edgeList);

    printGraph(graph);

    int count = 0;
    
    for(auto itr = graph.nodes.begin(); itr != graph.nodes.end(); itr++)
    {
        Node<int> *current = itr->second;

        if(!current->visited)
        {
            current->visited = true;
            count++;
        }

        dfs(current);
    }

    return count;
}


int main()
{
    std::vector<std::vector<int> > edges; 
    edges.push_back({ 1, 2 });
    edges.push_back({ 3, 4 });
    edges.push_back({ 4, 5 });
    edges.push_back({ 5, 3 });

    int result = countIslands(edges);
    printf("Number of islands in graph: %d\n", result);
}


