
#include <vector>
#include <cstdio>

long fib(int n)
{
    std::vector<long> table(n+1);

    table[0] = 0;
    table[1] = 1;

    for(int i = 2; i <= n; i++)
    {
        table[i] = table[i-1] + table[i-2];
    }
    
    printf("fib(%d): %ld\n", n, table[n]);
    return table[n];
}


int main()
{
    fib(5);
    fib(10);
    fib(100);
    return 0;
}


