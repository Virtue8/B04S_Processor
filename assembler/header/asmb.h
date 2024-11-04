#ifndef ASMB_H
#define ASMB_H

//--------------------------------------------------------//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/param.h>

#include "../../stack/stack.h"
#include <stdio.h>

//--------------------------------------------------------//

const int ASMB_VERSION = 1;

struct Assembler
{
    FILE * asmb_file = NULL;
    const char * file_name = NULL;
    char * Code = 0;
    int CodeSize = 0;
    int LinesAmount = 0;
    int ip = 0;
    //int start_ip = -1;
    struct Command * Commands = NULL;
};

struct Command
{
    size_t len = 0;
    char * ptr = 0;
};

typedef unsigned long int ProcElem_t;

enum Command_Codes
{
    HLT,
    PUSH,
    POP,
    JMP,
    JA,
    JAE,
    JB,
    JBE,
    JE,
    JNE,
    ADD,
    SUB,
    MUL,
    DIV,
    SQRT,
    POW,
    LN,
    SIN,
    COS
};

enum Registers
{
    ax = 1,
    bx = 2,
    cx = 3,
    dx = 4
};

//--------------------------------------------//

void CodeReader (Assembler * asmb);
void CodeSeparator (Assembler * asmb);
void CommandIdentifier (Assembler * asmb);
void CodeAssemble (Assembler * asmb, int LinesNum);
void CodeOutput (Assembler * asmb, FILE * output_file);

#endif