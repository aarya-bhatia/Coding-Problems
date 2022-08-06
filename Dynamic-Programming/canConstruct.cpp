#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

bool canConstruct(const std::string &target, 
        const std::vector<std::string> &wordBank, int strIndex,
        std::unordered_map<int, bool> &lookup)
{
    if(lookup.find(strIndex) != lookup.end()) return lookup[strIndex];

    if(strIndex >= target.size()) return true;

    for(const std::string &s: wordBank)
    {
        // current string is longer than target[strIndex:]
        if(strIndex + s.size() - 1 >= target.size()) continue;
        
        bool startsWith = true;

        // check if target[strIndex:] starts with s
        for(int i = 0; i < s.size(); i++)
        {
            if(s[i] != target[strIndex + i])
            {
                startsWith = false;
            }
        }

        if(startsWith)
        {
            int nextIndex = strIndex + s.size();

            if(canConstruct(target, wordBank, nextIndex, lookup))
            {
                lookup[strIndex] = true;
                return true;
            }
        }
    }

    lookup[strIndex] = false;
    return false;
}

/**
 * @param target string
 * @param wordBank array of strings
 * @return boolean indicating whether or not the target string can be
 * constructed by concatenating elements of the wordBank array.
 * You may reuse elements of wordBank as many times as needed.
 */
bool canConstruct(const std::string &target, const std::vector<std::string> &wordBank)
{
    if(target.size() == 0) return true;
    if(wordBank.size() == 0) return false;

    std::unordered_map<int, bool> lookup;

    return canConstruct(target, wordBank, 0, lookup); 
}

int main()
{
    std::string target = "abcdef";

    std::vector<std::string> wordBank {
        "ab", "abc", "cd", "def", "abcd"
    };

    bool result = canConstruct(target, wordBank);

    std::cout << "Result: " << result << "\n";

    return 0;
}

