#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int helper(int n, int *value)
{
    if(value[n] != 0)
    {
        return value[n];
    }
    value[n] = helper(n-1, value) + helper(n-2, value);
    return value[n];
}

int climbStaris(int n)
{
    int *value = NULL;
    int res = 0;
    value = (int *)malloc(sizeof(int) * (n+1));
    if(value == NULL)
        return -1;
    
    memset(value, 0, sizeof(int)*(n+1));
    value[0] = 0;
    value[1] = 1;
    value[2] = 2;
    res = helper(n,value);
    free(value);
    return res;
}

int main()
{
    printf("\r\nnum%d ,%d",5,climbStaris(5));
	printf("\r\nnum%d ,%d",6,climbStaris(6));
	printf("\r\nnum%d ,%d",7,climbStaris(7));
	return 0;
}