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
    EXIT,
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
    size_t file_size = 0;
    char * file_name = NULL;

    FILE * output_file = NULL;
    char * output_file_name = NULL;

    char * code = 0;
    size_t lines_amount = 0;

    int ip = 0;
    struct Line * line = NULL;
};

struct Line
{
    // bool have_ram = false;
    size_t len = 0;
    char * ptr = 0;
    int args   = 0;
};

//---------------------- Collecting the sample_code Data ----------------------//

FILE * FileOpener (char * file_name);
char * CodeReader (FILE * file, size_t file_size, char * code);
void CodeSeparator (Assembler * asmb);

//------------------------ Reworking the sample_code --------------------------//

int CommandIdentifier (Assembler * asmb);
void CodeAssemble (Assembler * asmb);
void CoverTracks (Assembler * asmb);

//--------------------------------------------//

#endif