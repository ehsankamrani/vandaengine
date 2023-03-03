#ifndef FILE_SYSTEM_H

#define FILE_SYSTEM_H

#include <stdio.h>

class FileSystem
{
public:
	virtual const char * FileOpenString(const char *fname,bool search) = 0; // return the full path name for this file, set 'search' to true to try to 'find' the file.
};


#endif
