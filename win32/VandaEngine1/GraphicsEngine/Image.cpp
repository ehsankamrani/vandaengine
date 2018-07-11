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

#include "stdafx.h"
#include "image.h"
#include "texture.h"

CImage::CImage()
{
	m_id = -1; 
	m_fileName[0] = 0; 
	m_width = 0;
	m_height = 0; 
	m_size = 0;
	m_format = -1;
	m_data = NULL; 
}

CImage::~CImage()
{
	Destroy();
	CTexture::DeleteTexture(this);
}

 CVoid CImage::SetFileName( const CChar * name )
{
	Cpy( m_fileName, name ); 
}

 CChar* CImage::GetFileName()
{
	return m_fileName; 	
}

CBool CImage::LoadImageFile( CChar * sceneFileName )
{
	return CTexture::LoadDDSTexture( this, m_fileName, sceneFileName ); 		
	//return CTexture::LoadDDSTexture( this, m_fileName, sceneFileName ); 		
}


 CVoid CImage::SetId( unsigned CInt32 i )
{
	m_id = i;
}

 CVoid CImage::SetWidth( CInt32 w)
{
	m_width = w;
}

 CVoid CImage::SetHeight( CInt32 h )
{
	m_height = h;
} 

CVoid CImage::SetSize( CInt32 s )
{
	m_size = s;
} 

 CVoid CImage::SetImageData( CUChar * d )
{
	m_data = d;
}

 CVoid CImage::SetFormat( CInt32 f )
{
	m_format = f;
}

 CUInt32 CImage::GetId()
{
	return m_id;
}

 CInt32 CImage::GetWidth()
{
	return m_width;
}

 CInt32 CImage::GetHeight()
{
	return m_height;
}

CInt32 CImage::GetSize()
{
	return m_size;
}

 CInt32 CImage::GetFormat()
{
	return m_format;
}

 CUChar* CImage::GetImageData()
{
	return m_data;
}

CVoid CImage::Destroy()
{
	if( m_data )
	{
		free( m_data );
		m_data = NULL;
	}
	CTexture::DeleteTexture(this); //save functions

}

