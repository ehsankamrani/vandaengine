//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "sky.h"
#include "render.h"
#include "../VandaEngine1dlg.h"
CSkyDome::CSkyDome()
{
	Cpy (m_strImage, "\n");
	m_hasImage = CFalse;
	m_image = CNew( CImage );
    m_nameIndex = 0;
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
	m_VSceneList.clear();
}

CVoid CSkyDome::RenderDome()
{
	if (g_fogBlurPass)
	{
		g_shaderType = g_render.m_fogBlurProgram;
		glUseProgram(g_shaderType);
		glUniform1f(glGetUniformLocation(g_shaderType, "focalDistance"), g_multipleView->m_dof.m_focalDistance);
		glUniform1f(glGetUniformLocation(g_shaderType, "focalRange"), g_multipleView->m_dof.m_focalRange);
		CBool useFog;
		if (g_polygonMode != ePOLYGON_FILL || (g_dofProperties.m_enable && g_dofProperties.m_debug) || (g_shadowProperties.m_shadowType == eSHADOW_SINGLE_HL && g_shadowProperties.m_enable && g_render.UsingShadowShader()))
			useFog = CFalse;
		else
			useFog = CTrue;

		if ((g_fogProperties.m_enable && useFog) || (g_waterFogProperties.m_enable && useFog))
			glUniform1i(glGetUniformLocation(g_shaderType, "enableFog"), CTrue);
		else
			glUniform1i(glGetUniformLocation(g_shaderType, "enableFog"), CFalse);
	}
	else
	{
		glUseProgram(0);
	}
	glMatrixMode( GL_MODELVIEW );
	g_render.PushMatrix();
	glTranslatef( m_position[0], m_position[1], m_position[2] );

	glPushAttrib( GL_LIGHTING_BIT);
	glDisable( GL_LIGHTING );
	//glDisable(GL_DEPTH_TEST);
	int i;
	g_render.BindVBO(GL_ARRAY_BUFFER, 0 ); // Disable VBOs

    //glColor3f(1,1,1);

    //glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if( g_polygonMode == ePOLYGON_FILL )
	{
		glActiveTexture( GL_TEXTURE0 );
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, m_image->GetId() );

		glClientActiveTexture(GL_TEXTURE0);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, &m_texCoordBuffer[0]);
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &m_vertexBuffer[0]);

	
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

CVoid CSkyDome::RenderIcon(CBool selectionMode)
{
	glUseProgram(0);

	if (selectionMode)
	{
		glPushName(m_nameIndex);
	}
	if (!selectionMode)
	{
		if (m_nameIndex == g_selectedName || m_nameIndex == g_lastEngineObjectSelectedName)
		{
			g_tempLastEngineObjectSelectedName = m_nameIndex;

			if (g_transformObject)
			{
				m_position[0] = g_arrowPosition.x;
				m_position[1] = g_arrowPosition.y - 3.0f;
				m_position[2] = g_arrowPosition.z;
			}
			else
			{
				g_arrowPosition.x = m_position[0];
				g_arrowPosition.y = m_position[1] + 3.0f;
				g_arrowPosition.z = m_position[2];
			}
			g_glUtil.Billboarding(m_position[0], m_position[1] + 3.0f, m_position[2], g_skyImg->GetId(), 1.0f, 1.0f, 1.0, 0.0, 0.0);

			g_showArrow = CTrue;
		}
		else
			g_glUtil.Billboarding(m_position[0], m_position[1] + 3.0f, m_position[2], g_skyImg->GetId(), 1.0f, 1.0f);
	}
	else
		g_glUtil.Billboarding(m_position[0], m_position[1] + 3.0f, m_position[2], g_skyImg->GetId(), 1.0f, 1.0f);
	if (selectionMode)
		glPopName();

}