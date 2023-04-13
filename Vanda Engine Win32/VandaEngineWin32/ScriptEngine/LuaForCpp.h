//Copyright (C) 2023 Ehsan Kamrani 
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
		//PrintScriptInfo( lua_tostring(L, -1), COLOR_RED );
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

	lua_register(L, "ActivateThirdPersonCamera", ActivateThirdPersonCamera);
	lua_register(L, "ActivateFirstPersonCamera", ActivateFirstPersonCamera);
	lua_register(L, "ActivateImportedCamera", ActivateImportedCamera);
	lua_register(L, "ActivateImportedCameraOfPrefabInstance", ActivateImportedCameraOfPrefabInstance);
	lua_register(L, "ActivateEngineCamera", ActivateEngineCamera);
	lua_register(L, "SetPhysicsCameraAngle", SetPhysicsCameraAngle);
	lua_register(L, "GetPhysicsCameraAngle", GetPhysicsCameraAngle);
	lua_register(L, "SetPhysicsCameraTilt", SetPhysicsCameraTilt);
	lua_register(L, "SetPhysicsCameraMaxTilt", SetPhysicsCameraMaxTilt);
	lua_register(L, "SetPhysicsCameraMinTilt", SetPhysicsCameraMinTilt);
	lua_register(L, "GetPhysicsCameraTilt", GetPhysicsCameraTilt);
	lua_register(L, "GetPhysicsCameraMaxTilt", GetPhysicsCameraMaxTilt);
	lua_register(L, "GetPhysicsCameraMinTilt", GetPhysicsCameraMinTilt);
	lua_register(L, "SetPhysicsCameraYaw", SetPhysicsCameraYaw);
	lua_register(L, "GetPhysicsCameraYaw", GetPhysicsCameraYaw);

	lua_register(L, "LoadResource", LoadResource);
	lua_register(L, "DeleteResource", DeleteResource);
	lua_register(L, "DeleteAllResources", DeleteAllResources);
	lua_register(L, "PlayResourceSoundLoop", PlayResourceSoundLoop);
	lua_register(L, "PlayResourceSoundOnce", PlayResourceSoundOnce);
	lua_register(L, "StopResourceSound", StopResourceSound);
	lua_register(L, "PauseResourceSound", PauseResourceSound);
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
	lua_register(L, "GetElapsedTime", GetElapsedTime);
	lua_register(L, "IsCharacterControllerLocked", IsCharacterControllerLocked);
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

	lua_register(L, "SetPhysicsDefaultRestitution", SetPhysicsDefaultRestitution);
	lua_register(L, "SetPhysicsDefaultSkinWidth", SetPhysicsDefaultSkinWidth);
	lua_register(L, "SetPhysicsDefaultStaticFriction", SetPhysicsDefaultStaticFriction);
	lua_register(L, "SetPhysicsDefaultDynamicFriction", SetPhysicsDefaultDynamicFriction);
	lua_register(L, "EnablePhysicsGravity", EnablePhysicsGravity);
	lua_register(L, "DisablePhysicsGravity", DisablePhysicsGravity);
	lua_register(L, "SetPhysicsGravity", SetPhysicsGravity);
	lua_register(L, "EnablePhysicsGroundPlane", EnablePhysicsGroundPlane);
	lua_register(L, "DisablePhysicsGroundPlane", DisablePhysicsGroundPlane);
	lua_register(L, "SetPhysicGroundHeight", SetPhysicGroundHeight);
	lua_register(L, "SetDistanceBetweenPhysicsCameraAndCharacterController", SetDistanceBetweenPhysicsCameraAndCharacterController);
	lua_register(L, "SetCharacterControllerCapsuleRadius", SetCharacterControllerCapsuleRadius);
	lua_register(L, "SetCharacterControllerCapsuleHeight", SetCharacterControllerCapsuleHeight);
	lua_register(L, "SetCharacterControllerForcePower", SetCharacterControllerForcePower);
	lua_register(L, "SetCharacterControllerWalkSpeed", SetCharacterControllerWalkSpeed);
	lua_register(L, "SetCharacterControllerRunSpeed", SetCharacterControllerRunSpeed);
	lua_register(L, "SetCharacterControllerSkinWidth", SetCharacterControllerSkinWidth);
	lua_register(L, "SetCharacterControllerStepOffset", SetCharacterControllerStepOffset);
	lua_register(L, "SetCharacterControllerSlopeLimit", SetCharacterControllerSlopeLimit);
	lua_register(L, "SetCharacterControllerJumpPower", SetCharacterControllerJumpPower);
	lua_register(L, "EnableCharacterControllerJump", EnableCharacterControllerJump);
	lua_register(L, "DisableCharacterControllerJump", DisableCharacterControllerJump);
	lua_register(L, "EnablePhysicsDebugMode", EnablePhysicsDebugMode);
	lua_register(L, "DisablePhysicsDebugMode", DisablePhysicsDebugMode);
	lua_register(L, "SetCharacterControllerPosition", SetCharacterControllerPosition);
	lua_register(L, "GetCharacterControllerPosition", GetCharacterControllerPosition);

	lua_register(L, "SetMaxMultisampling", SetMaxMultisampling);
	lua_register(L, "SetMaxAnisotropicFiltering", SetMaxAnisotropicFiltering);
	lua_register(L, "EnableVSync", EnableVSync);
	lua_register(L, "DisableVSync", DisableVSync);
	lua_register(L, "EnableWaterReflection", EnableWaterReflection);
	lua_register(L, "DisableWaterReflection", DisableWaterReflection);
	lua_register(L, "SetScreenResolution", SetScreenResolution);
	lua_register(L, "SaveGeneralProperties", SaveGeneralProperties);
	lua_register(L, "GetMaxMultisampling", GetMaxMultisampling);
	lua_register(L, "GetMaxAnisotropicFiltering", GetMaxAnisotropicFiltering);
	lua_register(L, "IsVSyncEnabled", IsVSyncEnabled);
	lua_register(L, "IsWaterReflectionEnabled", IsWaterReflectionEnabled);
	lua_register(L, "GetScreenResolution", GetScreenResolution);

	lua_register(L, "GetVSceneScriptStringVariable", GetVSceneScriptStringVariable);
	lua_register(L, "GetVSceneScriptBoolVariable", GetVSceneScriptBoolVariable);
	lua_register(L, "GetVSceneScriptIntVariable", GetVSceneScriptIntVariable);
	lua_register(L, "GetVSceneScriptDoubleVariable", GetVSceneScriptDoubleVariable);
	lua_register(L, "SetVSceneScriptStringVariable", SetVSceneScriptStringVariable);
	lua_register(L, "SetVSceneScriptBoolVariable", SetVSceneScriptBoolVariable);
	lua_register(L, "SetVSceneScriptIntVariable", SetVSceneScriptIntVariable);
	lua_register(L, "SetVSceneScriptDoubleVariable", SetVSceneScriptDoubleVariable);

	lua_register(L, "GetSkyScriptStringVariable", GetSkyScriptStringVariable);
	lua_register(L, "GetSkyScriptBoolVariable", GetSkyScriptBoolVariable);
	lua_register(L, "GetSkyScriptIntVariable", GetSkyScriptIntVariable);
	lua_register(L, "GetSkyScriptDoubleVariable", GetSkyScriptDoubleVariable);
	lua_register(L, "SetSkyScriptStringVariable", SetSkyScriptStringVariable);
	lua_register(L, "SetSkyScriptBoolVariable", SetSkyScriptBoolVariable);
	lua_register(L, "SetSkyScriptIntVariable", SetSkyScriptIntVariable);
	lua_register(L, "SetSkyScriptDoubleVariable", SetSkyScriptDoubleVariable);

	lua_register(L, "GetTerrainScriptStringVariable", GetTerrainScriptStringVariable);
	lua_register(L, "GetTerrainScriptBoolVariable", GetTerrainScriptBoolVariable);
	lua_register(L, "GetTerrainScriptIntVariable", GetTerrainScriptIntVariable);
	lua_register(L, "GetTerrainScriptDoubleVariable", GetTerrainScriptDoubleVariable);
	lua_register(L, "SetTerrainScriptStringVariable", SetTerrainScriptStringVariable);
	lua_register(L, "SetTerrainScriptBoolVariable", SetTerrainScriptBoolVariable);
	lua_register(L, "SetTerrainScriptIntVariable", SetTerrainScriptIntVariable);
	lua_register(L, "SetTerrainScriptDoubleVariable", SetTerrainScriptDoubleVariable);

	lua_register(L, "GetPrefabInstanceScriptStringVariable", GetPrefabInstanceScriptStringVariable);
	lua_register(L, "GetPrefabInstanceScriptBoolVariable", GetPrefabInstanceScriptBoolVariable);
	lua_register(L, "GetPrefabInstanceScriptIntVariable", GetPrefabInstanceScriptIntVariable);
	lua_register(L, "GetPrefabInstanceScriptDoubleVariable", GetPrefabInstanceScriptDoubleVariable);
	lua_register(L, "SetPrefabInstanceScriptStringVariable", SetPrefabInstanceScriptStringVariable);
	lua_register(L, "SetPrefabInstanceScriptBoolVariable", SetPrefabInstanceScriptBoolVariable);
	lua_register(L, "SetPrefabInstanceScriptIntVariable", SetPrefabInstanceScriptIntVariable);
	lua_register(L, "SetPrefabInstanceScriptDoubleVariable", SetPrefabInstanceScriptDoubleVariable);

	lua_register(L, "GetGUIButtonScriptStringVariable", GetGUIButtonScriptStringVariable);
	lua_register(L, "GetGUIButtonScriptBoolVariable", GetGUIButtonScriptBoolVariable);
	lua_register(L, "GetGUIButtonScriptIntVariable", GetGUIButtonScriptIntVariable);
	lua_register(L, "GetGUIButtonScriptDoubleVariable", GetGUIButtonScriptDoubleVariable);
	lua_register(L, "SetGUIButtonScriptStringVariable", SetGUIButtonScriptStringVariable);
	lua_register(L, "SetGUIButtonScriptBoolVariable", SetGUIButtonScriptBoolVariable);
	lua_register(L, "SetGUIButtonScriptIntVariable", SetGUIButtonScriptIntVariable);
	lua_register(L, "SetGUIButtonScriptDoubleVariable", SetGUIButtonScriptDoubleVariable);

	lua_register(L, "GetTriggerScriptStringVariable", GetTriggerScriptStringVariable);
	lua_register(L, "GetTriggerScriptBoolVariable", GetTriggerScriptBoolVariable);
	lua_register(L, "GetTriggerScriptIntVariable", GetTriggerScriptIntVariable);
	lua_register(L, "GetTriggerScriptDoubleVariable", GetTriggerScriptDoubleVariable);
	lua_register(L, "SetTriggerScriptStringVariable", SetTriggerScriptStringVariable);
	lua_register(L, "SetTriggerScriptBoolVariable", SetTriggerScriptBoolVariable);
	lua_register(L, "SetTriggerScriptIntVariable", SetTriggerScriptIntVariable);
	lua_register(L, "SetTriggerScriptDoubleVariable", SetTriggerScriptDoubleVariable);

	lua_register(L, "GetWaterScriptStringVariable", GetWaterScriptStringVariable);
	lua_register(L, "GetWaterScriptBoolVariable", GetWaterScriptBoolVariable);
	lua_register(L, "GetWaterScriptIntVariable", GetWaterScriptIntVariable);
	lua_register(L, "GetWaterScriptDoubleVariable", GetWaterScriptDoubleVariable);
	lua_register(L, "SetWaterScriptStringVariable", SetWaterScriptStringVariable);
	lua_register(L, "SetWaterScriptBoolVariable", SetWaterScriptBoolVariable);
	lua_register(L, "SetWaterScriptIntVariable", SetWaterScriptIntVariable);
	lua_register(L, "SetWaterScriptDoubleVariable", SetWaterScriptDoubleVariable);

	lua_register(L, "GetVideoScriptStringVariable", GetVideoScriptStringVariable);
	lua_register(L, "GetVideoScriptBoolVariable", GetVideoScriptBoolVariable);
	lua_register(L, "GetVideoScriptIntVariable", GetVideoScriptIntVariable);
	lua_register(L, "GetVideoScriptDoubleVariable", GetVideoScriptDoubleVariable);
	lua_register(L, "SetVideoScriptStringVariable", SetVideoScriptStringVariable);
	lua_register(L, "SetVideoScriptBoolVariable", SetVideoScriptBoolVariable);
	lua_register(L, "SetVideoScriptIntVariable", SetVideoScriptIntVariable);
	lua_register(L, "SetVideoScriptDoubleVariable", SetVideoScriptDoubleVariable);

	lua_register(L, "GetAmbientSoundScriptStringVariable", GetAmbientSoundScriptStringVariable);
	lua_register(L, "GetAmbientSoundScriptBoolVariable", GetAmbientSoundScriptBoolVariable);
	lua_register(L, "GetAmbientSoundScriptIntVariable", GetAmbientSoundScriptIntVariable);
	lua_register(L, "GetAmbientSoundScriptDoubleVariable", GetAmbientSoundScriptDoubleVariable);
	lua_register(L, "SetAmbientSoundScriptStringVariable", SetAmbientSoundScriptStringVariable);
	lua_register(L, "SetAmbientSoundScriptBoolVariable", SetAmbientSoundScriptBoolVariable);
	lua_register(L, "SetAmbientSoundScriptIntVariable", SetAmbientSoundScriptIntVariable);
	lua_register(L, "SetAmbientSoundScriptDoubleVariable", SetAmbientSoundScriptDoubleVariable);

	lua_register(L, "Get3DSoundScriptStringVariable", Get3DSoundScriptStringVariable);
	lua_register(L, "Get3DSoundScriptBoolVariable", Get3DSoundScriptBoolVariable);
	lua_register(L, "Get3DSoundScriptIntVariable", Get3DSoundScriptIntVariable);
	lua_register(L, "Get3DSoundScriptDoubleVariable", Get3DSoundScriptDoubleVariable);
	lua_register(L, "Set3DSoundScriptStringVariable", Set3DSoundScriptStringVariable);
	lua_register(L, "Set3DSoundScriptBoolVariable", Set3DSoundScriptBoolVariable);
	lua_register(L, "Set3DSoundScriptIntVariable", Set3DSoundScriptIntVariable);
	lua_register(L, "Set3DSoundScriptDoubleVariable", Set3DSoundScriptDoubleVariable);

	lua_register(L, "GetLightScriptStringVariable", GetLightScriptStringVariable);
	lua_register(L, "GetLightScriptBoolVariable", GetLightScriptBoolVariable);
	lua_register(L, "GetLightScriptIntVariable", GetLightScriptIntVariable);
	lua_register(L, "GetLightScriptDoubleVariable", GetLightScriptDoubleVariable);
	lua_register(L, "SetLightScriptStringVariable", SetLightScriptStringVariable);
	lua_register(L, "SetLightScriptBoolVariable", SetLightScriptBoolVariable);
	lua_register(L, "SetLightScriptIntVariable", SetLightScriptIntVariable);
	lua_register(L, "SetLightScriptDoubleVariable", SetLightScriptDoubleVariable);

	lua_register(L, "GetCameraScriptStringVariable", GetCameraScriptStringVariable);
	lua_register(L, "GetCameraScriptBoolVariable", GetCameraScriptBoolVariable);
	lua_register(L, "GetCameraScriptIntVariable", GetCameraScriptIntVariable);
	lua_register(L, "GetCameraScriptDoubleVariable", GetCameraScriptDoubleVariable);
	lua_register(L, "SetCameraScriptStringVariable", SetCameraScriptStringVariable);
	lua_register(L, "SetCameraScriptBoolVariable", SetCameraScriptBoolVariable);
	lua_register(L, "SetCameraScriptIntVariable", SetCameraScriptIntVariable);
	lua_register(L, "SetCameraScriptDoubleVariable", SetCameraScriptDoubleVariable);

	lua_register(L, "GetMainCharacterScriptStringVariable", GetMainCharacterScriptStringVariable);
	lua_register(L, "GetMainCharacterScriptBoolVariable", GetMainCharacterScriptBoolVariable);
	lua_register(L, "GetMainCharacterScriptIntVariable", GetMainCharacterScriptIntVariable);
	lua_register(L, "GetMainCharacterScriptDoubleVariable", GetMainCharacterScriptDoubleVariable);
	lua_register(L, "SetMainCharacterScriptStringVariable", SetMainCharacterScriptStringVariable);
	lua_register(L, "SetMainCharacterScriptBoolVariable", SetMainCharacterScriptBoolVariable);
	lua_register(L, "SetMainCharacterScriptIntVariable", SetMainCharacterScriptIntVariable);
	lua_register(L, "SetMainCharacterScriptDoubleVariable", SetMainCharacterScriptDoubleVariable);

	lua_register(L, "ShowGUIButton", ShowGUIButton);
	lua_register(L, "HideGUIButton", HideGUIButton);
	lua_register(L, "ShowGUIImage", ShowGUIImage);
	lua_register(L, "HideGUIImage", HideGUIImage);
	lua_register(L, "ShowGUIText", ShowGUIText);
	lua_register(L, "HideGUIText", HideGUIText);
	lua_register(L, "ScaleGUIButton", ScaleGUIButton);
	lua_register(L, "ScaleGUIImage", ScaleGUIImage);

	lua_register(L, "SetGUIButtonPosition", SetGUIButtonPosition);
	lua_register(L, "SetGUIImagePosition", SetGUIImagePosition);
	lua_register(L, "SetGUITextPosition", SetGUITextPosition);
	lua_register(L, "GetGUIButtonPosition", GetGUIButtonPosition);
	lua_register(L, "GetGUIImagePosition", GetGUIImagePosition);
	lua_register(L, "GetGUITextPosition", GetGUITextPosition);

	lua_register(L, "SetGUIPosition", SetGUIPosition);
	lua_register(L, "GetGUIPosition", GetGUIPosition);

	lua_register(L, "AddForceToCharacterController", AddForceToCharacterController);
	lua_register(L, "AddForceToPrefabInstance", AddForceToPrefabInstance);
	lua_register(L, "AddTorqueToPrefabInstance", AddTorqueToPrefabInstance);

	lua_register(L, "GetPhysicsActorGroup", GetPhysicsActorGroup);
	lua_register(L, "SetPhysicsCollisionFlags", SetPhysicsCollisionFlags);

	lua_register(L, "GeneratePrefabInstance", GeneratePrefabInstance);
	lua_register(L, "DeletePrefabInstance", DeletePrefabInstance);

	lua_register(L, "AttachPrefabInstanceToWater", AttachPrefabInstanceToWater);
	lua_register(L, "DetachPrefabInstanceFromWater", DetachPrefabInstanceFromWater);

	lua_register(L, "SetSoundVolume", SetSoundVolume);
	lua_register(L, "SetSoundPitch", SetSoundPitch);
	lua_register(L, "SetSoundPlay", SetSoundPlay);
	lua_register(L, "SetSoundLoop", SetSoundLoop);
	lua_register(L, "SetSoundPosition", SetSoundPosition);
	lua_register(L, "SetSoundRollOff", SetSoundRollOff);
	lua_register(L, "SetSoundReferenceDistance", SetSoundReferenceDistance);
	lua_register(L, "SetSoundMaxDistance", SetSoundMaxDistance);

	lua_register(L, "GetSoundVolume", GetSoundVolume);
	lua_register(L, "GetSoundPitch", GetSoundPitch);
	lua_register(L, "GetSoundPlay", GetSoundPlay);
	lua_register(L, "GetSoundLoop", GetSoundLoop);
	lua_register(L, "GetSoundPosition", GetSoundPosition);
	lua_register(L, "GetSoundRollOff", GetSoundRollOff);
	lua_register(L, "GetSoundReferenceDistance", GetSoundReferenceDistance);
	lua_register(L, "GetSoundMaxDistance", GetSoundMaxDistance);

	lua_register(L, "SetGlobalSoundVolume", SetGlobalSoundVolume);
	lua_register(L, "GetGlobalSoundVolume", GetGlobalSoundVolume);

	lua_register(L, "PlayVideo", PlayVideo);
	lua_register(L, "PlayVideoLoop", PlayVideoLoop);
	lua_register(L, "PlayVideoOnce", PlayVideoOnce);
	lua_register(L, "StopVideo", StopVideo);

	lua_register(L, "SetVideoLoop", SetVideoLoop);
	lua_register(L, "SetVideoVolume", SetVideoVolume);

	lua_register(L, "GetVideoPlay", GetVideoPlay);
	lua_register(L, "GetVideoLoop", GetVideoLoop);
	lua_register(L, "GetVideoVolume", GetVideoVolume);
	lua_register(L, "GetVideoDuration", GetVideoDuration);


	//Stop Sounds
	lua_register(L, "StopAllSounds", StopAllSounds);
	lua_register(L, "StopAllAmbientSounds", StopAllAmbientSounds);
	lua_register(L, "StopAll3DSounds", StopAll3DSounds);
	lua_register(L, "StopAllResourceSounds", StopAllResourceSounds);
	//Play Sounds
	lua_register(L, "PlayAllSounds", PlayAllSounds);
	lua_register(L, "PlayAllPausedSounds", PlayAllPausedSounds);
	lua_register(L, "PlayAllStoppedSounds", PlayAllStoppedSounds);
	lua_register(L, "PlayAllAmbientSounds", PlayAllAmbientSounds);
	lua_register(L, "PlayAll3DSounds", PlayAll3DSounds);
	lua_register(L, "PlayAllResourceSounds", PlayAllResourceSounds);
	lua_register(L, "PlayAllStoppedAmbientSounds", PlayAllStoppedAmbientSounds);
	lua_register(L, "PlayAllStopped3DSounds", PlayAllStopped3DSounds);
	lua_register(L, "PlayAllStoppedResourceSounds", PlayAllStoppedResourceSounds);
	lua_register(L, "PlayAllPausedAmbientSounds", PlayAllPausedAmbientSounds);
	lua_register(L, "PlayAllPaused3DSounds", PlayAllPaused3DSounds);
	lua_register(L, "PlayAllPausedResourceSounds", PlayAllPausedResourceSounds);
	//Play Sounds loop
	lua_register(L, "PlayAllSoundsLoop", PlayAllSoundsLoop);
	lua_register(L, "PlayAllPausedSoundsLoop", PlayAllPausedSoundsLoop);
	lua_register(L, "PlayAllStoppedSoundsLoop", PlayAllStoppedSoundsLoop);
	lua_register(L, "PlayAllAmbientSoundsLoop", PlayAllAmbientSoundsLoop);
	lua_register(L, "PlayAll3DSoundsLoop", PlayAll3DSoundsLoop);
	lua_register(L, "PlayAllResourceSoundsLoop", PlayAllResourceSoundsLoop);
	lua_register(L, "PlayAllStoppedAmbientSoundsLoop", PlayAllStoppedAmbientSoundsLoop);
	lua_register(L, "PlayAllStopped3DSoundsLoop", PlayAllStopped3DSoundsLoop);
	lua_register(L, "PlayAllStoppedResourceSoundsLoop", PlayAllStoppedResourceSoundsLoop);
	lua_register(L, "PlayAllPausedAmbientSoundsLoop", PlayAllPausedAmbientSoundsLoop);
	lua_register(L, "PlayAllPaused3DSoundsLoop", PlayAllPaused3DSoundsLoop);
	lua_register(L, "PlayAllPausedResourceSoundsLoop", PlayAllPausedResourceSoundsLoop);
	//Play Sounds once
	lua_register(L, "PlayAllSoundsOnce", PlayAllSoundsOnce);
	lua_register(L, "PlayAllPausedSoundsOnce", PlayAllPausedSoundsOnce);
	lua_register(L, "PlayAllStoppedSoundsOnce", PlayAllStoppedSoundsOnce);
	lua_register(L, "PlayAllAmbientSoundsOnce", PlayAllAmbientSoundsOnce);
	lua_register(L, "PlayAll3DSoundsOnce", PlayAll3DSoundsOnce);
	lua_register(L, "PlayAllResourceSoundsOnce", PlayAllResourceSoundsOnce);
	lua_register(L, "PlayAllStoppedAmbientSoundsOnce", PlayAllStoppedAmbientSoundsOnce);
	lua_register(L, "PlayAllStopped3DSoundsOnce", PlayAllStopped3DSoundsOnce);
	lua_register(L, "PlayAllStoppedResourceSoundsOnce", PlayAllStoppedResourceSoundsOnce);
	lua_register(L, "PlayAllPausedAmbientSoundsOnce", PlayAllPausedAmbientSoundsOnce);
	lua_register(L, "PlayAllPaused3DSoundsOnce", PlayAllPaused3DSoundsOnce);
	lua_register(L, "PlayAllPausedResourceSoundsOnce", PlayAllPausedResourceSoundsOnce);
	//Pause Sounds
	lua_register(L, "PauseAllSounds", PauseAllSounds);
	lua_register(L, "PauseAllAmbientSounds", PauseAllAmbientSounds);
	lua_register(L, "PauseAll3DSounds", PauseAll3DSounds);
	lua_register(L, "PauseAllResourceSounds", PauseAllResourceSounds);

	//Pause game 
	lua_register(L, "PauseGame", PauseGame);
	lua_register(L, "PauseAllAnimationsOfPrefabInstances", PauseAllAnimationsOfPrefabInstances);
	lua_register(L, "PauseMainCharacterAnimations", PauseMainCharacterAnimations);
	lua_register(L, "PausePhysics", PausePhysics);
	lua_register(L, "PauseAllWaters", PauseAllWaters);

	//resume game
	lua_register(L, "ResumeGame", ResumeGame);
	lua_register(L, "ResumeAllAnimationsOfPrefabInstances", ResumeAllAnimationsOfPrefabInstances);
	lua_register(L, "ResumeMainCharacterAnimations", ResumeMainCharacterAnimations);
	lua_register(L, "ResumePhysics", ResumePhysics);
	lua_register(L, "ResumeAllWaters", ResumeAllWaters);

	//lock/unlock character
	lua_register(L, "LockCharacterController", LockCharacterController);
	lua_register(L, "UnlockCharacterController", UnlockCharacterController);

	//menu cursor
	lua_register(L, "ShowMenuCursor", ShowMenuCursor);
	lua_register(L, "HideMenuCursor", HideMenuCursor);
	lua_register(L, "SetMenuCursorSize", SetMenuCursorSize);
	lua_register(L, "GetMenuCursorSize", GetMenuCursorSize);

}
