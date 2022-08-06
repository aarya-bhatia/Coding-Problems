/**
 * Shortest Common Supersequence
 */

#include <string>
#include <iostream>
#include <unordered_map>
#include <utility>

struct MyHash
{
    std::size_t operator()(const std::pair<int, int> &val) const noexcept
    {
        std::hash<int> hashInt;
        std::size_t first = hashInt(val.first);
        std::size_t second = hashInt(val.second);
        return first ^ (second << 1);
    }
};

/**
 * @param x first subsequence
 * @param y second subsequence
 * @param m end index of first sequence
 * @param n end index of second sequence
 * @return length of shortest sequence z obtained by adding items to x and y s.t. 
 * both x,y are subsequences of z
 */
int SCSLength(std::string x, std::string y, int m, int n, 
        std::unordered_map<std::pair<int, int>, int, MyHash> &lookup)
{
    if(m == 0 || n == 0)
    {
        return std::max(m, n);
    }

    std::pair<int,int> key = std::make_pair(m, n);

    if(lookup.find(key) == lookup.end())
    {
        if(x[m-1] == y[n-1])
        {
            lookup[key] = 1 + SCSLength(x,y,m-1,n-1,lookup);
        }
        else
        {
            lookup[key] = 1 + std::min(
                SCSLength(x,y,m-1,n,lookup),
                SCSLength(x,y,m,n-1,lookup)
            );
        }
    }

    return lookup[key];
}

int SCSLength(std::string x, std::string y)
{
    std::unordered_map<std::pair<int, int>, int, MyHash> lookup;

    return SCSLength(x, y, x.length(), y.length(), lookup);
}

int main()
{
    std::string x = "ABCBDAB";
    std::string y = "BDCABA";
    int res = SCSLength(x, y);
    std::cout << "Length of shortest common supersequence = " << res << "\n";
    return 0;
}
