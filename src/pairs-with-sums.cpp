#include <bits/stdc++.h>

/**
 * Write a program to find all pairs of integers in an array, that sum to a given integer.
 */
std::vector<std::pair<int, int> > find_pairs_with_sum(int sum, std::vector<int> numbers)
{
    std::vector<std::pair<int, int> > results;
    std::unordered_set<int> found;

    for(int number: numbers)
    {
        if(found.find(sum - number) == found.end())
        {
            found.insert(number);
        }
        else 
        {
            found.erase(sum - number);
            results.push_back(std::make_pair(number, sum - number));
        }
    }

    return results;
}


int main()
{
    std::vector<int> numbers { 4, 6, 3, 2, 8, 5 };
    std::vector<std::pair<int, int> > results = find_pairs_with_sum(7, numbers);

    printf("Given array: ");

    for(auto &num: numbers)
    {
        printf("%d ", num);
    }

    printf("\nPairs with sum %d are: ", 7);

    for(auto &result: results) 
    {
        printf("(%d, %d) ", result.first, result.second);
    }

    return 0;
}
