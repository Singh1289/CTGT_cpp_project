/*
    Program to Reverse All Bits of a 32-bit Integer
*/

#include<stdio.h>
#include<math.h>

// flip the bit by 
// convert into binary then flip and convert it back in decimal 
int reverseBits(int num) {
    
    int count=0, result= 0;
    int bit[32]= {0};
    
    //code
    // convert in binary 
    while(num != 0)
    {
        bit[count++]= num % 2;
        num /= 2;
    }
    
    for(int i = 0 ;i<count;i++ )
        bit[i] = (bit[i] == 0)? 1: 0;

    // Convert back to decimal
    for (int i = 0; i < count; i++) {
        result += bit[i] * pow(2,i);
    }
    return result;
}


void main()
{
    int number;
    // taking input in integer
    while (1)
    {
        printf("\nENter number : ");
        if(scanf("%d",&number));
         break;
         printf("\nInvalid.. Only integer value.");
    }


    // fliging the bits and store in result
    int result = reverseBits(number);

    printf("\n After Fliping: %d",result);
    

}