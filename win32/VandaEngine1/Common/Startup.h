#pragma once
#include "Utility.h"
#include "Defines.h"

class CStartUp
{
public:
	CStartUp();
	~CStartUp();
	CVoid SetName(CChar* name) { Cpy(m_name, name); }
	inline CChar* GetName() { return m_name; }
	CVoid SetScriptPath(CChar* path) { Cpy(m_scriptPath, path); }
	inline CChar* GetScriptPath() { return m_scriptPath; }
	inline CVoid SetUpdateScript(CBool state) { m_updateScript = state; }
	inline CBool GetUpdateScript() { return m_updateScript; }

private:
	CChar m_name[MAX_NAME_SIZE];
	CChar m_scriptPath[MAX_URI_SIZE];
	CBool m_updateScript;
};

