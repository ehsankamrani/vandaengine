//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

class CInstancePrefab;

#include <string>
#include <map>
#include <vector>
#include "../Common/Utility.h"
#include "..\\AudioEngine\\AmbientSound.h"
class CMainCharacter
{
public:
	CMainCharacter();
	~CMainCharacter();
	CVoid Destroy();
	CVoid Reset();
	CVoid ResetLua();
	CBool LoadLuaFile();
	CVoid SetInstancePrefab(CInstancePrefab* instancePrefab);
	CVoid SetName(CChar* name);
	CVoid SetPackageName(CChar* name);
	CVoid SetPrefabName(CChar* name);
	CVoid SetCameraType(CPhysXCameraType type);
	CVoid SetPosition(CVec3f pos);
	CVoid SetScale(CFloat scale);
	CVoid SetCurrentRotation(CFloat rotation);

	CVoid SetIdleName(std::vector<std::string> name);
	CVoid SetWalkName(std::vector<std::string> name);
	CVoid SetRunName(std::vector<std::string> name);
	CVoid SetJumpName(std::vector<std::string> name);
	CVoid SetIdleDelayForRandomPlay(CFloat delay);

	CVoid SetRunSoundPath(CChar* path) { Cpy(m_runSoundPath, path); }
	CVoid SetWalkSoundPath(CChar* path) { Cpy(m_walkSoundPath, path); }
	CVoid SetJumpSoundPath(CChar* path) { Cpy(m_jumpSoundPath, path); }

	CInstancePrefab* GetInstancePrefab();

	CFloat GetIdleDelayForRandomPlay();
	CChar* GetName();
	CChar* GetPackageName();
	CChar* GetPrefabName();
	CFloat GetScale();
	CVec3f GetPosition();
	CFloat GetCurrentRotation();
	CChar* GetSoundRunPath() { return m_runSoundPath; }
	CChar* GetSoundWalkPath() { return m_walkSoundPath; }
	CChar* GetSoundJumpPath() { return m_jumpSoundPath; }


	CPhysXCameraType GetCameraType();
	std::vector<std::string> GetIdleName();
	std::vector<std::string> GetWalkName();
	std::vector<std::string> GetRunName();
	std::vector<std::string> GetJumpName();
	CFloat m_delayForRandomPlay;

	CAmbientSound* m_walkSound;
	CAmbientSound* m_runSound;
	CAmbientSound* m_jumpSound;

	CVoid SetWalkSound();
	CVoid SetRunSound();
	CVoid SetJumpSound();

	CVoid InitScript();
	CVoid UpdateScript();
	CVoid OnTriggerEnterScript(CChar *otherActorName);
	CVoid OnTriggerStayScript(CChar *otherActorName);
	CVoid OnTriggerExitScript(CChar *otherActorName);

	CVoid SetHasScript(CBool set) { m_hasScript = set; }
	CBool GetHasScript() { return m_hasScript; }
	CVoid SetScriptPath(CChar* script) { Cpy(m_script, script); }
	CChar* GetScriptPath() { return m_script; }
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

	std::vector<std::map<std::string, CBool>> m_VSceneList; //List of all VScenes created via the editor, save functions

	inline CVoid AddVSceneToList(std::string vSceneName, CBool save) //save functions
	{
		std::map<std::string, CBool> tempVScene;
		tempVScene[vSceneName] = save;
		m_VSceneList.push_back(tempVScene);
	}
	inline CBool IsInVSceneList(std::string vSceneName, CBool content, CBool reverseTheContent) //save functions
	{
		for (CUInt i = 0; i < m_VSceneList.size(); i++)
		{
			if (m_VSceneList[i].begin()->first == vSceneName)
			{
				if (m_VSceneList[i].begin()->second == content) //found the target
				{
					if (reverseTheContent)
						m_VSceneList[i].begin()->second = !content;
					return CTrue;
				}
				else
					return CFalse;
			}
		}
		if (reverseTheContent)
			AddVSceneToList(vSceneName, !content);
		else
			AddVSceneToList(vSceneName, content);
		return CTrue;
	}
	CVoid SetUpdateEvent(CBool set) { m_updateEvent = set; }
	CBool GetUpdateEvent() { return m_updateEvent; }

private:
	CChar m_name[MAX_NAME_SIZE];
	CChar m_packageName[MAX_NAME_SIZE];
	CChar m_prefabName[MAX_NAME_SIZE];
	std::vector<std::string> m_idleName;
	std::vector<std::string> m_walkName;
	std::vector<std::string> m_jumpName;
	std::vector<std::string> m_runName;

	CChar m_runSoundPath[MAX_URI_SIZE];
	CChar m_walkSoundPath[MAX_URI_SIZE];
	CChar m_jumpSoundPath[MAX_URI_SIZE];

	CInstancePrefab* m_instancePrefab;
	CPhysXCameraType m_type;
	CVec3f m_position;
	CFloat m_scale;
	CFloat m_currentRotation;

	CBool m_hasScript;
	CChar m_script[MAX_URI_SIZE];
	CBool m_updateScript;
	CChar m_tempScriptPath[MAX_URI_SIZE];
	CChar m_tempCurrentScriptPath[MAX_URI_SIZE];
	CChar m_lastScriptPath[MAX_URI_SIZE];
	lua_State* m_lua;
	CBool m_updateEvent;
};