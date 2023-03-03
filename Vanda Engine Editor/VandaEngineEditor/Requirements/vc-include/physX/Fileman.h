/*----------------------------------------------------------------------------*\
|
|						    NVIDIA PhysX Technology
|
|							     www.nvidia.com
|
\*----------------------------------------------------------------------------*/




/*
  file class header , (C) 1996 Adam Moravanszky
  class clFile
  Uses:  clException,stdio

  Encapsulation Rating: Excellent
  */
#ifndef INCLUDED_FILE_H
#define INCLUDED_FILE_H

#define FM_CREATE 0
#define FM_APPEND 2
#define FM_READ	3
#include "stdio.h"//needed to define "FILE"

class clFile
	{
	FILE * Fp;
	void Error(unsigned short Msg);
	public:
	clFile(const char *sFName,char Mode);
	~clFile();
	void Read(void * Buffer,unsigned int cbBuffer);
	void Write(void * Buffer,unsigned int cbBuffer);
	void Seek(unsigned int Offset);//from the start of file this many bytes
	void ReadMarker(void * Marker);
	};

#endif //Last Line!
//NVIDIACOPYRIGHTBEGIN
///////////////////////////////////////////////////////////////////////////
// Copyright © 2010 NVIDIA Corporation.
// All rights reserved. www.nvidia.com
///////////////////////////////////////////////////////////////////////////
//NVIDIACOPYRIGHTEND