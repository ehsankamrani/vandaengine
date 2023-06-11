//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "MainCharacter.h"
#include "../GraphicsEngine/Scene.h"

CMainCharacter::CMainCharacter()
{
	//default character properties
	Cpy(m_name, "Default Character");
	Cpy(m_packageName, "Vanda_Basics");
	Cpy(m_prefabName, "Character");
	m_idleName.clear();
	m_idleName.push_back("idle");
	m_idleName.push_back("holding_idle");
	m_idleName.push_back("dwarf_idle");
	m_idleName.push_back("arm_stretching_idle");
	m_walkName.clear();
	m_walkName.push_back("walk");
	m_jumpName.clear();
	m_jumpName.push_back("jump");
	m_runName.clear();
	m_runName.push_back("run");
	m_instancePrefab = NULL;
	m_type = ePHYSX_CAMERA_THIRD_PERSON;
	m_position.x = m_position.y = m_position.z = 0.0f;
	m_scale = 0.01f;
	m_currentRotation = 0.0f;
	m_delayForRandomPlay = 8.0; //more idles will be played randomly every 8 seconds

	sprintf(m_walkSoundPath, "%s%s", g_pathProperties.m_soundPath, "walk.ogg");
	sprintf(m_runSoundPath, "%s%s", g_pathProperties.m_soundPath, "run.ogg");
	sprintf(m_jumpSoundPath, "%s%s", g_pathProperties.m_soundPath, "jump.ogg");

	m_walkSound = NULL;
	m_runSound = NULL;
	m_jumpSound = NULL;

	m_hasScript = CFalse;
	m_updateScript = CFalse;
	Cpy(m_script, "\n");
	Cpy(m_lastScriptPath, "\n");

	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
	m_updateEvent = CTrue;
}

CMainCharacter::~CMainCharacter()
{
	Destroy();
	LuaClose(m_lua);
}

CVoid CMainCharacter::ResetLua()
{
	LuaClose(m_lua);
	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
}

CBool CMainCharacter::LoadLuaFile()
{
	ResetLua();
	if (!LuaLoadFile(m_lua, m_script))
		return CFalse;
	return CTrue;
}

CVoid CMainCharacter::Destroy()
{
	if (m_walkSound)
		g_multipleView->m_soundSystem->StopALSound(*(m_walkSound->GetSoundSource()));
	if (m_runSound)
		g_multipleView->m_soundSystem->StopALSound(*(m_runSound->GetSoundSource()));
	if (m_jumpSound)
		g_multipleView->m_soundSystem->StopALSound(*(m_jumpSound->GetSoundSource()));

	CDelete(m_walkSound);
	CDelete(m_runSound);
	CDelete(m_jumpSound);

	CBool foundTarget = CFalse;
	if (!m_instancePrefab)
		return;
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
	for (CUInt k = 0; k < 3; k++)
	if (m_instancePrefab->GetScene(k))
	{
		CScene* scene = m_instancePrefab->GetScene(k);
		ex_pVandaEngineDlg->RemoveSelectedScene(scene->GetName(), scene->GetDocURI());
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

CVoid CMainCharacter::Reset()
{
	//default character properties
	Cpy(m_name, "Default Character");
	Cpy(m_packageName, "Vanda_Basics");
	Cpy(m_prefabName, "Character");
	m_idleName.clear();
	m_idleName.push_back("idle");
	m_idleName.push_back("holding_idle");
	m_idleName.push_back("dwarf_idle");
	m_idleName.push_back("arm_stretching_idle");
	m_walkName.clear();
	m_walkName.push_back("walk");
	m_jumpName.clear();
	m_jumpName.push_back("jump");
	m_runName.clear();
	m_runName.push_back("run");
	m_position.x = m_position.y = m_position.z = 0.0f;
	m_currentRotation = 0.0f;
	m_scale = 0.01f;
}

CVoid CMainCharacter::SetName(CChar* name)
{
	Cpy(m_name, name);
}

CVoid CMainCharacter::SetCameraType(CPhysXCameraType type)
{
	m_type = type;
}

CVoid CMainCharacter::SetPosition(CVec3f pos)
{
	m_position = pos;
}

CVoid CMainCharacter::SetCurrentRotation(CFloat rot)
{
	m_currentRotation = rot;
}

CVoid CMainCharacter::SetScale(CFloat scale)
{
	m_scale = scale;
}
CVoid CMainCharacter::SetPackageName(CChar* name)
{
	Cpy(m_packageName, name);
}

CVoid CMainCharacter::SetPrefabName(CChar* name)
{
	Cpy(m_prefabName, name);
}

CVoid CMainCharacter::SetIdleName(std::vector<std::string> name)
{
	m_idleName.clear();
	m_idleName = name;
}

CVoid CMainCharacter::SetWalkName(std::vector<std::string> name)
{
	m_walkName.clear();
	m_walkName = name;
}

CVoid CMainCharacter::SetRunName(std::vector<std::string> name)
{
	m_runName.clear();
	m_runName = name;
}

CVoid CMainCharacter::SetJumpName(std::vector<std::string> name)
{
	m_jumpName.clear();
	m_jumpName = name;
}

CVoid CMainCharacter::SetIdleDelayForRandomPlay(CFloat delay)
{
	m_delayForRandomPlay = delay;
}

CFloat CMainCharacter::GetIdleDelayForRandomPlay()
{
	return m_delayForRandomPlay;
}
CChar* CMainCharacter::GetName()
{
	return m_name;
}

CPhysXCameraType CMainCharacter::GetCameraType()
{
	return m_type;
}

CFloat CMainCharacter::GetScale()
{
	return m_scale;
}

CVec3f CMainCharacter::GetPosition()
{
	return m_position;
}

CFloat CMainCharacter::GetCurrentRotation()
{
	return m_currentRotation;
}

std::vector<std::string> CMainCharacter::GetIdleName()
{
	return m_idleName;
}

std::vector<std::string> CMainCharacter::GetWalkName()
{
	return m_walkName;
}

std::vector<std::string> CMainCharacter::GetRunName()
{
	return m_runName;
}

std::vector<std::string> CMainCharacter::GetJumpName()
{
	return m_jumpName;
}

CChar* CMainCharacter::GetPackageName()
{
	return m_packageName;
}

CChar* CMainCharacter::GetPrefabName()
{
	return m_prefabName;
}

CVoid CMainCharacter::SetInstancePrefab(CInstancePrefab* instancePrefab)
{
	m_instancePrefab = instancePrefab;
}

CInstancePrefab* CMainCharacter::GetInstancePrefab()
{
	return m_instancePrefab;
}

CVoid CMainCharacter::SetWalkSound()
{
	if (!m_walkSound)
		m_walkSound = CNew(CAmbientSound);
	else if (m_walkSound)
	{
		CDelete(m_walkSound);
		m_walkSound = CNew(CAmbientSound);
	}

	COpenALSoundSource* m_soundSource = CNew(COpenALSoundSource);
	COpenALSoundBuffer* m_soundBuffer = CNew(COpenALSoundBuffer);

	if (!m_soundBuffer->LoadOggVorbisFromFile(m_walkSoundPath))
		return;
	m_soundSource->BindSoundBuffer(*(m_soundBuffer));

	m_soundSource->SetLooping(true);
	m_soundSource->SetPitch(1.0f);
	m_soundSource->SetVolume(1.0f);

	m_walkSound->SetSoundSource(m_soundSource);
	m_walkSound->SetSoundBuffer(m_soundBuffer);
	m_walkSound->SetName("walk");
	m_walkSound->SetPath(m_walkSoundPath);
	m_walkSound->SetVolume(1.0f);
	m_walkSound->SetPitch(1.0f);
}

CVoid CMainCharacter::SetRunSound()
{
	if (!m_runSound)
		m_runSound = CNew(CAmbientSound);
	else if (m_runSound)
	{
		CDelete(m_runSound);
		m_runSound = CNew(CAmbientSound);
	}

	COpenALSoundSource* m_soundSource = CNew(COpenALSoundSource);
	COpenALSoundBuffer* m_soundBuffer = CNew(COpenALSoundBuffer);

	if (!m_soundBuffer->LoadOggVorbisFromFile(m_runSoundPath))
		return;
	m_soundSource->BindSoundBuffer(*(m_soundBuffer));

	m_soundSource->SetLooping(true);
	m_soundSource->SetPitch(1.0f);
	m_soundSource->SetVolume(1.0f);

	m_runSound->SetSoundSource(m_soundSource);
	m_runSound->SetSoundBuffer(m_soundBuffer);
	m_runSound->SetName("run");
	m_runSound->SetPath(m_runSoundPath);
	m_runSound->SetVolume(1.0f);
	m_runSound->SetPitch(1.0f);
}

CVoid CMainCharacter::SetJumpSound()
{
	if (!m_jumpSound)
		m_jumpSound = CNew(CAmbientSound);
	else if (m_jumpSound)
	{
		CDelete(m_jumpSound);
		m_jumpSound = CNew(CAmbientSound);
	}
	COpenALSoundSource* m_soundSource = CNew(COpenALSoundSource);
	COpenALSoundBuffer* m_soundBuffer = CNew(COpenALSoundBuffer);

	if (!m_soundBuffer->LoadOggVorbisFromFile(m_jumpSoundPath))
		return;
	m_soundSource->BindSoundBuffer(*(m_soundBuffer));

	m_soundSource->SetLooping(false);
	m_soundSource->SetPitch(1.0f);
	m_soundSource->SetVolume(1.0f);

	m_jumpSound->SetSoundSource(m_soundSource);
	m_jumpSound->SetSoundBuffer(m_soundBuffer);
	m_jumpSound->SetName("jump");
	m_jumpSound->SetPath(m_jumpSoundPath);
	m_jumpSound->SetVolume(1.0f);
	m_jumpSound->SetPitch(1.0f);
}

CVoid CMainCharacter::InitScript()
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = NULL;
		g_currentWater = NULL;
		g_currentLight = NULL;
		g_currentEngineCamera = NULL;
		g_currentVideo = NULL;
		g_current3DSound = NULL;
		g_currentAmbientSound = NULL;

		lua_getglobal(m_lua, "Init");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pcall(m_lua, 0, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

CVoid CMainCharacter::UpdateScript()
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = NULL;
		g_currentWater = NULL;
		g_currentLight = NULL;
		g_currentEngineCamera = NULL;
		g_currentVideo = NULL;
		g_current3DSound = NULL;
		g_currentAmbientSound = NULL;

		lua_getglobal(m_lua, "Update");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pcall(m_lua, 0, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

CVoid CMainCharacter::OnTriggerEnterScript(CChar *otherActorName)
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = NULL;
		g_currentWater = NULL;
		g_currentLight = NULL;
		g_currentEngineCamera = NULL;
		g_currentVideo = NULL;
		g_current3DSound = NULL;
		g_currentAmbientSound = NULL;

		lua_getglobal(m_lua, "OnTriggerEnter");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pushstring(m_lua, otherActorName);
			lua_pcall(m_lua, 1, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

CVoid CMainCharacter::OnTriggerStayScript(CChar *otherActorName)
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = NULL;
		g_currentWater = NULL;
		g_currentLight = NULL;
		g_currentEngineCamera = NULL;
		g_currentVideo = NULL;
		g_current3DSound = NULL;
		g_currentAmbientSound = NULL;

		lua_getglobal(m_lua, "OnTriggerStay");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pushstring(m_lua, otherActorName);
			lua_pcall(m_lua, 1, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

CVoid CMainCharacter::OnTriggerExitScript(CChar *otherActorName)
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = NULL;
		g_currentWater = NULL;
		g_currentLight = NULL;
		g_currentEngineCamera = NULL;
		g_currentVideo = NULL;
		g_current3DSound = NULL;
		g_currentAmbientSound = NULL;

		lua_getglobal(m_lua, "OnTriggerExit");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pushstring(m_lua, otherActorName);
			lua_pcall(m_lua, 1, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

CChar* CMainCharacter::GetScriptStringVariable(CChar* variableName)
{
	CChar *s = NULL;
	lua_getglobal(m_lua, variableName);
	if (!lua_isnil(m_lua, -1))
		s = _strdup(lua_tostring(m_lua, -1));
	else
		s = _strdup("");

	lua_pop(m_lua, 1);
	return s;
}

CBool CMainCharacter::GetScriptBoolVariable(CChar* variableName)
{
	CInt value;
	CBool result;
	lua_getglobal(m_lua, variableName);
	value = lua_toboolean(m_lua, -1);
	if (value)
		result = CTrue;
	else
		result = CFalse;
	lua_pop(m_lua, 1);
	return result;
}

CInt CMainCharacter::GetScriptIntVariable(CChar* variableName)
{
	CInt value;
	lua_getglobal(m_lua, variableName);
	value = lua_tointeger(m_lua, -1);
	lua_pop(m_lua, 1);
	return value;
}

CDouble CMainCharacter::GetScriptDoubleVariable(CChar* variableName)
{
	CDouble value;
	lua_getglobal(m_lua, variableName);
	value = lua_tonumber(m_lua, -1);
	lua_pop(m_lua, 1);
	return value;
}

CVoid CMainCharacter::SetScriptStringVariable(CChar* variableName, CChar* value)
{
	lua_pushstring(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CMainCharacter::SetScriptBoolVariable(CChar* variableName, CBool value)
{
	lua_pushboolean(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CMainCharacter::SetScriptIntVariable(CChar* variableName, CInt value)
{
	lua_pushinteger(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CMainCharacter::SetScriptDoubleVariable(CChar* variableName, CDouble value)
{
	lua_pushnumber(m_lua, value);
	lua_setglobal(m_lua, variableName);
}