#include <stdio.h>

#include "assembler.h"

int main(int argc, char** argv) {

  // printf("Input: %s\n", argv[1]);

  // char* testString = "    addiu $sp, $sp, 0x4  # increment stack pointer";

  int inst = assembleLine(argv[1]);

  printf("0x%08x\n", inst);

  return 0;
}


