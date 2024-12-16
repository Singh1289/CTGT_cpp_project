/*
    Program to Convert a number from Base 1 to Base 2 where Base 1 and Base 2 
    are specified by the user.
*/

#include<stdio.h>
#include<string.h>
#include<math.h>


/*
    - ask user to provide base of input and input
    - convert it is decimal 
    - then convert it in any base 
*/

// showing base list
void showDataTypes(int *base)
{
    printf("\n~~~~~ Base table ~~~~~");
    printf("\n Binary - 2 ");
    printf("\n Octal - 8");
    printf("\n Decimal - 10");
    printf("\n Hexa - 16");
    while(1)
    {   // validatiing the choice at same time
        printf("\nChoose from the list : ");
        scanf("%d",base);
        if(*base == 2 || *base == 8 || *base == 10 || *base == 16 )
            break;
    }
}


// Function to convert binary input to decimal
void getBinary(char *in, int *decimal) {
    while (1) {
        // Reset flag for each input attempt
        int flag = 1; 
        printf("\nEnter input: ");
        scanf("%s", in); 
        
        for (int i = 0; i < strlen(in); i++) {
            if (in[i] != '0' && in[i] != '1') {
                flag = 0; 
                break;
            }
        }
        if (flag) break; 
        printf("\nInvalid input. Only 0 or 1 allowed.");
    }
    
    // Convert binary string to decimal
    *decimal = 0;
    for (int i = 0; i < strlen(in); i++) {
        *decimal = (*decimal << 1) | (in[i] - '0');
    }
}


// Function to convert decimal input and validate
void getDecimal(int *decimal) {
    while (1) {
        printf("\nEnter decimal input: ");
        if (scanf("%d", decimal) == 1) {
            break;
        }
        printf("\nInvalid input. Please enter a valid decimal number.");
        while (getchar() != '\n'); // Clear the buffer
    }
}

// Function to convert hexadecimal input to decimal
void getHexa(char *in, int *decimal) {
    while (1) {
        int flag = 1; 
        printf("\nEnter hexadecimal input: ");
        scanf("%s", in);
        
        for (int i = 0; i < strlen(in); i++) {
            if (!((in[i] >= '0' && in[i] <= '9') || 
                  (in[i] >= 'A' && in[i] <= 'F') || 
                  (in[i] >= 'a' && in[i] <= 'f')))  {
                flag = 0; 
                break;
            }
        }
        // it input is valid then break
        if (flag) break; 
        printf("\nInvalid input. Only digits 0-9 and letters A-F allowed.");
    }
    
    // Convert hexadecimal string to decimal
    *decimal = 0;
    for (int i = 0; i < strlen(in); i++) {
        if (in[i] >= '0' && in[i] <= '9') {
            *decimal = (*decimal * 16) + (in[i] - '0');
        } else if (in[i] >= 'A' && in[i] <= 'F') {
            *decimal = (*decimal * 16) + (in[i] - 'A' + 10);
        } else if (in[i] >= 'a' && in[i] <= 'f') {
            *decimal = (*decimal * 16) + (in[i] - 'a' + 10);
        }
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// converting decimal to binary 
void printBinary(int *decimal) {
    int num = *decimal;
    char result[32] = {0};  
    int count = 0;

    // Handle the case for 0
    if (num == 0) {
        printf("\nIn Binary: 0\n");
        return;
    }

    // Convert to binary
    while (num != 0) {
         // Store as character
        result[count++] = (num % 2) + '0';
        num /= 2;
    }

    printf("\nIn Binary: ");
    // Print in reverse order
    for (int i = count - 1; i >= 0; i--) {
        printf("%c", result[i]);
    }
    printf("\n");
}



void printOctal(int *decimal) {
    int num = *decimal;
    char result[32] = {0};  // To hold octal digits
    int count = 0;

    // Handle the case for 0
    if (num == 0) {
        printf("\nIn Octal: 0\n");
        return;
    }

    // Convert to octal
    while (num != 0) {
        result[count++] = (num % 8) + '0'; 
        num /= 8;
    }

    printf("\nIn Octal: ");
    
    for (int i = count - 1; i >= 0; i--) {
        printf("%c", result[i]);
    }
    printf("\n");
}

 // Convert to hexadecimal
void printHexa(int *decimal) {
    int num = *decimal;
    char result[32];  
    int count = 0;

    // Handle the case for 0
    if (num == 0) {
        printf("\nIn Hexadecimal: 0\n");
        return;
    }

    // Convert to hexadecimal
    while (num != 0) {
        int remainder = num % 16;
        if (remainder < 10) {
             // Store as character '0' to '9'
            result[count++] = remainder + '0';
        } else {
            // Store as character 'A' to 'F'
            result[count++] = (remainder - 10) + 'A'; 
        }
        num /= 16;
    }

    printf("\nIn Hexadecimal: ");
    // Print in reverse order
    for (int i = count - 1; i >= 0; i--) {
        printf("%c", result[i]);
    }
    printf("\n");
}



void main()
{
    char input[50];
    int base;
    int decimal;
    showDataTypes(&base);
    
    
    switch(base)
    {
        case 2: getBinary(input,&decimal);
                break;
       // case 8: getOctal(input, &decimal);
                break;
                
        case 10: getDecimal(&decimal);
                break;
        case 16 : getHexa(input, &decimal);
    }

    base = 0;
    printf("\nIn which bse you want to convert : ");
    showDataTypes(&base);


    // converting it and display on screen
    switch(base)
    {
        case 2: printBinary(&decimal);
                break;
        case 8: printOctal(&decimal);
                break;
        case 10: printf("\nIn decimal : %d\n",decimal);
                break;
        case 16 : printHexa(&decimal);
    }  

}