#include <string>
#include <iostream>
#include <stack>

std::string lcs(std::string s1, std::string s2)
{
    size_t n1 = s1.size() + 1;
    size_t n2 = s2.size() + 1; 

    unsigned int dp[n1][n2];

    for(int i = 0; i < n1; i++)
    {
        dp[i][0] = 0;
    }

    for(int j = 0; j < n2; j++)
    {
        dp[0][j] = 0;
    }

    unsigned int maxLen = 0;
    unsigned int row = 0;
    unsigned int col = 0;

    for(int i = 1; i < n1; i++)
    {
        for(int j = 1; j < n2; j++)
        {
            if(s1[i-1]==s2[j-1])
            {
                dp[i][j] = 1 + dp[i-1][j-1];
            }
            else
            {
                dp[i][j] = 0;
            }

            if(maxLen < dp[i][j])
            {
                maxLen = dp[i][j];
                row = i;
                col = j;
            }
        }
    }

    std::stack<char> substring;

    while(row > 0 && col > 0 && s1[row-1] > 0)
    {
        substring.push(s1[row-1]);
        row--;
        col--;
    }

    std::string s = "";

    while(!substring.empty())
    {
        s.push_back(substring.top());
        substring.pop();
    }

    return s;
}

int main()
{
    std::string result = "";
    std::string s1 = "nabzd";
    std::string s2 = "ababfd";

    result = lcs(s1, s2);

    std::cout << "result:" << result << "\n";
}