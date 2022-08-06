/**
 * Longest Common Subsequence Problem
 */
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>

/**
 * Time Complexity: O(2^(m+n))
 * @param x first sequence
 * @param y second sequence
 * @param m length of string x
 * @param n length of string y
 * @returns length of longest subsequence obtained by removed some items from 
 * both sequences such that the subsequence occurs in the same order in both 
 * sequences.
 */
int LCSLength(const std::string &x, const std::string &y, int m, int n)
{
    if(m == 0 || n == 0)
    {
        return 0;
    }

    if(x[m-1] == y[n-1])
    {
        return 1 + LCSLength(x, y, m-1, n-1);
    }
    else
    {
        return std::max(LCSLength(x, y, m-1, n), LCSLength(x, y, m, n-1));
    }
}

/**
 * Time and Space Complexity = O(mn)
 * LCS with memoization
 * @param lookup maps a key in the form "m,n" to the result
 */
int LCSLengthOptimized(const std::string &x, const std::string &y, int m, int n, 
        std::unordered_map<std::string, int> &lookup)
{
    if(m == 0 || n == 0)
    {
        return 0;
    }

    std::string key = std::to_string(m) + "," + std::to_string(n);

    if(lookup.find(key) == lookup.end())
    {
        if(x[m-1] == y[n-1])
        {
            lookup[key] = 1 + LCSLengthOptimized(x, y, m-1, n-1, lookup);
        }
        else
        {
            lookup[key] = std::max(LCSLengthOptimized(x, y, m-1, n, lookup), 
                    LCSLengthOptimized(x, y, m, n-1, lookup));
        }
    }
    
    return lookup[key];
}

int LCSLengthOptimized(const std::string &x, const std::string &y)
{
    std::unordered_map<std::string, int> lookup;
    return LCSLengthOptimized(x, y, x.length(), y.length(), lookup);
}

int main()
{
    std::string x = "ABCBDAB";
    std::string y = "BDCABA";

    int res = LCSLengthOptimized(x,y);

    std::cout << "Length of LCS is " << res << "\n";

    return 0;
}

