/*----------------------------------------------------------------------------*\
|
|						    NVIDIA PhysX Technology
|
|							     www.nvidia.com
|
\*----------------------------------------------------------------------------*/

#ifndef __TIMEWIN_H__
#define __TIMEWIN_H__

#include <smart.h>
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#define NOMINMAX				//suppress windows' global min,max macros.

#include <Windows.h>

#define s_clTime	clWinTime	//this is so we can say "new s_clTime" and stay platform independent.

class clWinTime //: public clTime
	{
//	milisec lstTime;
	second  lstTimeS;
	DWORD	previousTime;

	public:
	clWinTime();
	~clWinTime();
	void Sleep(milisec Milisecs);
/*
	milisec GetElapsedTime();	//returns ms elapsed since last call.
	milisec PeekElapsedTime();	 
	static milisec GetTime();
*/


	//hi precision timer:
	second GetElapsedSeconds();	//returns ms elapsed since last call.
	second PeekElapsedSeconds();	 
	static double GetTimeTicks();
	static second GetClockFrequency();

	};
#endif //__TIMEWIN_H__
//NVIDIACOPYRIGHTBEGIN
///////////////////////////////////////////////////////////////////////////
// Copyright © 2010 NVIDIA Corporation.
// All rights reserved. www.nvidia.com
///////////////////////////////////////////////////////////////////////////
//NVIDIACOPYRIGHTEND
	