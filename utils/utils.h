#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <stdio.h>

#include "../assembler/asmb.h"

//---------------------------- Text Editing -----------------------------//

size_t GimmeFileSize (FILE * file);
size_t BufferLinesRefactorer (char * buffer);

//---------------------------- File Reading -----------------------------//

FILE * FileOpener (const char * file_name);
char * BufferCtor (FILE * file, size_t file_size);

//-----------------------------------------------------------------------//

#endif