//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

class CInstancePrefab;

class CTrigger
{
public:
	CTrigger();
	~CTrigger();
	CVoid Destroy();
	CVoid SetTriggerType(CTriggerType);
	CVoid SetInstancePrefab(CInstancePrefab* instancePrefab);
	CVoid SetName(CChar* name);

	CTriggerType GetTriggerType();
	CInstancePrefab* GetInstancePrefab();
	CChar* GetName();
private:
	CTriggerType m_triggerType;
	CChar m_name[MAX_NAME_SIZE];
	CInstancePrefab* m_instancePrefab;
};