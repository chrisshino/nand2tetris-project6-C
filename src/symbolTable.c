#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/symbolTable.h"

unsigned int hash(const char *symbol)
{
    unsigned int hash = 0;
    while (*symbol)
    {
        hash = (hash << 5) + (*symbol);
        symbol++;
    }
    return hash % HASH_TABLE_SIZE;
}

// Function to insert a key-value pair into the hash table
void insert(HashTable *ht, const char *symbol, int address)
{
    unsigned int index = hash(symbol);

    // Create a new KeyValue pair
    KeyValue *newPair = (KeyValue *)malloc(sizeof(KeyValue));
    if (newPair == NULL)
    {
        perror("Memory allocation failed");
        exit(1);
    }

    strcpy(newPair->symbol, symbol);
    newPair->address = address;
    newPair->next = NULL;

    // If the slot is empty, insert the pair
    if (ht->table[index] == NULL)
    {
        ht->table[index] = newPair;
    }
    else
    {
        // If there's a collision, add the pair to the linked list3
        KeyValue *current = ht->table[index];
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newPair;
    }
}

// Function to retrieve the address for a given symbol
int get(HashTable *ht, const char *symbol)
{
    unsigned int index = hash(symbol);

    // Print the hash value for debugging
    // printf("Debug: Hash value for symbol '%s' is %u\n", symbol, index);

    // Search for the symbol in the linked list
    KeyValue *current = ht->table[index];
    while (current != NULL)
    {
        if (strcmp(current->symbol, symbol) == 0)
        {
            return current->address;
        }
        current = current->next;
    }
    return -1;
}

HashTable *symbolTable_init()
{
    // create a hash data structure where the key is symbol and the value is address
    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
    if (ht == NULL)
    {
        perror("Memory allocation failed");
        exit(1);
    }

    // Initialize the hash table
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        ht->table[i] = NULL;
    }

    // Add the predefined symbols to the hash table
    insert(ht, "SP", 0);
    insert(ht, "LCL", 1);
    insert(ht, "ARG", 2);
    insert(ht, "THIS", 3);
    insert(ht, "THAT", 4);

    // for loop to add R0-R15 to the hash table
    for (int i = 0; i < 16; i++)
    {
        char symbol[64];
        sprintf(symbol, "R%d", i);
        insert(ht, symbol, i);
    }

    insert(ht, "SCREEN", 16384);
    insert(ht, "KBD", 24576);

    return ht;
}

void addEntry(char *symbol, int address, HashTable *symboltable)
{
    printf("Adding symbol '%s' with address %d\n", symbol, address);

    // insert the symbol and address into the hash table
    insert(symboltable, symbol, address);
}

bool contains(HashTable *ht, const char *symbol)
{
    return get(ht, symbol) != -1;
}