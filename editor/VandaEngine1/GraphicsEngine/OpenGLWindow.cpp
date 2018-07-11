#include "stdafx.h"
#include "OpenGLWindow.h"
#include "..\resource.h"
CWindow::CWindow()
{
}

CWindow:: ~CWindow()
{
}

CBool CWindow::ChangeScreenResolution ( CInt width, CInt height, CInt bitsPerPixel )	// Change The Screen Resolution
{
	DEVMODE dmScreenSettings;											// device mode
    EnumDisplaySettings (NULL, ENUM_CURRENT_SETTINGS, &dmScreenSettings);	
	dmScreenSettings.dmPelsWidth = width;								// screen width
	dmScreenSettings.dmPelsHeight = height;								// screen height
	dmScreenSettings.dmBitsPerPel = bitsPerPixel;						// bits per pixel
	if ( ChangeDisplaySettings (&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL )
	{
		return CTrue;													// Display Change Failed, Return False
	}
	return CFalse;														// Display Change Was Successful, Return True
}

CBool CWindow::InitMultisample( HINSTANCE hInstance,HWND hWnd,PIXELFORMATDESCRIPTOR pfd )
{  
	 // See If The String Exists In WGL!
	if(!WGLEW_ARB_multisample)
	{
		return CFalse;
	}

	// Get Our Current Device Context
	HDC hDC = GetDC(hWnd);

	CInt	pixelFormat;
	CInt	valid;
	UINT	numFormats;
	CFloat	fAttributes[] = {0,0};

	// These Attributes Are The Bits We Want To Test For In Our Sample
	// Everything Is Pretty Standard, The Only One We Want To 
	// Really Focus On Is The SAMPLE BUFFERS ARB And WGL SAMPLES
	// These Two Are Going To Do The Main Testing For Whether Or Not
	// We Support Multisampling On This Hardware.
	CInt iAttributes[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_COLOR_BITS_ARB, 24,
		WGL_ALPHA_BITS_ARB, 8,
		WGL_DEPTH_BITS_ARB, 16,
		WGL_STENCIL_BITS_ARB, 0,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
		WGL_SAMPLES_ARB, m_numSamples,
		0, 0
	};

	// First We Check To See If We Can Get A Pixel Format For 4 Samples
	valid = wglChoosePixelFormatARB(hDC,iAttributes,fAttributes,1,&pixelFormat,&numFormats);
 
	// If We Returned True, And Our Format Count Is Greater Than 1
	if (valid && numFormats >= 1)
	{
		m_arbMultisampleFormat = pixelFormat;	
		return CTrue;
	}

	// Our Pixel Format With 4 Samples Failed, Test For 2 Samples
	CInt temp = m_numSamples / 2;
	for( ; ; )
	{
		if( temp < 2 )
			return CFalse;
		iAttributes[19] = temp;
		valid = wglChoosePixelFormatARB( hDC, iAttributes, fAttributes, 1, &pixelFormat, &numFormats );
		if (valid && numFormats >= 1)
		{
			m_arbMultisampleFormat = pixelFormat;	 
			return CTrue;
		}
		temp = m_numSamples / 2;
	}
	  
	return  CFalse;
}

CVoid CWindow::Reshape( GLsizei width, GLsizei height )									// Reshape The Window When It's Moved Or Resized
{
	glViewport (0, 0, (GLsizei)(width), (GLsizei)(height));				// Reset The Current Viewport
	glMatrixMode (GL_PROJECTION);										// Select The Projection Matrix
	glLoadIdentity ();													// Reset The Projection Matrix
	gluPerspective( 45.0f, (CFloat)width/(CFloat)height, 0.1,  1000.0);
	glMatrixMode (GL_MODELVIEW);										// Select The Modelview Matrix
	glLoadIdentity ();													// Reset The Modelview Matrix
}

CBool CWindow::Create( COpenGLWindow* window )									// This Code Creates Our OpenGL Window
{
	m_arbMultisampleFormat = 0;

	if( (window->m_init.m_testWindow) )
		ShowCursor( CTrue );
	else
		ShowCursor( CFalse );

	WNDCLASSEX windowClass;		// window class
	DWORD windowStyle;							// Define Our Window Style
	DWORD windowExtendedStyle;	// Window Extended Style

	if (window->m_init.m_isFullScreen)								// Are We Still In Fullscreen Mode?
	{
		windowExtendedStyle=WS_EX_APPWINDOW;				// Window Extended Style
		windowStyle=WS_POPUP;						// Windows Style
	}
	else
	{
		windowExtendedStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	// Window Extended Style
		windowStyle=WS_OVERLAPPEDWINDOW;					// Windows Style
	}


	// fill out the window class structure
	windowClass.cbSize			= sizeof(WNDCLASSEX);
	windowClass.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	windowClass.lpfnWndProc		= window->m_init.m_windowProc;
	windowClass.cbClsExtra		= 0;
	windowClass.cbWndExtra		= 0;
	windowClass.hInstance		= window->m_init.m_hInstance;
	windowClass.hCursor			= LoadCursor(NULL, IDC_ARROW);		// default arrow
	windowClass.hbrBackground	= NULL;								// don't need background
	windowClass.lpszMenuName	= NULL;								// no menu
	windowClass.lpszClassName	= window->m_init.m_className;
	windowClass.hIconSm			= LoadIcon( window->m_init.m_hInstance, MAKEINTRESOURCE( IDR_MAINFRAME ) );
	windowClass.hIcon			= LoadIcon( window->m_init.m_hInstance, MAKEINTRESOURCE( IDR_MAINFRAME ) );

	// register the windows class
	if (!RegisterClassEx(&windowClass))
		return 0;

	RECT windowRect = {0, 0, window->m_init.m_width, window->m_init.m_height};	// Define Our Window Coordinates


 
	if ( window->m_init.m_isFullScreen == CTrue )								// Fullscreen Requested, Try Changing Video Modes
	{
		if ( ChangeScreenResolution( window->m_init.m_width, window->m_init.m_height, window->m_init.m_bitsPerPixel ) == CFalse )
		{
			// Fullscreen Mode Failed.  Run In Windowed Mode Instead
			MessageBox (HWND_DESKTOP, _T("CWindow::Create\nMode Switch Failed.\nRunning In Windowed Mode."), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
			window->m_init.m_isFullScreen = CFalse;							// Set isFullscreen To False (Windowed Mode)
		}
	}
	else if( window->m_init.m_isFullScreen == CFalse )																// If Fullscreen Was Not Selected
	{
		// Adjust Window, Account For Window Borders
		AdjustWindowRectEx (&windowRect, windowStyle, 0, windowExtendedStyle);
	}

	// Create The OpenGL Window
	window->m_hwnd = CreateWindowEx (windowExtendedStyle,				// Extended Style
									window->m_init.m_className,			// Class Name
									window->m_init.m_title,				// Window Title
									windowStyle | WS_CLIPCHILDREN |
									WS_CLIPSIBLINGS | WS_VISIBLE,		// Window Style
									0, 0,								// Window X,Y Position
									windowRect.right - windowRect.left,	// Window Width
									windowRect.bottom - windowRect.top,	// Window Height
									window->m_parent,						        // Desktop Is Window's Parent
									NULL,								// No Menu
									window->m_init.m_hInstance,				// Pass The Window Instance
									NULL);

	if (window->m_hwnd == 0)												// Was Window Creation A Success?
	{
		return CFalse;													// If Not Return False
	}

	window->m_hdc = GetDC (window->m_hwnd);									// Grab A Device Context For This Window
	if (window->m_hdc == 0)												// Did We Get A Device Context?
	{
		// Failed
		DestroyWindow( window->m_hwnd );									// Destroy The Window
		window->m_hwnd = 0;												// Zero The Window Handle
		return CFalse;													// Return False
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
	pfd.cColorBits = window->m_init.m_bitsPerPixel ;
	pfd.cDepthBits = 32 ;
	pfd.iLayerType = PFD_MAIN_PLANE ;

	GLuint PixelFormat;													// Will Hold The Selected Pixel Format
  
	if( !window->m_multiSampling )
	{
		PixelFormat = ChoosePixelFormat (window->m_hdc, &pfd);				// Find A Compatible Pixel Format

		if (PixelFormat == 0)												// Did We Find A Compatible Format?
		{
			// Failed
			ReleaseDC (window->m_hwnd, window->m_hdc);							// Release Our Device Context
			window->m_hdc = 0;												// Zero The Device Context
			DestroyWindow (window->m_hwnd);									// Destroy The Window
			window->m_hwnd = 0;												// Zero The Window Handle
			return CFalse;													// Return False
		}

	}
	else
	{
        if(!InitMultisample(window->m_init.m_hInstance,window->m_hwnd,pfd))
		{
			MessageBox( NULL, _T("CWindow::Create\nCouldn't initialize multisampling"), _T("Error"), MB_OK );
			window->m_multiSampling = CFalse;
            Destroy(window);
            return Create(window);
        }
		else
		{
			window->m_multiSampling = CTrue;
			PixelFormat = m_arbMultisampleFormat;
		}
	}
//ENDROACH

	if (SetPixelFormat (window->m_hdc, PixelFormat, &pfd) == CFalse)	// Try To Set The Pixel Format
	{

		// Failed
		ReleaseDC( window->m_hwnd, window->m_hdc );						// Release Our Device Context
		window->m_hdc = 0;												// Zero The Device Context
		DestroyWindow (window->m_hwnd);									// Destroy The Window
		window->m_hwnd = 0;												// Zero The Window Handle
		return CFalse;													// Return False
	}

	window->m_hrc = wglCreateContext( window->m_hdc );					// Try To Get A Rendering Context
	if (window->m_hdc == 0)												// Did We Get A Rendering Context?
	{

		// Failed
		ReleaseDC ( window->m_hwnd, window->m_hdc );							// Release Our Device Context
		window->m_hdc = 0;												// Zero The Device Context
		DestroyWindow (window->m_hwnd);									// Destroy The Window
		window->m_hwnd = 0;												// Zero The Window Handle
		return CFalse;													// Return False
	}

	// Make The Rendering Context Our Current Rendering Context
	if (wglMakeCurrent( window->m_hdc, window->m_hrc ) == CFalse )
	{
		// Failed
		wglDeleteContext( window->m_hrc );									// Delete The Rendering Context
		window->m_hrc = 0;												// Zero The Rendering Context
		ReleaseDC( window->m_hwnd, window->m_hdc);							// Release Our Device Context
		window->m_hdc = 0;												// Zero The Device Context
		DestroyWindow( window->m_hwnd );									// Destroy The Window
		window->m_hwnd = 0;												// Zero The Window Handle
		return CFalse;													// Return False
	}

	
//ROACH
	/*
	Now that our window is created, we want to queary what samples are available
	we call our InitMultiSample window
	if we return a valid context, we want to destroy our current window
	and create a new one using the multisample interface.
	*/

//ENDROACH

	if( !( window->m_init.m_testWindow) )
	{
		ShowWindow(window->m_hwnd, SW_SHOW);							// Make The Window Visible
		window->m_isVisible = CTrue;									// Set isVisible To True
	}
	else
	{
		ShowWindow( window->m_hwnd, SW_HIDE );							// Make The Window Visible
		window->m_isVisible = CFalse;									// Set isVisible To True

	}

	Reshape(window->m_init.m_width, window->m_init.m_height);			// Reshape Our GL Window

	return CTrue;														// Window Creating Was A Success
																		// Initialization Will Be Done In WM_CREATE
}

CBool CWindow::Destroy( COpenGLWindow* window)							// Destroy The OpenGL Window & Release Resources
{
	if( window->m_multiSampling )
		glDisable( GL_MULTISAMPLE );
	if (window->m_hwnd != 0)												// Does The Window Have A Handle?
	{	
		if (window->m_hdc != 0)											// Does The Window Have A Device Context?
		{
			wglMakeCurrent (window->m_hdc, 0);							// Set The Current Active Rendering Context To Zero
			if (window->m_hrc != 0)										// Does The Window Have A Rendering Context?
			{
				wglDeleteContext (window->m_hrc);							// Release The Rendering Context
				window->m_hrc = 0;										// Zero The Rendering Context

			}
			ReleaseDC (window->m_hwnd, window->m_hdc);						// Release The Device Context
			window->m_hdc = 0;											// Zero The Device Context
		}
		DestroyWindow (window->m_hwnd);									// Destroy The Window
		window->m_hwnd = 0;												// Zero The Window Handle
	}

	if (window->m_init.m_isFullScreen)										// Is Window In Fullscreen Mode
	{
		ChangeDisplaySettings (NULL,0);									// Switch Back To Desktop Resolution
	}	
	//ShowCursor (CTrue);												// Show The Cursor

	UnregisterClass( window->m_init.m_className, window->m_init.m_hInstance );		// UnRegister Window Class
	return CTrue;														// Return True
}
