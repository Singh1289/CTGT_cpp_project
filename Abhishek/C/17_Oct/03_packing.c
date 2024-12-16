/*
    Program to compress data by packing multiple small values into a single integer to save space. 
    Each value is a small integer, and use bitwise operations to pack and unpack these values efficiently. 
    Implement functions to pack and unpack values using bitwise operations. Example, Pack four 8-bit 
    values into a single 32-bit integer and Unpack the 32-bit integer back into four 8-bit values. 
    Example output: Packed Integer: 0x0C192525 (hexadecimal representation) and Unpacked Values: 12, 25, 37, 55.

 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// converting into binary
void convertInBinary(int num,int number[])
{
    static int index = 31;
    printf("\n function called");
    int temp;
 
    for(int i=0;i<8 || (num != 0 && index != -1);i++)
    {   
        if(num == 0) number[index--]= 0;
        else
        {
            temp = num % 2;
            number[index--] = temp;
            num /= 2;
        }
    }
    
}

    // takin input arr
void takingInput(int input[])
{
    for(int i=0;i<4;)
    {
        printf("\nEnter Number : ");
        scanf("%d",&input[i++]);
    }
}

int convert_in_decimal( int number[])
{
    int res=0 , power=0;
    for(int i=31 ;i>=0; i--)
    {
        res += number[i]* pow((double)2,(double)power);
        power++;
    }
    return res;
}


void main()
{
    int input[4];
    takingInput(input);
    int number[32]={0};
    char arr[32]={' '};
    for(int i =3;i>=0;i--)
    {
        convertInBinary(input[i], number);
    }

    printf("\nUnpacked numbers : ");
    for(int i=0;i<4;)
        printf("%d, ",input[i++]);
    

    printf("\nBig endian : ");
    for(int i=0; i<32; i++)
    {
        printf("%d ",number[i]);
        arr[i] = number[i];
    }
    

    printf("\nLittle endian : ");
    for(int i=31; i>=0; i--)
    {
        printf("%d ",number[i]);
    }
    int temp = convert_in_decimal(number);
    printf("\nPacked number : 0x%X",temp);


}