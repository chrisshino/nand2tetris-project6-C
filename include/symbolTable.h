#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#define HASH_TABLE_SIZE 100

// Define a structure for key-value pairs
typedef struct KeyValue
{
    char symbol[64]; // Assuming a maximum symbol length of 63 characters
    int address;
    struct KeyValue *next; // Pointer to the next KeyValue pair in case of collisions
} KeyValue;

// Define a hash table structure
typedef struct
{
    KeyValue *table[HASH_TABLE_SIZE];
} HashTable;

HashTable *symbolTable_init();
void addEntry(char *symbol, int address, HashTable *symboltable);
int get(HashTable *ht, const char *symbol);
bool contains(HashTable *ht, const char *symbol);

#endif