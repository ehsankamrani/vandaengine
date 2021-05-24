//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "Trigger.h"
#include "../GraphicsEngine/Scene.h"
#include "../Main.h"
CTrigger::CTrigger()
{
	m_hasScript = CFalse;
	m_updateScript = CFalse;
	Cpy(m_script, "\n");
	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
}

CTrigger::~CTrigger()
{
	Destroy();
	LuaClose(m_lua);
}

CVoid CTrigger::ResetLua()
{
	LuaClose(m_lua);
	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
}

CVoid CTrigger::Destroy()
{
	CBool foundTarget = CFalse;
	for (CUInt i = 0; i < g_instancePrefab.size(); i++)
	{
		if (Cmp(g_instancePrefab[i]->GetName(), m_instancePrefab->GetName()))
		{
			foundTarget = CTrue;
			break;
		}
	}
	if (!foundTarget)
		return;

	CPrefab* dstPrefab = NULL;
	dstPrefab = m_instancePrefab->GetPrefab();
	//remove instance from prefab
	for (CUInt j = 0; j < dstPrefab->GetNumInstances(); j++)
	{
		CBool foundTarget = CFalse;
		if (Cmp(dstPrefab->GetInstance(j)->GetName(), m_instancePrefab->GetName()))
		{
			dstPrefab->RemoveInstance(j);
			foundTarget = CTrue;
		}
		if (foundTarget)
			break;
	}
	if (m_instancePrefab->GetScene(0))
	{
		CScene* scene = m_instancePrefab->GetScene(0);
		g_main->RemoveSelectedScene(scene->GetName(), scene->GetDocURI());

	}

	for (CUInt i = 0; i < g_instancePrefab.size(); i++)
	{
		if (Cmp(g_instancePrefab[i]->GetName(), m_instancePrefab->GetName()))
		{
			g_instancePrefab.erase(g_instancePrefab.begin() + i);
			break;
		}
	}
	CDelete(m_instancePrefab);

	if (dstPrefab->GetNumInstances() == 0)
	{
		//now remove the prefab
		for (CUInt k = 0; k < g_prefab.size(); k++)
		{
			if (Cmp(dstPrefab->GetName(), g_prefab[k]->GetName()))
			{
				CDelete(g_prefab[k]);
				g_prefab.erase(g_prefab.begin() + k);
				break;
			}
		}
	}
}

CVoid CTrigger::SetName(CChar* name)
{
	Cpy(m_name, name);
}

CChar* CTrigger::GetName()
{
	return m_name;
}

CVoid CTrigger::SetTriggerType(CTriggerType triggerType)
{
	m_triggerType = triggerType;
}

CVoid CTrigger::SetInstancePrefab(CInstancePrefab* instancePrefab)
{
	m_instancePrefab = instancePrefab;
}

CTriggerType CTrigger::GetTriggerType()
{
	return m_triggerType;
}

CInstancePrefab* CTrigger::GetInstancePrefab()
{
	return m_instancePrefab;
}

CBool CTrigger::LoadLuaFile()
{
	//ResetLua();
	if (!LuaLoadFile(m_lua, m_script))
		return CFalse;
	return CTrue;
}

CVoid CTrigger::OnTriggerEnterScript()
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = NULL;

		lua_getglobal(m_lua, "OnTriggerEnter");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pcall(m_lua, 0, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

CVoid CTrigger::OnTriggerStayScript()
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = NULL;

		lua_getglobal(m_lua, "OnTriggerStay");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pcall(m_lua, 0, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

CVoid CTrigger::OnTriggerExitScript()
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = NULL;

		lua_getglobal(m_lua, "OnTriggerExit");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pcall(m_lua, 0, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}
