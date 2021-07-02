//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "../stdafx.h"
#include <windows.h>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

#pragma comment( lib, "lua5.1.lib")

class CLuaState
{
  lua_State *L;
public:
  CLuaState() : L(lua_open()) { }

  ~CLuaState() {
    lua_close(L);
  }

  // implicitly act as a lua_State pointer
  inline operator lua_State*() {
    return L;
  }
};

static lua_State* LuaNewState()
{
	return luaL_newstate();
}

static void LuaOpenLibs(lua_State *L)
{
	luaL_openlibs(L);
}

static void LuaClose(lua_State *L)
{
	lua_close(L);
}

static int LuaExecuteProgram(lua_State *L)
{
	// make a short function to make program behaviour more clear
	return lua_pcall(L, 0, LUA_MULTRET, 0);
}

static void LuaReportErrors(lua_State *L, const int status)
{
	if ( status!=0 ) {
		PrintScriptInfo( lua_tostring(L, -1), COLOR_RED );
		lua_pop(L, 1); // remove error message
	}
}

static void LuaReportErrors2(lua_State *L, const int status)
{
	if (status != 0) {
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "\n%s", lua_tostring(L, -1));

		PrintInfo(temp, COLOR_RED);
		lua_pop(L, 1); // remove error message
	}
}

static void LuaLoadAndExecute( lua_State* L, CChar* path )
{
	luaL_dofile( L, path );
}

static bool LuaLoadFile(lua_State* L, CChar* path)
{
	if (luaL_loadfile(L, path) || lua_pcall(L, 0, LUA_MULTRET, 0))
		return CFalse;
	else
		return CTrue;
}

static void LuaRegisterFunctions(lua_State* L)
{
	lua_register(L, "PlaySoundLoop", PlaySoundLoop);
	lua_register(L, "PlaySoundOnce", PlaySoundOnce);
	lua_register(L, "PauseSound", PauseSound);
	lua_register(L, "StopSound", StopSound);

	lua_register(L, "BlendCycle", BlendCycle);
	lua_register(L, "ClearCycle", ClearCycle);
	lua_register(L, "ExecuteAction", ExecuteAction);
	lua_register(L, "ReverseExecuteAction", ReverseExecuteAction);
	lua_register(L, "RemoveAction", RemoveAction);
	lua_register(L, "GetAnimationClipDuration", GetAnimationClipDuration);
	lua_register(L, "PauseAnimations", PauseAnimations);

	lua_register(L, "LoadVScene", LoadVScene);
	lua_register(L, "ExitGame", ExitGame);
	lua_register(L, "SetCurrentVSceneAsMenu", SetCurrentVSceneAsMenu);

	lua_register(L, "ActivateThirdPersonCamera", ActivateThirdPersonCamera);
	lua_register(L, "ActivateFirstPersonCamera", ActivateFirstPersonCamera);
	lua_register(L, "ActivateImportedCamera", ActivateImportedCamera);
	lua_register(L, "ActivateImportedCameraOfPrefabInstance", ActivateImportedCameraOfPrefabInstance);
	lua_register(L, "ActivateEngineCamera", ActivateEngineCamera);
	lua_register(L, "SetPhysicsCameraAngle", SetPhysicsCameraAngle);
	lua_register(L, "GetPhysicsCameraAngle", GetPhysicsCameraAngle);

	lua_register(L, "LoadResource", LoadResource);
	lua_register(L, "DeleteResource", DeleteResource);
	lua_register(L, "DeleteAllResources", DeleteAllResources);
	lua_register(L, "PlayResourceSoundLoop", PlayResourceSoundLoop);
	lua_register(L, "PlayResourceSoundOnce", PlayResourceSoundOnce);
	lua_register(L, "StopResourceSound", StopResourceSound);
	lua_register(L, "PauseResourceSound", PauseResourceSound);
	lua_register(L, "StopAllResourceSounds", StopAllResourceSounds);
	lua_register(L, "ShowCursorIcon", ShowCursorIcon);
	lua_register(L, "HideCursorIcon", HideCursorIcon);

	lua_register(L, "PrintConsole", PrintConsole);

	lua_register(L, "ShowGUI", ShowGUI);
	lua_register(L, "HideGUI", HideGUI);

	lua_register(L, "IsKeyDown", IsKeyDown);

	lua_register(L, "ShowPrefabInstance", ShowPrefabInstance);
	lua_register(L, "HidePrefabInstance", HidePrefabInstance);

	lua_register(L, "SetSelectionDistance", SetSelectionDistance);
	lua_register(L, "GetSelectionDistance", GetSelectionDistance);
	lua_register(L, "SelectPrefabInstances", SelectPrefabInstances);

	lua_register(L, "GetScreenWidth", GetScreenWidth);
	lua_register(L, "GetScreenHeight", GetScreenHeight);
	lua_register(L, "GetCursorX", GetCursorX);
	lua_register(L, "GetCursorY", GetCursorY);
	lua_register(L, "IsMenuEnabled", IsMenuEnabled);
	lua_register(L, "GetElapsedTime", GetElapsedTime);
	lua_register(L, "GetPrefabInstanceNameFromActor", GetPrefabInstanceNameFromActor);

	lua_register(L, "TranslatePrefabInstance", TranslatePrefabInstance);
	lua_register(L, "RotatePrefabInstance", RotatePrefabInstance);
	lua_register(L, "ScalePrefabInstance", ScalePrefabInstance);
	lua_register(L, "GetPrefabInstanceTranslate", GetPrefabInstanceTranslate);
	lua_register(L, "GetPrefabInstanceRotate", GetPrefabInstanceRotate);
	lua_register(L, "GetPrefabInstanceScale", GetPrefabInstanceScale);

	lua_register(L, "GetPrefabInstanceRadius", GetPrefabInstanceRadius);
	lua_register(L, "GetDistanceOfPrefabInstanceFromPhysicsCamera", GetDistanceOfPrefabInstanceFromPhysicsCamera);

	lua_register(L, "EnableDepthOfField", EnableDepthOfField);
	lua_register(L, "DisableDepthOfField", DisableDepthOfField);
	lua_register(L, "SetDepthOfFieldFocalDistance", SetDepthOfFieldFocalDistance);
	lua_register(L, "SetDepthOfFieldFocalRange", SetDepthOfFieldFocalRange);

	lua_register(L, "EnableFog", EnableFog);
	lua_register(L, "DisableFog", DisableFog);
	lua_register(L, "SetFogColor", SetFogColor);
	lua_register(L, "SetFogDensity", SetFogDensity);

	lua_register(L, "EnableBloom", EnableBloom);
	lua_register(L, "DisableBloom", DisableBloom);
	lua_register(L, "SetBloomColor", SetBloomColor);
	lua_register(L, "SetBloomIntensity", SetBloomIntensity);

	lua_register(L, "EnableDirectionalShadow", EnableDirectionalShadow);
	lua_register(L, "DisableDirectionalShadow", DisableDirectionalShadow);
	lua_register(L, "SetDirectionalShadowAlgorithm", SetDirectionalShadowAlgorithm);
	lua_register(L, "SetDirectionalShadowNumberOfSplits", SetDirectionalShadowNumberOfSplits);
	lua_register(L, "SetDirectionalShadowWeightOfSplits", SetDirectionalShadowWeightOfSplits);
	lua_register(L, "SetDirectionalShadowNearClipPlane", SetDirectionalShadowNearClipPlane);
	lua_register(L, "SetDirectionalShadowFarClipPlane", SetDirectionalShadowFarClipPlane);
	lua_register(L, "SetDirectionalShadowResolution", SetDirectionalShadowResolution);
	lua_register(L, "SetDirectionalShadowIntensity", SetDirectionalShadowIntensity);
	lua_register(L, "SetDirectionalShadowLight", SetDirectionalShadowLight);

	lua_register(L, "SetLightAmbient", SetLightAmbient);
	lua_register(L, "SetLightDiffuse", SetLightDiffuse);
	lua_register(L, "SetLightSpecular", SetLightSpecular);
	lua_register(L, "SetLightShininess", SetLightShininess);

	lua_register(L, "SetPrefabInstanceAmbient", SetPrefabInstanceAmbient);
	lua_register(L, "SetPrefabInstanceDiffuse", SetPrefabInstanceDiffuse);
	lua_register(L, "SetPrefabInstanceSpecular", SetPrefabInstanceSpecular);
	lua_register(L, "SetPrefabInstanceEmission", SetPrefabInstanceEmission);
	lua_register(L, "SetPrefabInstanceShininess", SetPrefabInstanceShininess);
	lua_register(L, "SetPrefabInstanceTransparency", SetPrefabInstanceTransparency);
	lua_register(L, "EnablePrefabInstanceMaterial", EnablePrefabInstanceMaterial);
	lua_register(L, "DisablePrefabInstanceMaterial", DisablePrefabInstanceMaterial);

}
