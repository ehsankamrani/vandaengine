//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

/************************************************
*************************************************
***************HOW TO PLAY CAvi FILES************


Files:
..\GraphicEngine\Avi.h
..\GraphicEngine\Avi.cpp

Usage:
1) Include the header file:
   #include "GraphicEngine\Avi.h"

2)Define an CAvi object:
   CAvi avi;

3)In your initialization function, write the following code:
	if( !avi.Load( "m_data/Face.avi" ) )
	{
	   //Report an error
	   MessageBox( NULL, "error loading", "error", MB_ICONINFORMATION );
	}

4)in your rendering function:
   	static int frame = 0;
	frame += miliseconds;
	float index = frame / avi.m_mpf;
	//Repeat playing the file( You have other options;It's on to you )
	if( index >= avi.m_lastFrame )
	{
		frame = 0;
        index = 0.0f;
	}
   	avi.GrabAVIFrame( index );

	//Enable texturing and draw your object here with glTexCoord2*()

5)In your release code:
    avi.Unload();

************************************************/

#pragma once

#include <windows.h>
#include <vfw.h>
#include "OpenGL.h"

#pragma comment( lib, "vfw32.lib" )

class CAvi
{
public:
	CAvi();
	~CAvi();

private:
	bool m_loaded;
	PAVISTREAM m_pavi;	// Handle To An Open Stream
	PGETFRAME m_pgf;	// Pointer To A GetFrame Object
	HDC m_hDC;
	HDRAWDIB m_hdd;	// Handle For Our Dib
	HBITMAP m_hBitmap;	// Handle To A Device Dependant Bitmap
	int m_width;
	int m_height;
	unsigned char * m_data;
	bool OpenAVI( LPCWSTR szFile );

	//void Flip( void* buffer );

public:
	long m_lastFrame;          //Number Of Frames
    int m_mpf;                 //MiliSeconds Per Frame
	GLuint m_textureId;


	bool Load( LPCWSTR szFile );
	void GrabAVIFrame( int frame );

private:
	void cleanUp();

};

