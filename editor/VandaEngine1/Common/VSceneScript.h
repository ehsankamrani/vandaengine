#pragma once
#include "Utility.h"
#include "Defines.h"

class CVSceneScript
{
public:
	CVSceneScript();
	~CVSceneScript();
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

	//functions to get and set script variables
	CChar* GetScriptStringVariable(CChar* variableName);
	CBool GetScriptBoolVariable(CChar* variableName);
	CInt GetScriptIntVariable(CChar* variableName);
	CDouble GetScriptDoubleVariable(CChar* variableName);
	CVoid SetScriptStringVariable(CChar* variableName, CChar* value);
	CVoid SetScriptBoolVariable(CChar* variableName, CBool value);
	CVoid SetScriptIntVariable(CChar* variableName, CInt value);
	CVoid SetScriptDoubleVariable(CChar* variableName, CDouble value);

private:
	CChar m_name[MAX_NAME_SIZE];
	CChar m_scriptPath[MAX_URI_SIZE];
	CChar m_tempScriptPath[MAX_NAME_SIZE];
	CChar m_tempCurrentScriptPath[MAX_NAME_SIZE];
	CBool m_updateScript;
	lua_State* m_lua;
};

