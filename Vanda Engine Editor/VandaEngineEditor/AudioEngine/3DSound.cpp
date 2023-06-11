//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "3DSound.h"
#include "../VandaEngineEditorDlg.h"
#include "../graphicsEngine/scene.h"

C3DSound::C3DSound()
{
	m_f3DSoundVolume = 0.0f;
	SetIndex();
	m_source = NULL;
	m_buffer = NULL;

	m_hasScript = CFalse;
	m_updateScript = CFalse;
	Cpy(m_script, "\n");
	Cpy(m_lastScriptPath, "\n");

	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
	m_updateEvent = CTrue;
}

C3DSound::~C3DSound()
{
	if (m_buffer)
	{
		alSourceStop(m_source->GetSource());
		alSourcei(m_source->GetSource(), AL_BUFFER, AL_NONE);
		CDelete(m_buffer);
	}

	CDelete(m_source);
	m_VSceneList.clear();

	LuaClose(m_lua);
}

CVoid C3DSound::ResetLua()
{
	LuaClose(m_lua);
	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
}

CBool C3DSound::LoadLuaFile()
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

CVoid C3DSound::RenderIcon(CBool selectionMode)
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
				m_f3DSoundPos[0] = g_arrowPosition.x;
				m_f3DSoundPos[1] = g_arrowPosition.y;
				m_f3DSoundPos[2] = g_arrowPosition.z;
			}
			else
			{
				g_arrowPosition.x = m_f3DSoundPos[0];
				g_arrowPosition.y = m_f3DSoundPos[1];
				g_arrowPosition.z = m_f3DSoundPos[2];
			}
			g_glUtil.Billboarding(m_f3DSoundPos[0], m_f3DSoundPos[1], m_f3DSoundPos[2], g_soundImg->GetId(), 1.0f, 1.0f, 1.0, 0.0, 0.0);

			m_source->SetSoundPosition(m_f3DSoundPos);
			g_showArrow = CTrue;
		}
		else
			g_glUtil.Billboarding(m_f3DSoundPos[0], m_f3DSoundPos[1], m_f3DSoundPos[2], g_soundImg->GetId(), 1.0f, 1.0f);
	}
	else
		g_glUtil.Billboarding(m_f3DSoundPos[0], m_f3DSoundPos[1], m_f3DSoundPos[2], g_soundImg->GetId(), 1.0f, 1.0f);
	if (selectionMode)
		glPopName();
}

CChar* C3DSound::GetScriptStringVariable(CChar* variableName)
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

CBool C3DSound::GetScriptBoolVariable(CChar* variableName)
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

CInt C3DSound::GetScriptIntVariable(CChar* variableName)
{
	CInt value;
	lua_getglobal(m_lua, variableName);
	value = lua_tointeger(m_lua, -1);
	lua_pop(m_lua, 1);
	return value;
}

CDouble C3DSound::GetScriptDoubleVariable(CChar* variableName)
{
	CDouble value;
	lua_getglobal(m_lua, variableName);
	value = lua_tonumber(m_lua, -1);
	lua_pop(m_lua, 1);
	return value;
}

CVoid C3DSound::SetScriptStringVariable(CChar* variableName, CChar* value)
{
	lua_pushstring(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid C3DSound::SetScriptBoolVariable(CChar* variableName, CBool value)
{
	lua_pushboolean(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid C3DSound::SetScriptIntVariable(CChar* variableName, CInt value)
{
	lua_pushinteger(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid C3DSound::SetScriptDoubleVariable(CChar* variableName, CDouble value)
{
	lua_pushnumber(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid C3DSound::InitScript()
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = NULL;
		g_currentWater = NULL;
		g_currentLight = NULL;
		g_currentEngineCamera = NULL;
		g_currentVideo = NULL;
		g_current3DSound = this;
		g_currentAmbientSound = NULL;

		lua_getglobal(m_lua, "Init");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pcall(m_lua, 0, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

CVoid C3DSound::UpdateScript()
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = NULL;
		g_currentWater = NULL;
		g_currentLight = NULL;
		g_currentEngineCamera = NULL;
		g_currentVideo = NULL;
		g_current3DSound = this;
		g_currentAmbientSound = NULL;

		lua_getglobal(m_lua, "Update");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pcall(m_lua, 0, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

CVoid C3DSound::SetLastName(CChar* name)
{
	Cpy(m_lastName, name);
}

CChar* C3DSound::GetLastName()
{
	return m_lastName;
}
