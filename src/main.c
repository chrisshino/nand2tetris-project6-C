#include <stdio.h>
#include "../include/parser.h"
#include "../include/symbolTable.h"
#include <string.h>

int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        // Check if the user provided exactly one command-line argument
        printf("Usage: %s <filename>\n", argv[0]);
        return 1; // Return a non-zero value to indicate an error
    }

    const char *filename = argv[1]; // Get the filename from the command line

    // input file
    parser_init(filename, "r");
    // intermediate file
    parser_init("intermediate.asm", "w+");
    // output file
    parser_init("out.asm", "w");

    char current_instruction[1024];

    HashTable *symboltable = symbolTable_init();
    int current_line_number = 0;

    // print the symbolTable
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        KeyValue *current = symboltable->table[i];
        while (current != NULL)
        {
            // printf("%s: %d\n", current->symbol, current->address);
            current = current->next;
        }
    }

    // first pass
    while (hasMoreLines(current_instruction, 1))
    {
        advance(current_instruction, &current_line_number, symboltable, 1);
    }

    current_line_number = 0;
    rewindIntermediateFile();

    // second pass use the output file
    while (hasMoreLines(current_instruction, 2))
    {
        advance(current_instruction, &current_line_number, symboltable, 2);
    }

    // delete the intermediate file
    remove("intermediate.asm");

    return 0; // Return 0 to indicate successful execution
}
