#include<stdio.h>
#include<string.h>

void main(){
    char brand[] ="Abhishek";
    char brand1[] ="Pratap Singh";
    char brand3[30] ;
    strcpy(brand3,brand1);
    strcat(brand3,brand);
    printf("%s",brand3);
}