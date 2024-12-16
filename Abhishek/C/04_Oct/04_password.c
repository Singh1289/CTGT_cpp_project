/*
    Program to prompt the user to enter a password and check if it meets the strength criteria. 
    Inform the user if the password is unacceptable, strong or weak based on the criteria. 
    If the password doesn't meet the criteria, generate and suggest 2-3 strong passwords to the 
    user which the user can select. (Example Criteria: 
    (a) Minimum length of 8 characters. 
    (b) Must include at least one uppercase letter, one lowercase letter, one digit, and one special character.)
*/

#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


char message[]="at least one uppercase letter,\none lowercase letter, one digit,\none special character and\nno white space.";
char salt[15] = "SecretSalt123@";

/*
    checking password valid or not 
    returning true and false
*/
int CheckPassword(char *str, int length)
{
    
    if (length < 8 || length == 0 ) 
    {
        printf("\nMinimum length of 8 characters.");
        return 0;
    }
    
    // tkaing variables for each case
    int cap,small,special,digits;
    cap=small=special=digits = 0;

    //validating the password for each case
    for(int i=0 ; i< length; i++)
    {   
       
        char c= str[i];
        if(c > 32 && c < 127)
        {
            if(c>64 && c<91 && cap == 0) cap=1;
            if(c>96 && c<123 && small == 0) small=1;
            if(c>47 && c<58 && digits == 0) digits=1;
            if(!(c>64 && c<91) && !(c>96 && c<123) && !(c>47 && c<58) && special == 0) 
                special=1;
            if(cap == 1 && small == 1 && special == 1 && digits == 1) break;
        }
        else
        {
            printf("\n%s",message);
            return 0;
        }
    }

    if(cap == 0)
    {
        printf("\nAt least one uppercase letter required.");
        return 0; 
    }
    if(small == 0)
    {
        printf("\nAt least one lowercase letter required.");
        return 0; 
    }
    if(digits == 0)
    {
        printf("\nAt least one digit letter required.");
        return 0; 
    }
    if(special == 0)
    {
        printf("\nAt least one special letter required.");
        return 0; 
    }
   
    return 1;
}

// function to generate random password using salt
int randomPassword(char pass[])
{
    printf("\n Choose a random Password");
    int k=0 ,length = strlen(salt);
    char randomPass[3][15];
    
    while (k !=3)
    {
        for(int i=0;i<length;i++)
        {
            char c= salt[i];
            int randNum= (rand() % 94) + 33;
            if(c+randNum<125)
                salt[i]= c+randNum;
            else
                salt[i]= randNum;
        }
        strcpy(randomPass[k],salt);
        printf("\n%d : %s",k+1,randomPass[k]);
        k++;
    }
    printf("\n4 : try again!");
    while(1){
        int t;
        printf("\n Choose from the options.");
        scanf("%d",&t);
        getchar();
        if(t==4) return 0;
        if(t>0 && t<4)
        {
            strcpy(pass,randomPass[t-1]);
            return 1;
        }
    }
    
}


void main()
{
    
    char password[50];
   
   // code
    while(1)
    {
        // taking password from user
        printf("\nEnter Password : ");
        scanf("%s", password);
        getchar();
        int length = strlen(password);
        // validating password 
        if(CheckPassword(password, length))
        {
            printf("\n%s",password);
            printf("\nGiven password is strong.");
            break;
        }
        else
        {   
            // creating password and select from 3 suggestion
            if(randomPassword(password))
            {
                printf("\n%s",password);
                break;
            }
            printf("\n%s",message);
        }
    }
}