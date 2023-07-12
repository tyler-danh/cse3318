#include <stdio.h>
#include <string.h>

int main(void)
{
    #ifdef Woof
        int Dog[] = {2,3,4,10,42,47,49,50};
    #elif Bark
        int Dog[] = {1,2,3,4,5};
    #else
        int Dog[] = {2,3,4,10,11,15,40,42,47,49};
    #endif

    int i = 0;
    int sum = 0;
    int Cat = sizeof(Dog)/sizeof(Dog[0]);

    for(i = 0; i<Cat; i++)
        sum+=Dog[i];

    printf("%d", sum);
   
    return 0;
}