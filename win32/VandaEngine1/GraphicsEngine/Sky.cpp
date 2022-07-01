//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "sky.h"
#include "render.h"
#include "../main.h"
CSkyDome::CSkyDome()
{
	Cpy (m_strImage, "\n");
	m_hasImage = CFalse;
	m_image = CNew( CImage );
}

CSkyDome::~CSkyDome()
{
	Destroy();
}

CInt CSkyDome::Initialize()
{
	m_numIndices = m_numSlices * (m_numSides + 1) * 2;
	
	m_vertexBuffer = CNewData( CVec3f, (m_numSlices + 1) * (m_numSides + 1) );
	//m_colorBuffer = CNewData( CColor4f, (Slices + 1) * (Sides + 1) );
	m_texCoordBuffer = CNewData( CVec2f, (m_numSlices + 1) * (m_numSides + 1) );
	//m_skyMapTexCoordBuffer = CNewData( CVec2f, (Slices + 1) * (Sides + 1) );

	m_indexBuffer = CNewData( unsigned short, m_numIndices );
	
	CFloat polyAng = 2.0f * PI / m_numSides, ang;

	m_exponential = CFalse; //use to tesselate
		
	CFloat vx, vy, vz;
	
	CInt i, j;
	for (j = 0; j <= m_numSlices; j++)
	{
		ang = j * ( (PI / 2) / m_numSlices );
		for (i = 0; i <= m_numSides; i++)
		{						
			vx = cos(i * polyAng) * cos(ang);
			vy = sin(ang) * m_dampening;
			vz = sin(i * polyAng) * cos(ang);

			m_vertexBuffer[j * (m_numSides + 1) + i].x = vx * m_radius;
			m_vertexBuffer[j * (m_numSides + 1) + i].z = vz * m_radius;
			m_vertexBuffer[j * (m_numSides + 1) + i].y = vy * m_radius;	

			m_texCoordBuffer[j * (m_numSides + 1) + i].x = (CFloat)(i) / (CFloat)(m_numSides);
			m_texCoordBuffer[j * (m_numSides + 1) + i].y = (CFloat)(j) / (CFloat)(m_numSlices);

            //m_skyMapTexCoordBuffer[j * (Sides + 1) + i].y = (CFloat)(j) / (CFloat)(Slices);
		}
	}
	
	CInt ind = 0;
	for (j = 1; j <= m_numSlices; j++)
	{
		for (i = 0; i <= m_numSides; i++)
		{			
			m_indexBuffer[ind++] =  j * (m_numSides + 1) + i;
			m_indexBuffer[ind++] = (j - 1) * (m_numSides + 1) + i;
		}
	}
	SetSkyTexture( m_path );
	SetIndex();
	return 1;
}

CVoid CSkyDome::Destroy()
{
	CDeleteData( m_vertexBuffer );
	//CDeleteData( m_colorBuffer );
	CDeleteData( m_indexBuffer );
	CDeleteData( m_texCoordBuffer );
	//CDeleteData( m_skyMapTexCoordBuffer );
	CDelete( m_image );
}

CVoid CSkyDome::RenderDome()
{
	glUseProgram(g_render.m_skyProgram);
	glUniform1f(glGetUniformLocation(g_render.m_skyProgram, "focalDistance"), g_main->m_dof.m_focalDistance);
	glUniform1f(glGetUniformLocation(g_render.m_skyProgram, "focalRange"), g_main->m_dof.m_focalRange);
	CBool useFog;
	if (!m_fog || (g_dofProperties.m_enable && g_dofProperties.m_debug) || (g_shadowProperties.m_shadowType == eSHADOW_SINGLE_HL && g_shadowProperties.m_enable && g_render.UsingShadowShader()))
		useFog = CFalse;
	else
		useFog = CTrue;

	if (g_fogProperties.m_enable && useFog)
		glUniform1i(glGetUniformLocation(g_render.m_skyProgram, "enableFog"), CTrue);
	else
		glUniform1i(glGetUniformLocation(g_render.m_skyProgram, "enableFog"), CFalse);

	glMatrixMode(GL_MODELVIEW);
	g_render.PushMatrix();

	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);

	//glDisable(GL_DEPTH_TEST);
	int i;
	g_render.BindVBO(GL_ARRAY_BUFFER, 0 ); // Disable VBOs

    //glColor3f(1,1,1);

    //glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture( GL_TEXTURE0 );
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, m_image->GetId() );

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &m_vertexBuffer[0]);

	glClientActiveTexture(GL_TEXTURE0);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, &m_texCoordBuffer[0]);

	glTranslatef( m_position[0], m_position[1], m_position[2] );
	
	for (i = 0; i < m_numSlices; i++)
	{
		g_render.BindVBO(GL_ELEMENT_ARRAY_BUFFER, 0 );
		glDrawElements(GL_TRIANGLE_STRIP, (m_numSides + 1) * 2, GL_UNSIGNED_SHORT, &m_indexBuffer[i * (m_numSides + 1) * 2]);
	}
	
	glDisableClientState(GL_VERTEX_ARRAY);

    glClientActiveTexture(GL_TEXTURE0);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	//glDisable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);
	glPopAttrib();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();


}

CVoid CSkyDome::SetSkyTexture( CChar* path )
{ 
	CTexture::DeleteTexture( m_image );
	CTexture::LoadDDSTexture( m_image, path, NULL );
	m_hasImage = CTrue;
}