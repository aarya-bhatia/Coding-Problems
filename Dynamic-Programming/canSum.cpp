/**
 * Check if we can find some integers in array that sum to given integer.
 */

#include <vector>
#include <stack>
#include <tuple>
#include <iostream>
#include <unordered_map>

/* To check if we can achieve the given sum by using elements of the array atmost once */
bool canSum(const std::vector<int> &array, int sum, int index)
{
    if(sum == 0) return true;
    if(index >= array.size()) return false;

    return canSum(array, sum-array[index], index + 1) || canSum(array, sum, index + 1);
}

/* To check if we can achieve the given sum by using any elements of the array any number of times */
bool canSumWithRepeats(const std::vector<int> &array, int sum, std::unordered_map<int, bool> &lookup)
{ 
    if(sum == 0) return true;
    if(sum < 0) return false;
    if(lookup.find(sum) != lookup.end()) return lookup[sum];

    for(int number: array)
    {
        if(canSumWithRepeats(array, sum-number, lookup))
        {
            lookup[sum] = true;
            return true;
        }
    }

    lookup[sum] = false;
    return false;
}

/* canSum iterative function implementation */
bool canSumIterative(const std::vector<int> array, int sum)
{
    if(sum == 0) return true;
    if(array.size() == 0) return false;
    
    std::stack<std::tuple<int, int> > stack;

    stack.push(std::make_tuple(sum-array[0], 1));
    stack.push(std::make_tuple(sum, 1));

    while(!stack.empty())
    {
        std::tuple<int, int> &data = stack.top();

        int remainder = std::get<0>(data);
        int index = std::get<1>(data);

        stack.pop();

        std::cout << "remainer=" << remainder 
        << " index=" << index << "\n";

        if(remainder == 0) return true;
        if(index >= array.size()) return false;

        if(index + 1 < array.size())
        {
            if(remainder - array[index] >= 0)
            {
                stack.push(std::make_tuple(remainder - array[index], index + 1));
            }

            stack.push(std::make_tuple(remainder, index + 1));
        }
    }

    return false;
}

bool canSumWithRepeatsIterative(std::vector<int> array, int sum)
{
    std::stack<int> stack; // current sum

    for(int i: array) stack.push(i);

    while(!stack.empty())
    {
        int current = stack.top();
        stack.pop();

        if(current == 0) 
        {
            return true;
        }

        if(current < 0)
        {
            continue;
        }
        
        for(int i: array) 
        {
            if(current-i >= 0)
            {
                stack.push(current-i);
            }
        }
    }
    
    return false;
}

int main()
{
    std::vector<int> v { 5, 3, 4, 7 };
    std::cout << "canSum:" << canSumIterative(v, 7) << std::endl;

    std::vector<int> v2 { 4, 2, 1, 9 };
    std::unordered_map<int,bool> lookup;
    std::cout << "canSumWithRepeats(v2, 5): " << canSumWithRepeats(v2, 5, lookup) << std::endl;
    
    return 0;
}
