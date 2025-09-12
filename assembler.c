#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "assembler.h"

#include <stdio.h>

int assembleLine(char* line) {
  char* strA = removeComment(line);
  char* strB = trimString(strA);
  // free(strA);
  
  char* mnemonic = strtok(strB, " ");
  int inst = 0;

  if (strcmp(mnemonic, "add") == 0) {
    char* rdStr = trimString(strtok(NULL, ","));
    int rd = regNum(rdStr);
    free(rdStr);
    char* rsStr = trimString(strtok(NULL, ","));
    int rs = regNum(rsStr);
    free(rsStr);
    char* rtStr = trimString(strtok(NULL, ","));
    int rt = regNum(rtStr);
    free(rtStr);

    inst = (rs << 21) | (rt << 16) | (rd << 11) | 0x20;
        
  } else if (strcmp(mnemonic, "addiu") == 0) {
    char* rtStr = trimString(strtok(NULL, ","));
    int rt = regNum(rtStr);
    free(rtStr);
    char* rsStr = trimString(strtok(NULL, ","));
    int rs = regNum(rsStr);
    free(rsStr);
    char* immStr = trimString(strtok(NULL, ","));
    int imm = parseNum(immStr);
    free(immStr);

    inst = (0x09 << 26) | (rs << 21) | (rt << 16) | (imm & 0xFFFF);

  } else if (strcmp(mnemonic, "and") == 0) {
    char* rdStr = trimString(strtok(NULL, ","));
    int rd = regNum(rdStr);
    free(rdStr);
    char* rsStr = trimString(strtok(NULL, ","));
    int rs = regNum(rsStr);
    free(rsStr);
    char* rtStr = trimString(strtok(NULL, ","));
    int rt = regNum(rtStr);
    free(rtStr);

    inst = (rs << 21) | (rt << 16) | (rd << 11) | 0x24;

  } else if (strcmp(mnemonic, "andi") == 0) {
    char* rtStr = trimString(strtok(NULL, ","));
    int rt = regNum(rtStr);
    free(rtStr);
    char* rsStr = trimString(strtok(NULL, ","));
    int rs = regNum(rsStr);
    free(rsStr);
    char* immStr = trimString(strtok(NULL, ","));
    int imm = parseNum(immStr);
    free(immStr);

    inst = (0x0C << 26) | (rs << 21) | (rt << 16) | (imm & 0xFFFF);

  } else if (strcmp(mnemonic, "lui") == 0) {
    char* rtStr = trimString(strtok(NULL, ","));
    int rt = regNum(rtStr);
    free(rtStr);
    char* immStr = trimString(strtok(NULL, ","));
    int imm = parseNum(immStr);
    free(immStr);

    inst = (0x0F << 26) | (rt << 16) | (imm & 0xFFFF);
    
  }

  free(strB);

  return inst;
  
}

int parseNum(char* string) {
  char* endPtr;
  int num = (int) strtol(string, &endPtr, 0);
  return num;
}

char* removeComment(char* string) {
  char* start = string;
  char* end = string;

  while (*end != '#') {
    if (*end == 0)
      return string;

    end++;
  }

  int newLen = (end - start) / sizeof(char);

  char* newString = (char*) malloc(sizeof(char) * newLen);
  char* newStart = newString;
  
  for (int i=0; i<newLen; i++) {
    *newStart = *start;
    newStart++;
    start++;
  }

  *newStart = 0;

  return newString;
  
}

char* trimString(char* string) {
  char* start = string;
  while (isspace(*start)) {
    start++;
  }
  
  char* end = string;

  while (*end != 0) {
    end++;
  }
  end--;
  while (isspace(*end)) {
    end--;
  }

  int newLen = (end - start) / sizeof(char);

  char* newString = (char*) malloc(sizeof(char) * (newLen + 1));
  char* newStart = newString;

  for (int i=0; i<=newLen; i++) {
    *newStart = *start;
    newStart++;
    start++;
  }

  *newStart = 0;

  return newString;
}

int regNum(char* regString) {

  if (strcmp(regString, "$zero") == 0
      || strcmp(regString, "$0") == 0) {
    return 0;
  } else if (strcmp(regString, "$at") == 0
             || strcmp(regString, "$1") == 0) {
    return 1;
  } else if (strcmp(regString, "$v0") == 0
             || strcmp(regString, "$2") == 0) {
    return 2;
  } else if (strcmp(regString, "$v1") == 0
             || strcmp(regString, "$3") == 0) {
    return 3;
  } else if (strcmp(regString, "$a0") == 0
             || strcmp(regString, "$4") == 0) {
    return 4;
  } else if (strcmp(regString, "$a1") == 0
             || strcmp(regString, "$5") == 0) {
    return 5;
  } else if (strcmp(regString, "$a2") == 0
             || strcmp(regString, "$6") == 0) {
    return 6;
  } else if (strcmp(regString, "$a3") == 0
             || strcmp(regString, "$7") == 0) {
    return 7;
  } else if (strcmp(regString, "$t0") == 0
             || strcmp(regString, "$8") == 0) {
    return 8;
  } else if (strcmp(regString, "$t1") == 0
             || strcmp(regString, "$9") == 0) {
    return 9;
  } else if (strcmp(regString, "$t2") == 0
             || strcmp(regString, "$10") == 0) {
    return 10;
  } else if (strcmp(regString, "$t3") == 0
             || strcmp(regString, "$11") == 0) {
    return 11;
  } else if (strcmp(regString, "$t4") == 0
             || strcmp(regString, "$12") == 0) {
    return 12;
  } else if (strcmp(regString, "$t5") == 0
             || strcmp(regString, "$13") == 0) {
    return 13;
  } else if (strcmp(regString, "$t6") == 0
             || strcmp(regString, "$14") == 0) {
    return 14;
  } else if (strcmp(regString, "$t7") == 0
             || strcmp(regString, "$15") == 0) {
    return 15;
  } else if (strcmp(regString, "$s0") == 0
             || strcmp(regString, "$16") == 0) {
    return 16;
  } else if (strcmp(regString, "$s1") == 0
             || strcmp(regString, "$17") == 0) {
    return 17;
  } else if (strcmp(regString, "$s2") == 0
             || strcmp(regString, "$18") == 0) {
    return 18;
  } else if (strcmp(regString, "$s3") == 0
             || strcmp(regString, "$19") == 0) {
    return 19;
  } else if (strcmp(regString, "$s4") == 0
             || strcmp(regString, "$20") == 0) {
    return 20;
  } else if (strcmp(regString, "$s5") == 0
             || strcmp(regString, "$21") == 0) {
    return 21;
  } else if (strcmp(regString, "$s6") == 0
             || strcmp(regString, "$22") == 0) {
    return 22;
  } else if (strcmp(regString, "$s7") == 0
             || strcmp(regString, "$23") == 0) {
    return 23;
  } else if (strcmp(regString, "$t8") == 0
             || strcmp(regString, "$24") == 0) {
    return 24;
  } else if (strcmp(regString, "$t9") == 0
             || strcmp(regString, "$25") == 0) {
    return 25;
  } else if (strcmp(regString, "$k0") == 0
             || strcmp(regString, "$26") == 0) {
    return 26;
  } else if (strcmp(regString, "$k1") == 0
             || strcmp(regString, "$27") == 0) {
    return 27;
  } else if (strcmp(regString, "$gp") == 0
             || strcmp(regString, "$28") == 0) {
    return 28;
  } else if (strcmp(regString, "$sp") == 0
             || strcmp(regString, "$29") == 0) {
    return 29;
  } else if (strcmp(regString, "$fp") == 0
             || strcmp(regString, "$30") == 0) {
    return 30;
  } else if (strcmp(regString, "$ra") == 0
             || strcmp(regString, "$31") == 0) {
    return 31;
  }

  return 0;
}
