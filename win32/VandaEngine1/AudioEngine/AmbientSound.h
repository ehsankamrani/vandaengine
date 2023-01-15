//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

#include "../common/utility.h"
#include "OpenALSoundSource.h"
#include "OpenALSoundBuffer.h"
#include "../ScriptEngine/luaforcpp.h"

class CAmbientSound
{
public:
	CAmbientSound();
	~CAmbientSound();

	CVoid SetName( CChar* name ) {Cpy( m_name, name ); }
	CVoid SetPath( CChar* path ) {Cpy( m_path, path ); }
	CVoid SetVolume( CFloat volume) { m_volume = volume; }
	CVoid SetPitch( CFloat pitch ) { m_pitch = pitch; }
	CVoid SetSoundSource( COpenALSoundSource* source ) { m_source = source; }
	CVoid SetSoundBuffer( COpenALSoundBuffer* buffer ) { m_buffer = buffer; }
	CVoid SetLoop(CBool loop) { m_loop = loop; }
	CVoid SetPlay(CBool play) { m_play = play; }
	CVoid SetSoundFileName(CChar* soundName) { Cpy(m_soundFileName, soundName); }

	COpenALSoundSource* GetSoundSource() { return m_source; }
	COpenALSoundBuffer* GetSoundBuffer() { return m_buffer; }

	CChar* GetName(){ return m_name; }
	CChar* GetPath(){ return m_path; }
	CFloat GetVolume() { return m_volume; }
	CFloat GetPitch() { return m_pitch; }
	CBool GetLoop() { return m_loop; }
	CBool GetPlay() { return m_play; }
	CChar* GetSoundFileName() { return m_soundFileName; }

	CVoid ResetLua();
	CBool LoadLuaFile();

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

	CChar m_name[MAX_NAME_SIZE];
	CChar m_path[MAX_NAME_SIZE];
	CFloat m_pitch;
	CFloat m_volume;
	CBool m_loop, m_play;
	CChar m_soundFileName[MAX_NAME_SIZE];

	COpenALSoundBuffer* m_buffer;
	COpenALSoundSource* m_source;

private:
	lua_State* m_lua;
	CBool m_hasScript;
	CChar m_script[MAX_URI_SIZE];
	CBool m_updateScript;
	CChar m_tempScriptPath[MAX_URI_SIZE];
	CChar m_tempCurrentScriptPath[MAX_URI_SIZE];
	CChar m_lastScriptPath[MAX_URI_SIZE];
};
