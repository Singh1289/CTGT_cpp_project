/*
    Program to check if a user provided IP Address (IPv4) is valid or not
    Approch - first check lenght of the input
    2. split if with . 
    3. convert the string to decimal number
    4. then check the number range is it is in the range then return true and false.
*/

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

int checkLength(const char *input)
{
    if(strlen(input)<=15) 
        return 0; 
    else 
    {
        printf("\nAddress length is not valid.");
        return 1;
    }
}

/*
    validating string for special charator ,alphabats and .
*/
int validateString (const char *input)
{   
    char tempStr[16];  
    strcpy(tempStr, input);
    int dot = 0;
    for(int i=0;tempStr[i] != '\0';i++)
    {
        if(!isdigit(tempStr[i]))
        {
           // printf("\ninput %d: %c ",i,tempStr[i]);
            if(tempStr[i] == '.') 
                dot++;
            else
                return 0;
        }
    }
    //printf("\ndot: %d",dot);
    return (dot == 3) ? 1:0;
}


/*
    spliting IP string into sub string array according to delimeter '.'
*/
void splitString(const char *str, char tokens[4][4]) {
    //printf("\n splitString called");
    
    // Temporary variable to store string
    char tempStr[16];  
    strcpy(tempStr, str);  

    // Split string based on "."
    char *token = strtok(tempStr, ".");
    
    int i = 0;

    while (token != NULL && i < 4) {
        // Copy each token to the tokens array  
        strcpy(tokens[i], token); 
        i++;
        
        // Get the next token
        token = strtok(NULL, ".");
        //if(token != NULL) dot++;
    }
}

/* 
    here we convert each sub string into integer.
    then check the value is in range 0 - 255
*/
int validateRange(char tokens[4][4])
{
    int temp = 0;
    for (int j = 0; j < 4; j++) 
    { 
        temp =  strtol(tokens[j], NULL, 10);
        if(temp < 0 || temp > 255) return 0;
    }
    return 1;
}

// checking IP is valid and retrun true /false
int isIP_valid(const char *input)
{
    if(checkLength(input)) return 0;

    // validate string
    if(!validateString(input)) return 0;
    // spliting input into sub array 
    char stringArray[4][4];
    splitString(input,stringArray);

    return (validateRange(stringArray)) ? 1 :0;
}



void main()
{
    char input_IP[16];
    printf("enter IPv4 Address : ");
    scanf("%[^\n]s",input_IP);

    //fgets(input_IP,16,stdin);
    printf("\nGiven address : %s",input_IP);

    if(isIP_valid(input_IP))
        printf("\nIP address is valid.");
    else
        printf("\nIP address is not valid.");

}