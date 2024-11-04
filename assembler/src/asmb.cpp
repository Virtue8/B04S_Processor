#include <stdio.h>
#include "../header/asmb.h"
#include "../../utils/utils.h"

void CodeReader (struct Assembler * asmb)
{
    assert (asmb != NULL);

    asmb->asmb_file = fopen (asmb->file_name, "rb");
    assert (asmb->asmb_file != NULL);

    struct stat st = {};
    fstat (fileno (asmb->asmb_file), &st);
    asmb->CodeSize = (size_t) st.st_size;
    assert (asmb->CodeSize != 0);

    asmb->Code = (char *) calloc ((asmb->CodeSize + 1), sizeof(char));
    assert (asmb->Code != NULL);                                                                 

    size_t ReadStatus = fread (asmb->Code, sizeof(char), asmb->CodeSize, asmb->asmb_file);
    if (ReadStatus != asmb->CodeSize)
        printf ("Reading status is wrong!\n");

    *(asmb->Code + asmb->CodeSize) = '\0';

    fclose (asmb->asmb_file);
}

void CodeSeparator (Assembler * asmb)
{
    assert (asmb != NULL);

    asmb->LinesAmount = BufferLinesRefactorer (asmb);

    asmb->Commands = (Command*) calloc (asmb->LinesAmount, sizeof(Command));
    assert (asmb->Commands != NULL);
    size_t prev_i_value = 0;
    int k = 0;

    for (size_t i = 0; i < asmb->CodeSize + 1; i++)
    {
        if (asmb->Code[i] == '\0')
        {
            asmb->Commands[k].len = i - prev_i_value;
            asmb->Commands[k].ptr = asmb->Code + i - asmb->Commands[k].len;
            prev_i_value = i;
            assert (asmb->Commands[k].ptr);
            k += 1;
        }
    }
    assert (asmb->Commands[0].ptr);
}

void CommandIdentifier (Assembler * asmb)
{
    char ccom[10] = "";         //current command

    for (int i = 0; i != /*asmb->LinesAmount*/1; i++)
    {
        for (int j = 0; j != 4/*asmb->Commands[i].len-1*/; j++)
        {
            ccom[j] = *(asmb->Commands[i].ptr + j);
        }
    }

    if (strcmp (ccom, "PUSH") == 0)
    {
        printf ("1\n");
        exit (1);
    }

    else if (!strcmp (ccom, "POP"))
    {
        printf ("2");
    }

    else if (!strcmp (ccom, "JMP"))
    {
        printf ("3");
    }

    else if (!strcmp (ccom, "JA"))
    {
        printf ("4");
    }

    else if (!strcmp (ccom, "JAE"))
    {
        printf ("5");
    }

    else if (!strcmp (ccom, "JB"))
    {
        printf ("6");
    }

    else if (!strcmp (ccom, "JBE"))
    {
        printf ("7");
    }
    else if (!strcmp (ccom, "JE"))
    {
        printf ("8");
    }

    else if (!strcmp (ccom, "JNE"))
    {
        printf ("9");
    }

    else if (!strcmp (ccom, "ADD"))
    {
        printf ("10");
    }

    else if (!strcmp (ccom, "SUB"))
    {
        printf ("11");
    }

    else if (!strcmp (ccom, "MUL"))
    {
        printf ("12");
    }

    else if (!strcmp (ccom, "DIV"))
    {
        printf ("13");
    }

    else if (!strcmp (ccom, "SQRT"))
    {
        printf ("14");
    }

    else if (!strcmp (ccom, "POW"))
    {
        printf ("15");
    }

    else if (!strcmp (ccom, "LN"))
    {
        printf ("16");
    }

    else if (!strcmp (ccom, "SIN"))
    {
        printf ("17");
    }

    else if (!strcmp (ccom, "COS"))
    {
        printf ("18");
    }
}

void CodeAssemble (Assembler * asmb)
{

}

void CodeOutput (Assembler * asmb, FILE * output_file)
{

}
