//Original Work: Copyright 2006 Sony Computer Entertainment Inc.
//Modified Work: Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

class CDDS;
class CImage;

class CTexture
{
public:
	CTexture();
	~CTexture();
	CInt32 GetTextureType( CChar * name );
	CBool SetTexture( CImage *texObj );
	static CBool CreateTexture( CImage * texObj );
	static CBool CreateDDSTexture( CImage * texObj, CDDS * ddsImg );
	static CBool DeleteTexture( CImage * texObj );
	static CBool LoadTexture( CImage * texObj, CChar* name, CChar* sceneFileName, CBool createTexture = CTrue ); 
	static CBool LoadDDSTexture( CImage * texObj, CChar* name, CChar* sceneFileName ); 
};