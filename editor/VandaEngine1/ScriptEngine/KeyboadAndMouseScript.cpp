#include "stdafx.h"
#include "KeyboadAndMouseScript.h"
#include "../ScriptEngine/LuaForCpp.h"

CKeyboadAndMouseScript::CKeyboadAndMouseScript()
{
	m_hasEscapeScript = CFalse;
	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
}


CKeyboadAndMouseScript::~CKeyboadAndMouseScript()
{
	LuaClose(m_lua);
}

CVoid CKeyboadAndMouseScript::ExecuteScript(CChar* path)
{
	LuaLoadAndExecute(m_lua, path);
}