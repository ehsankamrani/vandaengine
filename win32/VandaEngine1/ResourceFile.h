#pragma once

#include "Common\Utility.h"

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
};

