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
class C3DSound
{
public:
	C3DSound(){ m_f3DSoundVolume = 0.0f; SetIndex(); m_source = NULL; m_buffer = NULL; }
	~C3DSound();

public:
	CChar m_name[MAX_NAME_SIZE];
	CChar m_path[MAX_NAME_SIZE];
	COpenALSoundBuffer* m_buffer;
	COpenALSoundSource* m_source;
	CFloat m_f3DSoundPos[3];
	CFloat m_f3DSoundPitch;
	CFloat m_f3DSoundVolume;
	CFloat m_f3DSoundRolloff;
	CFloat m_f3DSoundMaxDistance;
	CFloat m_f3DSoundReferenceDistance;
	CFloat m_f3DSoundGain;
	CBool m_loop, m_play;

	CInt m_nameIndex; //For selection
	//#user interface#
public:
	CVoid SetName( CChar* name ) { Cpy( m_name, name ); }
	CVoid SetPath( CChar* path ) { Cpy( m_path, path ); }
	CVoid SetPosition( CFloat* pos ){ m_f3DSoundPos[0] = pos[0];m_f3DSoundPos[1] = pos[1];m_f3DSoundPos[2] = pos[2]; }
	CVoid SetPitch( CFloat pitch ) { m_f3DSoundPitch = pitch; }
	CVoid SetVolume( CFloat volume ) { m_f3DSoundVolume = volume; }
	CVoid SetRolloff( CFloat rolloff ) { m_f3DSoundRolloff = rolloff; }
	CVoid SetMaxDistance( CFloat maxDistance ) { m_f3DSoundMaxDistance = maxDistance; }
	CVoid SetReferenceDistance( CFloat referenceDistance ) { m_f3DSoundReferenceDistance = referenceDistance; }
	CVoid SetLoop( CBool loop ) { m_loop = loop; }
	CVoid SetPlay( CBool play ) { m_play = play; }
	CVoid SetSoundSource( COpenALSoundSource* source ) { m_source = source; }
	CVoid SetSoundBuffer( COpenALSoundBuffer* buffer ) { m_buffer = buffer; }
	CVoid SetIndex() { m_nameIndex = g_nameIndex++; }
	CVoid SetIndex(CInt index) { m_nameIndex = index; }
public:
	CChar* GetName() { return m_name; }
	CChar* GetPath() { return m_path; }
	CVoid GetPosition( CFloat*p ) { p[0] = m_f3DSoundPos[0]; p[1] = m_f3DSoundPos[1]; p[2] = m_f3DSoundPos[2];}
	CFloat* GetPosition() { return m_f3DSoundPos;}
	CFloat GetPitch( ) { return m_f3DSoundPitch; }
	CFloat GetVolume() { return m_f3DSoundVolume; }
	CFloat GetRolloff() { return m_f3DSoundRolloff; }
	CFloat GetMaxDistance() { return m_f3DSoundMaxDistance; }

	CFloat GetReferenceDistance( ) { return m_f3DSoundReferenceDistance; }
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