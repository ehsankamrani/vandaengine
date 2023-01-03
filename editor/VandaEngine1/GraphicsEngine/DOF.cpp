//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "..\VandaEngine1.h"
#include "Dof.h"

CDOF::CDOF()
{
	m_focalDistance = g_dofProperties.m_dofFocalDistance;
	m_focalRange = g_dofProperties.m_dofFocalRange;
	m_init = CFalse;
}

CBool CDOF::InitFBOs( CInt width, CInt height)
{
	if (g_useOldRenderingStyle || !g_options.m_enableFBO)
	{
		m_init = CTrue;
		return CFalse;
	}

	CInt i;
	GLenum status;

	for (i = 0; i < 4; i++)
	{
		glGenFramebuffersEXT(1, &m_fbo[i]);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo[i]);

		glGenTextures(1, &m_texid[i]);

		glBindTexture(GL_TEXTURE_2D, m_texid[i]);
		if( i == 3 )
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width/2, height/2, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_texid[i], 0);

		status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		if (status != GL_FRAMEBUFFER_COMPLETE_EXT)
		{
			MessageBoxA( NULL, "CDOF::InitFBOs : Couldn't initialize the FBO", "VandaEngine Error", MB_OK );
			return CFalse;
		}
	}
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glBindTexture( GL_TEXTURE_2D, 0 );
	m_init = CTrue;
	return CTrue;
}


void CDOF::DeleteFBOs()
{
	if( m_init )
	{
		glDeleteTextures(4, m_texid);;
		glDeleteFramebuffersEXT(4, m_fbo);
	}
}

CVoid CDOF::InitShaderVariables()
{
	GLint loc;
	glUseProgram(g_render.m_dofProgram[0]);
	loc = glGetUniformLocation(g_render.m_dofProgram[1], "Width");
	glUniform1i(loc, g_width);
	glUseProgram(g_render.m_dofProgram[1]);
	loc = glGetUniformLocation(g_render.m_dofProgram[2], "Height");
	glUniform1i(loc, g_height);
	glUseProgram(g_render.m_dofProgram[2]);
	loc = glGetUniformLocation(g_render.m_dofProgram[3], "Tex0");
	glUniform1i(loc, 0);
	loc = glGetUniformLocation(g_render.m_dofProgram[3], "Tex1");
	glUniform1i(loc, 1);
	glUseProgram(0);

}

CVoid CDOF::DrawQuad(CVoid)
{
	m_focalDistance = g_dofProperties.m_dofFocalDistance;
	m_focalRange = g_dofProperties.m_dofFocalRange;

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2d(-1, -1);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2d(1, -1);
		glTexCoord2f( 1.0f, 1.0f);
		glVertex2d(1, 1);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2d(-1, 1);
	glEnd();
}
