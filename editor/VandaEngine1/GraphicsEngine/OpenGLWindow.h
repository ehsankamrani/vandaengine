#pragma once
#include "OpenGL.h"


typedef struct {									// Window Creation Info
	HINSTANCE		m_hInstance;					// Application Instance
	LPCWSTR			m_className;					// Application ClassName
	LPCWSTR			m_title;						// Window Title
	CInt			m_width;						// Width
	CInt			m_height;						// Height
	CInt			m_bitsPerPixel;					// Bits Per Pixel
	CBool			m_isFullScreen;					// FullScreen?
	WNDPROC         m_windowProc;
	CBool           m_testWindow;
} COpenGLWindowInit;								// GL_WindowInit

typedef struct {									    // Contains Information Vital To A Window
	HWND		    	m_hwnd;							// Window Handle
	HWND                m_parent;                       //window's parent. Pass NULL if there's no parent
	HDC			    	m_hdc;							// Device Context
	HGLRC			    m_hrc;							// Rendering Context
	COpenGLWindowInit	m_init;							// Window Init
	CBool		    	m_isVisible;					// Window Visible?
	CBool               m_multiSampling;                //Request multi-sampling

} COpenGLWindow;										// GL_Window

class CWindow
{
public:
	CWindow();
	~CWindow();
	CVoid Reshape( CInt width, CInt height);		// Reshape The Window When It's Moved Or Resized
    CBool Create( COpenGLWindow* window );			// This Code Creates Our OpenGL Window
    CBool Destroy( COpenGLWindow* window );			// This Code Destroys Our OpenGL Window
	CInt m_numSamples;								//number of samples when we use multisampling   

private:
	CBool ChangeScreenResolution ( CInt width, CInt height, CInt bitsPerPixel );
	CBool InitMultisample( HINSTANCE hInstance, HWND hWnd, PIXELFORMATDESCRIPTOR pfd );

private:
	CInt m_arbMultisampleFormat;

};
