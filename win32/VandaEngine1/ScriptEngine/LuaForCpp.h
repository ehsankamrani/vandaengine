//Copyright (C) 2022 Ehsan Kamrani 
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
	lua_register(L, "SetCurrentVSceneAsMenu", SetCurrentVSceneAsMenu);

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
	lua_register(L, "GetElapsedTime", GetElapsedTime);
	lua_register(L, "IsMenuEnabled", IsMenuEnabled);
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

}
