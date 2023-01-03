//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
// DevIL
#ifdef _UNICODE
#undef _UNICODE
#undef UNICODE
#define UNICODE_DISABLED
#endif
#include <IL\IL.h>
#include <IL\ILU.h>
#ifdef UNICODE_DISABLED
#define _UNICODE
#endif
#pragma comment( lib, "DevIL.lib" )
#pragma comment( lib, "ILU.lib" )
