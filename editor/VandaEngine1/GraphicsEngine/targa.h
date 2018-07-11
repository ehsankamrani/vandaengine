//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

#include "OpenGL.h"



/* Image descriptor.
      3-0: attribute bpp
      4:   left-to-right ordering
      5:   top-to-bottom ordering
      7-6: zero
*/


/*!
	Read a TGA bitmap
	Le TGA file must been :
	- Greyscale 8 bit per pixel uncompressed
	- Color 24 bit per pixel uncompressed
	- Color 32 bit per pixel uncompressed
	- Color 24 bit per pixel compressed (RLE)
	- Color 32 bit per pixel compressed (RLE)

	\param str : File name
	\param dest : Pointer on the destination 
	Pointeur vers lequel l'image est située après la fonction
	\param sizeX : width of the bitmap
	\param sizeY : height of the bitmap
	\param Bpp : Bit per pixel of the bitmap (8,24 or 32)
*/

class  CTargaHeader
{
public:
    CChar  idlength;
    CChar  colourmaptype;
    CChar  datatypecode;
    CInt16 colourmaporigin;
    CInt16 colourmaplength;
    CChar  colourmapdepth;
    CInt16 x_origin;
    CInt16 y_origin;
    CInt16 sizeX;
    CInt16 sizeY;
    CChar  bpp;
    CChar  imagedescriptor;
};

class CTargaTexture
{
public:
	CTargaTexture();	
	~CTargaTexture();	

	CInt GetSizeX();
	CInt GetSizeY();
	CInt GetBpp();
	CUChar * GetPointer();

	CInt ReadFile( const CChar *str);
	CInt Release();

private:
	CTargaHeader m_tgaHeader;
	CInt m_sizeX;
	CInt m_sizeY;
	CInt m_bpp;
	CUChar *m_dest;
};

