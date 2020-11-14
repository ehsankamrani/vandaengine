//Copyright (C) 2020 Ehsan Kamrani 
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

static void LuaOpenLibs(lua_State *L)
{
	luaL_openlibs(L);
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

