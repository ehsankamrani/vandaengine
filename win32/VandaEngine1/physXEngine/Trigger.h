//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "../Common/Defines.h"
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

	CTriggerType GetTriggerType();
	CInstancePrefab* GetInstancePrefab();
	CChar* GetName();

	CVoid OnTriggerEnterScript(CChar *otherActorName);
	CVoid OnTriggerStayScript(CChar *otherActorName);
	CVoid OnTriggerExitScript(CChar *otherActorName);

	CVoid SetHasScript(CBool set) { m_hasScript = set; }
	CBool GetHasScript() { return m_hasScript; }
	CVoid SetScript(CChar* script) { Cpy(m_script, script); }
	CChar* GetScript() { return m_script; }
	CVoid SetUpdateScript(CBool set) { m_updateScript = set; }
	CBool GetUpdateScript() { return m_updateScript; }
	CVoid SetTempScriptPath(CChar* path) { Cpy(m_tempScriptPath, path); }
	CVoid SetTempCurrentScriptPath(CChar* path) { Cpy(m_tempCurrentScriptPath, path); }

	CChar* GetTempScriptPath() { return m_tempScriptPath; }
	CChar* GetTempCurrentScriptPath() { return m_tempCurrentScriptPath; }

private:
	CTriggerType m_triggerType;
	CChar m_name[MAX_NAME_SIZE];
	CInstancePrefab* m_instancePrefab;
	CBool m_hasScript;
	CChar m_script[MAX_NAME_SIZE];
	CBool m_updateScript;
	CChar m_tempScriptPath[MAX_NAME_SIZE];
	CChar m_tempCurrentScriptPath[MAX_NAME_SIZE];
	lua_State* m_lua;
};