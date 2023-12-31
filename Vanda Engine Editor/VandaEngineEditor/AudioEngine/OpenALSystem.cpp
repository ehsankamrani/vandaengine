//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "OpenALSystem.h"

COpenALSystem::COpenALSystem()
{
	m_init = CFalse;
	m_device = NULL;
	m_context = NULL;
}

COpenALSystem::~COpenALSystem()
{
	CleanUp();
}

CBool COpenALSystem::Init()
{
	if (!m_init)
	{
		char* devices = (char*)alcGetString(NULL, ALC_DEVICE_SPECIFIER);
		while (devices && *devices != NULL)
		{
			if (Cmp(devices, "OpenAL Soft"))
			{
				m_device = alcOpenDevice(devices);
				if (!m_device)
				{
					MessageBoxA(NULL, "Couldn't initialize OpenAL device", "Vanda Engine Error", MB_OK | MB_ICONERROR);
					return CFalse;
				}
				m_context = alcCreateContext(m_device, NULL);
				if (!m_context)
				{
					MessageBoxA(NULL, "Couldn't create OpenAL context", "Vanda Engine Error", MB_OK | MB_ICONERROR);
					return CFalse;
				}

				alcMakeContextCurrent(m_context);

				break;
			}
			devices += strlen(devices) + 1; //next device
		}
	}

	if(alGetError() != AL_NO_ERROR)
	{
		m_init = CFalse;
	 	return CFalse;
	}
    m_init = CTrue;
	return CTrue;
}

CVoid COpenALSystem::CleanUp()
{
	if (m_init == CTrue)
	{
		alcDestroyContext(m_context);
		alcCloseDevice(m_device);
	}
	m_init = CFalse;
}

CVoid COpenALSystem::PlayALSound(COpenALSoundSource& source)
{
	if (m_init == CTrue)
	{
		ALenum state;

		alGetSourcei(source.GetSource(), AL_SOURCE_STATE, &state);

		if(state != AL_PLAYING)
			alSourcePlay(source.GetSource());
	}
}

CVoid COpenALSystem::PlayALPausedSound(COpenALSoundSource& source)
{
	if (m_init == CTrue)
	{
		ALenum state;

		alGetSourcei(source.GetSource(), AL_SOURCE_STATE, &state);

		if (state == AL_PAUSED)
			alSourcePlay(source.GetSource());
	}
}

CVoid COpenALSystem::PlayALStoppedSound(COpenALSoundSource& source)
{
	if (m_init == CTrue)
	{
		ALenum state;

		alGetSourcei(source.GetSource(), AL_SOURCE_STATE, &state);

		if (state == AL_STOPPED)
			alSourcePlay(source.GetSource());
	}
}

CVoid COpenALSystem::PauseALSound( COpenALSoundSource& source )
{
	if (m_init == CTrue)
	{
		ALenum state;

		alGetSourcei(source.GetSource(), AL_SOURCE_STATE, &state);

		if (state == AL_PLAYING)
			alSourcePause(source.GetSource());
	}
}

CVoid COpenALSystem::StopALSound( COpenALSoundSource& source )
{
	if (m_init == CTrue)
	{
		ALenum state;

		alGetSourcei(source.GetSource(), AL_SOURCE_STATE, &state);

		if (state == AL_PLAYING)
			alSourceStop(source.GetSource());
	}
}

CVoid COpenALSystem::RewindALSound( COpenALSoundSource& source )
{
	if(m_init == CTrue)
		alSourceRewind( source.GetSource() );
}

CVoid COpenALSystem::SetListenerPosition( CFloat* pos )
{
	if(m_init == CTrue)
		alListener3f( AL_POSITION, pos[0], pos[1], pos[2] );
}

CVoid COpenALSystem::SetListenerPosition( )
{
	if(m_init == CTrue)
	{
		CVector m_pos( 0.0f, 0.0f, 0.0f );
		alListener3f( AL_POSITION, m_pos.m_i, m_pos.m_j, m_pos.m_k );
	}
}

CVoid COpenALSystem::SetListenerVelocity( CFloat* velocity )
{
	if(m_init == CTrue)
		alListener3f( AL_VELOCITY, velocity[0], velocity[1], velocity[2]);
}

CVoid COpenALSystem::SetListenerOrientation( CFloat* orientation )
{
	if(m_init == CTrue)
	{
		ALfloat m_orientation[] = { orientation[0], orientation[1], orientation[2], orientation[3], orientation[4], orientation[5] };
		alListenerfv( AL_ORIENTATION, m_orientation );
	}
}

CVoid COpenALSystem::SetListenerGain(CFloat gain)
{
	if (m_init == CTrue)
	{
		alListenerf(AL_GAIN, gain);
	}
}

CVoid COpenALSystem::SetDopplerFactor( CFloat factor )
{
	if(m_init == CTrue)
		alDopplerFactor( factor );
}

CVoid COpenALSystem::SetDopplerSpeed( CFloat speed )
{
	if(m_init == CTrue)
		alSpeedOfSound( speed );
}

ALenum COpenALSystem::GetSourceState(COpenALSoundSource& source)
{
	if (m_init == CTrue)
	{
		ALenum state;

		alGetSourcei(source.GetSource(), AL_SOURCE_STATE, &state);

		return state;
	}
	return AL_INITIAL;
}
