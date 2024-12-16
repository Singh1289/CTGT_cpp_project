#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 1000
#define MAX_STR 100000
#define MAX_LEN_WORD 1024

int convertIntoArray(char *str, char arr[][MAX_LEN_WORD]) {
    int len = strlen(str);
    if (len < 2) { 
        printf("Invalid input\n");
        exit(-1);
    }
    if (str[len - 1] == ']') str[len - 1] = '\0';
    if (str[0] == '[') str++;

    int count = 0;
    char *token = strtok(str, " ");
    while (token != NULL) {
        int ll = strlen(token);
        if (token[ll - 1] == ',') token[ll - 1] = '\0';
        
        if (count < MAX_WORDS) {
            strncpy(arr[count], token, MAX_LEN_WORD - 1);
            arr[count][MAX_LEN_WORD - 1] = '\0';
            count++;
        } else {
            printf("Exceeded maximum number of words\n");
            break;
        }
        token = strtok(NULL, " ");
    }
    return count;
}

int makePattern(const char *str) {
    int len = strlen(str);
    if (len == 0) return 0;

    int res = 1, num = 1;
    for (int i = 1; i < len; i++) {
        if (str[i - 1] == str[i]) {
            res = res * 10 + num;
        } else {
            res = res * 10 + ++num;
        }
    }
    return res;
}

int findPattern(int wordIdx, char *pattern, char wordsArr[][MAX_LEN_WORD], char out[][MAX_LEN_WORD]) {
    int matchPattern = makePattern(pattern);
    int count = 0;
    for (int i = 0; i < wordIdx; i++) {
        int temp = makePattern(wordsArr[i]);
        if (temp == matchPattern) {
            strncpy(out[count], wordsArr[i], MAX_LEN_WORD - 1);
            out[count][MAX_LEN_WORD - 1] = '\0';
            count++;
        }
    }
    return count;
}

int main() {
    char input[MAX_STR];
    printf("Input: ");
    fgets(input, MAX_STR, stdin);
    input[strcspn(input, "\n")] = '\0';

    char pattern[MAX_STR];
    printf("Pattern: ");
    fgets(pattern, MAX_STR, stdin);
    pattern[strcspn(pattern, "\n")] = '\0';

    if (strlen(input) < 2 || strlen(pattern) == 0) {
        printf("Invalid input or pattern\n");
        return -1;
    }

    char wordsArr[MAX_WORDS][MAX_LEN_WORD];
    char outPutArr[MAX_WORDS][MAX_LEN_WORD];
    
    int wordCount = convertIntoArray(input, wordsArr);
    int matchCount = findPattern(wordCount, pattern, wordsArr, outPutArr);

    if (matchCount == 0) {
        printf("No match found..!\n");
    } else {
        printf("Output:\n");
        for (int i = 0; i < matchCount; i++) {
            printf("%d : %s\n", i + 1, outPutArr[i]);
        }
    }

    return 0;
}
