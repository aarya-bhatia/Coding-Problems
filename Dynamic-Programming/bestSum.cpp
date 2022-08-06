/**
 * Best Sum
 * =========
 * Find the shortest combination of numbers that add up to exactly the
 * target sum. For ties, return any of the solutions.
 */

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>

std::list<int> *bestSum(int target, std::vector<int> &numbers,
        std::unordered_map<int, std::list<int> *> &lookup)
{
    if(lookup.find(target) != lookup.end()) return lookup[target];

    if(target<0)return nullptr;

    if(target==0)
    {
        std::list<int> *res = new std::list<int>();
        return res;
    }

    std::list<int> *shortestCombination = nullptr;
    int prevSize = INT_MAX;

    for(int num: numbers)
    {
        int remainder = target - num;
        std::list<int> *remainderCombination = bestSum(remainder, numbers, lookup);

        if(remainderCombination)
        {
            remainderCombination->push_back(num);
            int currentSize = remainderCombination->size();

            if(!shortestCombination || currentSize < prevSize)
            {
                delete shortestCombination;
                shortestCombination = remainderCombination;
                prevSize = currentSize;
            }
            else
            {
                delete remainderCombination;
                remainderCombination = nullptr;
            }
        }
    }

    lookup[target] = shortestCombination;

    return lookup[target];
}

std::list<int> *bestSum(int target, std::vector<int> numbers)
{
    std::unordered_map<int, std::list<int> *> lookup;
    return bestSum(target, numbers, lookup);
}

void printResult(std::list<int> *result)
{
    if(!result)
    {
        std::cout << "No solution";
    }
    else
    {
        std::cout << "Solution: ";
        for(auto it = result->begin(); it != result->end(); it++)
        {
            std::cout << *it << " ";
        }
    }

    std::cout << "\n";
}

int main()
{
    std::vector<int> v { 5, 3, 4, 7 };
    int target = 7;

    std::list<int> *shortestCombination = bestSum(target, v);
    printResult(shortestCombination);

    delete shortestCombination;

    return 0;
}
