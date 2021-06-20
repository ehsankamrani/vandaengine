#pragma once

#include "Utility.h"

class CImage;
class COpenALSoundSource;
class COpenALSoundBuffer;
class CAmbientSound;

class CResourceFile
{
private:
	CChar m_name[MAX_NAME_SIZE];
	CImage* m_image;
	COpenALSoundSource* m_soundSource;
	COpenALSoundBuffer* m_soundBuffer;
	CAmbientSound* m_sound;
	CChar m_directoryName[MAX_NAME_SIZE];
	CChar m_fileName[MAX_NAME_SIZE];

public:
	CResourceFile();
	~CResourceFile();

	CAmbientSound* GetSoundSource();

	CImage* GetImage();

	CBool LoadDDSFile(CChar * fileName);
	CBool LoadOGGFile(CChar * fileName);
	CBool LoadAVIFile(CChar * fileName);
	
	inline CVoid SetName(CChar* name) { Cpy(m_name, name); }
	inline CChar* GetName() { return m_name; }

	inline CVoid SetDirectoryName(CChar* name) { Cpy(m_directoryName, name); }
	inline CVoid SetFileName(CChar* name) { Cpy(m_fileName, name); }
	inline CChar* GetDirectoryName() { return m_directoryName; }
	inline CChar* GetFileName() { return m_fileName; }

};

