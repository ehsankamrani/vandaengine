//Original Work: Copyright 2006 Sony Computer Entertainment Inc.
//Modified Work: Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license
#pragma once
#include "base.h"
#include "..\common\utility.h"

class CTexture;

class CImage: public CBase 
{
protected:
	CInt32 m_id; 
	CInt32 m_width;
	CInt32 m_height;
	CInt32 m_format; //32 or 24 bits?
	CInt32 m_size;
	CUChar*	m_data; 

public:
	CImage();
	~CImage();
	 CVoid SetFileName( const CChar * name );
	 CBool LoadImageFile( CChar * sceneFileName );

	 CVoid SetId( CUInt32 i );
	 CVoid SetWidth( CInt32 w );
	 CVoid SetHeight( CInt32 h );
	 CVoid SetImageData( CUChar * d );
	 CVoid SetFormat( CInt32 f );
	 CVoid SetSize( CInt32 s );

	 CUInt32 GetId();
	 CInt32 GetWidth();
	 CInt32 GetHeight();
	 CInt32 GetFormat();
	 CInt32 GetSize();
	 CUChar* GetImageData();
	 CChar* GetFileName();
	 CVoid Destroy();

	CChar m_fileName[MAX_NAME_SIZE];
};
