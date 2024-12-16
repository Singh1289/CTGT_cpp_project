#include<stdio.h>
#include<string.h>
#include <stdlib.h>

// implemanting checksum function
int checkSum(char * str, int size)
{
    int len= strlen(str);
    int sum=0,temp;
    char binary[size+1];
    for(int i=0; i< len/size; i++)
    {
        strncpy(binary, str,size);
        str += size;
        binary[size+1] = '\0';
        

	// converting binary to decimal number
        temp = strtol(binary,NULL,2);
       
	// adding all decimal number
        sum += temp;
    }
    
    // returning ~ value
    return ~sum;
}

// validating the msg on reciveing side
int validateMessage(char * sent, char *rec, int blockSize)
{
    // if length is not multiple of blocksize then return false
    if(strlen(sent) % blockSize != 0) return 0;
    if(strlen(rec) % blockSize != 0) return 0;

    int value1 = checkSum(sent, blockSize);
    int value2 = checkSum(rec, blockSize);
    printf("\nvalue1 :%d  value2: %d",value1,value2);

    return (value1 == value2)? 1:0;
}


void main()
{

    char sent[] = "1010101111101111";
    char rec[]= "1010101110101111";
    int blockSize = 8;

    // validate the msg
    if(validateMessage(sent,rec,blockSize))
        printf("\nNo Error");
    else
        printf("\nError");
}