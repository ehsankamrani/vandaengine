//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "../common/utility.h"
#include "OpenALSoundSource.h"
#include "OpenALSoundBuffer.h"
//std headers
#include <string>
#include <set>
#include <map>
#include <vector>
class CAmbientSound
{
public:
	CAmbientSound() { m_buffer = NULL; m_source = NULL; }
	~CAmbientSound() { alSourceStop(m_source->GetSource()); alSourcei(m_source->GetSource(), AL_BUFFER, AL_NONE); CDelete(m_buffer); CDelete(m_source); m_VSceneList.clear(); }
	CVoid SetName( CChar* name ) {Cpy( m_name, name ); }
	CVoid SetPath( CChar* path ) {Cpy( m_path, path ); }
	CVoid SetVolume( CFloat volume) { m_volume = volume; }
	CVoid SetPitch( CFloat pitch ) { m_pitch = pitch; }
	CVoid SetSoundSource( COpenALSoundSource* source ) { m_source = source; }
	CVoid SetSoundBuffer( COpenALSoundBuffer* buffer ) { m_buffer = buffer; }
	COpenALSoundSource* GetSoundSource() { return m_source; }
	COpenALSoundBuffer* GetSoundBuffer() { return m_buffer; }

	CChar* GetName(){ return m_name; }
	CChar* GetPath(){ return m_path; }
	CFloat GetVolume() { return m_volume; }
	CFloat GetPitch() { return m_pitch; }
	CChar m_name[MAX_NAME_SIZE];
	CChar m_path[MAX_NAME_SIZE];
	CFloat m_pitch;
	CFloat m_volume;
	COpenALSoundBuffer* m_buffer;
	COpenALSoundSource* m_source;

public:
		std::vector<std::map<std::string,CBool>> m_VSceneList; //List of all VScenes created via the editor, save functions

	inline CVoid AddVSceneToList(std::string vSceneName, CBool save) //save functions
	{
		for (CUInt i = 0; i < m_VSceneList.size(); i++)
		{
			if (m_VSceneList[i].begin()->first == vSceneName)
			{
				m_VSceneList[i].begin()->second = save;
				return;
			}
		}
		std::map<std::string, CBool> tempVScene;
		tempVScene[vSceneName] = save;
		m_VSceneList.push_back(tempVScene);
	}
	inline CBool IsInVSceneList( std::string vSceneName, CBool content, CBool reverseTheContent ) //save functions
	{
		for( CUInt i = 0; i < m_VSceneList.size(); i++ )
		{
			if( m_VSceneList[i].begin()->first == vSceneName )
			{
				if( m_VSceneList[i].begin()->second == content) //found the target
				{
					if( reverseTheContent )
						m_VSceneList[i].begin()->second = !content;
					return CTrue;
				}
				else
					return CFalse;
			}
		}
		if( reverseTheContent )
			AddVSceneToList( vSceneName, !content );
		else
			AddVSceneToList( vSceneName, content );
		return CTrue;
	}

};
