//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

/***************HOW TO PLAY AVI FILES*************
******Docment Written by Ehsan Kamrani ***********

Files:
..\GraphicsEngine\AviPlayer.h
..\GraphicsEngine\AviPlayer.cpp

Usage:
1) Include the header file:
   #include "GraphicsEngine\AviPlayer.h"

2)Define an AVI object:
   CAviPlayer avi;

3)In your initialization function, write the following code:
	if( !avi.CLoad( _T("Assets/sample.avi") ) )
	{
	   //Report an error
	   MessageBox( NULL, _T("error loading"), _T("Vanda Engine Error"), MB_ICONINFORMATION );
	}

4)in your rendering function:
   	static CInt frame = 0;
	frame += miliseconds;
	CFloat index = frame / avi.m_mpf;
	//Repeat playing the file( You have other options;It's on to you )
	if( index >= avi.m_lastFrame )
	{
		frame = 0;
        index = 0.0f;
	}
   	avi.CGrabAVIFrame( index );

	//Enable texturing and draw your object here with glTexCoord2*()

5)In your release code:
    avi.CUnload();

************************************************/
#pragma once 
#include <vfw.h>
#include "OpenGL.h"

#pragma comment( lib, "vfw32.lib" )

class CAviPlayer
{
public:
	CAviPlayer();
	~CAviPlayer();

public:
	long m_lastFrame;          //Number Of Frames
    CInt m_mpf;                 //MiliSeconds Per Frame
	GLuint m_textureId;

	CBool Load( LPCSTR szFile );
	CVoid GrabAVIFrame( CInt frame );

private:
	CBool m_loaded;
	PAVISTREAM m_pavi;	// Handle To An Open Stream
	PGETFRAME m_pgf;	// Pointer To A GetFrame Object
	HDC m_hdc;
	HDRAWDIB m_hdd;	    // Handle For Our Dib
	HBITMAP m_hBitmap;	// Handle To A Device Dependant Bitmap
	CInt m_width;
	CInt m_height;
	CUChar * m_data;

private:
	//CVoid Flip( CVoid* buffer );
	CBool OpenAVI( LPCSTR szFile );
	CVoid CleanUp();
};
