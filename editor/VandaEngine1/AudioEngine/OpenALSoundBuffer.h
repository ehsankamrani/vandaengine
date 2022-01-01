//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

#include "OpenAL.h"
#include <vorbis/vorbisfile.h >
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
	CBool m_loaded;

private:
	ALuint m_soundBuffer;
	ALuint m_oggSoundBuffer;
	//each buffer has a unique name
	CChar m_name[MAX_NAME_SIZE];
};


