//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "VSceneScript.h"
#include "../ScriptEngine/LuaForCpp.h"
#include "../VandaEngine1Win32.h"
CVSceneScript::CVSceneScript()
{
	m_updateScript = CTrue;
	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
}

CVSceneScript::~CVSceneScript()
{
	LuaClose(m_lua);
}

CVoid CVSceneScript::ResetLua()
{
	LuaClose(m_lua);
	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
}

CBool CVSceneScript::LoadLuaFile()
{
	//ResetLua();
	if (!LuaLoadFile(m_lua, m_scriptPath))
		return CFalse;
	return CTrue;
}

CVoid CVSceneScript::InitScript()
{
	g_currentInstancePrefab = NULL;

	lua_getglobal(m_lua, "Init");
	if (lua_isfunction(m_lua, -1))
	{
		lua_pcall(m_lua, 0, 0, 0);
	}

	lua_settop(m_lua, 0);
}

CVoid CVSceneScript::UpdateScript()
{
	g_currentInstancePrefab = NULL;

	lua_getglobal(m_lua, "Update");
	if (lua_isfunction(m_lua, -1))
	{
		lua_pcall(m_lua, 0, 0, 0);
	}

	lua_settop(m_lua, 0);
}

CChar* CVSceneScript::GetScriptStringVariable(CChar* variableName)
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

CBool CVSceneScript::GetScriptBoolVariable(CChar* variableName)
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

CInt CVSceneScript::GetScriptIntVariable(CChar* variableName)
{
	CInt value;
	lua_getglobal(m_lua, variableName);
	value = lua_tointeger(m_lua, -1);
	lua_pop(m_lua, 1);
	return value;
}

CDouble CVSceneScript::GetScriptDoubleVariable(CChar* variableName)
{
	CDouble value;
	lua_getglobal(m_lua, variableName);
	value = lua_tonumber(m_lua, -1);
	lua_pop(m_lua, 1);
	return value;
}

CVoid CVSceneScript::SetScriptStringVariable(CChar* variableName, CChar* value)
{
	lua_pushstring(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CVSceneScript::SetScriptBoolVariable(CChar* variableName, CBool value)
{
	lua_pushboolean(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CVSceneScript::SetScriptIntVariable(CChar* variableName, CInt value)
{
	lua_pushinteger(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CVSceneScript::SetScriptDoubleVariable(CChar* variableName, CDouble value)
{
	lua_pushnumber(m_lua, value);
	lua_setglobal(m_lua, variableName);
}