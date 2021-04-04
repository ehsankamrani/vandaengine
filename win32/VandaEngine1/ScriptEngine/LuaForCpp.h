//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include <windows.h>

extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

#pragma comment( lib, "lua5.1.lib")

class CLuaState
{
  lua_State *L;
public:
  CLuaState() : L(lua_open()) { }

  ~CLuaState() {
    lua_close(L);
  }

  // implicitly act as a lua_State pointer
  inline operator lua_State*() {
    return L;
  }
};

static lua_State* LuaNewState()
{
	return luaL_newstate();
}

static void LuaOpenLibs(lua_State *L)
{
	luaL_openlibs(L);
}

static void LuaClose(lua_State *L)
{
	lua_close(L);
}

static int LuaExecuteProgram(lua_State *L)
{
	// make a short function to make program behaviour more clear
	return lua_pcall(L, 0, LUA_MULTRET, 0);
}

static void LuaReportErrors(lua_State *L, const int status)
{
	if ( status!=0 ) {
		//PrintScriptInfo( lua_tostring(L, -1), COLOR_RED );
		lua_pop(L, 1); // remove error message
	}
}

static void LuaLoadAndExecute( lua_State* L, CChar* path )
{
	luaL_dofile( L, path );
}

static bool LuaLoadFile(lua_State* L, CChar* path)
{
	if (luaL_loadfile(L, path) || lua_pcall(L, 0, LUA_MULTRET, 0))
		return CFalse;
	else
		return CTrue;
}

static void LuaRegisterFunctions(lua_State* L)
{
	lua_register(L, "PlaySoundLoop", PlaySoundLoop);
	lua_register(L, "PlaySoundOnce", PlaySoundOnce);
	lua_register(L, "PauseSound", PauseSound);
	lua_register(L, "StopSound", StopSound);

	lua_register(L, "BlendCycle", BlendCycle);
	lua_register(L, "ClearCycle", ClearCycle);
	lua_register(L, "ExecuteAction", ExecuteAction);
	lua_register(L, "ReverseExecuteAction", ReverseExecuteAction);
	lua_register(L, "RemoveAction", RemoveAction);
	lua_register(L, "GetAnimationClipDuration", GetAnimationClipDuration);
	lua_register(L, "PauseAnimations", PauseAnimations);

	lua_register(L, "LoadVScene", LoadVScene);
	lua_register(L, "ExitGame", ExitGame);
	lua_register(L, "SetCurrentVSceneAsMenu", SetCurrentVSceneAsMenu);

	lua_register(L, "ActivateThirdPersonCamera", ActivateThirdPersonCamera);
	lua_register(L, "ActivateFirstPersonCamera", ActivateFirstPersonCamera);
	lua_register(L, "ActivateImportedCamera", ActivateImportedCamera);
	lua_register(L, "ActivateImportedCameraOfPrefab", ActivateImportedCameraOfPrefab);
	lua_register(L, "ActivateEngineCamera", ActivateEngineCamera);

	lua_register(L, "LoadResource", LoadResource);
	lua_register(L, "DeleteAllResources", DeleteAllResources);
	lua_register(L, "PlayResourceSoundLoop", PlayResourceSoundLoop);
	lua_register(L, "PlayResourceSoundOnce", PlayResourceSoundOnce);
	lua_register(L, "StopResourceSound", StopResourceSound);
	lua_register(L, "PauseResourceSound", PauseResourceSound);
	lua_register(L, "StopAllResourceSounds", StopAllResourceSounds);
	lua_register(L, "ShowCursorIcon", ShowCursorIcon);
	lua_register(L, "HideCursorIcon", HideCursorIcon);
	lua_register(L, "AttachScriptToKey", AttachScriptToKey);
	lua_register(L, "PrintConsole", PrintConsole);

	lua_register(L, "ShowGUI", ShowGUI);
	lua_register(L, "HideGUI", HideGUI);

	lua_register(L, "SetPrefabInstanceVisible", SetPrefabInstanceVisible);
	lua_register(L, "SetPrefabInstanceInvisible", SetPrefabInstanceInvisible);
}
