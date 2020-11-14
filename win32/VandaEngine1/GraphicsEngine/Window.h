//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

#include <windows.h>
#include "OpenGL.h"


typedef struct {									// Window Creation Info
	HINSTANCE	    	hInstance;					// Application Instance
	const wchar_t*		className;					// Application ClassName
	wchar_t*			title;						// Window Title
	int					width;						// Width
	int					height;						// Height
	int					bitsPerPixel;				// Bits Per Pixel
	BOOL				isFullScreen;				// FullScreen?
	WNDPROC             windowProc;
	BOOL                testWindow;
} CWindowInitGL;									// CWindowInitGL

typedef struct {									// Contains Information Vital To A Window
	HWND				hWnd;						// Window Handle
	HDC					hDC;						// Device Context
	HGLRC				hRC;						// Rendering Context
	CWindowInitGL		init;						// Window Init
	BOOL				isVisible;					// Window Visible?
	BOOL                multiSampling;              //Request multi-sampling
} CWindowGL;										// CWindowGL

class CWindow
{
private:
	BOOL ChangeScreenResolution (int width, int height, int bitsPerPixel);
	bool InitMultisample(HINSTANCE hInstance,HWND hWnd,PIXELFORMATDESCRIPTOR pfd);
	int arbMultisampleFormat;

public:
	int m_numSamples;  //number of samples when we use multisampling   
	CWindowGL m_windowGL;
	CWindow();
	~CWindow();
	void ReshapeGL(int width, int height);									// Reshape The Window When It's Moved Or Resized
    BOOL CreateWindowGL (CWindowGL* window);									// This Code Creates Our OpenGL Window
    BOOL DestroyWindowGL(CWindowGL* window);			                        // This Code Destroys Our OpenGL Window
};

