#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *compress(const char *str)
{
    char *res = malloc(strlen(str) + 1);
    int end = 0;

    int start;
    
    for(start = 0; start < strlen(str) && end < strlen(res); )
    {
        int count= 1;

        for(int i = start+1; i < strlen(str); i++)
        {
            if(str[i] != str[start])break;
            count++;
        }

        char next[8];
        sprintf(next,"%c%d", str[start], count);
        strcpy(res, next);

        end += strlen(next);
        start += count;
    }    

    res = realloc(res, end+1);
    res[end] = 0;

    return res;
}

int main(int argc, const char *argv[])
{
    //int n = 4;
    //const char *tests[4] = { "AABBCC", "ABC", "BBAAAACCDDDD", "EEEEEEYYYYYPOPPPPOOOOPEEEY" };


    int n;
    if(argc < 2) n = 0;
    else n = atoi(argv[1]);

    for(int i = 0; i < n; i++)
    {
        const char *test = argv[2+i];

        char *s = compress(test);
        printf("%s -> %s:", test, s);

        if(strlen(s) < strlen(test)){ 
            printf("size decreased by %lu bytes\n", strlen(s) - strlen(test)); 
        }
        else {
            printf("size increased by %lu bytes\n", strlen(test) - strlen(s)); 
        }

        free(s);
    }

    return 0;
}
