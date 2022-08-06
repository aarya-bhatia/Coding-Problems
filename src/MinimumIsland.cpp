#include <bits/stdc++.h>

#define WATER 'W'
#define LAND 'L'

int setFindRoot(std::vector<int> &set, int index)
{
    if(set[index] < 0) return index;
    set[index] = setFindRoot(set, set[index]);
    return set[index];
}

void unionSet(std::vector<int> &set, int x, int y)
{
    int xRoot = setFindRoot(set, x);
    int yRoot = setFindRoot(set, y);
    if(xRoot == yRoot) return;
    set[yRoot] += set[xRoot];// store -ve size of tree at current root
    set[xRoot] = yRoot;
}

int getMinimumIsland(const std::vector<std::vector<char> > &grid)
{
    unsigned height = grid.size();
    unsigned width = grid[0].size();
    std::vector<int> disjointSet(height * width);

    for(int i = 0; i < disjointSet.size(); i++) disjointSet[i] = -1;

    for(int row = 0; row < height; row++)
    {
        for(int col = 0; col < width; col++)
        {
            int current = row * width + col;
            
            if(grid[row][col] == WATER) continue;
            
            if(col+1 < width && grid[row][col+1] == LAND) 
            {
                unionSet(disjointSet, current, current+1);
            }
            if(col-1 >= 0 && grid[row][col-1] == LAND) 
            {
                unionSet(disjointSet, current, current-1);
            }
            if(row+1 < height && grid[row+1][col] == LAND) 
            {
                unionSet(disjointSet, current, current+width);
            }
            if(row-1 >= 0 && grid[row-1][col] == LAND) 
            {
                unionSet(disjointSet, current, current-width);
            }
        }
    }

    int smallest = 0;
    for(int i = 0; i < disjointSet.size(); i++) 
    {
        if(disjointSet[i]<0) 
        {
            smallest = std::min(smallest, -disjointSet[i]);
        }
    }

    return smallest;
}

int main()
{
    return 0;
}