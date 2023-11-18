#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/parser.h"
#include <stdlib.h>

void stripWhitespace(char *input)
{
    int start = 0;
    int end = strlen(input) - 1;

    while (input[start] == ' ')
    {
        start++;
    }

    while (input[end] == ' ' || input[end] == '\n')
    {
        end--;
    }

    if (input[end + 1] != '\n')
    {
        input[end + 1] = '\n';
        end++;
    }

    input[end + 1] = '\0';

    memmove(input, input + start, end - start + 2);
}

void stripComments(char *input)
{
    char *pos = strstr(input, "//"); // Look for inline comments
    if (pos != NULL)
    {
        *pos = '\0'; // Null-terminate the string at the start of the comment
    }

    // Remove full-line comments by checking for empty lines after removing inline comments
    char *line = input;
    while (*line)
    {
        if (isblank((unsigned char)*line))
        {
            line++;
            continue; // Skip leading whitespace
        }
        if (isspace((unsigned char)*line))
        {
            *line = '\0'; // Null-terminate the string at the start of an empty line
            break;
        }
        line++;
    }

    strcat(input, "\n"); // Add a newline character to the end of the line
}

void extractLabel(const char *input, char *label, size_t labelSize)
{
    const char *start = strchr(input, '(');
    const char *end = strrchr(input, ')');

    if (start != NULL && end != NULL && start < end)
    {
        start++; // Move past the opening parenthesis
        size_t length = end - start;

        // Ensure the label size is not exceeded
        if (length >= labelSize - 1)
        {
            length = labelSize - 2;
        }

        strncpy(label, start, length);
        label[length] = '\0'; // Null-terminate the label
    }
    else
    {
        label[0] = '\0'; // No valid label found
    }
}

void stripNewline(char *str)
{
    int len = strlen(str);

    // Iterate through the string
    for (int i = 0; i < len; i++)
    {
        if (str[i] == '\n')
        {
            // Replace newline character with null terminator
            str[i] = '\0';
            break; // Exit the loop, assuming only one newline needs to be stripped
        }
    }
}

char *decimal_to_binary(int *output)
{
    //   so for example if I have output number of 20, I want it to look like: 0000000000010100

    char *binary = malloc(16 * sizeof(char));
    int i = 0;

    while (i < 16)
    {
        binary[i] = '0';
        i++;
    }

    int index = 15;

    while (*output > 0)
    {
        if (*output % 2 == 0)
        {
            binary[index] = '0';
        }
        else
        {
            binary[index] = '1';
        }

        *output = *output / 2;
        index--;
    }

    return binary;
}