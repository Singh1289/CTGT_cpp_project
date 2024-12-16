#include <stdio.h>
#include <string.h>
#include <ctype.h>
 
void removeSpecialChar(char *text) {
    int i = 0, j = 0;
    while (text[i] != '\0') {
        // Allow only letters, digits, and spaces
        if (isalnum(text[i]) || text[i] == ' ') {
            text[j++] = text[i];
        }
        i++;
    }
    text[j] = '\0';
}
 
void removeExtraSpaces(char *text) {
    int i = 0, j = 0;
    int inSpace = 0;
 
    while (text[i] != '\0') {
        if (text[i] != ' ') {
            text[j++] = text[i];
            inSpace = 0;
        } else if (!inSpace) {
            text[j++] = ' ';
            inSpace = 1;
        }
        i++;
    }
 
    if (j > 0 && text[j - 1] == ' ') {
        j--; 
    }
 
    text[j] = '\0';
}
 
void sanitizeText(char *text) {
    removeSpecialChar(text);
    removeExtraSpaces(text);
}
 
int main() {
    //char input[256]= "abhishek    .....abhi$$$$   ///  is dyebron3435b 2343 34 djfdisnns.....,,,,adsygdsad,,,,sdfs    asdd  }}}} kfdjn.";
    char input[256];
    printf("Enter a block of text: ");
    fgets(input, sizeof(input), stdin);
    sanitizeText(input);
    printf("Sanitized text: %s\n", input);
    return 0;
}