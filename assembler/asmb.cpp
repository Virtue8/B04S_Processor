#include <stdio.h>
#include "asmb.h"
#include "../utils/utils.h"

void asmbCtor (Assembler * asmb, const char * input_file_name, const char * output_file_name)
{
    assert (asmb != NULL);

    asmb->file_name = input_file_name;                              //entering info about files names
    asmb->output_file_name = output_file_name;

    asmb->file = fopen (asmb->file_name, "rb");                               //opening sample_code  to read
    asmb->output_file = fopen (asmb->output_file_name, "w");                  //opening machine_code to write
}

void asmbDtor (Assembler * asmb)
{
    assert (asmb != NULL);

    free (asmb->code);
    fclose (asmb->file);
    fclose (asmb->output_file);
}

void CodeSeparator (Assembler * asmb)
{
    assert (asmb != NULL);

    asmb->lines_amount = BufferLinesRefactorer (asmb->code);

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
    }
}

int GetCommandNumber(const char * command) 
{
    assert (command != NULL);

    for (int k = 0; k < COMMANDS_AMOUNT; k++)
    {
        if (strcmp(command, Command_Names[k]) == 0)
            return k;
    }

    return -1;
}

void LineIdentifier (char * input_line, char * output_line)
{
    assert (input_line != NULL);
    assert (output_line != NULL);

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
            sprintf (output_line, "%d\n", command_number);
            break;
        case 2:
            sprintf (output_line, "%d %d\n", command_number, arg1);
            break;
        case 3:
            sprintf (output_line, "%d %d %d\n", command_number, arg1, arg2);
            break;
        default:
            fprintf (stderr, "Error: Invalid input format\n");
            strcpy (output_line, "ERROR");
    }
}

void CodeAssemble (Assembler * asmb)
{
    assert (asmb != NULL);

    for (int i = 0; i < asmb->lines_amount; i++)
    {
        char input_line[30] = "";
        char output_line[10] = "";
        
        if (i == 0)
        {
            for (int q = 0; q < asmb->line[i].len; q++)
                input_line[q] = *(asmb->line[i].ptr + q);

            LineIdentifier (input_line, output_line);
            MachineCodeWriter (asmb, output_line);
        }
        else
        {
            asmb->line[i].ptr ++;
            for (int q = 0; q < asmb->line[i].len; q++)
                input_line[q] = *(asmb->line[i].ptr + q);

            LineIdentifier (input_line, output_line);
            MachineCodeWriter (asmb, output_line);
        }
    }
}

void MachineCodeWriter (Assembler * asmb, const char * output_code) 
{
    assert (asmb != NULL);

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
