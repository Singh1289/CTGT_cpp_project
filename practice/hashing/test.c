#include<stdio.h>
int hashFunctionInteger(int key){
    // return (int)(((long)key * (long)key) % 1003);
    int a = key % 1003;
    return (a*a) % 1003;
}

void main()
{
   int i=24;
    printf("%xd \n",i);
    printf("%zu \n",i);
    printf("%d\n",&i);
 
    int array[100];
    printf("%d \n",&array[0]);
    printf("%zu",array);
}