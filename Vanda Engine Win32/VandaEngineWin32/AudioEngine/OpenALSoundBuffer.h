//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

#include "OpenAL.h"
#include <vector>
#include "..\common\defines.h"
#include "..\common\utility.h"
using namespace std;



class COpenALSoundBuffer
{
public:
	COpenALSoundBuffer();
	~COpenALSoundBuffer();

	ALuint GetSoundBuffer();
	CChar* GetName() { return m_name; }
	CVoid SetName( CChar* name ) { Cpy( m_name, name ); }
    CBool LoadOggVorbisFromFile( CChar* fileName );
	CVoid CleanUp();

private:
	ALuint m_soundBuffer;
	ALuint m_oggSoundBuffer;
	//each buffer has a unique name
	CChar m_name[MAX_NAME_SIZE];
};


