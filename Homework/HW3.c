#include <stdio.h>
#include <stdlib.h>

int FunctionR(int n)
{
   if(n==0)
   {
        return n;
   }
   else
   {
    return FunctionR(n-1) + n;
   }
}

int main(void)
{
    int num;

    printf("Enter a positive integer: ");
    scanf("%d", &num);

    printf("%d", FunctionR(num));

    return 0;
}