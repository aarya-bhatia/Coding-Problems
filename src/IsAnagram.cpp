#include <bits/stdc++.h>

/**
 * Given strings s1, s2 check if they are anagrams.
 * Two strings are anagrams if they are made of the same characters with the
 * same frequencies.
 */
bool is_anagram(const std::string &s1, const std::string &s2)
{
    if(s1.size() != s2.size())
    {
        return false;
    }

    std::unordered_map<int, int> c1;
    std::unordered_map<int, int> c2;

    for(int i = 0; i < s1.size(); i++)
    {
        if(s1[i] >= 'A' && s1[i] <= 'Z')
        {
            c1[s1[i] - 'A']++;
        }
        else if(s1[i] >= 'a' && s1[i] <= 'z')
        {
            c1[s1[i] - 'a']++;
        }

        if(s2[i] >= 'A' && s2[i] <= 'Z')
        {
            c2[s2[i] - 'A']++;
        }
        else if(s2[i] >= 'a' && s2[i] <= 'z')
        {
            c2[s2[i] - 'a']++;
        }
    }

    for(auto it = c1.begin(); it != c1.end(); it++)
    {
        if(c2.find(it->first) == c2.end() || c2[it->first] != c1[it->first])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    std::string s1 = "ABBABAC";
    std::string s2 = "BABCABA";
    std::string s3 = "BBBCABC";

    assert(is_anagram(s1, s2) == true);
    assert(is_anagram(s2, s3) == false);
    assert(is_anagram(s1, s3) == false);
}
