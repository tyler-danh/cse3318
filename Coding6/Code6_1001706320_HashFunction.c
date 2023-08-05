//Tyler Danh 1001706320
#include <stdio.h>
#define HASHTABLESIZE 10

int MyHashFunction(char HashValue[])
{
    int i,j = 0;
    while(HashValue[i] != '\0')
    {
        j += (int)HashValue[i];
        i++;
    }
    return j % HASHTABLESIZE;
}

int main(void)
{
    char HashValue[20];
    printf("Enter value ");
    scanf("%s", HashValue);
    printf("The hash value for %s is %d\n", HashValue, MyHashFunction(HashValue));
    return 0;
}