#pragma once
#include "..\common\utility.h"
class CKeyboadAndMouseScript
{
public:
	CKeyboadAndMouseScript();
	~CKeyboadAndMouseScript();

	CBool GetHasEscapeScript() { return m_hasEscapeScript; }
	CVoid SetHasEscapeScript(CBool set) { m_hasEscapeScript = set; }
	CVoid SetEscapeScriptFile(CChar* fileName) 
	{
		Cpy(m_escapeScriptFile, fileName); 
		m_hasEscapeScript = CTrue;
	}
	CChar* GetEscapeScriptFile()
	{
		if (m_hasEscapeScript)
			return m_escapeScriptFile;
		else
			return NULL;
	}
	CVoid ExecuteScript(CChar* path);
private:
	CChar m_escapeScriptFile[MAX_NAME_SIZE];
	CBool m_hasEscapeScript;
	lua_State* m_lua;
};

