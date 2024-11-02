#ifndef PROC_H
#define PROC_H

//--------------------------------------------------------//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

#include "../../stack/stack.h"

//--------------------------------------------------------//

typedef unsigned long int ProcElem_t;

struct SPU
{
    struct Stack * stk = {};
    int ip = 0;
    int* Code = 0;
    size_t CodeSize = 0;
    ProcElem_t Reg [4] = {};
    size_t* RAM = 0;
    size_t RAM_Size = 0;
};

//--------------------------------------------------------//

void CodeReader (struct SPU * spu);
void CommandExecutor (struct SPU * spu);

#endif