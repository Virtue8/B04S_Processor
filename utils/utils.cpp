#ifndef UTILS_CPP
#define UTILS_CPP

#include "utils.h"

size_t BufferLinesRefactorer (struct Assembler * asmb) 
{
    size_t lines = 0;
    for (size_t i = 0; i != asmb->CodeSize + 1; i++)
    {
        if ( *(asmb->Code + i) == '\n')
        {
            *(asmb->Code + i) = '\0';
            lines++;
        }
    }
    return lines + 1; 
}

#endif