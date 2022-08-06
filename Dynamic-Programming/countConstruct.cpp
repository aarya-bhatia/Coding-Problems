#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

int countConstruct(const std::string &target, 
        const std::vector<std::string> &wordBank, int strIndex,
        std::unordered_map<int, int> &lookup)
{
    if(lookup.find(strIndex) != lookup.end()) return lookup[strIndex];

    if(strIndex >= target.size()) return true;

    int count = 0;

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

            if(countConstruct(target, wordBank, nextIndex, lookup))
            {
                count++;
            }
        }
    }

    lookup[strIndex] = count;
    return count;
}

int countConstruct(const std::string &target, const std::vector<std::string> &wordBank)
{
    std::unordered_map<int, int> lookup;

    return countConstruct(target, wordBank, 0, lookup); 
}

int main()
{
    std::string target = "abcdef";

    std::vector<std::string> wordBank {
        "ab", "abc", "cd", "def", "ef", "abcd"
    };

    int result = countConstruct(target, wordBank);

    std::cout << "Result: " << result << "\n";

    return 0;
}

