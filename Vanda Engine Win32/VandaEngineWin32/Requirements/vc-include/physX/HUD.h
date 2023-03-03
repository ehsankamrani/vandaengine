// ===============================================================================
//						  NVIDIA PHYSX SDK TRAINING PROGRAMS
//			                       HEADS-UP DISPLAY
//
//						    Written by Bob Schade, 5-1-06
//							Updated by Yang Liu, 7-1-08
// ===============================================================================

#ifndef HUD_H
#define HUD_H
#define _CRT_SECURE_NO_WARNINGS
#include <GL/glut.h>
#include <stdio.h>

#include "NxPhysics.h"

class DisplayString
{
public:
    char m_string[512];
	NxReal m_xpos;
	NxReal m_ypos;

	DisplayString() 
	{
		m_string[0]='\0';
		m_ypos = m_xpos = 0;
	}

	void Set(char* s, NxReal x, NxReal y)
	{
        sprintf(m_string, s);
		m_xpos = x;
		m_ypos = y;
	}
};

class HUD
{
public:
	NxArray<DisplayString> m_DisplayString;

    void AddDisplayString(char* s, NxReal x, NxReal y);
    void SetDisplayString(NxU32 i, char* s, NxReal x, NxReal y);
	void Clear();
    void Render();
};
#endif  // HUD_H

