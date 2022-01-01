//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

#include "OpenAL.h"
#include "OpenALSoundBuffer.h"

class COpenALSoundSource
{
public:
	COpenALSoundSource();
	~COpenALSoundSource();

public:
	CVoid SetSoundPosition( CFloat* pos );
	CVoid SetSoundPosition( CVoid );
	CVoid SetSoundVelocity( CFloat* vel );
	CVoid SetLooping( CBool enable = CFalse );
	CVoid SetMaxDistance( CFloat distance );
	CVoid SetReferenceDistance( CFloat distance );
	CVoid SetVolume( CFloat vol );
	CVoid SetVolume( CFloat vol, CFloat min, CFloat max );
	CVoid SetConeOuterVol( CFloat gain );
	CVoid SetConeAngle( CFloat inner, CFloat outer );
	CVoid SetRolloff( CFloat rolloff );
	CVoid SetPitch( CFloat pitch );
	CVoid SetType( CInt type );
	CVoid SetSeekTime( CInt second );

	CBool BindSoundBuffer( COpenALSoundBuffer &soundBuffer );
	CVoid QueueBuffers( COpenALSoundBuffer& buffer1, COpenALSoundBuffer& buffer2 );
	CVoid CleanUp();
	ALuint GetSource();
	//CBool CIsPlaying( CVoid );

private:
	ALuint m_soundSource;
};

