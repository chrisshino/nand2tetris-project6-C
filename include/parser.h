#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include <stdio.h>
#include "../include/symbolTable.h"

enum InstructionType
{
    A_INSTRUCTION,
    L_INSTRUCTION,
    C_INSTRUCTION
};

void parser_init(const char *filename, char *mode);
bool hasMoreLines(char *current_instruction, int pass_iteration);
void advance(char *current_instruction, int *current_line_number, HashTable *symboltable, int pass_iteration);
enum InstructionType instructionType(char *current_instruction);
void rewindIntermediateFile();

#endif