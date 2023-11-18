#include <stdio.h>
#include <string.h>
#include "../include/code.h"
#include <stdlib.h>
#include "../include/helpers.h"

char *code_translate(char *input)
{

    char *comp_input = comp(input);
    char *jump_input = jump(input);
    char *dest_input = dest(input);

    // remove any newlines from the input
    char *dest_binary_output = "000";
    char *comp_binary_output = "0000000";
    char *jump_binary_output = "000";

    if (dest_input != NULL)
    {
        stripNewline(dest_input);
        dest_binary_output = dest_binary(dest_input);
    }

    if (comp_input != NULL)
    {
        stripNewline(comp_input);
        comp_binary_output = comp_binary(comp_input);
    }

    if (jump_input != NULL)
    {
        stripNewline(jump_input);
        jump_binary_output = jump_binary(jump_input);
    }

    char *output = malloc(16 * sizeof(char));
    strcpy(output, "111");
    strcat(output, comp_binary_output);
    strcat(output, dest_binary_output);
    strcat(output, jump_binary_output);

    return output;
}

char *dest(char *input)
{
    char *copy_input = strdup(input);
    char *dest_string = strtok(copy_input, "=");

    // if dest_string produces an equal value to copy_input then there is no dest
    if (strcmp(dest_string, input) == 0)
    {
        return NULL;
    }

    // strtok to return anything before an = sign
    return dest_string;
}

char *dest_binary(char *dest_string)
{
    // if dest_string == M return 001
    if (strcmp(dest_string, "M") == 0)
    {
        return "001";
    }

    // if dest_string == D return 010
    if (strcmp(dest_string, "D") == 0)
    {
        return "010";
    }

    // if dest_string == MD return 011
    if (strcmp(dest_string, "MD") == 0)
    {
        return "011";
    }

    // if dest_string == A return 100
    if (strcmp(dest_string, "A") == 0)
    {
        return "100";
    }

    // if dest_string == AM return 101
    if (strcmp(dest_string, "AM") == 0)
    {
        return "101";
    }

    // if dest_string == AD return 110
    if (strcmp(dest_string, "AD") == 0)
    {
        return "110";
    }

    // if dest_string == ADM return 111
    if (strcmp(dest_string, "ADM") == 0)
    {
        return "111";
    }

    return "000";
}

char *comp(char *input)
{
    char *copy_input = strdup(input);
    char *comp_string = strtok(copy_input, ";");

    if (strcmp(comp_string, input) == 0)
    {
        comp_string = strtok(copy_input, "=");
        comp_string = strtok(NULL, "=");

        if (comp_string == NULL)
        {
            return NULL;
        }
    }

    return comp_string;
}

char *comp_binary(char *comp_string)
{
    // if comp_string == 0 return 0101010
    if (strcmp(comp_string, "0") == 0)
    {
        return "0101010";
    }

    // if comp_string == 1 return 0111111
    if (strcmp(comp_string, "1") == 0)
    {
        return "0111111";
    }

    // if comp_string == -1 return 0111010
    if (strcmp(comp_string, "-1") == 0)
    {
        return "0111010";
    }

    // if comp_string == D return 0001100
    if (strcmp(comp_string, "D") == 0)
    {
        return "0001100";
    }

    // if comp_string == A return 0110000
    if (strcmp(comp_string, "A") == 0)
    {
        return "0110000";
    }

    // if comp_string == M return 1110000
    if (strcmp(comp_string, "M") == 0)
    {
        return "1110000";
    }

    // if comp_string == !D return 0001101
    if (strcmp(comp_string, "!D") == 0)
    {
        return "0001101";
    }

    // if comp_string == !A return 0110001
    if (strcmp(comp_string, "!A") == 0)
    {
        return "0110001";
    }

    // if comp_string == !M return 1110001
    if (strcmp(comp_string, "!M") == 0)
    {
        return "1110001";
    }

    // if comp_string == -D return 0001111
    if (strcmp(comp_string, "-D") == 0)
    {
        return "0001111";
    }

    // if comp_string == -A return 0110011
    if (strcmp(comp_string, "-A") == 0)
    {
        return "0110011";
    }

    // if comp_string == -M return 1110011
    if (strcmp(comp_string, "-M") == 0)
    {
        return "1110011";
    }

    // if comp_string == D+1 return 0011111
    if (strcmp(comp_string, "D+1") == 0)
    {
        return "0011111";
    }

    // if comp_string == A+1 return 0110111
    if (strcmp(comp_string, "A+1") == 0)
    {
        return "0110111";
    }

    // if comp_string == M+1 return 1110111
    if (strcmp(comp_string, "M+1") == 0)
    {
        return "1110111";
    }

    // if comp_string == D-1 return 0001110
    if (strcmp(comp_string, "D-1") == 0)
    {
        return "0001110";
    }

    // if comp_string == A-1 return 0110010
    if (strcmp(comp_string, "A-1") == 0)
    {
        return "0110010";
    }

    // if comp_string == M-1 return 1110010
    if (strcmp(comp_string, "M-1") == 0)
    {
        return "1110010";
    }

    // if comp_string == D+A return 0000010
    if (strcmp(comp_string, "D+A") == 0)
    {
        return "0000010";
    }

    // if comp_string == D+M return 1000010
    if (strcmp(comp_string, "D+M") == 0)
    {
        return "1000010";
    }

    // if comp_string == D-A return 0010011
    if (strcmp(comp_string, "D-A") == 0)
    {
        return "0010011";
    }

    // if comp_string == D-M return 1010011
    if (strcmp(comp_string, "D-M") == 0)
    {
        return "1010011";
    }

    // if comp_string == A-D return 0000111
    if (strcmp(comp_string, "A-D") == 0)
    {
        return "0000111";
    }

    // if comp_string == M-D return 1000111
    if (strcmp(comp_string, "M-D") == 0)
    {
        return "1000111";
    }

    // if comp_string == D&A return 0000000
    if (strcmp(comp_string, "D&A") == 0)
    {
        return "0000000";
    }

    // if comp_string == D&M return 1000000
    if (strcmp(comp_string, "D&M") == 0)
    {
        return "1000000";
    }

    // if comp_string == D|A return 0010101
    if (strcmp(comp_string, "D|A") == 0)
    {
        return "0010101";
    }

    // if comp_string == D|M return 1010101
    if (strcmp(comp_string, "D|M") == 0)
    {
        return "1010101";
    }

    return "0000000";
}

char *jump(char *input)
{
    char *copy_input = strdup(input);
    char *jump_string = strtok(copy_input, ";");

    // don't capture the value before ; capture the value after
    jump_string = strtok(NULL, ";");

    if (jump_string == NULL)
    {
        return NULL;
    }

    return jump_string;
}

char *jump_binary(char *jump_string)
{
    // if jump_string == JGT return 001
    if (strcmp(jump_string, "JGT") == 0)
    {
        return "001";
    }

    // if jump_string == JEQ return 010
    if (strcmp(jump_string, "JEQ") == 0)
    {
        return "010";
    }

    // if jump_string == JGE return 011
    if (strcmp(jump_string, "JGE") == 0)
    {
        return "011";
    }

    // if jump_string == JLT return 100
    if (strcmp(jump_string, "JLT") == 0)
    {
        return "100";
    }

    // if jump_string == JNE return 101
    if (strcmp(jump_string, "JNE") == 0)
    {
        return "101";
    }

    // if jump_string == JLE return 110
    if (strcmp(jump_string, "JLE") == 0)
    {
        return "110";
    }

    // if jump_string == JMP return 111
    if (strcmp(jump_string, "JMP") == 0)
    {
        return "111";
    }

    return "000";
}