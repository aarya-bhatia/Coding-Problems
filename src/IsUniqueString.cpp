#include <bits/stdc++.h>

/**
 * To determine if a string has all unique characters
 *
 */
bool has_unique_characters(const std::string &str)
{
    std::unordered_set<char> used;

    for(char c: str)
    {
        if(used.find(c) == used.end()) { used.insert(c); }
        else { return false; }
    }

    return true;
}

int main()
{
    assert(has_unique_characters(std::string("ABCAD")) == false);
    assert(has_unique_characters(std::string("EABCD")) == true);
    assert(has_unique_characters(std::string("")) == true);

    return 0;
}

