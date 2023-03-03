//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// VandaEngineEditor.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "graphicsEngine/scene.h"

// CVandaEngineApp:
// See VandaEngine.cpp for the implementation of this class
//

class CVandaEngineApp : public CWinApp
{
public:
	CVandaEngineApp();

// Overrides
	public:
	virtual BOOL InitInstance();
	HICON m_icon;
	// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CVandaEngineApp theApp;