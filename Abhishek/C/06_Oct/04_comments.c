/*
Program to extract comments from source code and print the extracted comments. The program should identify and extract comments in a user entered C/C++ program (using file handing)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LINE_LENGTH 1048

// array to store the lines of the source code
char lines[MAX_LINES][MAX_LINE_LENGTH];
int lineCount = 0;

// funtion to prints the comments from the file
void extractComments(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return;
    }

    // flag to keep track of multi line comments
    int multi_flag = 0; 

    while (fgets(lines[lineCount], MAX_LINE_LENGTH, file) != NULL) {

        if (multi_flag) {
            printf("%s", lines[lineCount]); 
            if (strstr(lines[lineCount], "*/") != NULL) {
                multi_flag = 0; 
            }
        } else if (strncmp(lines[lineCount], "//", 2) == 0) { 
            printf("%s", lines[lineCount]);

        } else if (strstr(lines[lineCount], "/*") != NULL) {
           
            multi_flag = 1;
            printf("%s", lines[lineCount]);
        }
        lineCount++;
        
        if (lineCount >= MAX_LINES) {
            printf("Reached maximum number of lines.\n");
            break;
        }
    }

    fclose(file);
    printf("Comments extracted successfully.\n");
}

int main() {
    char filename[100];
    printf("Enter the filename to extract comments from: ");
    scanf("%s", filename);
    // calling function to extract comments
    extractComments(filename);

    return 0;
}

