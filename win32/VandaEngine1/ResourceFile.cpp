//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "ResourceFile.h"
#include "GraphicsEngine/Image.h"
#include "GraphicsEngine/Texture.h"
#include "GraphicsEngine/Avi.h"
#include "AudioEngine/OpenAL.h"
#include "AudioEngine/AmbientSound.h"

CResourceFile::CResourceFile()
{
	m_image = NULL;
	m_soundSource = NULL;
	m_soundBuffer = NULL;
	m_sound = NULL;

}

CResourceFile::~CResourceFile()
{
	CDelete(m_image);
	CDelete(m_sound);
}

CAmbientSound* CResourceFile::GetSoundSource()
{
	return m_sound;
}

CImage* CResourceFile::GetImage()
{
	return m_image;
}


CBool CResourceFile::LoadDDSFile(CChar * fileName)
{
	m_image = CNew(CImage);
	if (!CTexture::LoadDDSTexture(m_image, fileName, NULL))
	{
		//CChar temp[MAX_URI_SIZE];
		//sprintf(temp, "\nCouldn't load the resource image '%s'", fileName);
		//PrintInfo(temp, COLOR_RED);
		CDelete(m_image);
		return CFalse;
	}

	return CTrue;
}

CBool CResourceFile::LoadOGGFile(CChar * fileName)
{
	m_soundSource = CNew(COpenALSoundSource);
	m_soundBuffer = CNew(COpenALSoundBuffer);

	if (!m_soundBuffer->LoadOggVorbisFromFile(fileName))
		return CFalse;
	m_soundSource->BindSoundBuffer(*(m_soundBuffer));

	m_soundSource->SetLooping(true);
	m_soundSource->SetPitch(1.0f);
	m_soundSource->SetVolume(1.0f);

	m_sound = CNew(CAmbientSound);

	m_sound->SetSoundSource(m_soundSource);
	m_sound->SetSoundBuffer(m_soundBuffer);
	m_sound->SetPath(fileName);
	m_sound->SetVolume(1.0f);
	m_sound->SetPitch(1.0f);

	return CTrue;
}

CBool CResourceFile::LoadAVIFile(CChar * fileName)
{
	return CTrue;
}
