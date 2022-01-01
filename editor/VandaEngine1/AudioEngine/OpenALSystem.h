//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

#include "..\common\vector.h"
#include "OpenAL.h"
#include "OpenALSoundSource.h"

class COpenALSystem
{
public:
	COpenALSystem();
	~COpenALSystem();
public:
	CBool Init();
	CVoid CleanUp();
	CVoid PlayALSound( COpenALSoundSource& source );
	CVoid StopALSound( COpenALSoundSource& source );
	CVoid PauseALSound( COpenALSoundSource& source );
	CVoid RewindALSound( COpenALSoundSource& source );
	CVoid SetListenerPosition( CFloat* position );
	CVoid SetListenerPosition( CVoid );
	CVoid SetListenerVelocity( CFloat* velocity );
	CVoid SetListenerOrientation( CFloat* orientation );
	CVoid SetDopplerFactor( CFloat factor );
	CVoid SetDopplerSpeed( CFloat speed );
private:
	CBool m_init;
	ALCdevice* m_device;
	ALCcontext* m_context;
};
