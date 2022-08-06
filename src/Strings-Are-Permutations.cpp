#include <bits/stdc++.h>

/**
 * To determine if the given two strings are permutations of each other.
 * Time: O(n) | n = size of string
 */
bool are_permutations(const std::string &s1, const std::string &s2)
{
    if(s1.empty() && s2.empty()) return true;
    if(s1.size() != s2.size()) return false;

    std::unordered_map<char, int> map;

    for(char c: s1)
    {
        map[c]++;
    }

    for(char c: s2)
    {
        map[c]--;
        if(map[c] < 0) return false;
    }

    return true;
}


int main()
{
    assert(are_permutations(std::string("ABBA"), std::string("BABA")) == true);
    assert(are_permutations(std::string("ABBA"), std::string("BABC")) == false);
    assert(are_permutations(std::string("ABBA"), std::string("BABAB")) == false);

    return 0;
}

