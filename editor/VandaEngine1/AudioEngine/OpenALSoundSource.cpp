//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "OpenALSoundSource.h"

COpenALSoundSource::COpenALSoundSource()
{
	m_soundSource = 0;
}

COpenALSoundSource::~COpenALSoundSource()
{
	CleanUp();
}

ALuint COpenALSoundSource::GetSource()
{
	return m_soundSource;
}

CVoid COpenALSoundSource::SetLooping( CBool enable )
{
	alSourcei( m_soundSource, AL_LOOPING, enable );
}

CVoid COpenALSoundSource::SetSoundPosition( CFloat* pos )
{
	alSource3f( m_soundSource, AL_POSITION, pos[0], pos[1], pos[2] );
}

CVoid COpenALSoundSource::SetSoundPosition( )
{
	alSource3f( m_soundSource, AL_POSITION, 0.0f, 0.0f, 1.0f );
}

CVoid COpenALSoundSource::SetSoundVelocity( CFloat* vel )
{
	alSource3f( m_soundSource, AL_VELOCITY, vel[0], vel[1], vel[2] );
}

CVoid COpenALSoundSource::CleanUp()
{
	if( m_soundSource )
	{
		alDeleteSources( 1, &m_soundSource );
		m_soundSource = 0;
	}
}

CBool COpenALSoundSource::BindSoundBuffer( COpenALSoundBuffer& soundBuffer )
{
	if( m_soundSource == 0 )
	{
		alGenSources( 1, &m_soundSource );
		//SetSoundPosition();
	}

	alSourcei( m_soundSource, AL_BUFFER, soundBuffer.GetSoundBuffer() );
	if( alGetError() == AL_NO_ERROR )
		return CTrue;
	else
	{
		return CFalse;
	}
}

CVoid COpenALSoundSource::SetMaxDistance( CFloat distance )
{
	alSourcef( m_soundSource, AL_MAX_DISTANCE, distance );
}

CVoid COpenALSoundSource::SetReferenceDistance( CFloat distance )
{
	alSourcef( m_soundSource, AL_REFERENCE_DISTANCE, distance );
}

CVoid COpenALSoundSource::SetVolume( CFloat vol )
{
	alSourcef( m_soundSource, AL_GAIN, vol );
}

CVoid COpenALSoundSource::SetVolume( CFloat vol, CFloat min, CFloat max )
{
	alSourcef( m_soundSource, AL_MIN_GAIN, min );
	alSourcef( m_soundSource, AL_MAX_GAIN, max );
	alSourcef( m_soundSource, AL_GAIN, vol );
}

CVoid COpenALSoundSource::SetConeOuterVol( CFloat gain )
{
	alSourcef( m_soundSource, AL_CONE_OUTER_GAIN, gain );
}

CVoid COpenALSoundSource::SetConeAngle( CFloat inner, CFloat outer )
{
	alSourcef( m_soundSource, AL_CONE_INNER_ANGLE, inner );
	alSourcef( m_soundSource, AL_CONE_OUTER_ANGLE, outer );
}

CVoid COpenALSoundSource::SetRolloff( CFloat rolloff )
{
	alSourcef( m_soundSource, AL_ROLLOFF_FACTOR, rolloff );
}

CVoid COpenALSoundSource::SetPitch( CFloat pitch )
{
	alSourcef( m_soundSource, AL_PITCH, pitch );
}

CVoid COpenALSoundSource::SetType( CInt type )
{
	alSourcei( m_soundSource, AL_SOURCE_TYPE, type );
}

CVoid COpenALSoundSource::SetSeekTime( CInt second )
{
	alSourcei( m_soundSource, AL_SEC_OFFSET, second );
}

CVoid COpenALSoundSource::QueueBuffers( COpenALSoundBuffer& buffer1, COpenALSoundBuffer& buffer2 )
{
	ALuint buffers[2] = { buffer1.GetSoundBuffer(), buffer2.GetSoundBuffer() };
	alSourceQueueBuffers( m_soundSource , 2, buffers );
}

/*CBool COpenALSoundSource::IsPlaying( CVoid )
{
	alSourcei( m_soundSource, AL_SOURCE_STATE, AL_PLAYING );
	if( alGetError() == AL_NO_ERROR )
		return CTrue;
	return CFalse;
}
*/
