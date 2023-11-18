#ifndef HELPERS_H
#define HELPERS_H

#include <ctype.h>

void stripWhitespace(char *input);
void stripComments(char *input);
void extractLabel(const char *input, char *label, size_t labelMaxLength);
void stripNewline(char *input);
char *decimal_to_binary(int *output);

#endif