//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// VandaEngine.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "graphicsEngine/scene.h"

// CVandaEngine1App:
// See VandaEngine1.cpp for the implementation of this class
//

class CVandaEngine1App : public CWinApp
{
public:
	CVandaEngine1App();

// Overrides
	public:
	virtual BOOL InitInstance();
	HICON m_icon;
	// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CVandaEngine1App theApp;