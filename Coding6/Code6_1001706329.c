#include <stdio.h>

typedef struct
{
    /* data */
}
placeholder;

int MyHashFunction(HashValue)
{

}

int main(void)
{
    char HashValue[20];
    printf("Enter value ");
    scanf("%s ", HashValue);
    printf("The hash value for %s is %d\n", HashValue, MyHashFunction(HashValue));
    return 0;
}