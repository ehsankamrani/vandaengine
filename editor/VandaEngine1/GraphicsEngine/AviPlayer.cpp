//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "Aviplayer.h"

CAviPlayer::CAviPlayer()
{
	m_loaded = CFalse;
}
CAviPlayer::~CAviPlayer()
{
	if( m_loaded )
        CleanUp();
}

CBool CAviPlayer::Load( LPCSTR szFile )
{
	m_data = NULL;
	m_hdc = CreateCompatibleDC(0);
	if( !m_hdc )
	{ 
		MessageBox( NULL, _T("CAviPlayer::Load\nCouldn't find the device context to play the AVI file."), _T("Vanda Engine Error"), MB_OK | MB_ICONERROR );
		return 0;
	}
	m_hdd = DrawDibOpen();
	if( !m_hdd )
	{
		MessageBox( NULL, _T("CAviPlayer::Load\nCouldn't find HDD to initialize AVI file."), _T("Vanda Engine Error"), MB_OK | MB_ICONERROR );
		return 0;
	}
    if( !OpenAVI( szFile ) ) 
		return 0;

	glGenTextures( 1, &m_textureId );
	glBindTexture( GL_TEXTURE_2D, m_textureId ); 

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, 1024, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_data );
	m_loaded = CTrue;
	return 1;
}

CBool CAviPlayer::OpenAVI( LPCSTR szFile )
{
	AVISTREAMINFO psi;
	AVIFileInit();
	if( AVIStreamOpenFromFile( &m_pavi, szFile, streamtypeVIDEO, 0, OF_READ, NULL ) != 0 )
	{
		MessageBox( NULL, _T( "CAviPlayer::OpenAVI\nCouldnt open the AVI stream." ), _T("Vanda Engine Error"), MB_OK | MB_ICONERROR );
		return 0;
	}
	AVIStreamInfo( m_pavi, &psi, sizeof( psi ) );				// Reads Information About The Stream into psi
	m_width = psi.rcFrame.right - psi.rcFrame.left;			// Width Is Right Side Of Frame Minus Left
	m_height = psi.rcFrame.bottom - psi.rcFrame.top;			// Height Is Bottom Of Frame Minus Top
	m_lastFrame = AVIStreamLength( m_pavi );	
	m_mpf = AVIStreamSampleToTime( m_pavi, m_lastFrame ) / m_lastFrame;		// Calculate Rough Milliseconds Per Frame
	if( m_mpf == 0 )
	{
		MessageBox( NULL, _T("CAviPlayer::OpenAVI\nMPF is 0"), _T("Vanda Engine Error"), MB_OK | MB_ICONINFORMATION );
		return 0;
	}

    BITMAPINFOHEADER bmih;
	bmih.biSize = sizeof (BITMAPINFOHEADER);					// Size Of The BitmapInfoHeader
	bmih.biPlanes = 1;											// Bitplanes	
	bmih.biBitCount = 24;										// Bits Format We Want (24 Bit, 3 Bytes)
	bmih.biWidth = 1024;										// Width We Want (512 Pixels)
	bmih.biHeight = 512;										// Height We Want (256 Pixels)
	bmih.biCompression = BI_RGB;								// Requested Mode = RGB

	m_hBitmap = CreateDIBSection (m_hdc, ( BITMAPINFO* )( &bmih ), DIB_RGB_COLORS, ( CVoid** )( &m_data ), NULL, NULL);
	SelectObject ( m_hdc, m_hBitmap );		                        // Select hBitmap into Our Device Context (hdc)

	m_pgf = AVIStreamGetFrameOpen( m_pavi, NULL );           	// Create The PGETFRAME	Using Our Request Mode
	if ( m_pgf == NULL )
	{
		//An Error Occurred Opening The Frame
		MessageBox( NULL, _T("CAviPlayer::OpenAVI\nCouldn't open the AVI frame."), _T("Vanda Engine Error"), MB_OK | MB_ICONINFORMATION );
		return 0;
	}
	return 1;
}

CVoid CAviPlayer::GrabAVIFrame( CInt frame )
{
	if( m_loaded )
	{
		CChar* pdata;
		LPBITMAPINFOHEADER lpbi;									        // Holds The Bitmap Header Information
		lpbi = ( LPBITMAPINFOHEADER )AVIStreamGetFrame( m_pgf, frame );	    // Grab Data From The AVI Stream
		pdata = ( CChar * )lpbi + lpbi->biSize + lpbi->biClrUsed * sizeof( RGBQUAD );	// Pointer To Data Returned By AVIStreamGetFrame

		// Convert Data To Requested Bitmap Format
		DrawDibDraw ( m_hdd, m_hdc, 0, 0, 1024, 512, lpbi, pdata, 0, 0, m_width, m_height, 0 );

		//Flip( data );
		// Update The Texture
		glBindTexture( GL_TEXTURE_2D, m_textureId );
		glTexSubImage2D (GL_TEXTURE_2D, 0, 0, 0, 1024, 512, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_data);
	}
}

CVoid CAviPlayer::CleanUp(CVoid)												// Properly Closes The Avi File
{
	glDeleteTextures( 1, &m_textureId );
	DeleteObject( m_hBitmap );										// Delete The Device Dependant Bitmap Object
	DrawDibClose( m_hdd );											// Closes The DrawDib Device Context
	AVIStreamGetFrameClose( m_pgf );								// Deallocates The GetFrame Resources
	AVIStreamRelease( m_pavi );										// Release The Stream
	AVIFileExit();												// Release The File
}

/*
CVoid AVI::Flip(CVoid* buffer)								    		// Flips The Red And Blue Bytes (256x256)
{
	CVoid* b = buffer;											// Pointer To The Buffer
	__asm														// Assembler Code To Follow
	{
		mov ecx, 256*256										// Counter Set To Dimensions Of Our Memory Block
		mov ebx, b												// Points ebx To Our Data (b)
		label:													// Label Used For Looping
			mov al,[ebx+0]										// Loads Value At ebx into al
			mov ah,[ebx+2]										// Loads Value At ebx+2 into ah
			mov [ebx+2],al										// Stores Value In al At ebx+2
			mov [ebx+0],ah										// Stores Value In ah At ebx
			
			add ebx,3											// Moves Through The Data By 3 Bytes
			dec ecx												// Decreases Our Loop Counter
			jnz label											// If Not Zero Jump Back To Label
	}
}
*/
