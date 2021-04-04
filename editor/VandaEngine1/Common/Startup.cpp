#include "stdafx.h"
#include "startup.h"
#include "../ScriptEngine/LuaForCpp.h"
#include "../VandaEngine1Dlg.h"
CStartUp::CStartUp()
{
	m_updateScript = CTrue;
	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
}

CStartUp::~CStartUp()
{
	LuaClose(m_lua);
}

CVoid CStartUp::ResetLua()
{
	LuaClose(m_lua);
	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
}

CBool CStartUp::LoadLuaFile()
{
	ResetLua();
	if (!LuaLoadFile(m_lua, m_scriptPath))
		return CFalse;
	return CTrue;
}

CVoid CStartUp::InitScript()
{
	g_currentInstancePrefab = NULL;

	lua_getglobal(m_lua, "Init");
	if (lua_isfunction(m_lua, -1))
	{
		lua_pcall(m_lua, 0, 0, 0);
	}

	lua_settop(m_lua, 0);
}

CVoid CStartUp::UpdateScript()
{
	g_currentInstancePrefab = NULL;

	lua_getglobal(m_lua, "Update");
	if (lua_isfunction(m_lua, -1))
	{
		lua_pcall(m_lua, 0, 0, 0);
	}

	lua_settop(m_lua, 0);
}