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

#include "../stack/stack.h"
#include "../utils/utils.h"
#include <stdio.h>

//--------------------------------------------------------//

typedef unsigned long int ProcElem_t;

const int COMMANDS_AMOUNT = 20;

static const char * Command_Names[20]
{
    "HLT",
    "PUSH",
    "POP",
    "JMP",
    "JA",
    "JAE",
    "JB",
    "JBE",
    "JE",
    "JNE",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "SQRT",
    "POW",
    "LN",
    "SIN",
    "COS",
    "BACKSPACE"
};

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
    COS,
    BACKSPACE,
};

enum Registers
{
    ax = 1,
    bx = 2,
    cx = 3,
    dx = 4
};

const int ASMB_VERSION = 1;

struct Assembler
{
    FILE * file = NULL;
    FILE * output_file = NULL;
    size_t file_size = 0;

    const char * file_name = NULL;
    const char * output_file_name = NULL;

    char * code = 0;
    size_t lines_amount = 0;

    int ip = 0;
    struct Line * line = NULL;
};

struct Line
{
    size_t len = 0;
    char * ptr = 0;
    int args   = 0;
    int words  = 0;
};

//---------------------- Collecting the sample_code Data ----------------------//

void CodeSeparator (Assembler * asmb);

//----------------- Reworking and Analyzing the sample_code -------------------//

void LineIdentifier (char * input_line, char * output_line);
void CodeAssemble (Assembler * asmb);
void MachineCodeWriter(Assembler * asmb, const char *output_code);
void CoverTracks (Assembler * asmb);

//--------------------------------------------//

#endif