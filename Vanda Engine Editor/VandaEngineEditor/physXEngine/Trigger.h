//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "Defines.h"
#include "../common/utility.h"
class CInstancePrefab;

class CTrigger
{
public:
	CTrigger();
	~CTrigger();
	CVoid Destroy();
	CVoid ResetLua();
	CBool LoadLuaFile();
	CVoid SetTriggerType(CTriggerType);
	CVoid SetInstancePrefab(CInstancePrefab* instancePrefab);
	CVoid SetName(CChar* name);
	CChar* GetName();

	CVoid SetLastName(CChar* name);
	CChar* GetLastName();

	CTriggerType GetTriggerType();
	CInstancePrefab* GetInstancePrefab();
	CVoid OnTriggerEnterScript(CChar *otherActorName);
	CVoid OnTriggerStayScript(CChar *otherActorName);
	CVoid OnTriggerExitScript(CChar *otherActorName);

	CVoid SetHasScript(CBool set) { m_hasScript = set; }
	CBool GetHasScript() { return m_hasScript; }
	CVoid SetScript(CChar* script) { Cpy(m_script, script); }
	CChar* GetScript() { return m_script; }
	CVoid SetLastScriptPath(CChar* script) { Cpy(m_lastScriptPath, script); }
	CChar* GetLastScriptPath() { return m_lastScriptPath; }

	CVoid SetUpdateScript(CBool set) { m_updateScript = set; }
	CBool GetUpdateScript() { return m_updateScript; }

	CVoid SetTempScriptPath(CChar* path) { Cpy(m_tempScriptPath, path); }
	CVoid SetTempCurrentScriptPath(CChar* path) { Cpy(m_tempCurrentScriptPath, path); }

	CChar* GetTempScriptPath() { return m_tempScriptPath; }
	CChar* GetTempCurrentScriptPath() { return m_tempCurrentScriptPath; }

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
	CTriggerType m_triggerType;
	CChar m_name[MAX_NAME_SIZE];
	CChar m_lastName[MAX_NAME_SIZE];
	CInstancePrefab* m_instancePrefab;
	CBool m_hasScript;
	CChar m_script[MAX_URI_SIZE];
	CBool m_updateScript;
	CChar m_tempScriptPath[MAX_URI_SIZE];
	CChar m_tempCurrentScriptPath[MAX_URI_SIZE];
	CChar m_lastScriptPath[MAX_URI_SIZE];
	lua_State* m_lua;
};