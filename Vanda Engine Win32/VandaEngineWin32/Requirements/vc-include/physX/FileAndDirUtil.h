/*
 *  FileAndDirUtil.h
 * 
 *  Author: Michael Sauter
 *
 *  Content: Tools for directory structure handling and file processing.
 *
 */

#ifndef _FileAndDirUtil_H_
#define _FileAndDirUtil_H_

#ifdef WIN32

#include <stdio.h>
#include <assert.h>
#include <windows.h>


bool isFile(const char* filename);
bool isDir(const char* dirpath);
bool getDir(char* path, bool cutLastSlash);
HANDLE fileSearchGetNext(HANDLE searchHandle, const char* path, char* file_name);

#endif // WIN32



#endif // _FileAndDirUtil_H_
