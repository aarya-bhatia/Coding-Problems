#include <bits/stdc++.h>

bool contains(const std::vector<std::unordered_set<std::string>> &blocks, int i, const std::string &building)
{
    return blocks[i].find(building) != blocks[i].end();
}

int getBestDistance(const std::vector<std::unordered_set<std::string>> &blocks, const std::vector<std::string> &requirements)
{
    int n = blocks.size();
    int m = requirements.size();
    int best = INT_MAX;

    // dp[i][j] = min distance from block i to requirements[j]
    std::vector<std::vector<int>> dp(n, std::vector<int>(m, INT_MAX));

    for (int j = 0; j < m; j++)
    {
        dp[0][j] = contains(blocks, 0, requirements[j]) ? 0 : INT_MAX;
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (contains(blocks, i, requirements[j]))
            {
                dp[i][j] = 0;
            }
            else if (dp[i - 1][j] == INT_MAX)
            {
                dp[i][j] = std::min(dp[i][j], INT_MAX);
            }
            else
            {
                dp[i][j] = std::min(dp[i][j], dp[i - 1][j] + 1);
            }
        }
    }

    for (int j = 0; j < m; j++)
    {
        dp[n - 1][j] = contains(blocks, n - 1, requirements[j]) ? 0: INT_MAX;
    }

    for (int i = n - 2; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (contains(blocks, i, requirements[j]))
            {
                dp[i][j] = 0;
            }
            else if (dp[i + 1][j] == INT_MAX)
            {
                dp[i][j] = std::min(dp[i][j], INT_MAX);
            }
            else
            {
                dp[i][j] = std::min(dp[i][j], dp[i + 1][j] + 1);
            }
        }
    }

    for(int i = 0; i < n; i++)
    {
        int farthest = INT_MIN;

        for(int j = 0; j < m; j++)
        {
            farthest = std::max(farthest, dp[i][j]);
        }

        best = std::min(best, farthest);
    }

    return best;
}

int main()
{
    std::vector<std::unordered_set<std::string>> blocks = {
        {"school"},
        {"gym"},
        {"gym", "school"},
        {"school"},
        {"school", "store"}};

    std::vector<std::string> requirements = {"gym", "school", "store"};

    int result = getBestDistance(blocks, requirements);

    std::cout << "To minimum farthest distance to any of the buildings from an apartment is: " << result << " unit";

    return 0;
}
