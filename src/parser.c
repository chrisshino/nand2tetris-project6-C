#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "../include/parser.h"
#include "../include/helpers.h"
#include "../include/symbolTable.h"
#include "../include/code.h"
#include <stdlib.h>

FILE *parser_file;
FILE *intermediatry_file;
FILE *output_file;

void parser_init(const char *filename, char *mode)
{
    if (strcmp(mode, "r") == 0)
    {
        parser_file = fopen(filename, mode);
        if (parser_file == NULL)
        {
            printf("Error: could not open file %s\n", filename);
            return;
        }

        return;
    }
    if (strcmp(mode, "w+") == 0)
    {
        intermediatry_file = fopen(filename, mode);
        if (intermediatry_file == NULL)
        {
            printf("Error: could not open file %s\n", filename);
            return;
        }

        return;
    }
    output_file = fopen(filename, mode);
}

bool hasMoreLines(char *current_instruction, int pass_iteration)
{
    char line[1024];

    FILE *current_file;

    if (pass_iteration == 1)
    {
        current_file = parser_file;
    }
    else
    {
        current_file = intermediatry_file;
    }

    if (fgets(line, sizeof(line), current_file) != NULL)
    {
        strcpy(current_instruction, line);
        return true;
    }

    return false;
}

int A_INSTRUCTION_ADDRESS = 16;

void advance(char *current_instruction, int *current_line_number, HashTable *symboltable, int pass_iteration)
{
    stripWhitespace(current_instruction);
    stripComments(current_instruction);

    if (current_instruction[0] == '\n')
    {
        stripNewline(current_instruction);
        return;
    }

    enum InstructionType type = instructionType(current_instruction);

    if (pass_iteration == 1)
    {
        fprintf(intermediatry_file, "%s", current_instruction);
    }

    // If the instruction is a L instruction / Label declaration, we need to add it to the symbol table
    if (type == L_INSTRUCTION && pass_iteration == 1)
    {
        char label[1024];

        extractLabel(current_instruction, label, sizeof(label));
        addEntry(label, *current_line_number, symboltable);
        return;
    }

    if (type == A_INSTRUCTION && !isdigit(current_instruction[1]) && pass_iteration == 2)
    {
        memmove(current_instruction, current_instruction + 1, strlen(current_instruction));
        stripWhitespace(current_instruction);
        stripNewline(current_instruction);

        bool contains_symbol = contains(symboltable, current_instruction);

        if (!contains_symbol)
        {
            addEntry(current_instruction, A_INSTRUCTION_ADDRESS, symboltable);
            A_INSTRUCTION_ADDRESS++;
        }

        int address = get(symboltable, current_instruction);

        // convert the address to binary
        char *output_binary;
        output_binary = decimal_to_binary(&address);

        fprintf(output_file, "%s\n", output_binary);
    }

    if (type == A_INSTRUCTION && isdigit(current_instruction[1]) && pass_iteration == 2)
    {
        memmove(current_instruction, current_instruction + 1, strlen(current_instruction));
        stripWhitespace(current_instruction);
        stripNewline(current_instruction);

        int address = atoi(current_instruction);

        // convert the address to binary
        char *output_binary;
        output_binary = decimal_to_binary(&address);

        fprintf(output_file, "%s\n", output_binary);
    }

    if (type == C_INSTRUCTION && pass_iteration == 2)
    {
        char *output_binary;
        output_binary = code_translate(current_instruction);

        // write the instruction to the output file
        fprintf(output_file, "%s\n", output_binary);
    }

    (*current_line_number)++;
}

enum InstructionType instructionType(char *current_instruction)
{
    if (*current_instruction == '@')
    {
        return A_INSTRUCTION;
    }
    else if (*current_instruction == '(')
    {
        return L_INSTRUCTION;
    }
    else
    {
        return C_INSTRUCTION;
    }
}

void rewindIntermediateFile()
{
    fseek(intermediatry_file, 0, SEEK_SET);
}