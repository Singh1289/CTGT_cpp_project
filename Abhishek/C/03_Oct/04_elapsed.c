/*
    Program to calculate total elapsed time by the program and a function used in 
    the program (i.e., the time taken to process the set of statements within a 
    function/program) and print source code along with the total elapsed time. 
*/


#include<stdio.h>
#include<time.h>
#include<math.h>

// function defination
void function()
{
    long a = 1;
    for(int i=0; i<1000000;i++)
    {
        a= log(i*i);
    }
}

int main()
{
    // calculate time before fucction call
    clock_t elapsedTime = clock();
    
    // function call
    function();
   
    // mark the time atfer function execution and calaulate elaplsed time
    elapsedTime = clock()-elapsedTime;

    // printing funtion
    printf("\nvoid function()");
    printf("\n{");
    printf("\nlong a = 1");
    printf("\nfor(int i=0; i<1000000;i++)");
    printf("\n{");
    printf("\n    a= log(i*i);");
    printf("\n}");
    printf("\n}");

    // printing time that it takes in sec
    printf("total time taken : %.10f", (double)elapsedTime/CLOCKS_PER_SEC);

    return 0;
}