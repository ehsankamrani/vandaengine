//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "..\\common\\utility.h"
#include "opengl.h"
#include "image.h"
#include "texture.h"
#include <stdio.h>

//std headers
#include <string>
#include <set>
#include <map>
#include <vector>

class CSkyDome
{
public:
	CSkyDome();
	~CSkyDome();
	CInt Initialize();
	CVoid RenderDome();
	CVoid SetSkyTexture( CChar* path );
	CVoid SetName( CChar* name ) { Cpy( m_name, name ); }
	CVoid SetPath( CChar* path ) { Cpy( m_path, path ); }
	CVoid SetRadius( CFloat radius ) { m_radius = radius; }
	CVoid SetPosition( CFloat* pos ) { m_position[0] = pos[0]; m_position[1] = pos[1]; m_position[2] = pos[2]; }
	CVoid SetDampening( CFloat dampening ) { m_dampening = dampening; }
	CVoid SetSides( CInt numSides ) { m_numSides = numSides; }
	CVoid SetSlices( CInt numSlices ) { m_numSlices = numSlices; }
	CVoid SetExponential( CBool exponential ) { m_exponential = exponential; }

	CChar* GetName() { return m_name; }
	CChar* GetPath() { return m_path; }
	CFloat GetRadius() { return m_radius; }
	CFloat* GetPosition() { return m_position; }
	CFloat GetDampening() { return m_dampening; }
	CInt GetSides() { return m_numSides; }
	CInt GetSlices() { return m_numSlices; }
	CBool GetExponential() { return m_exponential; }

	CVoid RenderIcon(CBool selectionMode = CFalse);
	CVoid SetIndex() { m_nameIndex = g_nameIndex++; } //selection
	CInt GetIndex() { return m_nameIndex; }
	CVoid Destroy();
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

	CChar m_name[MAX_NAME_SIZE];
	CChar m_path[MAX_NAME_SIZE];
	CInt m_numSlices;
	CInt m_numSides;
	CFloat m_radius;
	CFloat m_position[3];
	CFloat m_dampening;
	CBool m_exponential;
	CInt m_numIndices;

private:
	CVec3f *m_vertexBuffer;
	//CColor4f *ColorBuffer;
	CVec2f *m_texCoordBuffer;
	//CVec2f *m_skyMapTexCoordBuffer;
	unsigned short *m_indexBuffer;


	CImage *m_image;
	CChar m_strImage[MAX_NAME_SIZE];
	CBool m_hasImage;

	CInt m_nameIndex; // selection

};

