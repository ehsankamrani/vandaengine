//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once


#define NOMINMAX

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes

#include "common\defines.h"

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// MFC support for internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

//This variable is used for selection. there's the same variable inside CNode class
//This name is used inside glPushName() when the user presses the left mouse button to select the objects
extern CUInt g_nameIndex;  
extern CUInt g_nodeIndex;
extern CInt g_selectedName; //holds the name of the selected object
extern CInt g_tempLastEngineObjectSelectedName; //temporary holds the name of the previous selected object
extern CInt g_lastEngineObjectSelectedName; //holds the name of the previous selected object
extern CBool g_transformObject; //we are in translation mode if an arrow is selected
extern CInt g_transformDirection; //X, Y, or Z
extern CBool g_importColladaImages;
extern CInt g_numVerts; 
extern CBool g_reportInfo;
#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
struct lua_State;
class CGeometry;
CVoid PrintShaderLog( CString strText ); // global print
CVoid PrintInfo(CString strText, COLORREF color = COLOR_WHITE, CBool reset = CFalse); // global print
CVoid PrintScriptInfo(CString strText, COLORREF color = COLOR_GREEN); // global print
CGeometry* GetGeometryFromScenes(const CChar * name, const CChar * DocURI);

class CPrefab;
CPrefab* GetPrefab(CChar* name);

CInt PlaySoundLoop(lua_State *L);
CInt PlaySoundOnce(lua_State *L);
CInt StopSound(lua_State *L);
CInt PauseSound(lua_State *L);
CInt BlendCycle(lua_State *L);
CInt ClearCycle(lua_State *L);
CInt ExecuteAction(lua_State *L);
CInt ReverseExecuteAction(lua_State *L);
CInt LoadVScene( lua_State *L);
CInt ActivateCamera(lua_State *L);

CInt LoadResource(lua_State *L);
CInt PlayResourceSoundLoop(lua_State *L);
CInt PlayResourceSoundOnce(lua_State *L);
CInt StopResourceSound(lua_State *L);
CInt PauseResourceSound(lua_State *L);
CInt StopAllResourceSounds(lua_State *L);

CInt LoadGUI(lua_State *L);
CInt ShowGUI(lua_State *L);
CInt HideGUI(lua_State *L);
CInt ShowIcon(lua_State *L);
CInt HideIcon(lua_State *L);