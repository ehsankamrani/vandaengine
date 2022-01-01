//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "OpenAL.h"
#include "OpenALSoundBuffer.h"
#include "OpenALSoundSource.h"
#include "../common/utility.h"
//std headers
#include <string>
#include <set>
#include <map>
#include <vector>
class CStaticSound
{
public:
	CStaticSound(){ m_fStaticSoundVolume = 0.0f; SetIndex(); m_source = NULL; m_buffer = NULL; }
	~CStaticSound();

public:
	CChar m_name[MAX_NAME_SIZE];
	CChar m_path[MAX_NAME_SIZE];
	COpenALSoundBuffer* m_buffer;
	COpenALSoundSource* m_source;
	CFloat m_fStaticSoundPos[3];
	CFloat m_fStaticSoundPitch;
	CFloat m_fStaticSoundVolume;
	CFloat m_fStaticSoundRolloff;
	CFloat m_fStaticSoundMaxDistance;
	CFloat m_fStaticSoundReferenceDistance;
	CFloat m_fStaticSoundGain;
	CBool m_loop, m_play;

	CInt m_nameIndex; //For selection
	//#user interface#
public:
	CVoid SetName( CChar* name ) { Cpy( m_name, name ); }
	CVoid SetPath( CChar* path ) { Cpy( m_path, path ); }
	CVoid SetPosition( CFloat* pos ){ m_fStaticSoundPos[0] = pos[0];m_fStaticSoundPos[1] = pos[1];m_fStaticSoundPos[2] = pos[2]; }
	CVoid SetPitch( CFloat pitch ) { m_fStaticSoundPitch = pitch; }
	CVoid SetVolume( CFloat volume ) { m_fStaticSoundVolume = volume; }
	CVoid SetRolloff( CFloat rolloff ) { m_fStaticSoundRolloff = rolloff; }
	CVoid SetMaxDistance( CFloat maxDistance ) { m_fStaticSoundMaxDistance = maxDistance; }
	CVoid SetRefrenceDistance( CFloat referenceDistance ) { m_fStaticSoundReferenceDistance = referenceDistance; }
	CVoid SetLoop( CBool loop ) { m_loop = loop; }
	CVoid SetPlay( CBool play ) { m_play = play; }
	CVoid SetSoundSource( COpenALSoundSource* source ) { m_source = source; }
	CVoid SetSoundBuffer( COpenALSoundBuffer* buffer ) { m_buffer = buffer; }
	CVoid SetIndex() { m_nameIndex = g_nameIndex++; }
	CVoid SetIndex(CInt index) { m_nameIndex = index; }
public:
	CChar* GetName() { return m_name; }
	CChar* GetPath() { return m_path; }
	CVoid GetPosition( CFloat*p ) { p[0] = m_fStaticSoundPos[0]; p[1] = m_fStaticSoundPos[1]; p[2] = m_fStaticSoundPos[2];}
	CFloat* GetPosition() { return m_fStaticSoundPos;}
	CFloat GetPitch( ) { return m_fStaticSoundPitch; }
	CFloat GetVolume() { return m_fStaticSoundVolume; }
	CFloat GetRolloff() { return m_fStaticSoundRolloff; }
	CFloat GetMaxDistance() { return m_fStaticSoundMaxDistance; }

	CFloat GetRefrenceDistance( ) { return m_fStaticSoundReferenceDistance; }
	CBool GetLoop() { return m_loop; }
	CBool GetPlay() { return m_play; }
	CInt GetIndex() { return m_nameIndex; }

	COpenALSoundSource* GetSoundSource() { return m_source; }
	COpenALSoundBuffer* GetSoundBuffer() { return m_buffer; }

	CVoid RenderIcon( CBool selectionMode = CFalse );

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