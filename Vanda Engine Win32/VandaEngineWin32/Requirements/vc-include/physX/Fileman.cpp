/*

//fileman class. (C) 1996 Adam Moravanszky

*/

#include <Fileman.h>

#include <Smart.h>





clFile::clFile(const char *sFName,char Mode)

	{//Mode:0= createfor Write,1=openfor write,2=open for read

	char * MStr;

	switch (Mode)

		{

		case FM_CREATE:

			MStr="wb";

			break;

		case FM_APPEND:

			MStr="ab";

			break;

		default://FM_READ

			MStr="rb";

		}

	if ((Fp = fopen(sFName,MStr))== NULL) 

		{

		char * Err = new char[40];

		sprintf(Err,"FM: Can't open file '%13s",sFName);

		throw (Err);

		}

	}

clFile::~clFile()

	{

	fclose(Fp);

	}



void clFile::Read(void * hpvBuffer,unsigned int NumBytes)

	{

	if  (fread(hpvBuffer,1,NumBytes,Fp)!=NumBytes)

		{

		fclose(Fp);

		SMART_EXCEPTION("Can't read file");

		}

	}

void clFile::Write(void * hpvBuffer,unsigned int NumBytes)

	{

	if  (fwrite(hpvBuffer,1,NumBytes,Fp)!=NumBytes)

		{

		fclose(Fp);

		SMART_EXCEPTION("Can't write file");

		}

	}



void clFile::ReadMarker(void * Marker)

	{//this funct throws an exception if the 4 character string passed is not equal the 4 chars it reads from file

	unsigned int *iMarker=(unsigned int *)Marker;

	unsigned int Buffer;

	Read((void *)&Buffer,4);

	if (*iMarker!=Buffer)

		{

		fclose(Fp);

		SMART_EXCEPTION("Invalid file");

		}

	}

void clFile::Seek(unsigned int Offset)

	{//from the start of file this many bytes

	if (fseek(Fp, Offset, SEEK_SET))

		{

		fclose(Fp);

		SMART_EXCEPTION("Can't seek file");

		}

	}



