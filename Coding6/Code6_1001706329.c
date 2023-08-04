#include <stdio.h>

typedef struct YourStructName
{
char *name;
float height;
float weight;
char gender;
int age;
char *grade;
char *jujutsu;
struct CursedEnergyUser *next_ptr;
}
CursedEnergyUser;

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