/*
 * Copyright 2006 Sony Computer Entertainment Inc.
 *
 * Licensed under the SCEA Shared Source License, Version 1.0 (the "License"); you may not use this 
 * file except in compliance with the License. You may obtain a copy of the License at:
 * http://research.scea.com/scea_shared_source_license.html
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License 
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
 * implied. See the License for the specific language governing permissions and limitations under the 
 * License. 
 */

#pragma once
#include "base.h"
#include "..\common\utility.h"
#include "geometry.h"
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
