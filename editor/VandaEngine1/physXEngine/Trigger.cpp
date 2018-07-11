//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "Trigger.h"
#include "../GraphicsEngine/Scene.h"

CTrigger::CTrigger()
{
}

CTrigger::~CTrigger()
{
	Destroy();
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

	if (g_selectedName == m_instancePrefab->GetNameIndex())
	{
		g_selectedName = -1;
		g_lastEngineObjectSelectedName = -1;
		g_showArrow = CFalse;
		SetDialogData3(CFalse);
	}
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
		ex_pVandaEngine1Dlg->RemoveSelectedScene(scene->GetName(), scene->GetDocURI());
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
				CChar prefabName[MAX_NAME_SIZE];
				sprintf(prefabName, "%s%s%s", "\nPrefab ' ", dstPrefab->GetName(), " ' removed from memory");
				PrintInfo(prefabName, COLOR_YELLOW);

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


