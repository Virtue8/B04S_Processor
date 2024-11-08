#ifndef UTILS_CPP
#define UTILS_CPP

#include "utils.h"

//-----------------------------------------------------------------------//

size_t GimmeFileSize (FILE * file)
{
    struct stat st = {};
    fstat (fileno (file), &st);
    size_t file_size = (size_t) st.st_size;
    assert (file_size != 0);

    return file_size;
}

//-----------------------------------------------------------------------//

size_t BufferLinesRefactorer (char * code, size_t file_size) 
{
    size_t lines = 0;
    for (size_t i = 0; i != file_size + 1; i++)
    {
        if ( *(code + i) == '\n')
        {
            *(code + i) = '\0';
            lines++;
        }
    }
    return lines + 1; 
}

//-----------------------------------------------------------------------//

#endif