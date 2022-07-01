//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "..\\common\\utility.h"
#include "opengl.h"
#include "image.h"
#include "texture.h"

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
	CVoid SetFog(CBool set) { m_fog = set; }

	CChar* GetName() { return m_name; }
	CChar* GetPath() { return m_path; }
	CFloat GetRadius() { return m_radius; }
	CFloat* GetPosition() { return m_position; }
	CFloat GetDampening() { return m_dampening; }
	CInt GetSides() { return m_numSides; }
	CInt GetSlices() { return m_numSlices; }
	CBool GetExponential() { return m_exponential; }
	CBool GetFog() { return m_fog; }

	CVoid SetIndex() { m_nameIndex = g_nameIndex++; } //selection

	CVoid Destroy();

	CChar m_name[MAX_NAME_SIZE];
	CChar m_path[MAX_NAME_SIZE];
	CInt m_numSlices;
	CInt m_numSides;
	CFloat m_radius;
	CFloat m_position[3];
	CFloat m_dampening;
	CBool m_exponential;
	CBool m_fog;
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

	CInt m_nameIndex; //selection
};

