/*************************************************
***********HOW TO USE THE BITMAP CLASS***********
******Docment Written by Ehsan Kamrani***********

Files: 
..\GraphicsEngine\Bitmap.h
..\GraphicsEngine\Bitmap.cpp

Usage:
1)Include the header file:
   #include "GraphicEngines\Bitmap.h"

2)Define a CBitmapTexture object:
	CBitmapTexture bitmap_texture;

3)To load a file:
	if( !bitmap_texture.CLoad( fileName ) )
		return CFalse;

4)To unload a file:
	bitmap_texture.CUnload();

************************************************/
#pragma once

class CBitmapTexture
{
public:
	CBitmapTexture();
	~CBitmapTexture();

	BITMAPFILEHEADER	m_bitmapFileHeader;	// bitmap file header
	BITMAPINFOHEADER    m_bitmapInfoHeader; 
	CUChar		*m_bitmapImage;			// bitmap image data
	CUChar       *m_bitmapImageWithAlpha;      
	CBool CLoad( CChar *filename );
	CBool CLoadWithAlpha( CChar* filename );
	CVoid CUnload();
};
