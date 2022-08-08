#include <bits/stdc++.h>
using namespace std;

bool debug = false;

// Keypad digits 0 to 9 mapped to letters on the button
vector<vector<char>> keynums = {
    {},
    {},
    {'a', 'b', 'c'},
    {'d', 'e', 'f'},
    {'g', 'h', 'i'},
    {'j', 'k', 'l'},
    {'m', 'n', 'o'},
    {'p', 'q', 'r', 's'},
    {'t', 'u', 'v'},
    {'w', 'x', 'y', 'z'},
};

struct TrieNode
{
    char value;
    TrieNode *children[26];
    bool terminates = false;

    TrieNode(char c)
    {
        value = c;

        for (int i = 0; i < 26; i++)
        {
            children[i] = nullptr;
        }
    }

    void add(string s)
    {
        if (s.empty())
        {
            return;
        }

        char current = s[0];
        int i = current - 'a';

        if (!children[i])
        {
            children[i] = new TrieNode(current);
        }

        if (s.size() == 1)
        {
            children[i]->terminates = true;
        }

        children[i]->add(s.substr(1));
    }

    ~TrieNode()
    {
        for (int i = 0; i < 26; i++)
        {
            if (children[i])
                delete children[i];
        }
    }
};

vector<string> getMatchingWords(string number, vector<string> dictionary, TrieNode *root)
{
    stack<pair<TrieNode *, string>> searchStack;
    vector<string> result;

    searchStack.push({root, ""});

    while (!searchStack.empty())
    {
        const auto &p = searchStack.top();
        TrieNode *curr = p.first;
        string s = p.second;
        searchStack.pop();

        if (!curr)
        {
            continue;
        }

        size_t len = s.size();

        // Found partial word
        if (s.size() >= number.size())
        {
            if (curr->terminates)
            {
                cout << number << " -> " << s << endl;
                result.push_back(s);
            }
        }
        else
        {
            vector<char> &ch = keynums[number[len] - '0'];

            for (char c : ch)
            {
                int index = c - 'a';
                if (curr->children[index] != nullptr)
                {
                    TrieNode *node = curr->children[index];
                    string partial = s + c;
                    searchStack.push(make_pair(node, partial));
                }
            }
        }
    }

    return result;
}

int main()
{
    vector<string> words;
    string line;

    ifstream myfile("/Users/Aarya/Development/four-letter-words.txt");

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            words.push_back(line);
        }

        myfile.close();
    }
    else
    {
        cout << "Failed to open file\n";
    }

    // build trie

    TrieNode *root = new TrieNode(0);

    for (const string &s : words)
    {
        root->add(s);
    }

    vector<string> inputs = {"8733", "5423", "6777", "8094", "3702", "5645", "5498", "3484", "3767", "4322",
                             "2236", "2663", "2257", "7634", "5888", "5555", "4456", "4587", "8456", "9745"};

    for_each(inputs.begin(), inputs.end(), [&](const string &str)
             { getMatchingWords(str, words, root); });

    delete root;

    return 0;
}