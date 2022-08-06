#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>

bool howSum(int target, std::vector<int> &numbers, std::vector<int> &path)
{
    if(target == 0) return true;
    if(target < 0) return false;

    for(int i = 0; i < numbers.size(); i++)
    {
        if(target - numbers[i] >= 0)
        {
            int remainder = target-numbers[i];
            path.push_back(numbers[i]);

            if(howSum(remainder, numbers, path))
            {
                return true;
            }

            path.pop_back();
        }
    }

    return false;
}

std::list<int> *howSumMemo(int target, std::vector<int> &numbers,
    std::unordered_map<int, std::list<int>*> &lookup)
{
    if(lookup.find(target) != lookup.end()) return lookup[target];
    if(target < 0) return nullptr;
    if(target == 0) return new std::list<int>();

    for(int num: numbers)
    {
        int remainder = target - num;
        std::list<int> *result = howSumMemo(remainder, numbers, lookup); 

        if(result)
        {
            result->push_back(num);

            lookup[target] = result;
            return result;
        }
    }

    lookup[target] = nullptr;
    return nullptr;
}

/**
 * @param target the target sum
 * @param numbers array of numbers
 * @return an array containing any combination of elements that sum to exactly 
 * the target sum. If no combination exists, return NULL.
 */
std::vector<int> howSum(int target, std::vector<int> numbers)
{
    std::vector<int> path;

    howSum(target, numbers, path);

    return path;
}

int main()
{
    std::vector<int> v { 5, 3, 4, 7 };

    int target = 7;
    //std::vector<int> path = howSum(target, v);

    std::unordered_map<int, std::list<int>*> lookup;
    std::list<int> *path = howSumMemo(target, v, lookup);

    if(!path) std::cout << "No solution\n";

    std::cout << "Solution: ";

    for(auto it = path->begin(); it != path->end(); it++)
    {
        std::cout << *it << " ";
    }

    std::cout << "\n";

    delete path;

    return 0;
}
