//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "sky.h"
#include "render.h"
#include "../VandaEngineEditorDlg.h"

CSkyDome::CSkyDome()
{
	m_vertexBuffer = NULL;
	//m_colorBuffer = NULL;
	m_indexBuffer = NULL;
	m_texCoordBuffer = NULL;

	Cpy (m_strImage, "\n");
	m_hasImage = CFalse;
	m_image = CNew( CImage );
    m_nameIndex = 0;
	m_hasScript = CFalse;
	m_updateScript = CFalse;
	Cpy(m_script, "\n");
	Cpy(m_lastScriptPath, "\n");
	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
	m_updateEvent = CTrue;
}

CSkyDome::~CSkyDome()
{
	Destroy();
}

CVoid CSkyDome::ResetLua()
{
	LuaClose(m_lua);
	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
}

CBool CSkyDome::LoadLuaFile()
{
	ResetLua();

	if (!m_hasScript)
	{
		return CFalse;
	}

	if (!LuaLoadFile(m_lua, m_script))
		return CFalse;
	return CTrue;
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
	LuaClose(m_lua);
}

CVoid CSkyDome::RenderDome()
{
	if (g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader)
	{
		glUseProgram(g_render.m_skyProgram);
		glUniform1f(glGetUniformLocation(g_render.m_skyProgram, "focalDistance"), g_multipleView->m_dof.m_focalDistance);
		glUniform1f(glGetUniformLocation(g_render.m_skyProgram, "focalRange"), g_multipleView->m_dof.m_focalRange);
		CBool useFog;
		if (!m_fog || g_polygonMode != ePOLYGON_FILL || (g_dofProperties.m_enable && g_dofProperties.m_debug) || (g_shadowProperties.m_shadowType == eSHADOW_SINGLE_HL && g_shadowProperties.m_enable && g_render.UsingShadowShader()))
			useFog = CFalse;
		else
			useFog = CTrue;

		if (g_fogProperties.m_enable && useFog)
			glUniform1i(glGetUniformLocation(g_render.m_skyProgram, "enableFog"), CTrue);
		else
			glUniform1i(glGetUniformLocation(g_render.m_skyProgram, "enableFog"), CFalse);
	}
	else
	{
		glUseProgram(0);
	}

	glMatrixMode( GL_MODELVIEW );
	g_render.PushMatrix();
	glTranslatef( m_position[0], m_position[1], m_position[2] );

	int i;
	g_render.BindVBO(GL_ARRAY_BUFFER, 0 ); // Disable VBOs

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


CChar* CSkyDome::GetScriptStringVariable(CChar* variableName)
{
	CChar *s = NULL;
	lua_getglobal(m_lua, variableName);
	if (!lua_isnil(m_lua, -1))
		s = _strdup(lua_tostring(m_lua, -1));
	else
		s = _strdup("");

	lua_pop(m_lua, 1);
	return s;
}

CBool CSkyDome::GetScriptBoolVariable(CChar* variableName)
{
	CInt value;
	CBool result;
	lua_getglobal(m_lua, variableName);
	value = lua_toboolean(m_lua, -1);
	if (value)
		result = CTrue;
	else
		result = CFalse;
	lua_pop(m_lua, 1);
	return result;
}

CInt CSkyDome::GetScriptIntVariable(CChar* variableName)
{
	CInt value;
	lua_getglobal(m_lua, variableName);
	value = lua_tointeger(m_lua, -1);
	lua_pop(m_lua, 1);
	return value;
}

CDouble CSkyDome::GetScriptDoubleVariable(CChar* variableName)
{
	CDouble value;
	lua_getglobal(m_lua, variableName);
	value = lua_tonumber(m_lua, -1);
	lua_pop(m_lua, 1);
	return value;
}

CVoid CSkyDome::SetScriptStringVariable(CChar* variableName, CChar* value)
{
	lua_pushstring(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CSkyDome::SetScriptBoolVariable(CChar* variableName, CBool value)
{
	lua_pushboolean(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CSkyDome::SetScriptIntVariable(CChar* variableName, CInt value)
{
	lua_pushinteger(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CSkyDome::SetScriptDoubleVariable(CChar* variableName, CDouble value)
{
	lua_pushnumber(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CSkyDome::InitScript()
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = NULL;
		g_currentWater = NULL;
		g_currentLight = NULL;
		g_currentEngineCamera = NULL;
		g_currentVideo = NULL;
		g_current3DSound = NULL;
		g_currentAmbientSound = NULL;
		g_currentGUI = NULL;

		lua_getglobal(m_lua, "Init");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pcall(m_lua, 0, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

CVoid CSkyDome::UpdateScript()
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = NULL;
		g_currentWater = NULL;
		g_currentLight = NULL;
		g_currentEngineCamera = NULL;
		g_currentVideo = NULL;
		g_current3DSound = NULL;
		g_currentAmbientSound = NULL;
		g_currentGUI = NULL;

		lua_getglobal(m_lua, "Update");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pcall(m_lua, 0, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}