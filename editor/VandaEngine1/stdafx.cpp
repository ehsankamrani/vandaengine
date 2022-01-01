//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// stdafx.cpp : source file that includes just the standard includes
// VandaEngine.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

CUInt g_nameIndex = 1;  
CUInt g_nodeIndex = 1;
CUInt g_groupNameIndex = 1;
CInt g_selectedName = -1; //No valid name at the beginning
CInt g_tempLastEngineObjectSelectedName = -1;  //No valid name at the beginning
CInt g_lastEngineObjectSelectedName = -1;  //No valid name at the beginning
CBool g_transformObject = CFalse; //we are in translation mode if an arrow is selected
CInt g_transformDirection = -1; 
CBool g_importColladaImages = CTrue;
CInt g_numVerts = 0;
CBool g_reportInfo = CTrue;