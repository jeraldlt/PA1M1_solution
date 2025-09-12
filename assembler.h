#ifndef ASSEMBLER_H
#define ASSEMBLER_H

int parseNum(char* string);
char* removeComment(char* string);
char* trimString(char* string);
int regNum(char* regString);
int assembleLine(char* line);

#endif
