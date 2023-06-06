//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "terrain.h"
#include "render.h"
#include "../VandaEngineEditorDlg.h"
CTerrain::CTerrain()
{
    m_nameIndex = 0;
	m_cookPhysicsTriangles = CTrue;
	m_terrainHeightmap = CNew(CHeightClass);
	m_terrainTexture = CNew(CTerrainTexture);
	m_terrain = CNew(CTerrainVBOCull);

	m_hasScript = CFalse;
	m_updateScript = CFalse;
	Cpy(m_script, "\n");
	Cpy(m_lastScriptPath, "\n");
	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
	m_updateEvent = CTrue;
}

CTerrain::~CTerrain()
{
	Destroy();
}

CVoid CTerrain::ResetLua()
{
	LuaClose(m_lua);
	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
}

CBool CTerrain::LoadLuaFile()
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

CInt CTerrain::Initialize()
{
	SetIndex();
	// Initialize the heightmap by creating a midpoint displacement heightmap.
	m_terrainHeightmap = CNew(CHeightClass);
	m_terrainHeightmap->createHeightmap(CHeightClass::Image, g_terrain->GetHeightMapPath());

	//// Initialize the texture data.
	m_terrainTexture = CNew(CTerrainTexture);
	m_terrainTexture->init(m_terrainHeightmap->getHeightData());

	//// Create our mesh from the heightmap.
	m_terrain = CNew(CTerrainVBOCull);
	m_terrain->init(m_terrainHeightmap->getHeightData());

	//// Create the lightmap.
	//m_terrainTexture->createLightmap(10.f, 10.f, 10.f);

	return 1;
}

CVoid CTerrain::Destroy()
{
	m_VSceneList.clear();
	CDelete(m_terrainHeightmap);
	CDelete(m_terrainTexture);
	CDelete(m_terrain);

	LuaClose(m_lua);
}


CChar* CTerrain::GetScriptStringVariable(CChar* variableName)
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

CBool CTerrain::GetScriptBoolVariable(CChar* variableName)
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

CInt CTerrain::GetScriptIntVariable(CChar* variableName)
{
	CInt value;
	lua_getglobal(m_lua, variableName);
	value = lua_tointeger(m_lua, -1);
	lua_pop(m_lua, 1);
	return value;
}

CDouble CTerrain::GetScriptDoubleVariable(CChar* variableName)
{
	CDouble value;
	lua_getglobal(m_lua, variableName);
	value = lua_tonumber(m_lua, -1);
	lua_pop(m_lua, 1);
	return value;
}

CVoid CTerrain::SetScriptStringVariable(CChar* variableName, CChar* value)
{
	lua_pushstring(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CTerrain::SetScriptBoolVariable(CChar* variableName, CBool value)
{
	lua_pushboolean(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CTerrain::SetScriptIntVariable(CChar* variableName, CInt value)
{
	lua_pushinteger(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CTerrain::SetScriptDoubleVariable(CChar* variableName, CDouble value)
{
	lua_pushnumber(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CTerrain::InitScript()
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = NULL;
		g_currentWater = NULL;
		g_currentLight = NULL;

		lua_getglobal(m_lua, "Init");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pcall(m_lua, 0, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

CVoid CTerrain::UpdateScript()
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = NULL;
		g_currentWater = NULL;
		g_currentLight = NULL;

		lua_getglobal(m_lua, "Update");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pcall(m_lua, 0, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}