// hash table for handle any input like integer, double, string,character by using union and funtion pointer for every input type

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10000

typedef union {
    int integer;
    double double_value;
    char* string_value;
    char character;
} inputKey;


typedef struct Node {
    inputKey key;
    void* value;
    struct Node* next;
} Node;

typedef struct {
    Node** table;
    int size;
} HashTable;

HashTable* createHashTable(int size);

void insert(HashTable* hashTable, inputKey key, void* value);

void* search(HashTable* hashTable, inputKey key);

void destroyHashTable(HashTable* hashTable);

int hashFunction(HashTable* hashTable, inputKey key);

void printHashTable(HashTable* hashTable);

void freeNode(Node* node);


#endif // HASHTABLE_H