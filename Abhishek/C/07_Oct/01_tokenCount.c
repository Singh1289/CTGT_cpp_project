/*
    Program that dynamically splits a user entered string into tokens based on a delimiter provided by the user. Ask user whether splitting should be case-sensitive or case-insensitive and split accordingly. Trim whitespaces from each token and store it in a dynamically allocated data structure along with frequency of occurance of each token. Print the tokens along with their frequency.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 2000

// Structure to store each unique token and its frequency
typedef struct {
    char *token;
    int frequency;
} TokenFrequency;

// Function to trim whitespace 
char *trimWhitespace(char *str) {
    char *end=str + strlen(str) - 1;
    
    // Trim leading whitespace
    while (isspace((unsigned char)*str)) str++;

    // If the string is all spaces
    if (*str == 0) 
        return str;

    // tralling whitespace
    while (end > str && isspace((unsigned char)*end)) end--;

    *(end + 1) = '\0';

    return str;
}

// Convert a string to lowercase 
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
    }
}

int caseInSensitiveCompare(const char *s1, const char *s2) {
    char a[strlen(s1)], b[strlen(s2)];
    strcpy(a, s1);
    strcpy(b, s2);
    toLowerCase(a);
    toLowerCase(b);
    return strcmp(a, b);  
}

int findToken(TokenFrequency *tokens, int tokenCount, char *token, int caseInsensitive) {
    for (int i = 0; i < tokenCount; i++) {
        int result = caseInsensitive 
                     ? caseInSensitiveCompare(tokens[i].token, token)
                     : strcmp(tokens[i].token, token);
        if (result == 0) {
            return i;  
        }
    }
    return -1;  
}

// Function to split string and store tokens and their frequencies
void splitString(char *input,const char* delimiter, int caseInsensitive) {
    TokenFrequency *tokens = NULL;
    int tokenCount = 0;
    char *token = strtok(input, delimiter);

    while (token != NULL) {
        token = trimWhitespace(token);

        // Make a temporary copy of the token for case-insensitive comparison
        char tempToken[MAX_LEN];
        strcpy(tempToken, token);
        if (caseInsensitive) {
            toLowerCase(tempToken);
        }

        // Check if the token already exists in the list
        int index = findToken(tokens, tokenCount, tempToken, caseInsensitive);
        if (index != -1) {
            tokens[index].frequency++;
        } else {
            // Allocate memory for a new token
            tokens = realloc(tokens, (tokenCount + 1) * sizeof(TokenFrequency));
            tokens[tokenCount].token = strdup(token);
            tokens[tokenCount].frequency = 1;
            tokenCount++;
        }

        token = strtok(NULL, delimiter);
    }

    // Display the tokens and their frequencies
    printf("\nTokens and their frequencies:\n");
    for (int i = 0; i < tokenCount; i++) {
        printf("%-8s\t     -%5d\n", tokens[i].token, tokens[i].frequency);
        free(tokens[i].token); 
    }
    free(tokens); 
}

int main() {
    char input[MAX_LEN];
    char delimiter[] = " ";
    int caseInsensitive;

    printf("Enter a string: ");
    fgets(input, MAX_LEN, stdin);
    getchar();

    // printf("Enter a delimiter character: ");
    // scanf(" %c", &delimiter);

    printf("Case-insensitive split? (1 for Yes, 0 for No): ");
    scanf("%d", &caseInsensitive);

    // Call splitString with the user input
    splitString(input, delimiter, caseInsensitive);

    return 0;
}
