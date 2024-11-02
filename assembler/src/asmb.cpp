#include <stdio.h>
#include "../header/asmb.h"

inline const char * file_name = "../../sample_code.txt";

Assembler * asmb = {};

void CodeReader (struct Assembler * asmb)
{
    assert (asmb != NULL);

    FILE * file = fopen (file_name, "rb");
    assert (file != NULL);

    struct stat st = {};
    fstat (fileno (file), &st);
    asmb->CodeSize = (size_t) st.st_size;
    assert (asmb->CodeSize != 0);

    asmb->Code = (char *) calloc ((asmb->CodeSize + 1), sizeof(char));
    assert (asmb->Code != NULL);                                                                 

    size_t ReadStatus = fread (asmb->Code, sizeof(char), asmb->CodeSize, file);
    if (ReadStatus != asmb->CodeSize)
        printf ("wrong reading\n");

    *(asmb->Code + asmb->CodeSize) = '\0';

    fclose (file);
}

void CommandIdentifier (Assembler * asmb, Line * line)
{
    //if (strcmp ([asmb->ip]))
}

void CodeAssemble (Assembler * asmb, Line * line, int LinesNum)
{

}

void CodeOutput (Assembler * asmb, FILE * output_file)
{

}
