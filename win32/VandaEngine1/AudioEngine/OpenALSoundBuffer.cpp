//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "OpenALSoundBuffer.h"

COpenALSoundBuffer::COpenALSoundBuffer()
{
	 m_soundBuffer = 0;
	 m_oggSoundBuffer = 0;
}

COpenALSoundBuffer::~COpenALSoundBuffer()
{
	CleanUp();
}

CVoid COpenALSoundBuffer::CleanUp()
{
	if( m_soundBuffer )
	{
		alDeleteBuffers( 1, &m_soundBuffer );
		m_soundBuffer = 0;
	}
	if( m_oggSoundBuffer )
	{
		alDeleteBuffers( 1, &m_oggSoundBuffer );
		m_oggSoundBuffer = 0;
	}
}

ALuint COpenALSoundBuffer::GetSoundBuffer()
{
	if( m_soundBuffer )
        return m_soundBuffer;
	else if( m_oggSoundBuffer )
		return m_oggSoundBuffer;
	return CTrue;
}

CBool COpenALSoundBuffer::LoadOggVorbisFromFile( CChar* fileName )
{
	// Create sound buffer
	
	CInt endian = 0;             // 0 for Little-Endian, 1 for Big-Endian
	CInt bitStream;
	long bytes;
	CChar array[OPENAL_BUFFER_SIZE];    // Local fixed size array
	FILE *f;

	ALenum format;
	ALsizei freq;
    vector<CChar> bufferData;                // The sound buffer data from file
	
	// Open for binary reading
	f = fopen( fileName, "rb" );

	if( !f )
		return CFalse;
    vorbis_info *pInfo;
    OggVorbis_File oggFile;

	ov_open(f, &oggFile, NULL, 0);

	// Get some information about the OGG file
	pInfo = ov_info(&oggFile, -1);
	
	// Check the number of channels... always use 16-bit samples
	if (pInfo->channels == 1)
	    format = AL_FORMAT_MONO16;
	else
	format = AL_FORMAT_STEREO16;                             
	// end if
	
	// The frequency of the sampling rate
	freq = pInfo->rate;

	do {
	    // Read up to a buffer's worth of decoded sound data
	    bytes = ov_read(&oggFile, array, OPENAL_BUFFER_SIZE, endian, 2, 1, &bitStream);
	    // Append to end of buffer
	    bufferData.insert(bufferData.end(), array, array + bytes);
	} while (bytes > 0);
  

	// Upload sound data to buffer
	alGenBuffers(1, &m_oggSoundBuffer);
    alBufferData(m_oggSoundBuffer, format, &bufferData[0], static_cast<ALsizei>(bufferData.size()), freq);

	// Clean up!
    ov_clear(&oggFile);
	bufferData.clear();

	ALenum err = alGetError();
	if( err == AL_NO_ERROR )
		return CTrue;
	else if( err == AL_INVALID_NAME )
	MessageBox( NULL, _T("LoadOggVorbisFromFile::AL_INVALID_NAME"), _T("Error"), MB_OK );
	else if(  err == AL_INVALID_ENUM )
	MessageBox( NULL, _T("LoadOggVorbisFromFile::AL_INVALID_ENUM"), _T("Error"), MB_OK );
	else if( err == AL_INVALID_VALUE )
	MessageBox( NULL, _T("LoadOggVorbisFromFile::AL_INVALID_VALUE"), _T("Error"), MB_OK );
	else if( err == AL_INVALID_OPERATION )
	MessageBox( NULL, _T("LoadOggVorbisFromFile::AL_INVALID_OPERATION"), _T("Error"), MB_OK );
	else if( err == AL_OUT_OF_MEMORY )
	MessageBox( NULL, _T("LoadOggVorbisFromFile::AL_OUT_OF_MEMORY"), _T("Error"), MB_OK );
	return CFalse;
}
