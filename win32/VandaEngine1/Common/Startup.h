#pragma once
#include "../Common/Utility.h"
#include "../Common/Defines.h"

class CStartUp
{
public:
	CStartUp();
	~CStartUp();
	CVoid ResetLua();
	CBool LoadLuaFile();
	CVoid SetName(CChar* name) { Cpy(m_name, name); }
	inline CChar* GetName() { return m_name; }
	CVoid SetScriptPath(CChar* path) { Cpy(m_scriptPath, path); }
	inline CChar* GetScriptPath() { return m_scriptPath; }
	inline CVoid SetUpdateScript(CBool state) { m_updateScript = state; }
	inline CBool GetUpdateScript() { return m_updateScript; }

	CVoid SetTempScriptPath(CChar* path) { Cpy(m_tempScriptPath, path); }
	CVoid SetTempCurrentScriptPath(CChar* path) { Cpy(m_tempCurrentScriptPath, path); }

	CChar* GetTempScriptPath() { return m_tempScriptPath; }
	CChar* GetTempCurrentScriptPath() { return m_tempCurrentScriptPath; }
	CVoid InitScript();
	CVoid UpdateScript();

private:
	CChar m_name[MAX_NAME_SIZE];
	CChar m_scriptPath[MAX_URI_SIZE];
	CChar m_tempScriptPath[MAX_NAME_SIZE];
	CChar m_tempCurrentScriptPath[MAX_NAME_SIZE];
	CBool m_updateScript;
	lua_State* m_lua;
};

