#include "assembler/asmb.h"

int main ()
{
    Assembler asmb = {};

    asmb.file_name = "sample/sample_code.txt";                              //entering info about files names
    asmb.output_file_name = "sample/machine_code.txt";

    asmb.file = fopen (asmb.file_name, "rb");                               //opening sample_code  to read
    asmb.output_file = fopen (asmb.output_file_name, "w");                  //opening machine_code to write

    asmb.file_size = GimmeFileSize (asmb.file);                             //the data in buffer
    asmb.code = CodeReader (asmb.file, asmb.file_size, asmb.code);

    CodeSeparator (&asmb);                                                  //separating the code into lines

    CodeAssemble (&asmb);                                                   //assembling the machine_code_buffer

    CoverTracks (&asmb);                                                    //freeing the space and removing excess data
}