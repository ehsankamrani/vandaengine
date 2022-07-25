//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "bloom.h"
#include "texture.h"
#include "render.h"
#include "sky.h"
#include "scene.h"
#include "..\\main.h"

CBloom::~CBloom()
{
	glDeleteTextures( 1, &m_bloomTexture );
	glDeleteFramebuffersEXT( 1, &m_fboID );
	glDeleteRenderbuffersEXT(1, &m_rbID );
	glDeleteTextures( 1, &m_bloomTexture2 );
	glDeleteFramebuffersEXT( 1, &m_fboID2 );
	glDeleteRenderbuffersEXT(1, &m_rbID2 );
	
}

void CBloom::CreateEmptyTexture( CInt width, CInt height, CInt channels, CInt type )										
{
	glGenTextures(1, &m_bloomTexture );								
	glBindTexture(GL_TEXTURE_2D, m_bloomTexture );					
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, channels, width, height, 0, type, GL_UNSIGNED_BYTE, NULL );
	//glTexImage2D(GL_TEXTURE_2D, 0, channels, width, height, 0, type, GL_HALF_FLOAT, NULL );

	m_fboID = g_render.GenerateFBO();
	g_render.BindFBO( m_fboID );
	g_render.Attach2DTextureToFBOColor( m_bloomTexture );
	m_rbID = g_render.GenerateRenderBuffer();
	g_render.BindRenderBuffer( m_rbID );
	//g_render.RenderbufferStorage( size, size );
	g_render.RenderbufferStorage( width, height );
	g_render.AttachDepthToFBO( m_rbID );
	g_render.BindFBO(0);
	g_render.BindRenderBuffer(0);

	glGenTextures(1, &m_bloomTexture2 );								
	glBindTexture(GL_TEXTURE_2D, m_bloomTexture2 );					
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, channels, width, height, 0, type, GL_UNSIGNED_BYTE, NULL );
	//glTexImage2D(GL_TEXTURE_2D, 0, channels, width, height, 0, type, GL_HALF_FLOAT, NULL );

	m_fboID2 = g_render.GenerateFBO();
	g_render.BindFBO( m_fboID2 );
	g_render.Attach2DTextureToFBOColor( m_bloomTexture2 );
	m_rbID2 = g_render.GenerateRenderBuffer();
	g_render.BindRenderBuffer( m_rbID2 );
	//g_render.RenderbufferStorage( size, size );
	g_render.RenderbufferStorage( width, height );
	g_render.AttachDepthToFBO( m_rbID2 );
	g_render.BindFBO(0);
	g_render.BindRenderBuffer(0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void CBloom::CreateRuntimeTexture( int textureWidth, int textureHeight, int sceneTextureId )
{
	g_render.BindFBO(m_fboID);
	glPushAttrib( GL_VIEWPORT_BIT | GL_ENABLE_BIT ); 
	glViewport(0, 0, textureWidth, textureHeight);

	glDisable(GL_DEPTH_TEST); 
	glDisable( GL_LIGHTING );
	glDisable( GL_CULL_FACE );

	if( !g_useOldRenderingStyle )
	{
		glActiveTexture( GL_TEXTURE0 );
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, sceneTextureId );
		glClearColor( 0,0,0,0 );
		glClear(GL_COLOR_BUFFER_BIT );

		glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
		gluOrtho2D(0, g_width, 0, g_height );
		glMatrixMode(GL_MODELVIEW); glPushMatrix();	glLoadIdentity();
		glBegin(GL_QUADS);
		glTexCoord2i(0,	0);	glVertex2i(0, 0); 
		glTexCoord2i(1, 0);	glVertex2i(g_width, 0);
		glTexCoord2i(1, 1);	glVertex2i(g_width, g_height);
		glTexCoord2i(0, 1);	glVertex2i(0, g_height);
		glEnd();
		glActiveTexture( GL_TEXTURE0 );
		glDisable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, 0 );

		glMatrixMode(GL_PROJECTION); glPopMatrix();
		glMatrixMode(GL_MODELVIEW); glPopMatrix();
	}
	glFlush();

	// Restore the previous matrix
	g_render.BindFBO(0);
	float tSizeX = float(textureWidth);
	float tSizeY = float(textureHeight);
	if ( g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader )
	{
		glUseProgram( g_render.m_blurProgram );
		glUniform1f(glGetUniformLocation( g_render.m_blurProgram , "radius_x"), (float)(2.0/tSizeX) );
		glUniform1f(glGetUniformLocation( g_render.m_blurProgram , "radius_y"), (float)(2.0/tSizeY) );
		glUniform1i(glGetUniformLocation( g_render.m_blurProgram , "tex_unit_0"), 0 );
	}

	for( int i = 0; i < 5; i++ )
	{
		if( i % 2 == 0 )
		{
			g_render.BindFBO(m_fboID2);
			glActiveTexture( GL_TEXTURE0 );
			glEnable( GL_TEXTURE_2D );
			glBindTexture( GL_TEXTURE_2D, m_bloomTexture );
		}
		else
		{
			g_render.BindFBO(m_fboID);
			glActiveTexture( GL_TEXTURE0 );
			glEnable( GL_TEXTURE_2D );
			glBindTexture( GL_TEXTURE_2D, m_bloomTexture2 );
		}
		glClearColor( 0,0,0,0 );
		glClear(GL_COLOR_BUFFER_BIT );

		glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
		gluOrtho2D(0, g_width, 0, g_height);
		glMatrixMode(GL_MODELVIEW); glPushMatrix();	glLoadIdentity();
		glBegin(GL_QUADS);
		glTexCoord2i(0,	0);	glVertex2i(0, 0); 
		glTexCoord2i(1, 0);	glVertex2i(g_width, 0);
		glTexCoord2i(1, 1);	glVertex2i(g_width, g_height);
		glTexCoord2i(0, 1);	glVertex2i(0, g_height);
		glEnd();
		glFlush();

		g_render.BindFBO(0);


		glMatrixMode(GL_PROJECTION); glPopMatrix();
		glMatrixMode(GL_MODELVIEW); glPopMatrix();
	}
	if ( g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader )
	{
		glUseProgram(g_render.m_glowProgram);
		glUniform1i(glGetUniformLocation(g_render.m_glowProgram, "tex_unit_0"), 0);
	}
	g_render.BindFBO(m_fboID);

	glActiveTexture( GL_TEXTURE0 );
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, m_bloomTexture2 );
	glClearColor( 0,0,0,0 );
	glClear(GL_COLOR_BUFFER_BIT );

	glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
	gluOrtho2D(0, g_width, 0, g_height );
	glMatrixMode(GL_MODELVIEW); glPushMatrix();	glLoadIdentity();
	glBegin(GL_QUADS);
	glTexCoord2i(0,	0);	glVertex2i(0, 0); 
	glTexCoord2i(1, 0);	glVertex2i(g_width, 0);
	glTexCoord2i(1, 1);	glVertex2i(g_width, g_height);
	glTexCoord2i(0, 1);	glVertex2i(0, g_height);
	glEnd();
	glFlush();

	g_render.BindFBO(0);

	glActiveTexture( GL_TEXTURE0 );
	glDisable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, 0 );

	glMatrixMode(GL_PROJECTION); glPopMatrix();
	glMatrixMode(GL_MODELVIEW); glPopMatrix();

	if ( g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader )
		glUseProgram(0);

	glPopAttrib();
}