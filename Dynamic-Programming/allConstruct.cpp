#include <vector>
#include <list>
#include <unordered_map>
#include <string>
#include <iostream>
#include <assert.h>


bool hasPrefix(const std::string &target, const std::string &prefix, int offset)
{
    if(offset + prefix.size() - 1 >= target.size()) return false;

    for(int i = 0; i < prefix.size(); i++)
    {
        if(prefix[i] != target[i+offset])
        {
            return false;
        }
    }

    return true;
}


std::vector<std::list<int> > allConstruct(const std::string &target, 
        const std::vector<std::string> &wordBank, int offset)
{
    static std::unordered_map<int, std::vector<std::list<int> > > lookup;

    if(lookup.find(offset) != lookup.end())
    {
        return lookup[offset];
    }

    std::vector<std::list<int> > solutions;

    // solution found
    if(offset >= target.size())
    {
        std::list<int> temp;
        solutions.push_back(temp);
        return solutions;
    }

    for(int i = 0; i < wordBank.size(); i++)
    {
        const std::string &prefix = wordBank[i];

        // If target string at given offset begins with current prefix string
        if(hasPrefix(target, prefix, offset))
        {
            //std::cout << "Prefix: " << prefix << ", Target: " << target.substr(offset) << std::endl;
            std::vector<std::list<int> > results = allConstruct(target, wordBank, offset + prefix.size());

            for(auto &result: results)
            {
                result.push_front(i);
                solutions.push_back(result);
            }
        }
    }

    lookup[offset] = solutions;
    return solutions;
}

int main(int args, const char *argv[])
{
    std::string target = "abcdef";
    std::vector<std::string> wordBank { "ab", "abc", "cd", "def", "abcd" };

    // std::string target = "purple";
    // std::vector<std::string> wordBank { "purp", "p", "ur", "le", "purpl" };

    std::vector<std::list<int> > solutions = allConstruct(target, wordBank, 0);

    for(auto itr = solutions.begin(); itr != solutions.end(); itr++)
    {
        const std::list<int> &list = *itr;

        for(auto listItr = list.begin(); listItr != list.end(); listItr++)
        {
            if(listItr != list.begin()) std::cout << ", ";
            std::cout << wordBank[*listItr];
        }

        std::cout << std::endl;
    }

    return 0;
}
