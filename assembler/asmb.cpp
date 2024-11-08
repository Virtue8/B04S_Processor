#include <stdio.h>
#include "asmb.h"
#include "../utils/utils.h"

FILE * FileOpener (char * file_name)
{
    FILE * file = fopen (file_name, "rb");
    assert (file != NULL);

    return file;
}

char * CodeReader (FILE * file, size_t file_size, char * code)
{
    code = (char *) calloc ((file_size + 1), sizeof(char));
    assert (code != NULL);

    size_t ReadStatus = fread (code, sizeof(char), file_size, file);
    if (ReadStatus != file_size)
        printf ("Reading status is incorrect!\n");

    *(code + file_size) = '\0';

    fclose (file);

    return code;
}

void CodeSeparator (Assembler * asmb)
{
    assert (asmb != NULL);

    asmb->lines_amount = BufferLinesRefactorer (asmb->code, asmb->file_size);

    asmb->line = (Line *) calloc (asmb->lines_amount, sizeof(Line));
    assert (asmb->line != NULL);

    size_t prev_i_value = 0;
    int k = 0;

    for (size_t i = 0; i < asmb->file_size + 1; i++)
    {
        if (asmb->code[i] == '\0')
        {
            asmb->line[k].len = i - prev_i_value;
            asmb->line[k].ptr = asmb->code + i - asmb->line[k].len;

            prev_i_value = i;
            k += 1;
        }
        
        else if (asmb->code[i] == ' ')
            asmb->line[k].args++;
    }
}

int CommandIdentifier (Assembler * asmb)
{
    char ccom[10] = "";         //current command
    for (int i = 0; i != asmb->lines_amount; i++)
    {
        for (int j = 0; j != asmb->line[i].len - 1; j++)
        {
            ccom[j] = *(asmb->line[i].ptr + j); 
            printf ("%c %d\n", ccom[j], j);
        }
    }

    /*int k = 0;
    char * ccode[2] = {"PUSH", "POP"};

    if (!strcmp (ccom, ccode[k]))
    {
        return atoi (ccode[k]);
    }
    */
    return EXIT;
}

void CodeAssemble (Assembler * asmb)
{

}

void MachineBufferSize (Assembler * asmb)
{
    
}

void CoverTracks (Assembler * asmb)
{

}
