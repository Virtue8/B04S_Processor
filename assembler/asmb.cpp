#include <stdio.h>
#include "asmb.h"
#include "../utils/utils.h"

void CodeSeparator (Assembler * asmb)
{
    assert (asmb != NULL);

    asmb->lines_amount = BufferLinesRefactorer (asmb->code, asmb->file_size);

    asmb->line = (Line *) calloc (asmb->lines_amount, sizeof(Line));
    assert (asmb->line != NULL);

    size_t prev_i_value = 0;
    int k = 0;
    asmb->line[0].words = 1;

    for (size_t i = 0; i < asmb->file_size + 1; i++)
    {
        if (asmb->code[i] == '\0')
        {
            asmb->line[k].len = i - prev_i_value;
            asmb->line[k].ptr = asmb->code + i - asmb->line[k].len;

            prev_i_value = i;
            k += 1;
            asmb->line[k].words = asmb->line[k].args + 1;
        }
        
        else if (asmb->code[i] == ' ')
            asmb->line[k].args++;
    }
}

int GetCommandNumber(const char * command) 
{
    for (int k = 0; k < COMMANDS_AMOUNT; k++)
    {
        if (strcmp(command, Command_Names[k]) == 0)
            return k;
    }

    return -1;
}

void LineIdentifier (char * input_line, char * output_line)
{
    char command[10] = "";

    int arg1 = 0;
    int arg2 = 0;

    int words_amount = sscanf (input_line, "%s %d %d\0", command, &arg1, &arg2);

    int command_number = GetCommandNumber (command);

    if (command_number == -1) 
    {
        fprintf (stderr, "Error: Unknown command '%s'\n", command);
        strcpy (output_line, "ERROR");
        return;
    }

    switch (words_amount) 
    {
        case 1:
            sprintf (output_line, "%d\0", command_number);
            break;
        case 2:
            sprintf (output_line, "%d %d\0", command_number, arg1);
            break;
        case 3:
            sprintf (output_line, "%d %d %d\0", command_number, arg1, arg2);
            break;
        default:
            fprintf (stderr, "Error: Invalid input format\n");
            strcpy (output_line, "ERROR");
    }
}

void CodeAssemble (Assembler * asmb)
{
    char * output_code = (char *) calloc (10 * asmb->lines_amount, sizeof (int));

    for (int i = 0; i < asmb->lines_amount; i++)
    {
        char input_line[30] = "";
        char output_line[10] = "";
        
        if (i == 0)
        {
            for (int q = 0; q < asmb->line[i].len; q++)
                input_line[q] = *(asmb->line[i].ptr + q);

            LineIdentifier (input_line, output_line);
            sprintf (output_code, "%s\n", output_line);

            fprintf (stdout, "%s\n", output_code);
            MachineCodeWriter (asmb, output_code);
        }
        else
        {
            asmb->line[i].ptr ++;
            for (int q = 0; q < asmb->line[i].len; q++)
                input_line[q] = *(asmb->line[i].ptr + q);

            LineIdentifier (input_line, output_line);
            sprintf (output_code, "%s\n", output_line);
            MachineCodeWriter (asmb, output_code);
        }
    }

    free (output_code);
}

void MachineCodeWriter (Assembler * asmb, const char * output_code) 
{
    if (asmb->output_file == NULL || output_code == NULL) 
    {
        fprintf (stderr, "Error: Invalid file pointer or buffer\n");
        return;
    }

    int write_state = fwrite (output_code, sizeof (char), strlen (output_code), asmb->output_file);

    if (write_state < strlen (output_code)) 
    {
        fprintf (stderr, "Error: Failed to write complete data to file\n");
    }
}

void CoverTracks (Assembler * asmb)
{
    free (asmb->code);
    fclose (asmb->file);
    fclose (asmb->output_file);
}
