#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
 
#define WORDLENGTH 1000
#define WORDS 1000  
 
 
bool patternmatch(const char *word, const char *pattern) {
    if (strlen(word) != strlen(pattern)) {
        return false;
    }
 
    char wordarr[256] = {0};
    char patternarr[256] = {0};
 
    for (int i = 0; word[i] != '\0'; i++) {
        char pchar = pattern[i];
        char wchar = word[i];
 
        if (wordarr[(unsigned char)pchar] == 0) {
            wordarr[(unsigned char)pchar] = wchar;
        } else if (wordarr[(unsigned char)pchar] != wchar) {
            return false;
        }
 
        if (patternarr[(unsigned char)wchar] == 0) {
            patternarr[(unsigned char)wchar] = pchar;
        } else if (patternarr[(unsigned char)wchar] != pchar) {
            return false;
        }
    }
 
    return true;
}
 
 
int wordssplit(char *input, char *wordlist[], int maxwords) {
    char *start, *end;
    int count = 0;
 
 
    start = strchr(input, '[');
    if (start == NULL) {
        return 0;
    }
 
    end = strchr(start, ']');
    if (end == NULL) {
        return 0;
    }
 
    *end = '\0';
    start++;
 
    char *word = strtok(start, ",");
    while (word != NULL && count < maxwords)
    {
        while (*word == ' ') word++;
        char *word_end = word + strlen(word) - 1;
        while (*word_end == ' ') word_end--;
        *(word_end + 1) = '\0';
 
        wordlist[count] = (char *)malloc(strlen(word) + 1);
        if (wordlist[count] == NULL) {
            printf("error\n");
            exit(1);
        }
        strcpy(wordlist[count], word);
        count++;
        word = strtok(NULL, ",");
    }
 
    return count;
}
 
void findmatchingwords(char *wordlist[], int list_size, const char *pattern) {
    int found = 0;
    for (int i = 0; i < list_size; i++) {
        if (patternmatch(wordlist[i], pattern)) {
            if (found > 0) {
                printf(", ");
            }
            printf("%s", wordlist[i]);
            found++;
        }
    }
    if (found == 0) {
        printf("No matching words found.");
    }
    printf("\n");
}
 
int main() {
    char input[WORDLENGTH * WORDS];
    int listsize;
    printf("Enter the list of words : ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
 
    char *word_list[WORDS];
    listsize = wordssplit(input, word_list, WORDS);
 
    if (listsize == 0) {
        printf("Invalid input\n");
        return 1;
    }
 
    char pattern[WORDLENGTH];
    printf("Enter the pattern: ");
    scanf("%s", pattern);
 
 
    printf("Matching words are \n", pattern);
    findmatchingwords(word_list, listsize, pattern);
 
 
    return 0;
}