//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once


#define NOMINMAX

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

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

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes

#include "common\defines.h"

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// MFC support for internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

//This variable is used for selection. there's the same variable inside CNode class
//This name is used inside glPushName() when the user presses the left mouse button to select the objects
extern CUInt g_nameIndex;  
extern CUInt g_nodeIndex;
extern CInt g_selectedName; //holds the name of the selected object
extern CInt g_tempLastEngineObjectSelectedName; //temporary holds the name of the previous selected object
extern CInt g_lastEngineObjectSelectedName; //holds the name of the previous selected object
extern CBool g_transformObject; //we are in translation mode if an arrow is selected
extern CInt g_transformDirection; //X, Y, or Z
extern CBool g_importColladaImages;
extern CInt g_numVerts; 
extern CBool g_reportInfo;
#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
struct lua_State;
class CGeometry;
CVoid PrintShaderLog( CString strText ); // global print
CVoid PrintInfo(CString strText, COLORREF color = COLOR_WHITE, CBool reset = CFalse); // global print
CVoid PrintScriptInfo(CString strText, COLORREF color = COLOR_GREEN); // global print
CGeometry* GetGeometryFromScenes(const CChar * name, const CChar * DocURI);

class CPrefab;
CPrefab* GetPrefab(CChar* name);

//Sounds
CInt PlaySoundLoop(lua_State *L);
CInt PlaySoundOnce(lua_State *L);
CInt StopSound(lua_State *L);
CInt PauseSound(lua_State *L);

//Animations
CInt BlendCycle(lua_State *L);
CInt ClearCycle(lua_State *L);
CInt ExecuteAction(lua_State *L);
CInt ReverseExecuteAction(lua_State *L);
CInt RemoveAction(lua_State *L);
CInt PauseAnimations(lua_State *L);
CInt GetAnimationClipDuration(lua_State *L);

//Prefabs
CInt ShowPrefabInstance(lua_State *L);
CInt HidePrefabInstance(lua_State *L);

//VScene
CInt LoadVScene(lua_State *L);
CInt SetCurrentVSceneAsMenu(lua_State *L);
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
CInt StopAllResourceSounds(lua_State *L);
CInt ShowCursorIcon(lua_State *L);
CInt HideCursorIcon(lua_State *L);
CInt PrintConsole(lua_State* L);
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
CInt IsMenuEnabled(lua_State* L);
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

CInt SetPhysicsRestitution(lua_State* L);
CInt SetPhysicsSkinWidth(lua_State* L);
CInt SetPhysicsStaticFriction(lua_State* L);
CInt SetPhysicsDynamicFriction(lua_State* L);
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

CInt ShowGUIButton(lua_State* L);
CInt HideGUIButton(lua_State* L);
CInt ShowGUIImage(lua_State* L);
CInt HideGUIImage(lua_State* L);
CInt ShowGUIText(lua_State* L);
CInt HideGUIText(lua_State* L);
CInt ScaleGUIButton(lua_State* L);
CInt ScaleGUIImage(lua_State* L);
