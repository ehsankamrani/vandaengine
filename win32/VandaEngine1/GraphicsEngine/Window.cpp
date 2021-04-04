//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "window.h"
#include "..\resource.h"
#include "..\VandaEngine1Win32.h"
#include <dwmapi.h>

#pragma comment(lib, "Dwmapi.lib")

CWindow::CWindow()
{
}

CWindow:: ~CWindow()
{
}

BOOL CWindow::ChangeScreenResolution (int width, int height, int bitsPerPixel)	// Change The Screen Resolution
{
	DEVMODE dmScreenSettings;                   // Device Mode
	memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));       // Makes Sure Memory's Cleared
	dmScreenSettings.dmSize = sizeof(dmScreenSettings);       // Size Of The Devmode Structure
	dmScreenSettings.dmPelsWidth = width;            // Selected Screen Width
	dmScreenSettings.dmPelsHeight = height;           // Selected Screen Height
	dmScreenSettings.dmBitsPerPel = bitsPerPixel;             // Selected Bits Per Pixel
	dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		return FALSE;													// Display Change Failed, Return False
	}
	return TRUE;														// Display Change Was Successful, Return True
}

bool CWindow::InitMultisample(HINSTANCE hInstance,HWND hWnd,PIXELFORMATDESCRIPTOR pfd)
{  
	 // See If The String Exists In WGL!
	if(!WGLEW_ARB_multisample)
	{
		return false;
	}

	switch( g_options.m_numSamples )
	{
	case 2:
		m_numSamples = 2;
		break;
	case 4:
		m_numSamples = 4;
		break;
	case 8:
		m_numSamples = 8;
		break;
	case 16:
		m_numSamples = 16;
		break;
	default:
		m_numSamples = 0;
	}
	GLint samples;
	glGetIntegerv(GL_MAX_SAMPLES_EXT, &samples);
	if( m_numSamples > (CInt)samples )
		m_numSamples = samples;

	// Get Our Current Device Context
	HDC hDC = GetDC(hWnd);

	int		pixelFormat;
	int		valid;
	UINT	numFormats;
	float	fAttributes[] = {0,0};

	// These Attributes Are The Bits We Want To Test For In Our Sample
	// Everything Is Pretty Standard, The Only One We Want To 
	// Really Focus On Is The SAMPLE BUFFERS ARB And WGL SAMPLES
	// These Two Are Going To Do The Main Testing For Whether Or Not
	// We Support Multisampling On This Hardware.
	int iAttributes[] =
	{
		WGL_DRAW_TO_WINDOW_ARB,GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB,GL_TRUE,
		WGL_ACCELERATION_ARB,WGL_FULL_ACCELERATION_ARB,
		WGL_COLOR_BITS_ARB,24,
		WGL_ALPHA_BITS_ARB,8,
		WGL_DEPTH_BITS_ARB,24,
		WGL_STENCIL_BITS_ARB,0,
		WGL_DOUBLE_BUFFER_ARB,GL_TRUE,
		WGL_SAMPLE_BUFFERS_ARB,GL_TRUE,
		WGL_SAMPLES_ARB,m_numSamples,
		0,0
	};

	// First We Check To See If We Can Get A Pixel Format For 4 Samples
	valid = wglChoosePixelFormatARB(hDC,iAttributes,fAttributes,1,&pixelFormat,&numFormats);
 
	// If We Returned True, And Our Format Count Is Greater Than 1
	if (valid && numFormats >= 1)
	{
		arbMultisampleFormat = pixelFormat;	
		return true;
	}

	// Our Pixel Format With 4 Samples Failed, Test For 2 Samples
	int temp = m_numSamples / 2;
	for( ; ; )
	{
		if( temp < 2 )
			return false;
		iAttributes[19] = temp;
		valid = wglChoosePixelFormatARB(hDC,iAttributes,fAttributes,1,&pixelFormat,&numFormats);
		if (valid && numFormats >= 1)
		{
			arbMultisampleFormat = pixelFormat;	 
			return true;
		}
		temp = m_numSamples / 2;
	}
	  
	return  false;
}

void CWindow::ReshapeGL(GLsizei width, GLsizei height)									// Reshape The Window When It's Moved Or Resized
{
	glViewport (0, 0, (GLsizei)(width), (GLsizei)(height));				// Reset The Current Viewport
	glMatrixMode (GL_PROJECTION);										// Select The Projection Matrix
	glLoadIdentity ();													// Reset The Projection Matrix
	gluPerspective( 45.0f, (float)width/(float)height, 0.1,  1000.0);
	glMatrixMode (GL_MODELVIEW);										// Select The Modelview Matrix
	glLoadIdentity ();													// Reset The Modelview Matrix
}

BOOL CWindow::CreateWindowGL(CWindowGL* window)									// This Code Creates Our OpenGL Window
{
	arbMultisampleFormat = 0;

	if( (window->init.testWindow) )
		ShowCursor( TRUE );
	else
		ShowCursor( FALSE );

	WNDCLASSEX windowClass;		// window class
	DWORD windowStyle;							// Define Our Window Style
	DWORD windowExtendedStyle;	// Window Extended Style

	if (window->init.isFullScreen)								// Are We Still In Fullscreen Mode?
	{
		windowExtendedStyle=WS_EX_APPWINDOW;				// Window Extended Style
		windowStyle=WS_POPUP;						// Windows Style
	}
	else
	{
		windowExtendedStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	// Window Extended Style
		windowStyle=WS_POPUP;					// Windows Style
	}


	// fill out the window class structure
	windowClass.cbSize			= sizeof(WNDCLASSEX);
	windowClass.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	windowClass.lpfnWndProc		= window->init.windowProc;
	windowClass.cbClsExtra		= 0;
	windowClass.cbWndExtra		= 0;
	windowClass.hInstance		= window->init.hInstance;
	windowClass.hCursor			= LoadCursor(NULL, IDC_ARROW);		// default arrow
	windowClass.hbrBackground	= NULL;								// don't need background
	windowClass.lpszMenuName	= NULL;								// no menu
	windowClass.lpszClassName	= window->init.className;
	windowClass.hIconSm			= LoadIcon(window->init.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	windowClass.hIcon			= LoadIcon(window->init.hInstance, MAKEINTRESOURCE(IDI_VANDAENGINE));

	// register the windows class
	if (!RegisterClassEx(&windowClass))
		return 0;


	RECT windowRect = {0, 0, window->init.width, window->init.height};	// Define Our Window Coordinates


	if (window->init.isFullScreen == TRUE)								// Fullscreen Requested, Try Changing Video Modes
	{
		if (ChangeScreenResolution (window->init.width, window->init.height, window->init.bitsPerPixel) == FALSE)
		{
			// Fullscreen Mode Failed.  Run In Windowed Mode Instead
			MessageBox (HWND_DESKTOP, _T("Mode Switch Failed."), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
			return 0;							// Set isFullscreen To False (Windowed Mode)
		}
	}
	else if( window->init.isFullScreen == FALSE )																// If Fullscreen Was Not Selected
	{
		// Adjust Window, Account For Window Borders
		windowExtendedStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	// Window Extended Style
		AdjustWindowRectEx (&windowRect, windowStyle, 0, windowExtendedStyle);
	}
	// Create The OpenGL Window
	window->hWnd = CreateWindowEx (windowExtendedStyle,					// Extended Style
									window->init.className,	// Class Name
									window->init.title,					// Window Title
									windowStyle | WS_CLIPCHILDREN |
									WS_CLIPSIBLINGS | WS_VISIBLE,		// Window Style
									0, 0,								// Window X,Y Position
									windowRect.right - windowRect.left,	// Window Width
									windowRect.bottom - windowRect.top,	// Window Height
									NULL,						        // Desktop Is Window's Parent
									NULL,									// No Menu
									window->init.hInstance, // Pass The Window Instance
									NULL);

	if (window->hWnd == 0)												// Was Window Creation A Success?
	{
		return FALSE;													// If Not Return False
	}

	window->hDC = GetDC (window->hWnd);									// Grab A Device Context For This Window
	if (window->hDC == 0)												// Did We Get A Device Context?
	{
		// Failed
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
		return FALSE;													// Return False
	}

//ROACH
	/*
	Our first pass, Multisampling hasn't been created yet, so we create a window normally
	If it is supported, then we're on our second pass
	that means we want to use our pixel format for sampling
	so set PixelFormat to arbMultiSampleformat instead
  */
	PIXELFORMATDESCRIPTOR pfd ;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR)) ;
	pfd.nSize      = sizeof(PIXELFORMATDESCRIPTOR); 
	pfd.nVersion   = 1 ; 
	pfd.dwFlags    = PFD_DOUBLEBUFFER |
					PFD_SUPPORT_OPENGL |
					PFD_DRAW_TO_WINDOW ;
	pfd.iPixelType = PFD_TYPE_RGBA ;
	pfd.cColorBits = window->init.bitsPerPixel ;
	pfd.cDepthBits = 32 ;
	pfd.iLayerType = PFD_MAIN_PLANE ;

	GLuint PixelFormat;													// Will Hold The Selected Pixel Format
  
	if( !window->multiSampling )
	{
		PixelFormat = ChoosePixelFormat (window->hDC, &pfd);				// Find A Compatible Pixel Format

		if (PixelFormat == 0)												// Did We Find A Compatible Format?
		{
			// Failed
			ReleaseDC (window->hWnd, window->hDC);							// Release Our Device Context
			window->hDC = 0;												// Zero The Device Context
			DestroyWindow (window->hWnd);									// Destroy The Window
			window->hWnd = 0;												// Zero The Window Handle
			return FALSE;													// Return False
		}

	}
	else
	{
            if(!InitMultisample(window->init.hInstance,window->hWnd,pfd))
			{
				MessageBox( NULL, _T("Couldn't initialize multisampling"), _T("VandaEngine Error"), MB_OK );
				window->multiSampling = false;
                DestroyWindowGL (window);
                return CreateWindowGL(window);
            }
			else
			{
				window->multiSampling = true;
				PixelFormat = arbMultisampleFormat;
			}
	}
//ENDROACH

	if (SetPixelFormat (window->hDC, PixelFormat, &pfd) == FALSE)		// Try To Set The Pixel Format
	{

		// Failed
		ReleaseDC (window->hWnd, window->hDC);							// Release Our Device Context
		window->hDC = 0;												// Zero The Device Context
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
		return FALSE;													// Return False
	}

	window->hRC = wglCreateContext (window->hDC);						// Try To Get A Rendering Context
	if (window->hRC == 0)												// Did We Get A Rendering Context?
	{

		// Failed
		ReleaseDC (window->hWnd, window->hDC);							// Release Our Device Context
		window->hDC = 0;												// Zero The Device Context
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
		return FALSE;													// Return False
	}

	// Make The Rendering Context Our Current Rendering Context
	if (wglMakeCurrent (window->hDC, window->hRC) == FALSE)
	{
		// Failed
		wglDeleteContext (window->hRC);									// Delete The Rendering Context
		window->hRC = 0;												// Zero The Rendering Context
		ReleaseDC (window->hWnd, window->hDC);							// Release Our Device Context
		window->hDC = 0;												// Zero The Device Context
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
		return FALSE;													// Return False
	}

	
//ROACH
	/*
	Now that our window is created, we want to queary what samples are available
	we call our InitMultiSample window
	if we return a valid context, we want to destroy our current window
	and create a new one using the multisample interface.
	*/

//ENDROACH

	if( !(window->init.testWindow) )
	{
		ShowWindow(window->hWnd, SW_SHOW);								// Make The Window Visible
		window->isVisible = TRUE;											// Set isVisible To True
	}
	else
	{
		ShowWindow(window->hWnd, SW_HIDE);								// Make The Window Visible
		window->isVisible = FALSE;											// Set isVisible To True

	}


	ReshapeGL (window->init.width, window->init.height);				// Reshape Our GL Window

	return TRUE;														// Window Creating Was A Success
																		// Initialization Will Be Done In WM_CREATE
}

BOOL CWindow::DestroyWindowGL(CWindowGL* window)								// Destroy The OpenGL Window & Release Resources
{
	if( window->multiSampling )
		glDisable( GL_MULTISAMPLE );
	if (window->hWnd != 0)												// Does The Window Have A Handle?
	{	
		if (window->hDC != 0)											// Does The Window Have A Device Context?
		{
			wglMakeCurrent (window->hDC, 0);							// Set The Current Active Rendering Context To Zero
			if (window->hRC != 0)										// Does The Window Have A Rendering Context?
			{
				wglDeleteContext (window->hRC);							// Release The Rendering Context
				window->hRC = 0;										// Zero The Rendering Context

			}
			ReleaseDC (window->hWnd, window->hDC);						// Release The Device Context
			window->hDC = 0;											// Zero The Device Context
		}
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
	}

	if (window->init.isFullScreen)										// Is Window In Fullscreen Mode
	{
		ChangeDisplaySettings (NULL,0);									// Switch Back To Desktop Resolution
	}	
	//ShowCursor (TRUE);												// Show The Cursor

	UnregisterClass( window->init.className, window->init.hInstance );		// UnRegister Window Class
	return TRUE;														// Return True
}

