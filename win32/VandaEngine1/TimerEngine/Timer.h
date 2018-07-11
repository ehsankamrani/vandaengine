 /*Author   :   Dave Astle
 Date     :   11/22/2000

 Written for OpenGL Game Programming

************************************************
*****************HOW TO USE TIMER****************


Files:
TimerEngine\Timer.h
TimerEngine\Timer.cpp

Usage:
1)Include the header file:
   #include "TimerEngine\Timer.h"

2)Declare a timer object:
   	CTimer *timer;

3)In your initialization function, initialize timer:
    timer = new CTimer;
	if( !timer->CInit() )
	{
        //Report an error message
		MessageBox( NULL, _T("Cannot initialize the timer"), _T("ERROR"), MB_OK | MB_ICONINFORMATION );
		return 0; 
	}

4)In your rendering function:
    CFloat elapsedTime;
	elapsedTime = timer->CGetElapsedSeconds( 1 ) ;

5)In your release code, write the following code:
   delete timer;
   timer = NULL;
*/

#pragma once

#include "defines.h"

class CTimer
{
public:
  CTimer();
  ~CTimer();

  CBool Init();
  CFloat GetElapsedSeconds( CBool startFromBeginning = false );
  CFloat GetElapsedSeconds2(CBool startFromBeginning = false);
  CFloat GetFps( CULong elapsedFrames = 1, CBool reset = CFalse );
  CFloat LockFps( CULong targetFPS);

private:
  __int64   m_startTime;
  __int64   m_ticksPerSecond;

  __int64   m_startTime2;
  __int64   m_ticksPerSecond2;
};

