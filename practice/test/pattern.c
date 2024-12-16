#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_WORDS 1000
#define MAX_STR 100000
#define MAX_LEN_WORD 1024

int convertIntoArray(char *str, char arr[][MAX_LEN_WORD]){
    int len = strlen(str);
    if(str[len-1] == ']') str[len-1] = '\0';
    if(str[0] == '[') str++;

    len = strlen(str);
    if(len<2){printf("Invalid input"); exit(-1);}

    int count = 0;
    char *token = strtok(str," ");
    while(token != NULL){
        int ll = strlen(token);
        if(token[ll-1]== ',')token[ll-1]= '\0';
        //printf(" len : %d | %s \n", strlen(token),token);
        strncpy(arr[count],token, strlen(token));
        count++;
        token = strtok(NULL," ");
    }
    return count;
}



// int findPattern(char*str, char* pattern, char out[][MAX_LEN_WORD]){
//     char wordsArr[MAX_WORDS][MAX_LEN_WORD];
//     int wordIdx = convertIntoArray(str,wordsArr);

//     int matchPattern = makePattern(pattern);

//     int count =0;
//     for(int i =0 ;i< wordIdx; i++)
//     {
//         int temp = makepattern(wordsArr[i]);
//         if(temp == matchPattern){
//             int len = strlen(wordsArr[i]);
//             strncpy(out[count],wordsArr[i],len);
//             count++;
//         }
//     }

//     return count;
// }

//[peet, abcd, loot, geek, cool, for, peer]

int main() {
    char input[MAX_STR];
    printf("Input: ");
    fgets(input, MAX_STR ,stdin);
    input[strcspn(input,"\n")] = '\0';

    char pattern[MAX_STR];
    printf("pattern: ");
    fgets(pattern, MAX_STR,stdin);
    pattern[strcspn(pattern,"\n")] = '\0';
    // printf("Output: %s", input);

    char outPutArr[MAX_WORDS][MAX_LEN_WORD];
    char wordsArr[MAX_WORDS][MAX_LEN_WORD];
    int wordCount = convertIntoArray(input,wordsArr);
    // int wordCount = findPattern(input,pattern,outPutArr);

    if(wordCount == 0)
        printf("No match found..!");
    else {
        printf("Output: \n");
        for(int i =0 ;i<wordCount;i++)
            printf(" %d : %s\n",i+1, outPutArr[i]);
    }

    return 0;
}