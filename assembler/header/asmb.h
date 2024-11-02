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

/*
struct Label
{
    const char label[10] = "";      
    int address = -1;
    int is_define = -1;
};
*/

struct Assembler
{
    char * Code = 0;
    int CodeSize = 0;
    int ip = 0;
    int start_ip = -1;
};

struct Line
{
    size_t Size;
    char* Index;
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

void CodeAssemble (Assembler * asmb, Line * line, int LinesNum);
void CodeOutput (Assembler * asmb, FILE * output_file);
void CommandIdentifier (Assembler * asmb, Line * line);

#endif