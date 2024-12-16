/*
  Program to swap the byte ordering/endianness of a number from Little Endian 
  to Big Endian and vice versa.
*/

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

// checking if it is Hexa decimal on not
int isHex(const char * num)
{
    if(num[0]== '0' && (num[1] == 'x' || num[1] == 'X'))
    {
        for(int i = 2 ; i<strlen(num);i++)
        {
            if (!((num[i] >= '0' && num[i] <= '9') || 
                  (num[i] >= 'A' && num[i] <= 'F') || 
                  (num[i] >= 'a' && num[i] <= 'f')))  
            return 0;
        }
        return 1;
    }
    else 
        return 0;
}


// converting in binary for endian 
void convertInBinary(int num, int big[], int litle[])
{
    printf("\n function called");
    int temp, end = 31, start = 0;
    while (num != 0)
    {
        temp = num % 2;
        big[end--] = temp;
        litle[start++]= temp;
        num /= 2;
    }
    
}


void main()
{

    // declaration of vairables
   char input[100];
   int number;
   int bigEndian[32]= {0};
   int littleEndian[32]= {0};

    // taking input in string 
   printf("\nEnter number : ");
   scanf("%s",input);


    /*
        ~ first check is it hexadecimal number or not 
        ~ if yes then convert it in decimal
        ~ from string to integer
    */
   if(isHex(input))
     {   
        printf("\n it is HEX number");
        number = strtol(input,NULL,16);
     }
    else    
    {   
        printf("\n it is decimal number");
        number = atoi(input);
     }

    printf("\n Number is : %d",number); //1451


    // converting it in binary
    convertInBinary(number,bigEndian,littleEndian);



    // printing both big endian and little endian
    printf("\n Big endian : ");
    for(int i=0 ;i<32;i++)
        printf(" %d",bigEndian[i]);


    printf("\n Little endian : ");
    for(int i=0 ;i<32;i++)
        printf(" %d",littleEndian[i]);


}
