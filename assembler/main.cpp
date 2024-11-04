#include "header/asmb.h"

int main ()
{
    Assembler asmb = {};
    asmb.file_name = "sample/sample_code.txt";
    CodeReader (&asmb);
    CodeSeparator (&asmb);
    CommandIdentifier (&asmb);
}