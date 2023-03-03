//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "OpenGL.h"

class CDOF
{
public:
	CDOF();
	~CDOF() {};
	GLuint m_fbo[4];
	GLuint m_texid[4];
	CFloat m_focalDistance;
	CFloat m_focalRange;
	CBool InitFBOs( CInt width, CInt height);
	CVoid DeleteFBOs();
	CVoid DrawQuad();
private:
	CVoid InitShaderVariables();
	CBool m_init;
};