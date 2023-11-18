#ifndef CODE_H

char *code_translate(char *input);
char *dest(char *input);
char *comp(char *input);
char *jump(char *input);
char *dest_binary(char *dest_string);
char *comp_binary(char *comp_string);
char *jump_binary(char *jump_string);

#endif