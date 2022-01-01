//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

#include "OpenGL.h"

class CLightModel
{
public:
	GLvoid SetGlobalAmbient( GLfloat* ambient );
	GLvoid EnableLocalViewer();
	GLvoid DisableLocalViewer();
	GLvoid EnableTwoSide();
	GLvoid DisableTwoSide();
	GLvoid EnableSeparateSpecular();
	GLvoid DisableSepatrateSpecular();
	GLvoid Reset();

};
