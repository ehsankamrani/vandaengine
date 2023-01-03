//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "Avi.h"

CAvi::CAvi()
{
	m_loaded = false;
}
CAvi::~CAvi()
{
	if( m_loaded )
        cleanUp();
}

bool CAvi::Load( LPCWSTR szFile )
{
	m_data = NULL;
	m_hDC = CreateCompatibleDC(0);
	if( !m_hDC )
	{ 
		MessageBox( NULL, _T("Couldn't find the device context to play the CAvi file."), _T("VandaEngine Error"), MB_OK | MB_ICONERROR );
		return 0;
	}
	m_hdd = DrawDibOpen();
	if( !m_hdd )
	{
		MessageBox( NULL, _T("Couldn't find HDD to initialize CAvi file."), _T("VandaEngine Error"), MB_OK | MB_ICONERROR );
		return 0;
	}
    if( !OpenAVI( szFile ) ) 
		return 0;

	glGenTextures( 1, &m_textureId );
	glBindTexture( GL_TEXTURE_2D, m_textureId ); 

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, 1024, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_data );
	m_loaded = true;
	return 1;
}

bool CAvi::OpenAVI( LPCWSTR szFile )
{
	AVISTREAMINFO psi;
	AVIFileInit();
	if( AVIStreamOpenFromFile( &m_pavi, szFile, streamtypeVIDEO, 0, OF_READ, NULL) !=0)
	{
		MessageBox( NULL, _T("Couldnt open the CAvi stream."), _T("VandaEngine Error"), MB_OK | MB_ICONERROR );
		return 0;
	}
	AVIStreamInfo(m_pavi, &psi, sizeof(psi));				// Reads Information About The Stream Into psi
	m_width=psi.rcFrame.right-psi.rcFrame.left;			// Width Is Right Side Of Frame Minus Left
	m_height=psi.rcFrame.bottom-psi.rcFrame.top;			// Height Is Bottom Of Frame Minus Top
	m_lastFrame = AVIStreamLength(m_pavi);	
	m_mpf=AVIStreamSampleToTime(m_pavi,m_lastFrame)/m_lastFrame;		// Calculate Rough Milliseconds Per Frame
	if( m_mpf == 0 )
	{
		MessageBox( NULL, _T("MPF is 0"), _T("VandaEngine Error"), MB_OK | MB_ICONINFORMATION );
		return 0;
	}

    BITMAPINFOHEADER bmih;
	bmih.biSize = sizeof (BITMAPINFOHEADER);					// Size Of The BitmapInfoHeader
	bmih.biPlanes = 1;											// Bitplanes	
	bmih.biBitCount = 24;										// Bits Format We Want (24 Bit, 3 Bytes)
	bmih.biWidth = 1024;											// Width We Want (512 Pixels)
	bmih.biHeight = 512;										// Height We Want (256 Pixels)
	bmih.biCompression = BI_RGB;								// Requested Mode = RGB

	m_hBitmap = CreateDIBSection (m_hDC, (BITMAPINFO*)(&bmih), DIB_RGB_COLORS, (void**)(&m_data), NULL, NULL);
	SelectObject (m_hDC, m_hBitmap);		// Select m_hBitmap Into Our Device Context (hdc)

	m_pgf=AVIStreamGetFrameOpen(m_pavi, NULL);	// Create The PGETFRAME	Using Our Request Mode
	if (m_pgf==NULL)
	{
		//An Error Occurred Opening The Frame
		MessageBox( NULL, _T("Couldn't open the CAvi frame."), _T("VandaEngine Error"), MB_OK | MB_ICONINFORMATION );
		return 0;
	}
	return 1;
}

void CAvi::GrabAVIFrame( int frame )
{
	char* pdata;
	LPBITMAPINFOHEADER lpbi;									// Holds The Bitmap Header Information
	lpbi = (LPBITMAPINFOHEADER)AVIStreamGetFrame(m_pgf, frame);	// Grab Data From The CAvi Stream
	pdata=(char *)lpbi+lpbi->biSize+lpbi->biClrUsed * sizeof(RGBQUAD);	// Pointer To Data Returned By AVIStreamGetFrame

	// Convert Data To Requested Bitmap Format
	DrawDibDraw (m_hdd, m_hDC, 0, 0, 1024, 512, lpbi, pdata, 0, 0, m_width, m_height, 0);

	//Flip( data );
	// Update The Texture
	glBindTexture( GL_TEXTURE_2D, m_textureId );
	glTexSubImage2D (GL_TEXTURE_2D, 0, 0, 0, 1024, 512, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_data);
}

/*
void CAvi::Flip(void* buffer)										// Flips The Red And Blue Bytes (256x256)
{
	void* b = buffer;											// Pointer To The Buffer
	__asm														// Assembler Code To Follow
	{
		mov ecx, 256*256										// Counter Set To Dimensions Of Our Memory Block
		mov ebx, b												// Points ebx To Our Data (b)
		label:													// Label Used For Looping
			mov al,[ebx+0]										// Loads Value At ebx Into al
			mov ah,[ebx+2]										// Loads Value At ebx+2 Into ah
			mov [ebx+2],al										// Stores Value In al At ebx+2
			mov [ebx+0],ah										// Stores Value In ah At ebx
			
			add ebx,3											// Moves Through The Data By 3 Bytes
			dec ecx												// Decreases Our Loop Counter
			jnz label											// If Not Zero Jump Back To Label
	}
}
*/

void CAvi::cleanUp(void)												// Properly Closes The Avi File
{
	glDeleteTextures( 1, &m_textureId );
	DeleteObject(m_hBitmap);										// Delete The Device Dependant Bitmap Object
	DrawDibClose(m_hdd);											// Closes The DrawDib Device Context
	AVIStreamGetFrameClose(m_pgf);								// Deallocates The GetFrame Resources
	AVIStreamRelease(m_pavi);										// Release The Stream
	AVIFileExit();												// Release The File
}