#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 1000000  // Maximum number of words
#define MAX_LENGTH 100000  // Maximum length of a word

// Function to generate the pattern signature of a word
void get_pattern_signature(const char *word, int *signature) {
    int char_map[256];  // Mapping for characters
    int next_index = 0;

    for (int i = 0; i < 256; i++) {
        char_map[i] = -1;  // Initialize map to -1
    }

    int length = strlen(word);
    for (int i = 0; i < length; i++) {
        if (char_map[(unsigned char)word[i]] == -1) {
            char_map[(unsigned char)word[i]] = next_index++;
        }
        signature[i] = char_map[(unsigned char)word[i]];
    }
}

// Function to check if two signatures match
int signatures_match(int *sig1, int *sig2, int length) {
    for (int i = 0; i < length; i++) {
        if (sig1[i] != sig2[i]) {
            return 0;
        }
    }
    return 1;
}

// Function to find matching words
void find_matching_words(char words[][MAX_LENGTH], int num_words, const char *pattern) {
    int pattern_length = strlen(pattern);
    int pattern_signature[pattern_length];
    get_pattern_signature(pattern, pattern_signature);  // Get pattern signature

    for (int i = 0; i < num_words; i++) {
        int word_length = strlen(words[i]);
        
        // Skip words with different lengths
        if (word_length != pattern_length) {
            continue;
        }
        
        int word_signature[word_length];
        get_pattern_signature(words[i], word_signature);  // Get word signature
        
        // Compare the word signature to the pattern signature
        if (signatures_match(word_signature, pattern_signature, word_length)) {
            printf("%s ", words[i]);  // Print matching word
        }
    }
    printf("\n");
}

// Main function
int main() {
    char words[MAX_WORDS][MAX_LENGTH] = {
        "peet", "abcd", "loot", "geek", "cool", "for", "peer", "dear", "seed", "meet", "noon", "otto", "mess", "loss"
    };
    int num_words = 14;  // Number of words in the list

    char pattern[MAX_LENGTH] = "moon";

    printf("Matching words: ");
    find_matching_words(words, num_words, pattern);

    return 0;
}
