/*
    1. Program to check if a string of parentheses is balanced. 
    The string is balanced if every opening parenthesis has a 
    corresponding closing parenthesis and they are correctly nested. 
    Input: A string consisting of parentheses (and optionally other
    characters). E.g., (a + b) * (c - d), (a + b * (c - d). 
    Output: Balanced or Not-balanced.
*/

#include <stdio.h>
#include <string.h>
#include "MyStack.h"
#include "MyStack.c"

int isBalanced(const char *str,MyStack *stack,int size)
{
    char ch;
    for(int i=0; i<size;i++)
    {
        ch = str[i];
        // if it is opeing brackets then push
        if (ch == '(' || ch == '{' || ch == '[' || ch == '<') {
            push(stack, ch);
        } 
        // Check closing brackets then pop
        else if (ch == ')' || ch == '}' || ch == ']' || ch == '>') {
            if (isEmpty(stack)) return -1; 

            char top = peek(stack);

            // Check for matching opening brackets
            if ((ch == ')' && top == '(') || 
                (ch == '}' && top == '{') || 
                (ch == ']' && top == '[') || 
                (ch == '>' && top == '<')) {
                pop(stack);
            } else {
                return -1; 
            }
        }
    }
    return (isEmpty(stack)) ? 1 : -1; 
}

void main()
{
    char input[100];
    // taking input
    printf("\nEnter string : ");
    scanf("%100s",input);


    int size = strlen(input);
    // Intializing Mystack with null.
    MyStack stack;
    stack.top= NULL;
    
    // is Balance function will check weather is it balanced or not
    if(isBalanced(input,&stack, size) == 1)
        printf("\nBalanced");
    else
        printf("\nNot-balanced.");
}