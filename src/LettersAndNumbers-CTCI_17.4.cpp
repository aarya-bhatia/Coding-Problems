/* PROBLEM 17.4 FROM CRACKING THE CODING INTERVIEW BOOK */

/**
 * Description
 *
 * Given array of letters and numbers.
 * Find the longest subarray with an equal number of letters and numbers.
 *
 */


#include <bits/stdc++.h>

using namespace std;

vector<char> solve(vector<char> array)
{
    vector<int> deltas(array.size(), 0);

    int delta = 0;

    for(int i = 0; i < array.size(); i++)
    {
        char c = array[i];

        if(c >= '0' && c <= '9') delta--;

        char lower = tolower(c);

        if(lower >= 'a' && lower <= 'z') delta++;

        deltas[i] = delta;
    }

    unordered_map<int, int> deltaMap;
    deltaMap[0] = -1;
    int maxDist = -1, start = 0, end = 0;

    for(int i = 0; i < deltas.size(); i++)
    {
        int d = deltas[i];

        if(deltaMap.find(d) == deltaMap.end())
        {
            deltaMap[d] = i;
        }

        if(maxDist == -1 || maxDist < i - deltaMap[d])
        {
            maxDist = i - deltaMap[d];
            start = deltaMap[d] + 1;
            end = i;
        }
    }

    if(maxDist == -1) return {};

    vector<char> result;
    result.insert(result.begin(), array.begin() + start, array.begin() + end + 1);

    cout << "original array size: " << array.size() << endl;
    cout << "max subarray size: " << result.size() << endl;

    for(char i: result) cout << i << " ";
    cout << endl;

    return result;
}

vector<char> boolToCharArray(vector<bool> bv)
{
    vector<char> v;
    for(bool b: bv) v.push_back(b ? '1' : 'A');
    return v;
}

int main()
{
    solve(boolToCharArray({0,1,0,0,0,1,1,0,1,0,0,1,1,1,0,1}));
    solve(boolToCharArray({0,1,0,0,0,1,1,0,1,0,0,1,1,0,1}));
    solve(boolToCharArray({0,1,0,0,0,1,1,0,1,1,1,1,0,1}));
    solve(boolToCharArray({1,1,0,1,1,1,1,0,1}));
    solve(boolToCharArray({1,0,0,0,1,1,0,1,1,1,1,0,1}));
    solve(boolToCharArray({1,0,1,1,0,1,1,1,1,0,1}));
    solve(boolToCharArray({0,1,0,0,0,0,1,1,1,0,1}));
    solve(boolToCharArray({0,0,0,1,1,1,0,1}));
    solve(boolToCharArray({0,0,0,0,0,0,0,0}));
    return 0;
}
