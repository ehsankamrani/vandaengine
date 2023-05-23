//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define NOMINMAX
// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <fstream>
#include <stdio.h>
#include <atlstr.h>
#include <string>
#include "common\\defines.h"
using namespace std;

#pragma comment(lib, "legacy_stdio_definitions.lib")

#ifdef __cplusplus
FILE iob[] = { *stdin, *stdout, *stderr };
extern "C" {
	FILE * __cdecl _iob(void) { return iob; }
}
#endif

extern CUInt g_nameIndex;  
extern CUInt g_nodeIndex;
extern CInt g_selectedName; //holds the name of the selected object
extern CInt g_numVerts;
// TODO: reference additional headers your program requires here
struct lua_State;
class CGeometry;

CGeometry *GetGeometryFromScenes(const CChar * name, const CChar * DocURI);

//Sounds
CInt PlaySoundLoop(lua_State *L);
CInt PlaySoundOnce(lua_State *L);
CInt StopSound(lua_State *L);
CInt PauseSound(lua_State *L);

//Prefab Animations
CInt ExecuteCyclicAnimation(lua_State *L);
CInt RemoveCyclicAnimation(lua_State *L);
CInt ExecuteNonCyclicAnimation(lua_State *L);
CInt ReverseExecuteNonCyclicAnimation(lua_State *L);
CInt RemoveNonCyclicAnimation(lua_State *L);
CInt PausePrefabInstanceAnimations(lua_State* L);
CInt ResumePrefabInstanceAnimations(lua_State* L);
CInt GetAnimationClipDurationOfPrefabInstance(lua_State *L);

//Prefabs
CInt ShowPrefabInstance(lua_State *L);
CInt HidePrefabInstance(lua_State *L);

//VScene
CInt LoadVScene(lua_State *L);
CInt ExitGame(lua_State *L);

//Cameras
CInt ActivateImportedCamera(lua_State *L);
CInt ActivateImportedCameraOfPrefabInstance(lua_State *L);
CInt ActivateEngineCamera(lua_State *L);
CInt ActivateThirdPersonCamera(lua_State *L);
CInt ActivateFirstPersonCamera(lua_State *L);
CInt SetPhysicsCameraAngle(lua_State *L);
CInt GetPhysicsCameraAngle(lua_State *L);
CInt SetPhysicsCameraTilt(lua_State *L);
CInt SetPhysicsCameraMaxTilt(lua_State *L);
CInt SetPhysicsCameraMinTilt(lua_State *L);
CInt GetPhysicsCameraTilt(lua_State *L);
CInt GetPhysicsCameraMaxTilt(lua_State *L);
CInt GetPhysicsCameraMinTilt(lua_State *L);
CInt SetPhysicsCameraYaw(lua_State *L);
CInt GetPhysicsCameraYaw(lua_State *L);

//Resources
CInt LoadResource(lua_State *L);
CInt DeleteResource(lua_State *L);
CInt DeleteAllResources(lua_State *L);
CInt PlayResourceSoundLoop(lua_State *L);
CInt PlayResourceSoundOnce(lua_State *L);
CInt StopResourceSound(lua_State *L);
CInt PauseResourceSound(lua_State *L);
CInt ShowCursorIcon(lua_State *L);
CInt HideCursorIcon(lua_State *L);
CInt PrintConsole(lua_State *L);
//GUIs
CInt ShowGUI(lua_State *L);
CInt HideGUI(lua_State *L);

CInt IsKeyDown(lua_State* L);

//Selection
CInt SetSelectionDistance(lua_State *L);
CInt GetSelectionDistance(lua_State *L);
CInt SelectPrefabInstances(lua_State* L);

//Get
CInt GetScreenWidth(lua_State* L);
CInt GetScreenHeight(lua_State* L);
CInt GetCursorX(lua_State* L);
CInt GetCursorY(lua_State* L);
CInt GetElapsedTime(lua_State* L);
CInt IsCharacterControllerLocked(lua_State* L);
CInt GetPrefabInstanceNameFromActor(lua_State* L);

//translation, rotation and scaling of prefab instances
CInt TranslatePrefabInstance(lua_State* L);
CInt RotatePrefabInstance(lua_State* L);
CInt ScalePrefabInstance(lua_State* L);
CInt GetPrefabInstanceTranslate(lua_State* L);
CInt GetPrefabInstanceRotate(lua_State* L);
CInt GetPrefabInstanceScale(lua_State* L);

CInt GetPrefabInstanceRadius(lua_State* L);
CInt GetDistanceOfPrefabInstanceFromPhysicsCamera(lua_State* L);

CInt EnableDepthOfField(lua_State* L);
CInt DisableDepthOfField(lua_State* L);
CInt SetDepthOfFieldFocalDistance(lua_State* L);
CInt SetDepthOfFieldFocalRange(lua_State* L);

CInt EnableFog(lua_State* L);
CInt DisableFog(lua_State* L);
CInt SetFogColor(lua_State* L);
CInt SetFogDensity(lua_State* L);

CInt EnableBloom(lua_State* L);
CInt DisableBloom(lua_State* L);
CInt SetBloomColor(lua_State* L);
CInt SetBloomIntensity(lua_State* L);

CInt EnableDirectionalShadow(lua_State* L);
CInt DisableDirectionalShadow(lua_State* L);
CInt SetDirectionalShadowAlgorithm(lua_State* L);
CInt SetDirectionalShadowNumberOfSplits(lua_State* L);
CInt SetDirectionalShadowWeightOfSplits(lua_State* L);
CInt SetDirectionalShadowNearClipPlane(lua_State* L);
CInt SetDirectionalShadowFarClipPlane(lua_State* L);
CInt SetDirectionalShadowResolution(lua_State* L);
CInt SetDirectionalShadowIntensity(lua_State* L);
CInt SetDirectionalShadowLight(lua_State* L);

CInt SetLightAmbient(lua_State* L);
CInt SetLightDiffuse(lua_State* L);
CInt SetLightSpecular(lua_State* L);
CInt SetLightShininess(lua_State* L);

CInt SetPrefabInstanceAmbient(lua_State* L);
CInt SetPrefabInstanceDiffuse(lua_State* L);
CInt SetPrefabInstanceSpecular(lua_State* L);
CInt SetPrefabInstanceEmission(lua_State* L);
CInt SetPrefabInstanceShininess(lua_State* L);
CInt SetPrefabInstanceTransparency(lua_State* L);
CInt EnablePrefabInstanceMaterial(lua_State* L);
CInt DisablePrefabInstanceMaterial(lua_State* L);

CInt SetPhysicsDefaultRestitution(lua_State* L);
CInt SetPhysicsDefaultSkinWidth(lua_State* L);
CInt SetPhysicsDefaultStaticFriction(lua_State* L);
CInt SetPhysicsDefaultDynamicFriction(lua_State* L);
CInt EnablePhysicsGravity(lua_State* L);
CInt DisablePhysicsGravity(lua_State* L);
CInt SetPhysicsGravity(lua_State* L);
CInt EnablePhysicsGroundPlane(lua_State* L);
CInt DisablePhysicsGroundPlane(lua_State* L);
CInt SetPhysicGroundHeight(lua_State* L);
CInt SetDistanceBetweenPhysicsCameraAndCharacterController(lua_State* L);
CInt SetCharacterControllerCapsuleRadius(lua_State* L);
CInt SetCharacterControllerCapsuleHeight(lua_State* L);
CInt SetCharacterControllerForcePower(lua_State* L);
CInt SetCharacterControllerWalkSpeed(lua_State* L);
CInt SetCharacterControllerRunSpeed(lua_State* L);
CInt SetCharacterControllerSkinWidth(lua_State* L);
CInt SetCharacterControllerStepOffset(lua_State* L);
CInt SetCharacterControllerSlopeLimit(lua_State* L);
CInt SetCharacterControllerJumpPower(lua_State* L);
CInt EnableCharacterControllerJump(lua_State* L);
CInt DisableCharacterControllerJump(lua_State* L);
CInt EnablePhysicsDebugMode(lua_State* L);
CInt DisablePhysicsDebugMode(lua_State* L);
CInt SetCharacterControllerPosition(lua_State* L);
CInt GetCharacterControllerPosition(lua_State* L);

CInt SetMaxMultisampling(lua_State* L);
CInt SetMaxAnisotropicFiltering(lua_State* L);
CInt EnableVSync(lua_State* L);
CInt DisableVSync(lua_State* L);
CInt EnableWaterReflection(lua_State* L);
CInt DisableWaterReflection(lua_State* L);
CInt SetScreenResolution(lua_State* L);
CInt SaveGeneralProperties(lua_State* L);
CInt GetMaxMultisampling(lua_State* L);
CInt GetMaxAnisotropicFiltering(lua_State* L);
CInt IsVSyncEnabled(lua_State* L);
CInt IsWaterReflectionEnabled(lua_State* L);
CInt GetScreenResolution(lua_State* L);

CInt GetVSceneScriptStringVariable(lua_State* L);
CInt GetVSceneScriptBoolVariable(lua_State* L);
CInt GetVSceneScriptIntVariable(lua_State* L);
CInt GetVSceneScriptDoubleVariable(lua_State* L);
CInt SetVSceneScriptStringVariable(lua_State* L);
CInt SetVSceneScriptBoolVariable(lua_State* L);
CInt SetVSceneScriptIntVariable(lua_State* L);
CInt SetVSceneScriptDoubleVariable(lua_State* L);

CInt GetSkyScriptStringVariable(lua_State* L);
CInt GetSkyScriptBoolVariable(lua_State* L);
CInt GetSkyScriptIntVariable(lua_State* L);
CInt GetSkyScriptDoubleVariable(lua_State* L);
CInt SetSkyScriptStringVariable(lua_State* L);
CInt SetSkyScriptBoolVariable(lua_State* L);
CInt SetSkyScriptIntVariable(lua_State* L);
CInt SetSkyScriptDoubleVariable(lua_State* L);

CInt GetTerrainScriptStringVariable(lua_State* L);
CInt GetTerrainScriptBoolVariable(lua_State* L);
CInt GetTerrainScriptIntVariable(lua_State* L);
CInt GetTerrainScriptDoubleVariable(lua_State* L);
CInt SetTerrainScriptStringVariable(lua_State* L);
CInt SetTerrainScriptBoolVariable(lua_State* L);
CInt SetTerrainScriptIntVariable(lua_State* L);
CInt SetTerrainScriptDoubleVariable(lua_State* L);

CInt GetPrefabInstanceScriptStringVariable(lua_State* L);
CInt GetPrefabInstanceScriptBoolVariable(lua_State* L);
CInt GetPrefabInstanceScriptIntVariable(lua_State* L);
CInt GetPrefabInstanceScriptDoubleVariable(lua_State* L);
CInt SetPrefabInstanceScriptStringVariable(lua_State* L);
CInt SetPrefabInstanceScriptBoolVariable(lua_State* L);
CInt SetPrefabInstanceScriptIntVariable(lua_State* L);
CInt SetPrefabInstanceScriptDoubleVariable(lua_State* L);

CInt GetGUIButtonScriptStringVariable(lua_State* L);
CInt GetGUIButtonScriptBoolVariable(lua_State* L);
CInt GetGUIButtonScriptIntVariable(lua_State* L);
CInt GetGUIButtonScriptDoubleVariable(lua_State* L);
CInt SetGUIButtonScriptStringVariable(lua_State* L);
CInt SetGUIButtonScriptBoolVariable(lua_State* L);
CInt SetGUIButtonScriptIntVariable(lua_State* L);
CInt SetGUIButtonScriptDoubleVariable(lua_State* L);

CInt GetTriggerScriptStringVariable(lua_State* L);
CInt GetTriggerScriptBoolVariable(lua_State* L);
CInt GetTriggerScriptIntVariable(lua_State* L);
CInt GetTriggerScriptDoubleVariable(lua_State* L);
CInt SetTriggerScriptStringVariable(lua_State* L);
CInt SetTriggerScriptBoolVariable(lua_State* L);
CInt SetTriggerScriptIntVariable(lua_State* L);
CInt SetTriggerScriptDoubleVariable(lua_State* L);

CInt GetWaterScriptStringVariable(lua_State* L);
CInt GetWaterScriptBoolVariable(lua_State* L);
CInt GetWaterScriptIntVariable(lua_State* L);
CInt GetWaterScriptDoubleVariable(lua_State* L);
CInt SetWaterScriptStringVariable(lua_State* L);
CInt SetWaterScriptBoolVariable(lua_State* L);
CInt SetWaterScriptIntVariable(lua_State* L);
CInt SetWaterScriptDoubleVariable(lua_State* L);

CInt GetVideoScriptStringVariable(lua_State* L);
CInt GetVideoScriptBoolVariable(lua_State* L);
CInt GetVideoScriptIntVariable(lua_State* L);
CInt GetVideoScriptDoubleVariable(lua_State* L);
CInt SetVideoScriptStringVariable(lua_State* L);
CInt SetVideoScriptBoolVariable(lua_State* L);
CInt SetVideoScriptIntVariable(lua_State* L);
CInt SetVideoScriptDoubleVariable(lua_State* L);

CInt GetAmbientSoundScriptStringVariable(lua_State* L);
CInt GetAmbientSoundScriptBoolVariable(lua_State* L);
CInt GetAmbientSoundScriptIntVariable(lua_State* L);
CInt GetAmbientSoundScriptDoubleVariable(lua_State* L);
CInt SetAmbientSoundScriptStringVariable(lua_State* L);
CInt SetAmbientSoundScriptBoolVariable(lua_State* L);
CInt SetAmbientSoundScriptIntVariable(lua_State* L);
CInt SetAmbientSoundScriptDoubleVariable(lua_State* L);

CInt Get3DSoundScriptStringVariable(lua_State* L);
CInt Get3DSoundScriptBoolVariable(lua_State* L);
CInt Get3DSoundScriptIntVariable(lua_State* L);
CInt Get3DSoundScriptDoubleVariable(lua_State* L);
CInt Set3DSoundScriptStringVariable(lua_State* L);
CInt Set3DSoundScriptBoolVariable(lua_State* L);
CInt Set3DSoundScriptIntVariable(lua_State* L);
CInt Set3DSoundScriptDoubleVariable(lua_State* L);

CInt GetLightScriptStringVariable(lua_State* L);
CInt GetLightScriptBoolVariable(lua_State* L);
CInt GetLightScriptIntVariable(lua_State* L);
CInt GetLightScriptDoubleVariable(lua_State* L);
CInt SetLightScriptStringVariable(lua_State* L);
CInt SetLightScriptBoolVariable(lua_State* L);
CInt SetLightScriptIntVariable(lua_State* L);
CInt SetLightScriptDoubleVariable(lua_State* L);

CInt GetCameraScriptStringVariable(lua_State* L);
CInt GetCameraScriptBoolVariable(lua_State* L);
CInt GetCameraScriptIntVariable(lua_State* L);
CInt GetCameraScriptDoubleVariable(lua_State* L);
CInt SetCameraScriptStringVariable(lua_State* L);
CInt SetCameraScriptBoolVariable(lua_State* L);
CInt SetCameraScriptIntVariable(lua_State* L);
CInt SetCameraScriptDoubleVariable(lua_State* L);

CInt GetMainCharacterScriptStringVariable(lua_State* L);
CInt GetMainCharacterScriptBoolVariable(lua_State* L);
CInt GetMainCharacterScriptIntVariable(lua_State* L);
CInt GetMainCharacterScriptDoubleVariable(lua_State* L);
CInt SetMainCharacterScriptStringVariable(lua_State* L);
CInt SetMainCharacterScriptBoolVariable(lua_State* L);
CInt SetMainCharacterScriptIntVariable(lua_State* L);
CInt SetMainCharacterScriptDoubleVariable(lua_State* L);

CInt ShowGUIButton(lua_State* L);
CInt HideGUIButton(lua_State* L);
CInt ShowGUIImage(lua_State* L);
CInt HideGUIImage(lua_State* L);
CInt ShowGUIText(lua_State* L);
CInt HideGUIText(lua_State* L);
CInt ScaleGUIButton(lua_State* L);
CInt ScaleGUIImage(lua_State* L);

CInt SetGUIButtonPosition(lua_State* L);
CInt SetGUIImagePosition(lua_State* L);
CInt SetGUITextPosition(lua_State* L);
CInt GetGUIButtonPosition(lua_State* L);
CInt GetGUIImagePosition(lua_State* L);
CInt GetGUITextPosition(lua_State* L);

CInt SetGUIPosition(lua_State* L);
CInt GetGUIPosition(lua_State* L);

CInt AddForceToCharacterController(lua_State* L);
CInt AddForceToPrefabInstance(lua_State* L);
CInt AddTorqueToPrefabInstance(lua_State* L);

CInt GetPhysicsActorGroup(lua_State* L);
CInt SetPhysicsCollisionFlags(lua_State* L);

CInt GeneratePrefabInstance(lua_State* L);
CInt DeletePrefabInstance(lua_State* L);

CInt AttachPrefabInstanceToWater(lua_State* L);
CInt DetachPrefabInstanceFromWater(lua_State* L);

CInt SetSoundVolume(lua_State* L);
CInt SetSoundPitch(lua_State* L);
CInt SetSoundPlay(lua_State* L);
CInt SetSoundLoop(lua_State* L);
CInt SetSoundPosition(lua_State* L);
CInt SetSoundRollOff(lua_State* L);
CInt SetSoundReferenceDistance(lua_State* L);
CInt SetSoundMaxDistance(lua_State* L);

CInt GetSoundVolume(lua_State* L);
CInt GetSoundPitch(lua_State* L);
CInt GetSoundPlay(lua_State* L);
CInt GetSoundLoop(lua_State* L);
CInt GetSoundPosition(lua_State* L);
CInt GetSoundRollOff(lua_State* L);
CInt GetSoundReferenceDistance(lua_State* L);
CInt GetSoundMaxDistance(lua_State* L);

CInt SetGlobalSoundVolume(lua_State* L);
CInt GetGlobalSoundVolume(lua_State* L);

CInt PlayVideo(lua_State* L);
CInt PlayVideoLoop(lua_State* L);
CInt PlayVideoOnce(lua_State* L);
CInt StopVideo(lua_State* L);

CInt SetVideoLoop(lua_State* L);
CInt SetVideoVolume(lua_State* L);

CInt GetVideoPlay(lua_State* L);
CInt GetVideoLoop(lua_State* L);
CInt GetVideoVolume(lua_State* L);
CInt GetVideoDuration(lua_State* L);

//Stop Sounds
CInt StopAllSounds(lua_State* L);
CInt StopAllAmbientSounds(lua_State* L);
CInt StopAll3DSounds(lua_State* L);
CInt StopAllResourceSounds(lua_State* L);
//Play Sounds
CInt PlayAllSounds(lua_State* L);
CInt PlayAllPausedSounds(lua_State* L);
CInt PlayAllStoppedSounds(lua_State* L);
CInt PlayAllAmbientSounds(lua_State* L);
CInt PlayAll3DSounds(lua_State* L);
CInt PlayAllResourceSounds(lua_State* L);
CInt PlayAllStoppedAmbientSounds(lua_State* L);
CInt PlayAllStopped3DSounds(lua_State* L);
CInt PlayAllStoppedResourceSounds(lua_State* L);
CInt PlayAllPausedAmbientSounds(lua_State* L);
CInt PlayAllPaused3DSounds(lua_State* L);
CInt PlayAllPausedResourceSounds(lua_State* L);
//Play Sounds Loop
CInt PlayAllSoundsLoop(lua_State* L);
CInt PlayAllPausedSoundsLoop(lua_State* L);
CInt PlayAllStoppedSoundsLoop(lua_State* L);
CInt PlayAllAmbientSoundsLoop(lua_State* L);
CInt PlayAll3DSoundsLoop(lua_State* L);
CInt PlayAllResourceSoundsLoop(lua_State* L);
CInt PlayAllStoppedAmbientSoundsLoop(lua_State* L);
CInt PlayAllStopped3DSoundsLoop(lua_State* L);
CInt PlayAllStoppedResourceSoundsLoop(lua_State* L);
CInt PlayAllPausedAmbientSoundsLoop(lua_State* L);
CInt PlayAllPaused3DSoundsLoop(lua_State* L);
CInt PlayAllPausedResourceSoundsLoop(lua_State* L);
//Play Sounds once
CInt PlayAllSoundsOnce(lua_State* L);
CInt PlayAllPausedSoundsOnce(lua_State* L);
CInt PlayAllStoppedSoundsOnce(lua_State* L);
CInt PlayAllAmbientSoundsOnce(lua_State* L);
CInt PlayAll3DSoundsOnce(lua_State* L);
CInt PlayAllResourceSoundsOnce(lua_State* L);
CInt PlayAllStoppedAmbientSoundsOnce(lua_State* L);
CInt PlayAllStopped3DSoundsOnce(lua_State* L);
CInt PlayAllStoppedResourceSoundsOnce(lua_State* L);
CInt PlayAllPausedAmbientSoundsOnce(lua_State* L);
CInt PlayAllPaused3DSoundsOnce(lua_State* L);
CInt PlayAllPausedResourceSoundsOnce(lua_State* L);
//Pause Sounds
CInt PauseAllSounds(lua_State* L);
CInt PauseAllAmbientSounds(lua_State* L);
CInt PauseAll3DSounds(lua_State* L);
CInt PauseAllResourceSounds(lua_State* L);

//Pause game 
CInt PauseGame(lua_State* L);
CInt PauseAllAnimationsOfPrefabInstances(lua_State* L);
CInt PauseMainCharacterAnimations(lua_State* L);
CInt PausePhysics(lua_State* L);
CInt PauseAllWaterAnimations(lua_State* L);

//resume game
CInt ResumeGame(lua_State* L);
CInt ResumeAllAnimationsOfPrefabInstances(lua_State* L);
CInt ResumeMainCharacterAnimations(lua_State* L);
CInt ResumePhysics(lua_State* L);
CInt ResumeAllWaterAnimations(lua_State* L);

//lock/unlock character
CInt LockCharacterController(lua_State* L);
CInt UnlockCharacterController(lua_State* L);

//menu cursor
CInt ShowMenuCursor(lua_State* L);
CInt HideMenuCursor(lua_State* L);
CInt SetMenuCursorSize(lua_State* L);
CInt GetMenuCursorSize(lua_State* L);

//Pause script Update event of game objects
CInt PauseAllUpdateEvents(lua_State* L);
CInt PauseUpdateEventOfAllPrefabInstances(lua_State* L);
CInt PauseUpdateEventOfVSceneScript(lua_State* L);
CInt PauseUpdateEventOfSky(lua_State* L);
CInt PauseUpdateEventOfAllWaters(lua_State* L);
CInt PauseUpdateEventOfAllLights(lua_State* L);
CInt PauseUpdateEventOfAll3DSounds(lua_State* L);
CInt PauseUpdateEventOfAllAmbientSounds(lua_State* L);
CInt PauseUpdateEventOfMainCharacter(lua_State* L);
CInt PauseUpdateEventOfTerrain(lua_State* L);
CInt PauseUpdateEventOfAllEngineCameras(lua_State* L);

//Resume script Update event of game objects
CInt ResumeAllUpdateEvents(lua_State* L);
CInt ResumeUpdateEventOfAllPrefabInstances(lua_State* L);
CInt ResumeUpdateEventOfVSceneScript(lua_State* L);
CInt ResumeUpdateEventOfSky(lua_State* L);
CInt ResumeUpdateEventOfAllWaters(lua_State* L);
CInt ResumeUpdateEventOfAllLights(lua_State* L);
CInt ResumeUpdateEventOfAll3DSounds(lua_State* L);
CInt ResumeUpdateEventOfAllAmbientSounds(lua_State* L);
CInt ResumeUpdateEventOfMainCharacter(lua_State* L);
CInt ResumeUpdateEventOfTerrain(lua_State* L);
CInt ResumeUpdateEventOfAllEngineCameras(lua_State* L);


void GenerateLoadingTexture( char* fileName );
void DeleteLoadingTexture();
CVoid ShowLoadingScene(CChar* message = NULL);
