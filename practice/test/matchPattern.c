
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 100000
#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

int createWordsList(char *str, char list[MAX_WORDS][MAX_WORD_LENGTH])
{
    if (str[0] == '[')
        str++;
    if (str[strlen(str) - 1] == ']')
        str[strlen(str) - 1] = '\0';

    int len = strlen(str);
    if (len < 1)
    {
        printf("Empty string\n");
        exit(1);
    }

    int idx = 0;
    char *token = strtok(str, " ");
    while (token != NULL && idx < MAX_WORDS)
    {
        int len = strlen(token);
        if (token[len - 1] == ',')
        {
            token[len - 1] = '\0';
        }
        len = strlen(token);
        strncpy(list[idx], token, len);
        list[idx][len] = '\0';
        idx++;
        token = strtok(NULL, " ");
    }
    return idx;
}

int cretingPattern(const char *str)
{
    int num = 1;
    int result = 1;

    char tempStr[strlen(str) + 1];
    strcpy(tempStr, str);

    for (int i = 0; tempStr[i] != '\0'; i++)
    {
        tempStr[i] = tolower((unsigned char)tempStr[i]);
    }

    for (int i = 1; tempStr[i] != '\0'; i++)
    {
        if (tempStr[i - 1] == tempStr[i])
        {
            result = result * 10 + num;
        }
        else
        {
            result = result * 10 + ++num;
        }
    }

    return result;
}

int findWords(char list[MAX_WORDS][MAX_WORD_LENGTH], char out[MAX_WORDS][MAX_WORD_LENGTH], int listIdx, int pattern)
{
    printf("pattern: %d\n", pattern);
    int result = 0;
    for (int i = 0; i < listIdx; i++)
    {
        int wordPattern = cretingPattern(list[i]);
        printf("word: %s, pattern: %d\n", list[i], wordPattern);
        if (wordPattern == pattern)
        {
            strncpy(out[result], list[i], strlen(list[i]));
            result++;
        }
    }
    return result;
}

int main()
{
    printf("Input: ");
    char input[MAX_SIZE];
    if (fgets(input, MAX_SIZE, stdin) != NULL)
    {
        input[strcspn(input, "\n")] = '\0';
    }
    else
    {
        printf("Error reading input\n");
        return 1;
    }

    char list[MAX_WORDS][MAX_WORD_LENGTH];
    char outPut[MAX_WORDS][MAX_WORD_LENGTH];
    int listSize = createWordsList(input, list);

    char word[MAX_WORD_LENGTH];
    printf("Enter a word: ");
    fgets(word, MAX_WORD_LENGTH, stdin);
    word[strcspn(word, "\n")] = '\0';

    int pattern = cretingPattern(word);
    int index = findWords(list, outPut, listSize, pattern);

    if (index)
    {
        printf("Output: [");
        for (int i = 0; i < index; i++)
        {
            printf("%s", outPut[i]);
            if (i != index - 1)
                printf(", ");
        }
        printf("]\n");
    }
    else
    {
        printf("No words found\n");
    }

    return 0;
}
