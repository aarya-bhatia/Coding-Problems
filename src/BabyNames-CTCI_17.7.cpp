#include <bits/stdc++.h>
using namespace std;

/*

You are given a map of words to frequencies. There is a dictionary containing pairs of words that are synonyms with each other. The task is to compress the frequency table so that all rows containing synonyms are merged into one with their frequencies summed up. You must only use the longest synonym if there are any.


*/

struct Solution
{
    unordered_map<string, string> m;

    void solve(unordered_map<string,int> &frequencies, unordered_map<string,string> &dictionary);
    void updatePath(const string &word, unordered_map<string, string> &dictionary);
};

/* Merge synonym word rows in frequency table */
void Solution::solve(unordered_map<string, int> &frequencies, unordered_map<string, string> &dictionary)
{
    for (auto &kv : dictionary)
    {
        const string &k = kv.first;
        if(m.find(k) == m.end()) {
            updatePath(k, dictionary);
        }
    }

    for(auto &kv: dictionary)
    {
        dictionary[kv.second] = kv.first;
    }

    for(auto &kv: m)
    {
        const string &k = kv.first;
        frequencies[m[k]] += frequencies[k];
        frequencies.erase(k);
    }
}

/* Map every word to its longest synonym */
void Solution::updatePath(const string &word, unordered_map<string, string> &dictionary) {
    stack<string> path; // parent nodes in path
    string current = word;
    string best = word;

    while(dictionary.find(current) != dictionary.end()){
        const string &parent = dictionary[current];

        if (best.size() < parent.size()){
            best = parent;
        }

        path.push(current);
        path.push(dictionary[current]);
        current = parent;
    }

    while(!path.empty()){
        const string &s = path.top();
        m[s] = best;
        // printf("%s-> %s to %s\n", s.c_str(), dictionary[s].c_str(), m[s].c_str());
        path.pop();
    }

    m.erase(best);
}

int main()
{
    Solution s;
    unordered_map<string,int> frequencies;
    unordered_map<string,string> dictionary;

    frequencies = {
        {"A", 1},
        {"AA", 2},
        {"AAA", 4},
        {"AAAA", 1},
        {"B", 2},
        {"CC", 3},
        {"CCC", 4},
        {"ABAB", 1},
        {"D", 8},
    };

    dictionary = { 
        {"A","AA"},
        {"AA","AAA"},
        {"AAA","AAAA"},
        {"BB","B"},
        {"CCC","C"},
        {"CC","CCCC"},
        {"ABAB","AB"},
    };

    cout << "dictionary: ";
    for(auto &kv: dictionary) cout << kv.first << "-> " << kv.second << "\n";
    cout << endl;
    cout << endl;

    cout << "initial: ";
    for(auto &kv: frequencies) cout << kv.first << "-> " << kv.second << "\n";
    cout << endl;
    cout << endl;

    s.solve(frequencies, dictionary);

    cout << "new dictionary: ";
    for(auto &kv: s.m) cout << kv.first << "-> " << kv.second << "\n";
    cout << endl;
    cout << endl;

    cout << "solution: ";
    for(auto &kv: frequencies) cout << kv.first << "-> " << kv.second << "\n";
    cout << endl;
    cout << endl;
    
    return 0;
}
