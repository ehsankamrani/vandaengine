//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license
// ScriptEditorAddFunction.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngineEditor.h"
#include "ScriptEditorAddFunction.h"
#include "afxdialogex.h"
#include "Common/Utility.h"

// CScriptEditorAddFunction dialog

IMPLEMENT_DYNAMIC(CScriptEditorAddFunction, CDialog)

CScriptEditorAddFunction::CScriptEditorAddFunction(CWnd* pParent /*=NULL*/)
	: CDialog(CScriptEditorAddFunction::IDD, pParent)
{
	if (g_multipleView->m_enableTimer)
		g_multipleView->EnableTimer(CFalse);

	m_index = -1;
	Cpy( PlaySoundLoop, "PlaySoundLoop(string gameObjectSoundName)");
	Cpy(PlaySoundOnce, "PlaySoundOnce(string gameObjectSoundName)");
	Cpy(PauseSound, "PauseSound(string gameObjectSoundName)");
	Cpy(StopSound, "StopSound(string gameObjectSoundName)");

	Cpy(BlendCycle, "BlendCycle(string prefabInstanceName, string animationClipName, float weightTarget, float delayIn)");
	Cpy(ClearCycle, "ClearCycle(string prefabInstanceName, string animationClipName, float delayOut)");
	Cpy(ExecuteAction, "ExecuteAction(string prefabInstanceName, string animationClipName, float delayIn, float delayOut, float weightTarget, bool lock)");
	Cpy(ReverseExecuteAction, "ReverseExecuteAction(string prefabInstanceName, string animationClipName)");
	Cpy(RemoveAction, "RemoveAction(string prefabInstanceName, string animationClipName)");
	Cpy(GetAnimationClipDuration, "GetAnimationClipDuration(string prefabInstanceName, string animationClipName)");
	Cpy(PauseAnimations, "PauseAnimations(string prefabInstanceName)");

	Cpy(LoadVScene, "LoadVScene(string VSceneName)");
	Cpy(ExitGame, "ExitGame()");
	Cpy(SetCurrentVSceneAsMenu, "SetCurrentVSceneAsMenu(bool isMenu, bool PauseOrResumeGame, float cursorSize)");

	Cpy(ActivateThirdPersonCamera, "ActivateThirdPersonCamera()");
	Cpy(ActivateFirstPersonCamera, "ActivateFirstPersonCamera()");
	Cpy(ActivateImportedCamera, "ActivateImportedCamera(string importedCameraFullName, float endTime[optional])");
	Cpy(ActivateImportedCameraOfPrefabInstance, "ActivateImportedCameraOfPrefabInstance(string prefabInstanceName, string prefabCameraName, float endTime[optional])");
	Cpy(ActivateEngineCamera, "ActivateEngineCamera(string gameObjectCameraName, float endTime[optional])");
	Cpy(SetPhysicsCameraAngle, "SetPhysicsCameraAngle(float angleDegree)");
	Cpy(GetPhysicsCameraAngle, "GetPhysicsCameraAngle()");
	Cpy(SetPhysicsCameraTilt, "SetPhysicsCameraTilt(float tiltDegree)");
	Cpy(SetPhysicsCameraMaxTilt, "SetPhysicsCameraMaxTilt(float maxTiltDegree)");
	Cpy(SetPhysicsCameraMinTilt, "SetPhysicsCameraMinTilt(float minTiltDegree)");
	Cpy(GetPhysicsCameraTilt, "GetPhysicsCameraTilt()");
	Cpy(GetPhysicsCameraMaxTilt, "GetPhysicsCameraMaxTilt()");
	Cpy(GetPhysicsCameraMinTilt, "GetPhysicsCameraMinTilt()");
	Cpy(SetPhysicsCameraYaw, "SetPhysicsCameraYaw(float yawDegree)");
	Cpy(GetPhysicsCameraYaw, "GetPhysicsCameraYaw()");

	Cpy(LoadResource, "LoadResource(string resourceDirectoryName, string resourceFileName)");
	Cpy(DeleteResource, "DeleteResource(string resourceDirectoryName, string resourceFileName)");
	Cpy(DeleteAllResources, "DeleteAllResources()");
	Cpy(PlayResourceSoundLoop, "PlayResourceSoundLoop(string resourceDirectoryName_resourceFileName.ogg)");
	Cpy(PlayResourceSoundOnce, "PlayResourceSoundOnce(string resourceDirectoryName_resourceFileName.ogg)");
	Cpy(StopResourceSound, "StopResourceSound(string resourceDirectoryName_resourceFileName.ogg)");
	Cpy(PauseResourceSound, "PauseResourceSound(string resourceDirectoryName_resourceFileName.ogg)");
	Cpy(StopAllResourceSounds, "StopAllResourceSounds()");
	Cpy(ShowCursorIcon, "ShowCursorIcon(string resourceDirectoryName_resourceFileName.dds, float cursorSize)");
	Cpy(HideCursorIcon, "HideCursorIcon(string resourceDirectoryName_resourceFileName.dds)");

	Cpy(PrintConsole, "PrintConsole(string message)");

	Cpy(ShowGUI, "ShowGUI(string guiName)");
	Cpy(HideGUI, "HideGUI(string guiName)");

	Cpy(IsKeyDown, "IsKeyDown(string DirectInputKeyCode)");

	Cpy(ShowPrefabInstance, "ShowPrefabInstance(string prefabInstanceName)");
	Cpy(HidePrefabInstance, "HidePrefabInstance(string prefabInstanceName)");

	Cpy(SetSelectionDistance, "SetSelectionDistance(float selectionDistance)");
	Cpy(GetSelectionDistance, "GetSelectionDistance()");
	Cpy(SelectPrefabInstances , "SelectPrefabInstances(double mousePositionX, double mousePositionY, double selectionWidthSize, double selectionHeightSize)");
	Cpy(GetScreenWidth, "GetScreenWidth()");
	Cpy(GetScreenHeight, "GetScreenHeight()");
	Cpy(GetCursorX, "GetCursorX()");
	Cpy(GetCursorY, "GetCursorY()");
	Cpy(IsMenuEnabled, "IsMenuEnabled()");
	Cpy(GetElapsedTime, "GetElapsedTime()");
	Cpy(GetPrefabInstanceNameFromActor, "GetPrefabInstanceNameFromActor(string physicsActorName)");

	Cpy(TranslatePrefabInstance, "TranslatePrefabInstance(string prefabInstanceName, float XPosition, float YPosition, float ZPosition)");
	Cpy(RotatePrefabInstance, "RotatePrefabInstance(string prefabInstanceName, float XRotationAngle, float YRotationAngle, float ZRotationAngle)");
	Cpy(ScalePrefabInstance, "ScalePrefabInstance(string prefabInstanceName, float XScale, float YScale, float ZScale)");

	Cpy(GetPrefabInstanceTranslate, "GetPrefabInstanceTranslate(string prefabInstanceName)");
	Cpy(GetPrefabInstanceRotate, "GetPrefabInstanceRotate(string prefabInstanceName)");
	Cpy(GetPrefabInstanceScale, "GetPrefabInstanceScale(string prefabInstanceName)");

	Cpy(GetPrefabInstanceRadius, "GetPrefabInstanceRadius(string prefabInstanceName)");
	Cpy(GetDistanceOfPrefabInstanceFromPhysicsCamera, "GetDistanceOfPrefabInstanceFromPhysicsCamera(string prefabInstanceName)");

	Cpy(EnableDepthOfField, "EnableDepthOfField()");
	Cpy(DisableDepthOfField, "DisableDepthOfField()");
	Cpy(SetDepthOfFieldFocalDistance, "SetDepthOfFieldFocalDistance(float focalDistance)");
	Cpy(SetDepthOfFieldFocalRange, "SetDepthOfFieldFocalRange(float focalRange)");

	Cpy(EnableFog, "EnableFog()");
	Cpy(DisableFog, "DisableFog()");
	Cpy(SetFogColor, "SetFogColor(float red, float green, float blue)");
	Cpy(SetFogDensity, "SetFogDensity(float density)");

	Cpy(EnableBloom, "EnableBloom()");
	Cpy(DisableBloom, "DisableBloom()");
	Cpy(SetBloomColor, "SetBloomColor(float red, float green, float blue)");
	Cpy(SetBloomIntensity, "SetBloomIntensity(float intensity)");

	Cpy(EnableDirectionalShadow, "EnableDirectionalShadow()");
	Cpy(DisableDirectionalShadow, "DisableDirectionalShadow()");
	Cpy(SetDirectionalShadowAlgorithm, "SetDirectionalShadowAlgorithm(string shadowAlgorithmCode)");
	Cpy(SetDirectionalShadowNumberOfSplits, "SetDirectionalShadowNumberOfSplits(int numberOfSplits)");
	Cpy(SetDirectionalShadowWeightOfSplits, "SetDirectionalShadowWeightOfSplits(float weightOfSplits)");
	Cpy(SetDirectionalShadowNearClipPlane, "SetDirectionalShadowNearClipPlane(float nearClipPlane)");
	Cpy(SetDirectionalShadowFarClipPlane, "SetDirectionalShadowFarClipPlane(float farClipPlane)");
	Cpy(SetDirectionalShadowResolution, "SetDirectionalShadowResolution(int shadowResolution)");
	Cpy(SetDirectionalShadowIntensity, "SetDirectionalShadowIntensity(float shadowIntensity)");
	Cpy(SetDirectionalShadowLight, "SetDirectionalShadowLight(string directionalLightName)");

	Cpy(SetLightAmbient, "SetLightAmbient(string lightObjectName, float red, float green, float blue)");
	Cpy(SetLightDiffuse, "SetLightDiffuse(string lightObjectName, float red, float green, float blue)");
	Cpy(SetLightSpecular, "SetLightSpecular(string lightObjectName, float red, float green, float blue)");
	Cpy(SetLightShininess, "SetLightShininess(string lightObjectName, float shininess)");

	Cpy(SetPrefabInstanceAmbient, "SetPrefabInstanceAmbient(string prefabInstanceName, float red, float green, float blue)");
	Cpy(SetPrefabInstanceDiffuse, "SetPrefabInstanceDiffuse(string prefabInstanceName, float red, float green, float blue)");
	Cpy(SetPrefabInstanceSpecular, "SetPrefabInstanceSpecular(string prefabInstanceName, float red, float green, float blue)");
	Cpy(SetPrefabInstanceEmission, "SetPrefabInstanceEmission(string prefabInstanceName, float red, float green, float blue)");
	Cpy(SetPrefabInstanceShininess, "SetPrefabInstanceShininess(string prefabInstanceName, float shininess)");
	Cpy(SetPrefabInstanceTransparency, "SetPrefabInstanceTransparency(string prefabInstanceName, float transparency)");
	Cpy(EnablePrefabInstanceMaterial, "EnablePrefabInstanceMaterial(string prefabInstanceName)");
	Cpy(DisablePrefabInstanceMaterial, "DisablePrefabInstanceMaterial(string prefabInstanceName)");

	Cpy(SetPhysicsDefaultRestitution, "SetPhysicsDefaultRestitution(float restitution)");
	Cpy(SetPhysicsDefaultSkinWidth, "SetPhysicsDefaultSkinWidth(float skinWidth)");
	Cpy(SetPhysicsDefaultStaticFriction, "SetPhysicsDefaultStaticFriction(float staticFriction)");
	Cpy(SetPhysicsDefaultDynamicFriction, "SetPhysicsDefaultDynamicFriction(float dynamicFriction)");
	Cpy(EnablePhysicsGravity, "EnablePhysicsGravity()");
	Cpy(DisablePhysicsGravity, "DisablePhysicsGravity()");
	Cpy(SetPhysicsGravity, "SetPhysicsGravity(float x, float y, float z)");
	Cpy(EnablePhysicsGroundPlane, "EnablePhysicsGroundPlane()");
	Cpy(DisablePhysicsGroundPlane, "DisablePhysicsGroundPlane()");
	Cpy(SetPhysicGroundHeight, "SetPhysicGroundHeight(float height)");
	Cpy(SetDistanceBetweenPhysicsCameraAndCharacterController, "SetDistanceBetweenPhysicsCameraAndCharacterController(float distance)");
	Cpy(SetCharacterControllerCapsuleRadius, "SetCharacterControllerCapsuleRadius(float radius)");
	Cpy(SetCharacterControllerCapsuleHeight, "SetCharacterControllerCapsuleHeight(float height)");
	Cpy(SetCharacterControllerForcePower, "SetCharacterControllerForcePower(float forcePower)");
	Cpy(SetCharacterControllerWalkSpeed, "SetCharacterControllerWalkSpeed(float speed)");
	Cpy(SetCharacterControllerRunSpeed, "SetCharacterControllerRunSpeed(float speed)");
	Cpy(SetCharacterControllerSkinWidth, "SetCharacterControllerSkinWidth(float skinWidth)");
	Cpy(SetCharacterControllerStepOffset, "SetCharacterControllerStepOffset(float stepOffset)");
	Cpy(SetCharacterControllerSlopeLimit, "SetCharacterControllerSlopeLimit(float slope)");
	Cpy(SetCharacterControllerJumpPower, "SetCharacterControllerJumpPower(float jumpPower)");
	Cpy(EnableCharacterControllerJump, "EnableCharacterControllerJump()");
	Cpy(DisableCharacterControllerJump, "DisableCharacterControllerJump()");
	Cpy(EnablePhysicsDebugMode, "EnablePhysicsDebugMode()");
	Cpy(DisablePhysicsDebugMode, "DisablePhysicsDebugMode()");
	Cpy(SetCharacterControllerPosition, "SetCharacterControllerPosition(float x, float y, float z)");
	Cpy(GetCharacterControllerPosition, "GetCharacterControllerPosition()");

	Cpy(SetMaxMultisampling, "SetMaxMultisampling(int numSamples)");
	Cpy(SetMaxAnisotropicFiltering, "SetMaxAnisotropicFiltering(int max)");
	Cpy(EnableVSync, "EnableVSync()");
	Cpy(DisableVSync, "DisableVSync()");
	Cpy(EnableWaterReflection, "EnableWaterReflection()");
	Cpy(DisableWaterReflection, "DisableWaterReflection()");
	Cpy(SetScreenResolution, "SetScreenResolution(int screenWidth)");
	Cpy(SaveGeneralProperties, "SaveGeneralProperties()");
	Cpy(GetMaxMultisampling, "GetMaxMultisampling()");
	Cpy(GetMaxAnisotropicFiltering, "GetMaxAnisotropicFiltering()");
	Cpy(IsVSyncEnabled, "IsVSyncEnabled()");
	Cpy(IsWaterReflectionEnabled, "IsWaterReflectionEnabled()");
	Cpy(GetScreenResolution, "GetScreenResolution()");

	Cpy(GetVSceneScriptStringVariable, "GetVSceneScriptStringVariable(string variable)");
	Cpy(GetVSceneScriptBoolVariable, "GetVSceneScriptBoolVariable(string variable)");
	Cpy(GetVSceneScriptIntVariable, "GetVSceneScriptIntVariable(string variable)");
	Cpy(GetVSceneScriptDoubleVariable, "GetVSceneScriptDoubleVariable(string variable)");
	Cpy(SetVSceneScriptStringVariable, "SetVSceneScriptStringVariable(string variable, string value )");
	Cpy(SetVSceneScriptBoolVariable, "SetVSceneScriptBoolVariable(string variable, bool value)");
	Cpy(SetVSceneScriptIntVariable, "SetVSceneScriptIntVariable(string variable, int value)");
	Cpy(SetVSceneScriptDoubleVariable, "SetVSceneScriptDoubleVariable(string variable, double value)");

	Cpy(GetSkyScriptStringVariable, "GetSkyScriptStringVariable(string variable)");
	Cpy(GetSkyScriptBoolVariable, "GetSkyScriptBoolVariable(string variable)");
	Cpy(GetSkyScriptIntVariable, "GetSkyScriptIntVariable(string variable)");
	Cpy(GetSkyScriptDoubleVariable, "GetSkyScriptDoubleVariable(string variable)");
	Cpy(SetSkyScriptStringVariable, "SetSkyScriptStringVariable(string variable, string value )");
	Cpy(SetSkyScriptBoolVariable, "SetSkyScriptBoolVariable(string variable, bool value)");
	Cpy(SetSkyScriptIntVariable, "SetSkyScriptIntVariable(string variable, int value)");
	Cpy(SetSkyScriptDoubleVariable, "SetSkyScriptDoubleVariable(string variable, double value)");

	Cpy(GetTerrainScriptStringVariable, "GetTerrainScriptStringVariable(string variable)");
	Cpy(GetTerrainScriptBoolVariable, "GetTerrainScriptBoolVariable(string variable)");
	Cpy(GetTerrainScriptIntVariable, "GetTerrainScriptIntVariable(string variable)");
	Cpy(GetTerrainScriptDoubleVariable, "GetTerrainScriptDoubleVariable(string variable)");
	Cpy(SetTerrainScriptStringVariable, "SetTerrainScriptStringVariable(string variable, string value )");
	Cpy(SetTerrainScriptBoolVariable, "SetTerrainScriptBoolVariable(string variable, bool value)");
	Cpy(SetTerrainScriptIntVariable, "SetTerrainScriptIntVariable(string variable, int value)");
	Cpy(SetTerrainScriptDoubleVariable, "SetTerrainScriptDoubleVariable(string variable, double value)");

	Cpy(GetPrefabInstanceScriptStringVariable, "GetPrefabInstanceScriptStringVariable(string prefabInstanceName, string variable)");
	Cpy(GetPrefabInstanceScriptBoolVariable, "GetPrefabInstanceScriptBoolVariable(string prefabInstanceName, string variable)");
	Cpy(GetPrefabInstanceScriptIntVariable, "GetPrefabInstanceScriptIntVariable(string prefabInstanceName, string variable)");
	Cpy(GetPrefabInstanceScriptDoubleVariable, "GetPrefabInstanceScriptDoubleVariable(string prefabInstanceName, string variable)");
	Cpy(SetPrefabInstanceScriptStringVariable, "SetPrefabInstanceScriptStringVariable(string prefabInstanceName, string variable, string value)");
	Cpy(SetPrefabInstanceScriptBoolVariable, "SetPrefabInstanceScriptBoolVariable(string prefabInstanceName, string variable, bool variable)");
	Cpy(SetPrefabInstanceScriptIntVariable, "SetPrefabInstanceScriptIntVariable(string prefabInstanceName, string variable, int variable)");
	Cpy(SetPrefabInstanceScriptDoubleVariable, "SetPrefabInstanceScriptDoubleVariable(string prefabInstanceName, string variable, double variable)");

	Cpy(GetGUIButtonScriptStringVariable, "GetGUIButtonScriptStringVariable(string GUIName, string buttonName, string variable)");
	Cpy(GetGUIButtonScriptBoolVariable, "GetGUIButtonScriptBoolVariable(string GUIName, string buttonName, string variable)");
	Cpy(GetGUIButtonScriptIntVariable, "GetGUIButtonScriptIntVariable(string GUIName, string buttonName, string variable)");
	Cpy(GetGUIButtonScriptDoubleVariable, "GetGUIButtonScriptDoubleVariable(string GUIName, string buttonName, string variable)");
	Cpy(SetGUIButtonScriptStringVariable, "SetGUIButtonScriptStringVariable(string GUIName, string buttonName, string variable, string value)");
	Cpy(SetGUIButtonScriptBoolVariable, "SetGUIButtonScriptBoolVariable(string GUIName, string buttonName, string variable, bool value)");
	Cpy(SetGUIButtonScriptIntVariable, "SetGUIButtonScriptIntVariable(string GUIName, string buttonName, vstring variable, int value)");
	Cpy(SetGUIButtonScriptDoubleVariable, "SetGUIButtonScriptDoubleVariable(string GUIName, string buttonName, string variable, double value)");

	Cpy(GetTriggerScriptStringVariable, "GetTriggerScriptStringVariable(string triggerName, string variable)");
	Cpy(GetTriggerScriptBoolVariable, "GetTriggerScriptBoolVariable(string triggerName, string variable)");
	Cpy(GetTriggerScriptIntVariable, "GetTriggerScriptIntVariable(string triggerName, string variable)");
	Cpy(GetTriggerScriptDoubleVariable, "GetTriggerScriptDoubleVariable(string triggerName, string variable)");
	Cpy(SetTriggerScriptStringVariable, "SetTriggerScriptStringVariable(string triggerName, string variable, string value)");
	Cpy(SetTriggerScriptBoolVariable, "SetTriggerScriptBoolVariable(string triggerName, string variable, bool value)");
	Cpy(SetTriggerScriptIntVariable, "SetTriggerScriptIntVariable(string triggerName, string variable, int value)");
	Cpy(SetTriggerScriptDoubleVariable, "SetTriggerScriptDoubleVariable(string triggerName, string variable, double value)");

	Cpy(GetWaterScriptStringVariable, "GetWaterScriptStringVariable(string waterName, string variable)");
	Cpy(GetWaterScriptBoolVariable, "GetWaterScriptBoolVariable(string waterName, string variable)");
	Cpy(GetWaterScriptIntVariable, "GetWaterScriptIntVariable(string waterName, string variable)");
	Cpy(GetWaterScriptDoubleVariable, "GetWaterScriptDoubleVariable(string waterName, string variable)");
	Cpy(SetWaterScriptStringVariable, "SetWaterScriptStringVariable(string waterName, string variable, string value)");
	Cpy(SetWaterScriptBoolVariable, "SetWaterScriptBoolVariable(string waterName, string variable, bool value)");
	Cpy(SetWaterScriptIntVariable, "SetWaterScriptIntVariable(string waterName, string variable, int value)");
	Cpy(SetWaterScriptDoubleVariable, "SetWaterScriptDoubleVariable(string waterName, string variable, double value)");

	Cpy(GetVideoScriptStringVariable, "GetVideoScriptStringVariable(string videoName, string variable)");
	Cpy(GetVideoScriptBoolVariable, "GetVideoScriptBoolVariable(string videoName, string variable)");
	Cpy(GetVideoScriptIntVariable, "GetVideoScriptIntVariable(string videoName, string variable)");
	Cpy(GetVideoScriptDoubleVariable, "GetVideoScriptDoubleVariable(string videoName, string variable)");
	Cpy(SetVideoScriptStringVariable, "SetVideoScriptStringVariable(string videoName, string variable, string value)");
	Cpy(SetVideoScriptBoolVariable, "SetVideoScriptBoolVariable(string videoName, string variable, bool value)");
	Cpy(SetVideoScriptIntVariable, "SetVideoScriptIntVariable(string videoName, string variable, int value)");
	Cpy(SetVideoScriptDoubleVariable, "SetVideoScriptDoubleVariable(string videoName, string variable, double value)");

	Cpy(GetAmbientSoundScriptStringVariable, "GetAmbientSoundScriptStringVariable(string ambientSoundName, string variable)");
	Cpy(GetAmbientSoundScriptBoolVariable, "GetAmbientSoundScriptBoolVariable(string ambientSoundName, string variable)");
	Cpy(GetAmbientSoundScriptIntVariable, "GetAmbientSoundScriptIntVariable(string ambientSoundName, string variable)");
	Cpy(GetAmbientSoundScriptDoubleVariable, "GetAmbientSoundScriptDoubleVariable(string ambientSoundName, string variable)");
	Cpy(SetAmbientSoundScriptStringVariable, "SetAmbientSoundScriptStringVariable(string ambientSoundName, string variable, string value)");
	Cpy(SetAmbientSoundScriptBoolVariable, "SetAmbientSoundScriptBoolVariable(string ambientSoundName, string variable, bool value)");
	Cpy(SetAmbientSoundScriptIntVariable, "SetAmbientSoundScriptIntVariable(string ambientSoundName, string variable, int value)");
	Cpy(SetAmbientSoundScriptDoubleVariable, "SetAmbientSoundScriptDoubleVariable(string ambientSoundName, string variable, double value)");

	Cpy(Get3DSoundScriptStringVariable, "Get3DSoundScriptStringVariable(string 3DSoundName, string variable)");
	Cpy(Get3DSoundScriptBoolVariable, "Get3DSoundScriptBoolVariable(string 3DSoundName, string variable)");
	Cpy(Get3DSoundScriptIntVariable, "Get3DSoundScriptIntVariable(string 3DSoundName, string variable)");
	Cpy(Get3DSoundScriptDoubleVariable, "Get3DSoundScriptDoubleVariable(string 3DSoundName, string variable)");
	Cpy(Set3DSoundScriptStringVariable, "Set3DSoundScriptStringVariable(string 3DSoundName, string variable, string value)");
	Cpy(Set3DSoundScriptBoolVariable, "Set3DSoundScriptBoolVariable(string 3DSoundName, string variable, bool value)");
	Cpy(Set3DSoundScriptIntVariable, "Set3DSoundScriptIntVariable(string 3DSoundName, string variable, int value)");
	Cpy(Set3DSoundScriptDoubleVariable, "Set3DSoundScriptDoubleVariable(string 3DSoundName, string variable, double value)");

	Cpy(GetLightScriptStringVariable, "GetLightScriptStringVariable(string lightName, string variable)");
	Cpy(GetLightScriptBoolVariable, "GetLightScriptBoolVariable(string lightName, string variable)");
	Cpy(GetLightScriptIntVariable, "GetLightScriptIntVariable(string lightName, string variable)");
	Cpy(GetLightScriptDoubleVariable, "GetLightScriptDoubleVariable(string lightName, string variable)");
	Cpy(SetLightScriptStringVariable, "SetLightScriptStringVariable(string lightName, string variable, string value)");
	Cpy(SetLightScriptBoolVariable, "SetLightScriptBoolVariable(string lightName, string variable, bool value)");
	Cpy(SetLightScriptIntVariable, "SetLightScriptIntVariable(string lightName, string variable, int value)");
	Cpy(SetLightScriptDoubleVariable, "SetLightScriptDoubleVariable(string lightName, string variable, double value)");

	Cpy(GetCameraScriptStringVariable, "GetCameraScriptStringVariable(string cameraName, string variable)");
	Cpy(GetCameraScriptBoolVariable, "GetCameraScriptBoolVariable(string cameraName, string variable)");
	Cpy(GetCameraScriptIntVariable, "GetCameraScriptIntVariable(string cameraName, string variable)");
	Cpy(GetCameraScriptDoubleVariable, "GetCameraScriptDoubleVariable(string cameraName, string variable)");
	Cpy(SetCameraScriptStringVariable, "SetCameraScriptStringVariable(string cameraName, string variable, string value)");
	Cpy(SetCameraScriptBoolVariable, "SetCameraScriptBoolVariable(string cameraName, string variable, bool value)");
	Cpy(SetCameraScriptIntVariable, "SetCameraScriptIntVariable(string cameraName, string variable, int value)");
	Cpy(SetCameraScriptDoubleVariable, "SetCameraScriptDoubleVariable(string cameraName, string variable, double value)");

	Cpy(GetMainCharacterScriptStringVariable, "GetMainCharacterScriptStringVariable(string variable)");
	Cpy(GetMainCharacterScriptBoolVariable, "GetMainCharacterScriptBoolVariable(string variable)");
	Cpy(GetMainCharacterScriptIntVariable, "GetMainCharacterScriptIntVariable(string variable)");
	Cpy(GetMainCharacterScriptDoubleVariable, "GetMainCharacterScriptDoubleVariable(string variable)");
	Cpy(SetMainCharacterScriptStringVariable, "SetMainCharacterScriptStringVariable(string variable, string value )");
	Cpy(SetMainCharacterScriptBoolVariable, "SetMainCharacterScriptBoolVariable(string variable, bool value)");
	Cpy(SetMainCharacterScriptIntVariable, "SetMainCharacterScriptIntVariable(string variable, int value)");
	Cpy(SetMainCharacterScriptDoubleVariable, "SetMainCharacterScriptDoubleVariable(string variable, double value)");

	Cpy(ShowGUIButton, "ShowGUIButton(string GUIName, string buttonName)");
	Cpy(HideGUIButton, "HideGUIButton(string GUIName, string buttonName)");
	Cpy(ShowGUIImage, "ShowGUIImage(string GUIName, string imageName)");
	Cpy(HideGUIImage, "HideGUIImage(string GUIName, string imageName)");
	Cpy(ShowGUIText, "ShowGUIText(string GUIName, string textName)");
	Cpy(HideGUIText, "HideGUIText(string GUIName, string textName)");
	Cpy(ScaleGUIButton, "ScaleGUIButton(string GUIName, string buttonName, double scaleValue)");
	Cpy(ScaleGUIImage, "ScaleGUIImage(string GUIName, string imageName, double scaleValue)");

	Cpy(SetGUIButtonPosition, "SetGUIButtonPosition(string GUIName, string buttonName, int x, int y)");
	Cpy(SetGUIImagePosition, "SetGUIImagePosition(string GUIName, string imageName, int x, int y)");
	Cpy(SetGUITextPosition, "SetGUITextPosition(string GUIName, string textName, int x, int y)");
	Cpy(GetGUIButtonPosition, "GetGUIButtonPosition(string GUIName, string buttonName)");
	Cpy(GetGUIImagePosition, "GetGUIImagePosition(string GUIName, string imageName)");
	Cpy(GetGUITextPosition, "GetGUITextPosition(string GUIName, string textName)");

	Cpy(SetGUIPosition, "SetGUIPosition(string GUIName, int x, int y)");
	Cpy(GetGUIPosition, "GetGUIPosition(string GUIName)");

	Cpy(AddForceToCharacterController, "AddForceToCharacterController(float forceX, float forceY, float forceZ, float forceSpeed, float forceDecreaseValue)");
	Cpy(AddForceToPrefabInstance, "AddForceToPrefabInstance(string prefabInstanceName, float forceX, float forceY, float forceZ, float forcePower)");
	Cpy(AddTorqueToPrefabInstance, "AddTorqueToPrefabInstance(string prefabInstanceName, float torqueX, float torqueY, float torqueZ, float torquePower)");

	Cpy(GetPhysicsActorGroup, "GetPhysicsActorGroup(string physicsActorName)");
	Cpy(SetPhysicsCollisionFlags, "SetPhysicsCollisionFlags(string group1, string group2, bool flag)");

	Cpy(GeneratePrefabInstance, "GeneratePrefabInstance(string prefabName, float XPos, float YPos, float ZPos, float XRot, float YRot, float ZRot, float XScale, float YScale, float ZScale)");
	Cpy(DeletePrefabInstance, "DeletePrefabInstance(string prefabInstanceName)");

	Cpy(AttachPrefabInstanceToWater, "AttachPrefabInstanceToWater(string prefabInstanceName, string waterObjectName)");
	Cpy(DetachPrefabInstanceFromWater, "DetachPrefabInstanceFromWater(string prefabInstanceName, string waterObjectName)");

	Cpy(SetSoundVolume, "SetSoundVolume(string soundName, float volume)");
	Cpy(SetSoundPitch, "SetSoundPitch(string soundName, float pitch)");
	Cpy(SetSoundPlay, "SetSoundPlay(string soundName, bool play)");
	Cpy(SetSoundLoop, "SetSoundLoop(string soundName, bool loop)");
	Cpy(SetSoundPosition, "SetSoundPosition(string soundName, float x, float y, float z)");
	Cpy(SetSoundRollOff, "SetSoundRollOff(string soundName, float rollOff)");
	Cpy(SetSoundReferenceDistance, "SetSoundReferenceDistance(string soundName, float distance)");
	Cpy(SetSoundMaxDistance, "SetSoundMaxDistance(string soundName, float maxDistance)");

	Cpy(GetSoundVolume, "GetSoundVolume(string soundName)");
	Cpy(GetSoundPitch, "GetSoundPitch(string soundName)");
	Cpy(GetSoundPlay, "GetSoundPlay(string soundName)");
	Cpy(GetSoundLoop, "GetSoundLoop(string soundName)");
	Cpy(GetSoundPosition, "GetSoundPosition(string soundName)");
	Cpy(GetSoundRollOff, "GetSoundRollOff(string soundName)");
	Cpy(GetSoundReferenceDistance, "GetSoundReferenceDistance(string soundName)");
	Cpy(GetSoundMaxDistance, "GetSoundMaxDistance(string soundName)");

	Cpy(SetGlobalSoundVolume, "SetGlobalSoundVolume(float volume)");
	Cpy(GetGlobalSoundVolume, "GetGlobalSoundVolume()");

	Cpy(PlayVideoLoop, "PlayVideoLoop(string videoName)");
	Cpy(PlayVideoOnce, "PlayVideoOnce(string videoName)");
	Cpy(StopVideo, "StopVideo(string videoName)");

	Cpy(SetVideoPlay, "SetVideoPlay(string videoName, bool play)");
	Cpy(SetVideoLoop, "SetVideoLoop(string videoName, bool loop)");
	Cpy(SetVideoVolume, "SetVideoVolume(string videoName, float volume)");

	Cpy(GetVideoPlay, "GetVideoPlay(string videoName)");
	Cpy(GetVideoLoop, "GetVideoLoop(string videoName)");
	Cpy(GetVideoVolume, "GetVideoVolume(string videoName)");
	Cpy(GetVideoDuration, "GetVideoDuration(string videoName)");

}

CScriptEditorAddFunction::~CScriptEditorAddFunction()
{
}

void CScriptEditorAddFunction::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FUNCTIONS, m_listFunctions);
	DDX_Control(pDX, IDC_RICHED_FUNCTION_NAME, m_richFunctionName);
}


BEGIN_MESSAGE_MAP(CScriptEditorAddFunction, CDialog)
	ON_BN_CLICKED(IDOK, &CScriptEditorAddFunction::OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_FUNCTIONS, &CScriptEditorAddFunction::OnLvnItemchangedListFunctions)
	ON_BN_CLICKED(IDCANCEL, &CScriptEditorAddFunction::OnBnClickedCancel)
END_MESSAGE_MAP()


// CScriptEditorAddFunction message handlers


void CScriptEditorAddFunction::OnBnClickedOk()
{
	CString s;
	m_richFunctionName.GetWindowTextA(s);
	if (s.IsEmpty())
	{
		MessageBox("Please select an item from the list", "Error", MB_OK | MB_ICONERROR);
		return;
	}
	else
	{
		m_richFunctionName.Copy();
	}
	if (g_multipleView->m_enableTimer)
		g_multipleView->EnableTimer(CTrue);

	CDialog::OnOK();
}


void CScriptEditorAddFunction::OnLvnItemchangedListFunctions(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	int nSelected = -1;
	POSITION p = m_listFunctions.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listFunctions.GetNextSelectedItem(p);
	}
	TCHAR szBuffer[1024];

	if (nSelected >= 0)
	{
		DWORD cchBuf(1024);
		LVITEM lvi;
		lvi.iItem = nSelected;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuffer;
		lvi.cchTextMax = cchBuf;
		m_listFunctions.GetItem(&lvi);

		if (Cmp(szBuffer, "PlaySoundLoop"))
		{
			m_richFunctionName.SetWindowTextA(PlaySoundLoop);
		}
		else if (Cmp(szBuffer, "PlaySoundOnce"))
		{
			m_richFunctionName.SetWindowTextA(PlaySoundOnce);
		}
		else if (Cmp(szBuffer, "PauseSound"))
		{
			m_richFunctionName.SetWindowTextA(PauseSound);
		}
		else if (Cmp(szBuffer, "StopSound"))
		{
			m_richFunctionName.SetWindowTextA(StopSound);
		}
		else if (Cmp(szBuffer, "BlendCycle"))
		{
			m_richFunctionName.SetWindowTextA(BlendCycle);
		}
		else if (Cmp(szBuffer, "ClearCycle"))
		{
			m_richFunctionName.SetWindowTextA(ClearCycle);
		}
		else if (Cmp(szBuffer, "ExecuteAction"))
		{
			m_richFunctionName.SetWindowTextA(ExecuteAction);
		}
		else if (Cmp(szBuffer, "ReverseExecuteAction"))
		{
			m_richFunctionName.SetWindowTextA(ReverseExecuteAction);
		}
		else if (Cmp(szBuffer, "RemoveAction"))
		{
			m_richFunctionName.SetWindowTextA(RemoveAction);
		}
		else if (Cmp(szBuffer, "GetAnimationClipDuration"))
		{
			m_richFunctionName.SetWindowTextA(GetAnimationClipDuration);
		}
		else if (Cmp(szBuffer, "PauseAnimations"))
		{
			m_richFunctionName.SetWindowTextA(PauseAnimations);
		}
		else if (Cmp(szBuffer, "LoadVScene"))
		{
			m_richFunctionName.SetWindowTextA(LoadVScene);
		}
		else if (Cmp(szBuffer, "ExitGame"))
		{
			m_richFunctionName.SetWindowTextA(ExitGame);
		}
		else if (Cmp(szBuffer, "SetCurrentVSceneAsMenu"))
		{
			m_richFunctionName.SetWindowTextA(SetCurrentVSceneAsMenu);
		}
		else if (Cmp(szBuffer, "ActivateThirdPersonCamera"))
		{
			m_richFunctionName.SetWindowTextA(ActivateThirdPersonCamera);
		}
		else if (Cmp(szBuffer, "ActivateFirstPersonCamera"))
		{
			m_richFunctionName.SetWindowTextA(ActivateFirstPersonCamera);
		}
		else if (Cmp(szBuffer, "ActivateImportedCamera"))
		{
			m_richFunctionName.SetWindowTextA(ActivateImportedCamera);
		}
		else if (Cmp(szBuffer, "ActivateImportedCameraOfPrefabInstance"))
		{
			m_richFunctionName.SetWindowTextA(ActivateImportedCameraOfPrefabInstance);
		}
		else if (Cmp(szBuffer, "ActivateEngineCamera"))
		{
			m_richFunctionName.SetWindowTextA(ActivateEngineCamera);
		}
		else if (Cmp(szBuffer, "SetPhysicsCameraAngle"))
		{
			m_richFunctionName.SetWindowTextA(SetPhysicsCameraAngle);
		}
		else if (Cmp(szBuffer, "GetPhysicsCameraAngle"))
		{
			m_richFunctionName.SetWindowTextA(GetPhysicsCameraAngle);
		}
		else if (Cmp(szBuffer, "SetPhysicsCameraTilt"))
		{
			m_richFunctionName.SetWindowTextA(SetPhysicsCameraTilt);
		}
		else if (Cmp(szBuffer, "SetPhysicsCameraMaxTilt"))
		{
			m_richFunctionName.SetWindowTextA(SetPhysicsCameraMaxTilt);
		}
		else if (Cmp(szBuffer, "SetPhysicsCameraMinTilt"))
		{
			m_richFunctionName.SetWindowTextA(SetPhysicsCameraMinTilt);
		}
		else if (Cmp(szBuffer, "GetPhysicsCameraTilt"))
		{
			m_richFunctionName.SetWindowTextA(GetPhysicsCameraTilt);
		}
		else if (Cmp(szBuffer, "GetPhysicsCameraMaxTilt"))
		{
			m_richFunctionName.SetWindowTextA(GetPhysicsCameraMaxTilt);
		}
		else if (Cmp(szBuffer, "GetPhysicsCameraMinTilt"))
		{
			m_richFunctionName.SetWindowTextA(GetPhysicsCameraMinTilt);
		}
		else if (Cmp(szBuffer, "SetPhysicsCameraYaw"))
		{
			m_richFunctionName.SetWindowTextA(SetPhysicsCameraYaw);
		}
		else if (Cmp(szBuffer, "GetPhysicsCameraYaw"))
		{
			m_richFunctionName.SetWindowTextA(GetPhysicsCameraYaw);
		}
		else if (Cmp(szBuffer, "LoadResource"))
		{
			m_richFunctionName.SetWindowTextA(LoadResource);
		}
		else if (Cmp(szBuffer, "DeleteResource"))
		{
			m_richFunctionName.SetWindowTextA(DeleteResource);
		}
		else if (Cmp(szBuffer, "DeleteAllResources"))
		{
			m_richFunctionName.SetWindowTextA(DeleteAllResources);
		}
		else if (Cmp(szBuffer, "PlayResourceSoundLoop"))
		{
			m_richFunctionName.SetWindowTextA(PlayResourceSoundLoop);
		}
		else if (Cmp(szBuffer, "PlayResourceSoundOnce"))
		{
			m_richFunctionName.SetWindowTextA(PlayResourceSoundOnce);
		}
		else if (Cmp(szBuffer, "StopResourceSound"))
		{
			m_richFunctionName.SetWindowTextA(StopResourceSound);
		}
		else if (Cmp(szBuffer, "PauseResourceSound"))
		{
			m_richFunctionName.SetWindowTextA(PauseResourceSound);
		}
		else if (Cmp(szBuffer, "StopAllResourceSounds"))
		{
			m_richFunctionName.SetWindowTextA(StopAllResourceSounds);
		}
		else if (Cmp(szBuffer, "ShowCursorIcon"))
		{
			m_richFunctionName.SetWindowTextA(ShowCursorIcon);
		}
		else if (Cmp(szBuffer, "HideCursorIcon"))
		{
			m_richFunctionName.SetWindowTextA(HideCursorIcon);
		}
		else if (Cmp(szBuffer, "PrintConsole"))
		{
			m_richFunctionName.SetWindowTextA(PrintConsole);
		}
		else if (Cmp(szBuffer, "ShowGUI"))
		{
			m_richFunctionName.SetWindowTextA(ShowGUI);
		}
		else if (Cmp(szBuffer, "HideGUI"))
		{
			m_richFunctionName.SetWindowTextA(HideGUI);
		}
		else if (Cmp(szBuffer, "IsKeyDown"))
		{
			m_richFunctionName.SetWindowTextA(IsKeyDown);
		}
		else if (Cmp(szBuffer, "ShowPrefabInstance"))
		{
			m_richFunctionName.SetWindowTextA(ShowPrefabInstance);
		}
		else if (Cmp(szBuffer, "HidePrefabInstance"))
		{
			m_richFunctionName.SetWindowTextA(HidePrefabInstance);
		}
		else if (Cmp(szBuffer, "SetSelectionDistance"))
		{
			m_richFunctionName.SetWindowTextA(SetSelectionDistance);
		}
		else if (Cmp(szBuffer, "GetSelectionDistance"))
		{
			m_richFunctionName.SetWindowTextA(GetSelectionDistance);
		}
		else if (Cmp(szBuffer, "SelectPrefabInstances"))
		{
			m_richFunctionName.SetWindowTextA(SelectPrefabInstances);
		}
		else if (Cmp(szBuffer, "GetScreenWidth"))
		{
			m_richFunctionName.SetWindowTextA(GetScreenWidth);
		}
		else if (Cmp(szBuffer, "GetScreenHeight"))
		{
			m_richFunctionName.SetWindowTextA(GetScreenHeight);
		}
		else if (Cmp(szBuffer, "GetCursorX"))
		{
			m_richFunctionName.SetWindowTextA(GetCursorX);
		}
		else if (Cmp(szBuffer, "GetCursorY"))
		{
			m_richFunctionName.SetWindowTextA(GetCursorY);
		}
		else if (Cmp(szBuffer, "IsMenuEnabled"))
		{
			m_richFunctionName.SetWindowTextA(IsMenuEnabled);
		}
		else if (Cmp(szBuffer, "GetPrefabInstanceNameFromActor"))
		{
			m_richFunctionName.SetWindowTextA(GetPrefabInstanceNameFromActor);
		}
		else if (Cmp(szBuffer, "GetElapsedTime"))
		{
			m_richFunctionName.SetWindowTextA(GetElapsedTime);
		}
		else if (Cmp(szBuffer, "TranslatePrefabInstance"))
		{
			m_richFunctionName.SetWindowTextA(TranslatePrefabInstance);
		}
		else if (Cmp(szBuffer, "RotatePrefabInstance"))
		{
			m_richFunctionName.SetWindowTextA(RotatePrefabInstance);
		}
		else if (Cmp(szBuffer, "ScalePrefabInstance"))
		{
			m_richFunctionName.SetWindowTextA(ScalePrefabInstance);
		}
		else if (Cmp(szBuffer, "GetPrefabInstanceTranslate"))
		{
			m_richFunctionName.SetWindowTextA(GetPrefabInstanceTranslate);
		}
		else if (Cmp(szBuffer, "GetPrefabInstanceRotate"))
		{
			m_richFunctionName.SetWindowTextA(GetPrefabInstanceRotate);
		}
		else if (Cmp(szBuffer, "GetPrefabInstanceScale"))
		{
			m_richFunctionName.SetWindowTextA(GetPrefabInstanceScale);
		}

		else if (Cmp(szBuffer, "GetPrefabInstanceRadius"))
		{
			m_richFunctionName.SetWindowTextA(GetPrefabInstanceRadius);
		}
		else if (Cmp(szBuffer, "GetDistanceOfPrefabInstanceFromPhysicsCamera"))
		{
			m_richFunctionName.SetWindowTextA(GetDistanceOfPrefabInstanceFromPhysicsCamera);
		}
		else if (Cmp(szBuffer, "EnableDepthOfField"))
		{
			m_richFunctionName.SetWindowTextA(EnableDepthOfField);
		}
		else if (Cmp(szBuffer, "DisableDepthOfField"))
		{
			m_richFunctionName.SetWindowTextA(DisableDepthOfField);
		}
		else if (Cmp(szBuffer, "SetDepthOfFieldFocalDistance"))
		{
			m_richFunctionName.SetWindowTextA(SetDepthOfFieldFocalDistance);
		}
		else if (Cmp(szBuffer, "SetDepthOfFieldFocalRange"))
		{
			m_richFunctionName.SetWindowTextA(SetDepthOfFieldFocalRange);
		}
		else if (Cmp(szBuffer, "EnableFog"))
		{
			m_richFunctionName.SetWindowTextA(EnableFog);
		}
		else if (Cmp(szBuffer, "DisableFog"))
		{
			m_richFunctionName.SetWindowTextA(DisableFog);
		}
		else if (Cmp(szBuffer, "SetFogColor"))
		{
			m_richFunctionName.SetWindowTextA(SetFogColor);
		}
		else if (Cmp(szBuffer, "SetFogDensity"))
		{
			m_richFunctionName.SetWindowTextA(SetFogDensity);
		}
		else if (Cmp(szBuffer, "EnableBloom"))
		{
			m_richFunctionName.SetWindowTextA(EnableBloom);
		}
		else if (Cmp(szBuffer, "DisableBloom"))
		{
			m_richFunctionName.SetWindowTextA(DisableBloom);
		}
		else if (Cmp(szBuffer, "SetBloomColor"))
		{
			m_richFunctionName.SetWindowTextA(SetBloomColor);
		}
		else if (Cmp(szBuffer, "SetBloomIntensity"))
		{
			m_richFunctionName.SetWindowTextA(SetBloomIntensity);
		}
		else if (Cmp(szBuffer, "EnableDirectionalShadow"))
		{
			m_richFunctionName.SetWindowTextA(EnableDirectionalShadow);
		}
		else if (Cmp(szBuffer, "DisableDirectionalShadow"))
		{
			m_richFunctionName.SetWindowTextA(DisableDirectionalShadow);
		}
		else if (Cmp(szBuffer, "SetDirectionalShadowAlgorithm"))
		{
			m_richFunctionName.SetWindowTextA(SetDirectionalShadowAlgorithm);
		}
		else if (Cmp(szBuffer, "SetDirectionalShadowNumberOfSplits"))
		{
			m_richFunctionName.SetWindowTextA(SetDirectionalShadowNumberOfSplits);
		}
		else if (Cmp(szBuffer, "SetDirectionalShadowWeightOfSplits"))
		{
			m_richFunctionName.SetWindowTextA(SetDirectionalShadowWeightOfSplits);
		}
		else if (Cmp(szBuffer, "SetDirectionalShadowNearClipPlane"))
		{
			m_richFunctionName.SetWindowTextA(SetDirectionalShadowNearClipPlane);
		}
		else if (Cmp(szBuffer, "SetDirectionalShadowFarClipPlane"))
		{
			m_richFunctionName.SetWindowTextA(SetDirectionalShadowFarClipPlane);
		}
		else if (Cmp(szBuffer, "SetDirectionalShadowResolution"))
		{
			m_richFunctionName.SetWindowTextA(SetDirectionalShadowResolution);
		}
		else if (Cmp(szBuffer, "SetDirectionalShadowIntensity"))
		{
			m_richFunctionName.SetWindowTextA(SetDirectionalShadowIntensity);
		}
		else if (Cmp(szBuffer, "SetDirectionalShadowLight"))
		{
			m_richFunctionName.SetWindowTextA(SetDirectionalShadowLight);
		}
		else if (Cmp(szBuffer, "SetLightAmbient"))
		{
			m_richFunctionName.SetWindowTextA(SetLightAmbient);
		}
		else if (Cmp(szBuffer, "SetLightDiffuse"))
		{
			m_richFunctionName.SetWindowTextA(SetLightDiffuse);
		}
		else if (Cmp(szBuffer, "SetLightSpecular"))
		{
			m_richFunctionName.SetWindowTextA(SetLightSpecular);
		}
		else if (Cmp(szBuffer, "SetLightShininess"))
		{
			m_richFunctionName.SetWindowTextA(SetLightShininess);
		}
		else if (Cmp(szBuffer, "SetPrefabInstanceAmbient"))
		{
			m_richFunctionName.SetWindowTextA(SetPrefabInstanceAmbient);
		}
		else if (Cmp(szBuffer, "SetPrefabInstanceDiffuse"))
		{
			m_richFunctionName.SetWindowTextA(SetPrefabInstanceDiffuse);
		}
		else if (Cmp(szBuffer, "SetPrefabInstanceSpecular"))
		{
			m_richFunctionName.SetWindowTextA(SetPrefabInstanceSpecular);
		}
		else if (Cmp(szBuffer, "SetPrefabInstanceEmission"))
		{
			m_richFunctionName.SetWindowTextA(SetPrefabInstanceEmission);
		}
		else if (Cmp(szBuffer, "SetPrefabInstanceShininess"))
		{
			m_richFunctionName.SetWindowTextA(SetPrefabInstanceShininess);
		}
		else if (Cmp(szBuffer, "SetPrefabInstanceTransparency"))
		{
			m_richFunctionName.SetWindowTextA(SetPrefabInstanceTransparency);
		}
		else if (Cmp(szBuffer, "EnablePrefabInstanceMaterial"))
		{
			m_richFunctionName.SetWindowTextA(EnablePrefabInstanceMaterial);
		}
		else if (Cmp(szBuffer, "DisablePrefabInstanceMaterial"))
		{
			m_richFunctionName.SetWindowTextA(DisablePrefabInstanceMaterial);
		}
		else if (Cmp(szBuffer, "SetPhysicsDefaultRestitution"))
		{
			m_richFunctionName.SetWindowTextA(SetPhysicsDefaultRestitution);
		}
		else if (Cmp(szBuffer, "SetPhysicsDefaultSkinWidth"))
		{
			m_richFunctionName.SetWindowTextA(SetPhysicsDefaultSkinWidth);
		}
		else if (Cmp(szBuffer, "SetPhysicsDefaultStaticFriction"))
		{
			m_richFunctionName.SetWindowTextA(SetPhysicsDefaultStaticFriction);
		}
		else if (Cmp(szBuffer, "SetPhysicsDefaultDynamicFriction"))
		{
			m_richFunctionName.SetWindowTextA(SetPhysicsDefaultDynamicFriction);
		}
		else if (Cmp(szBuffer, "EnablePhysicsGravity"))
		{
			m_richFunctionName.SetWindowTextA(EnablePhysicsGravity);
		}
		else if (Cmp(szBuffer, "DisablePhysicsGravity"))
		{
			m_richFunctionName.SetWindowTextA(DisablePhysicsGravity);
		}
		else if (Cmp(szBuffer, "SetPhysicsGravity"))
		{
			m_richFunctionName.SetWindowTextA(SetPhysicsGravity);
		}
		else if (Cmp(szBuffer, "EnablePhysicsGroundPlane"))
		{
			m_richFunctionName.SetWindowTextA(EnablePhysicsGroundPlane);
		}
		else if (Cmp(szBuffer, "DisablePhysicsGroundPlane"))
		{
			m_richFunctionName.SetWindowTextA(DisablePhysicsGroundPlane);
		}
		else if (Cmp(szBuffer, "SetPhysicGroundHeight"))
		{
			m_richFunctionName.SetWindowTextA(SetPhysicGroundHeight);
		}
		else if (Cmp(szBuffer, "SetDistanceBetweenPhysicsCameraAndCharacterController"))
		{
			m_richFunctionName.SetWindowTextA(SetDistanceBetweenPhysicsCameraAndCharacterController);
		}
		else if (Cmp(szBuffer, "SetCharacterControllerCapsuleRadius"))
		{
			m_richFunctionName.SetWindowTextA(SetCharacterControllerCapsuleRadius);
		}
		else if (Cmp(szBuffer, "SetCharacterControllerCapsuleHeight"))
		{
			m_richFunctionName.SetWindowTextA(SetCharacterControllerCapsuleHeight);
		}
		else if (Cmp(szBuffer, "SetCharacterControllerForcePower"))
		{
			m_richFunctionName.SetWindowTextA(SetCharacterControllerForcePower);
		}
		else if (Cmp(szBuffer, "SetCharacterControllerWalkSpeed"))
		{
			m_richFunctionName.SetWindowTextA(SetCharacterControllerWalkSpeed);
		}
		else if (Cmp(szBuffer, "SetCharacterControllerRunSpeed"))
		{
			m_richFunctionName.SetWindowTextA(SetCharacterControllerRunSpeed);
		}
		else if (Cmp(szBuffer, "SetCharacterControllerSkinWidth"))
		{
			m_richFunctionName.SetWindowTextA(SetCharacterControllerSkinWidth);
		}
		else if (Cmp(szBuffer, "SetCharacterControllerStepOffset"))
		{
			m_richFunctionName.SetWindowTextA(SetCharacterControllerStepOffset);
		}
		else if (Cmp(szBuffer, "SetCharacterControllerSlopeLimit"))
		{
			m_richFunctionName.SetWindowTextA(SetCharacterControllerSlopeLimit);
		}
		else if (Cmp(szBuffer, "SetCharacterControllerJumpPower"))
		{
			m_richFunctionName.SetWindowTextA(SetCharacterControllerJumpPower);
		}
		else if (Cmp(szBuffer, "EnableCharacterControllerJump"))
		{
			m_richFunctionName.SetWindowTextA(EnableCharacterControllerJump);
		}
		else if (Cmp(szBuffer, "DisableCharacterControllerJump"))
		{
			m_richFunctionName.SetWindowTextA(DisableCharacterControllerJump);
		}
		else if (Cmp(szBuffer, "EnablePhysicsDebugMode"))
		{
			m_richFunctionName.SetWindowTextA(EnablePhysicsDebugMode);
		}
		else if (Cmp(szBuffer, "DisablePhysicsDebugMode"))
		{
			m_richFunctionName.SetWindowTextA(DisablePhysicsDebugMode);
		}
		if (Cmp(szBuffer, "SetCharacterControllerPosition"))
		{
			m_richFunctionName.SetWindowTextA(SetCharacterControllerPosition);
		}
		else if (Cmp(szBuffer, "GetCharacterControllerPosition"))
		{
			m_richFunctionName.SetWindowTextA(GetCharacterControllerPosition);
		}
		else if (Cmp(szBuffer, "SetMaxMultisampling"))
		{
			m_richFunctionName.SetWindowTextA(SetMaxMultisampling);
		}
		else if (Cmp(szBuffer, "SetMaxAnisotropicFiltering"))
		{
			m_richFunctionName.SetWindowTextA(SetMaxAnisotropicFiltering);
		}
		else if (Cmp(szBuffer, "EnableVSync"))
		{
			m_richFunctionName.SetWindowTextA(EnableVSync);
		}
		else if (Cmp(szBuffer, "DisableVSync"))
		{
			m_richFunctionName.SetWindowTextA(DisableVSync);
		}
		else if (Cmp(szBuffer, "EnableWaterReflection"))
		{
			m_richFunctionName.SetWindowTextA(EnableWaterReflection);
		}
		else if (Cmp(szBuffer, "DisableWaterReflection"))
		{
			m_richFunctionName.SetWindowTextA(DisableWaterReflection);
		}
		else if (Cmp(szBuffer, "SetScreenResolution"))
		{
			m_richFunctionName.SetWindowTextA(SetScreenResolution);
		}
		else if (Cmp(szBuffer, "SaveGeneralProperties"))
		{
			m_richFunctionName.SetWindowTextA(SaveGeneralProperties);
		}
		else if (Cmp(szBuffer, "GetMaxMultisampling"))
		{
			m_richFunctionName.SetWindowTextA(GetMaxMultisampling);
		}
		else if (Cmp(szBuffer, "GetMaxAnisotropicFiltering"))
		{
			m_richFunctionName.SetWindowTextA(GetMaxAnisotropicFiltering);
		}
		else if (Cmp(szBuffer, "IsVSyncEnabled"))
		{
			m_richFunctionName.SetWindowTextA(IsVSyncEnabled);
		}
		else if (Cmp(szBuffer, "IsWaterReflectionEnabled"))
		{
			m_richFunctionName.SetWindowTextA(IsWaterReflectionEnabled);
		}
		else if (Cmp(szBuffer, "GetScreenResolution"))
		{
			m_richFunctionName.SetWindowTextA(GetScreenResolution);
		}
		else if (Cmp(szBuffer, "GetVSceneScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetVSceneScriptStringVariable);
		}
		else if (Cmp(szBuffer, "GetVSceneScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetVSceneScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "GetVSceneScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetVSceneScriptIntVariable);
		}
		else if (Cmp(szBuffer, "GetVSceneScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetVSceneScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "SetVSceneScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetVSceneScriptStringVariable);
		}
		else if (Cmp(szBuffer, "SetVSceneScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetVSceneScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "SetVSceneScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetVSceneScriptIntVariable);
		}
		else if (Cmp(szBuffer, "SetVSceneScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetVSceneScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "GetSkyScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetSkyScriptStringVariable);
		}
		else if (Cmp(szBuffer, "GetSkyScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetSkyScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "GetSkyScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetSkyScriptIntVariable);
		}
		else if (Cmp(szBuffer, "GetSkyScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetSkyScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "SetSkyScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetSkyScriptStringVariable);
		}
		else if (Cmp(szBuffer, "SetSkyScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetSkyScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "SetSkyScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetSkyScriptIntVariable);
		}
		else if (Cmp(szBuffer, "SetSkyScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetSkyScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "GetTerrainScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetTerrainScriptStringVariable);
		}
		else if (Cmp(szBuffer, "GetTerrainScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetTerrainScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "GetTerrainScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetTerrainScriptIntVariable);
		}
		else if (Cmp(szBuffer, "GetTerrainScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetTerrainScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "SetTerrainScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetTerrainScriptStringVariable);
		}
		else if (Cmp(szBuffer, "SetTerrainScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetTerrainScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "SetTerrainScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetTerrainScriptIntVariable);
		}
		else if (Cmp(szBuffer, "SetTerrainScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetTerrainScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "GetPrefabInstanceScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetPrefabInstanceScriptStringVariable);
		}
		else if (Cmp(szBuffer, "GetPrefabInstanceScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetPrefabInstanceScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "GetPrefabInstanceScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetPrefabInstanceScriptIntVariable);
		}
		else if (Cmp(szBuffer, "GetPrefabInstanceScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetPrefabInstanceScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "SetPrefabInstanceScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetPrefabInstanceScriptStringVariable);
		}
		else if (Cmp(szBuffer, "SetPrefabInstanceScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetPrefabInstanceScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "SetPrefabInstanceScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetPrefabInstanceScriptIntVariable);
		}
		else if (Cmp(szBuffer, "SetPrefabInstanceScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetPrefabInstanceScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "GetGUIButtonScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetGUIButtonScriptStringVariable);
		}
		else if (Cmp(szBuffer, "GetGUIButtonScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetGUIButtonScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "GetGUIButtonScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetGUIButtonScriptIntVariable);
		}
		else if (Cmp(szBuffer, "GetGUIButtonScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetGUIButtonScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "SetGUIButtonScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetGUIButtonScriptStringVariable);
		}
		else if (Cmp(szBuffer, "SetGUIButtonScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetGUIButtonScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "SetGUIButtonScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetGUIButtonScriptIntVariable);
		}
		else if (Cmp(szBuffer, "SetGUIButtonScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetGUIButtonScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "GetTriggerScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetTriggerScriptStringVariable);
		}
		else if (Cmp(szBuffer, "GetTriggerScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetTriggerScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "GetTriggerScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetTriggerScriptIntVariable);
		}
		else if (Cmp(szBuffer, "GetTriggerScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetTriggerScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "SetTriggerScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetTriggerScriptStringVariable);
		}
		else if (Cmp(szBuffer, "SetTriggerScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetTriggerScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "SetTriggerScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetTriggerScriptIntVariable);
		}
		else if (Cmp(szBuffer, "SetTriggerScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetTriggerScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "GetWaterScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetWaterScriptStringVariable);
		}
		else if (Cmp(szBuffer, "GetWaterScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetWaterScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "GetWaterScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetWaterScriptIntVariable);
		}
		else if (Cmp(szBuffer, "GetWaterScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetWaterScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "SetWaterScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetWaterScriptStringVariable);
		}
		else if (Cmp(szBuffer, "SetWaterScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetWaterScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "SetWaterScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetWaterScriptIntVariable);
		}
		else if (Cmp(szBuffer, "SetWaterScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetWaterScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "GetVideoScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetVideoScriptStringVariable);
		}
		else if (Cmp(szBuffer, "GetVideoScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetVideoScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "GetVideoScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetVideoScriptIntVariable);
		}
		else if (Cmp(szBuffer, "GetVideoScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetVideoScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "SetVideoScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetVideoScriptStringVariable);
		}
		else if (Cmp(szBuffer, "SetVideoScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetVideoScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "SetVideoScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetVideoScriptIntVariable);
		}
		else if (Cmp(szBuffer, "SetVideoScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetVideoScriptDoubleVariable);
		}

		if (Cmp(szBuffer, "GetAmbientSoundScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetAmbientSoundScriptStringVariable);
		}
		else if (Cmp(szBuffer, "GetAmbientSoundScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetAmbientSoundScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "GetAmbientSoundScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetAmbientSoundScriptIntVariable);
		}
		else if (Cmp(szBuffer, "GetAmbientSoundScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetAmbientSoundScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "SetAmbientSoundScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetAmbientSoundScriptStringVariable);
		}
		else if (Cmp(szBuffer, "SetAmbientSoundScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetAmbientSoundScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "SetAmbientSoundScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetAmbientSoundScriptIntVariable);
		}
		else if (Cmp(szBuffer, "SetAmbientSoundScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetAmbientSoundScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "Get3DSoundScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(Get3DSoundScriptStringVariable);
		}
		else if (Cmp(szBuffer, "Get3DSoundScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(Get3DSoundScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "Get3DSoundScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(Get3DSoundScriptIntVariable);
		}
		else if (Cmp(szBuffer, "Get3DSoundScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(Get3DSoundScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "Set3DSoundScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(Set3DSoundScriptStringVariable);
		}
		else if (Cmp(szBuffer, "Set3DSoundScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(Set3DSoundScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "Set3DSoundScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(Set3DSoundScriptIntVariable);
		}
		else if (Cmp(szBuffer, "Set3DSoundScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(Set3DSoundScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "GetLightScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetLightScriptStringVariable);
		}
		else if (Cmp(szBuffer, "GetLightScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetLightScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "GetLightScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetLightScriptIntVariable);
		}
		else if (Cmp(szBuffer, "GetLightScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetLightScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "SetLightScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetLightScriptStringVariable);
		}
		else if (Cmp(szBuffer, "SetLightScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetLightScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "SetLightScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetLightScriptIntVariable);
		}
		else if (Cmp(szBuffer, "SetLightScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetLightScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "GetCameraScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetCameraScriptStringVariable);
		}
		else if (Cmp(szBuffer, "GetCameraScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetCameraScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "GetCameraScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetCameraScriptIntVariable);
		}
		else if (Cmp(szBuffer, "GetCameraScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetCameraScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "SetCameraScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetCameraScriptStringVariable);
		}
		else if (Cmp(szBuffer, "SetCameraScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetCameraScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "SetCameraScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetCameraScriptIntVariable);
		}
		else if (Cmp(szBuffer, "SetCameraScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetCameraScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "GetMainCharacterScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetMainCharacterScriptStringVariable);
		}
		else if (Cmp(szBuffer, "GetMainCharacterScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetMainCharacterScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "GetMainCharacterScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetMainCharacterScriptIntVariable);
		}
		else if (Cmp(szBuffer, "GetMainCharacterScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(GetMainCharacterScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "SetMainCharacterScriptStringVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetMainCharacterScriptStringVariable);
		}
		else if (Cmp(szBuffer, "SetMainCharacterScriptBoolVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetMainCharacterScriptBoolVariable);
		}
		else if (Cmp(szBuffer, "SetMainCharacterScriptIntVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetMainCharacterScriptIntVariable);
		}
		else if (Cmp(szBuffer, "SetMainCharacterScriptDoubleVariable"))
		{
			m_richFunctionName.SetWindowTextA(SetMainCharacterScriptDoubleVariable);
		}
		else if (Cmp(szBuffer, "ShowGUIButton"))
		{
			m_richFunctionName.SetWindowTextA(ShowGUIButton);
		}
		else if (Cmp(szBuffer, "HideGUIButton"))
		{
			m_richFunctionName.SetWindowTextA(HideGUIButton);
		}
		else if (Cmp(szBuffer, "ShowGUIImage"))
		{
			m_richFunctionName.SetWindowTextA(ShowGUIImage);
		}
		else if (Cmp(szBuffer, "HideGUIImage"))
		{
			m_richFunctionName.SetWindowTextA(HideGUIImage);
		}
		else if (Cmp(szBuffer, "ShowGUIText"))
		{
			m_richFunctionName.SetWindowTextA(ShowGUIText);
		}
		else if (Cmp(szBuffer, "HideGUIText"))
		{
			m_richFunctionName.SetWindowTextA(HideGUIText);
		}
		else if (Cmp(szBuffer, "ScaleGUIButton"))
		{
			m_richFunctionName.SetWindowTextA(ScaleGUIButton);
		}
		else if (Cmp(szBuffer, "ScaleGUIImage"))
		{
			m_richFunctionName.SetWindowTextA(ScaleGUIImage);
		}
		else if (Cmp(szBuffer, "SetGUIButtonPosition"))
		{
			m_richFunctionName.SetWindowTextA(SetGUIButtonPosition);
		}
		else if (Cmp(szBuffer, "SetGUIImagePosition"))
		{
			m_richFunctionName.SetWindowTextA(SetGUIImagePosition);
		}
		else if (Cmp(szBuffer, "SetGUITextPosition"))
		{
			m_richFunctionName.SetWindowTextA(SetGUITextPosition);
		}
		else if (Cmp(szBuffer, "GetGUIButtonPosition"))
		{
			m_richFunctionName.SetWindowTextA(GetGUIButtonPosition);
		}
		else if (Cmp(szBuffer, "GetGUIImagePosition"))
		{
			m_richFunctionName.SetWindowTextA(GetGUIImagePosition);
		}
		else if (Cmp(szBuffer, "GetGUITextPosition"))
		{
		m_richFunctionName.SetWindowTextA(GetGUITextPosition);
		}
		else if (Cmp(szBuffer, "SetGUIPosition"))
		{
		m_richFunctionName.SetWindowTextA(SetGUIPosition);
		}
		else if (Cmp(szBuffer, "GetGUIPosition"))
		{
		m_richFunctionName.SetWindowTextA(GetGUIPosition);
		}
		else if (Cmp(szBuffer, "AddForceToCharacterController"))
		{
			m_richFunctionName.SetWindowTextA(AddForceToCharacterController);
		}
		else if (Cmp(szBuffer, "AddForceToPrefabInstance"))
		{
			m_richFunctionName.SetWindowTextA(AddForceToPrefabInstance);
		}
		else if (Cmp(szBuffer, "AddTorqueToPrefabInstance"))
		{
			m_richFunctionName.SetWindowTextA(AddTorqueToPrefabInstance);
		}
		else if (Cmp(szBuffer, "GetPhysicsActorGroup"))
		{
			m_richFunctionName.SetWindowTextA(GetPhysicsActorGroup);
		}
		else if (Cmp(szBuffer, "SetPhysicsCollisionFlags"))
		{
			m_richFunctionName.SetWindowTextA(SetPhysicsCollisionFlags);
		}
		else if (Cmp(szBuffer, "GeneratePrefabInstance"))
		{
			m_richFunctionName.SetWindowTextA(GeneratePrefabInstance);
		}
		else if (Cmp(szBuffer, "DeletePrefabInstance"))
		{
			m_richFunctionName.SetWindowTextA(DeletePrefabInstance);
		}
		else if (Cmp(szBuffer, "AttachPrefabInstanceToWater"))
		{
			m_richFunctionName.SetWindowTextA(AttachPrefabInstanceToWater);
		}
		else if (Cmp(szBuffer, "DetachPrefabInstanceFromWater"))
		{
			m_richFunctionName.SetWindowTextA(DetachPrefabInstanceFromWater);
		}

		if (Cmp(szBuffer, "SetSoundVolume"))
		{
			m_richFunctionName.SetWindowTextA(SetSoundVolume);
		}
		else if (Cmp(szBuffer, "SetSoundPitch"))
		{
			m_richFunctionName.SetWindowTextA(SetSoundPitch);
		}
		else if (Cmp(szBuffer, "SetSoundPlay"))
		{
			m_richFunctionName.SetWindowTextA(SetSoundPlay);
		}
		else if (Cmp(szBuffer, "SetSoundLoop"))
		{
			m_richFunctionName.SetWindowTextA(SetSoundLoop);
		}
		else if (Cmp(szBuffer, "SetSoundPosition"))
		{
			m_richFunctionName.SetWindowTextA(SetSoundPosition);
		}
		else if (Cmp(szBuffer, "SetSoundRollOff"))
		{
			m_richFunctionName.SetWindowTextA(SetSoundRollOff);
		}
		else if (Cmp(szBuffer, "SetSoundReferenceDistance"))
		{
			m_richFunctionName.SetWindowTextA(SetSoundReferenceDistance);
		}
		else if (Cmp(szBuffer, "SetSoundMaxDistance"))
		{
			m_richFunctionName.SetWindowTextA(SetSoundMaxDistance);
		}
		else if (Cmp(szBuffer, "GetSoundVolume"))
		{
			m_richFunctionName.SetWindowTextA(GetSoundVolume);
		}
		else if (Cmp(szBuffer, "GetSoundPitch"))
		{
			m_richFunctionName.SetWindowTextA(GetSoundPitch);
		}
		else if (Cmp(szBuffer, "GetSoundPlay"))
		{
			m_richFunctionName.SetWindowTextA(GetSoundPlay);
		}
		else if (Cmp(szBuffer, "GetSoundLoop"))
		{
			m_richFunctionName.SetWindowTextA(GetSoundLoop);
		}
		else if (Cmp(szBuffer, "GetSoundPosition"))
		{
			m_richFunctionName.SetWindowTextA(GetSoundPosition);
		}
		else if (Cmp(szBuffer, "GetSoundRollOff"))
		{
			m_richFunctionName.SetWindowTextA(GetSoundRollOff);
		}
		else if (Cmp(szBuffer, "GetSoundReferenceDistance"))
		{
			m_richFunctionName.SetWindowTextA(GetSoundReferenceDistance);
		}
		else if (Cmp(szBuffer, "GetSoundMaxDistance"))
		{
			m_richFunctionName.SetWindowTextA(GetSoundMaxDistance);
		}
		else if (Cmp(szBuffer, "SetGlobalSoundVolume"))
		{
			m_richFunctionName.SetWindowTextA(SetGlobalSoundVolume);
		}
		else if (Cmp(szBuffer, "GetGlobalSoundVolume"))
		{
			m_richFunctionName.SetWindowTextA(GetGlobalSoundVolume);
		}
		else if (Cmp(szBuffer, "PlayVideoLoop"))
		{
			m_richFunctionName.SetWindowTextA(PlayVideoLoop);
		}
		else if (Cmp(szBuffer, "PlayVideoOnce"))
		{
			m_richFunctionName.SetWindowTextA(PlayVideoOnce);
		}
		else if (Cmp(szBuffer, "StopVideo"))
		{
			m_richFunctionName.SetWindowTextA(StopVideo);
		}
		else if (Cmp(szBuffer, "SetVideoPlay"))
		{
			m_richFunctionName.SetWindowTextA(SetVideoPlay);
		}
		else if (Cmp(szBuffer, "SetVideoLoop"))
		{
			m_richFunctionName.SetWindowTextA(SetVideoLoop);
		}
		else if (Cmp(szBuffer, "SetVideoVolume"))
		{
			m_richFunctionName.SetWindowTextA(SetVideoVolume);
		}
		else if (Cmp(szBuffer, "GetVideoPlay"))
		{
			m_richFunctionName.SetWindowTextA(GetVideoPlay);
		}
		else if (Cmp(szBuffer, "GetVideoLoop"))
		{
			m_richFunctionName.SetWindowTextA(GetVideoLoop);
		}
		else if (Cmp(szBuffer, "GetVideoVolume"))
		{
			m_richFunctionName.SetWindowTextA(GetVideoVolume);
		}
		else if (Cmp(szBuffer, "GetVideoDuration"))
		{
			m_richFunctionName.SetWindowTextA(GetVideoDuration);
		}

		CInt end = m_richFunctionName.GetWindowTextLengthA();
		m_richFunctionName.SetSel(0, end);
	}
	else
	{
		m_richFunctionName.SetWindowTextA("");
		m_richFunctionName.SetSel(0, 0);
	}

	*pResult = 0;
}


BOOL CScriptEditorAddFunction::OnInitDialog()
{
	CDialog::OnInitDialog();

	CBitmap cBmp;
	CBitmap* cBmpMask = NULL;
	m_image.Create(32, 32, ILC_COLOR24, 1, 1);

	cBmp.LoadBitmap(IDB_BITMAP_ADD_ITEM);
	m_image.Add(&cBmp, cBmpMask);
	cBmp.DeleteObject();

	RECT tempRect;
	m_listFunctions.GetClientRect(&tempRect);
	m_listFunctions.SetImageList(&m_image, LVSIL_SMALL);
	m_listFunctions.InsertColumn(0, "Functions", LVCFMT_LEFT | LVS_SHOWSELALWAYS, (tempRect.right - tempRect.left) * 90 / 100);
	m_listFunctions.ShowWindow(SW_SHOW);
	m_listFunctions.UpdateWindow();

	InsertItem("PlaySoundLoop");
	InsertItem("PlaySoundOnce");
	InsertItem("PauseSound");
	InsertItem("StopSound");

	InsertItem("BlendCycle");
	InsertItem("ClearCycle");
	InsertItem("ExecuteAction");
	InsertItem("ReverseExecuteAction");
	InsertItem("RemoveAction");
	InsertItem("GetAnimationClipDuration");
	InsertItem("PauseAnimations");

	InsertItem("LoadVScene");
	InsertItem("ExitGame");
	InsertItem("SetCurrentVSceneAsMenu");

	InsertItem("ActivateThirdPersonCamera");
	InsertItem("ActivateFirstPersonCamera");
	InsertItem("ActivateImportedCamera");
	InsertItem("ActivateImportedCameraOfPrefabInstance");
	InsertItem("ActivateEngineCamera");
	InsertItem("SetPhysicsCameraAngle");
	InsertItem("GetPhysicsCameraAngle");
	InsertItem("SetPhysicsCameraTilt");
	InsertItem("SetPhysicsCameraMinTilt");
	InsertItem("SetPhysicsCameraMaxTilt");
	InsertItem("GetPhysicsCameraTilt");
	InsertItem("GetPhysicsCameraMinTilt");
	InsertItem("GetPhysicsCameraMaxTilt");
	InsertItem("SetPhysicsCameraYaw");
	InsertItem("GetPhysicsCameraYaw");

	InsertItem("LoadResource");
	InsertItem("DeleteResource");
	InsertItem("DeleteAllResources");
	InsertItem("PlayResourceSoundLoop");
	InsertItem("PlayResourceSoundOnce");
	InsertItem("StopResourceSound");
	InsertItem("PauseResourceSound");
	InsertItem("StopAllResourceSounds");
	InsertItem("ShowCursorIcon");
	InsertItem("HideCursorIcon");

	InsertItem("PrintConsole");

	InsertItem("ShowGUI");
	InsertItem("HideGUI");

	InsertItem("IsKeyDown");

	InsertItem("ShowPrefabInstance");
	InsertItem("HidePrefabInstance");

	InsertItem("SetSelectionDistance");
	InsertItem("GetSelectionDistance");
	InsertItem("SelectPrefabInstances");

	InsertItem("GetScreenWidth");
	InsertItem("GetScreenHeight");
	InsertItem("GetCursorX");
	InsertItem("GetCursorY");
	InsertItem("IsMenuEnabled");
	InsertItem("GetElapsedTime");
	InsertItem("GetPrefabInstanceNameFromActor");

	InsertItem("TranslatePrefabInstance");
	InsertItem("RotatePrefabInstance");
	InsertItem("ScalePrefabInstance");

	InsertItem("GetPrefabInstanceTranslate");
	InsertItem("GetPrefabInstanceRotate");
	InsertItem("GetPrefabInstanceScale");

	InsertItem("GetPrefabInstanceRadius");
	InsertItem("GetDistanceOfPrefabInstanceFromPhysicsCamera");

	InsertItem("EnableDepthOfField");
	InsertItem("DisableDepthOfField");
	InsertItem("SetDepthOfFieldFocalDistance");
	InsertItem("SetDepthOfFieldFocalRange");

	InsertItem("EnableFog");
	InsertItem("DisableFog");
	InsertItem("SetFogColor");
	InsertItem("SetFogDensity");

	InsertItem("EnableBloom");
	InsertItem("DisableBloom");
	InsertItem("SetBloomColor");
	InsertItem("SetBloomIntensity");

	InsertItem("EnableDirectionalShadow");
	InsertItem("DisableDirectionalShadow");
	InsertItem("SetDirectionalShadowAlgorithm");
	InsertItem("SetDirectionalShadowNumberOfSplits");
	InsertItem("SetDirectionalShadowWeightOfSplits");
	InsertItem("SetDirectionalShadowNearClipPlane");
	InsertItem("SetDirectionalShadowFarClipPlane");
	InsertItem("SetDirectionalShadowResolution");
	InsertItem("SetDirectionalShadowIntensity");
	InsertItem("SetDirectionalShadowLight");

	InsertItem("SetLightAmbient");
	InsertItem("SetLightDiffuse");
	InsertItem("SetLightSpecular");
	InsertItem("SetLightShininess");

	InsertItem("SetPrefabInstanceAmbient");
	InsertItem("SetPrefabInstanceDiffuse");
	InsertItem("SetPrefabInstanceSpecular");
	InsertItem("SetPrefabInstanceEmission");
	InsertItem("SetPrefabInstanceShininess");
	InsertItem("SetPrefabInstanceTransparency");
	InsertItem("EnablePrefabInstanceMaterial");
	InsertItem("DisablePrefabInstanceMaterial");

	InsertItem("SetPhysicsDefaultRestitution");
	InsertItem("SetPhysicsDefaultSkinWidth");
	InsertItem("SetPhysicsDefaultStaticFriction");
	InsertItem("SetPhysicsDefaultDynamicFriction");
	InsertItem("EnablePhysicsGravity");
	InsertItem("DisablePhysicsGravity");
	InsertItem("SetPhysicsGravity");
	InsertItem("EnablePhysicsGroundPlane");
	InsertItem("DisablePhysicsGroundPlane");
	InsertItem("SetPhysicGroundHeight");
	InsertItem("SetDistanceBetweenPhysicsCameraAndCharacterController");
	InsertItem("SetCharacterControllerCapsuleRadius");
	InsertItem("SetCharacterControllerCapsuleHeight");
	InsertItem("SetCharacterControllerForcePower");
	InsertItem("SetCharacterControllerWalkSpeed");
	InsertItem("SetCharacterControllerRunSpeed");
	//InsertItem("SetCharacterControllerSkinWidth");
	InsertItem("SetCharacterControllerStepOffset");
	//InsertItem("SetCharacterControllerSlopeLimit");
	InsertItem("SetCharacterControllerJumpPower");
	InsertItem("EnableCharacterControllerJump");
	InsertItem("DisableCharacterControllerJump");
	InsertItem("EnablePhysicsDebugMode");
	InsertItem("DisablePhysicsDebugMode");
	InsertItem("SetCharacterControllerPosition");
	InsertItem("GetCharacterControllerPosition");

	InsertItem("SetMaxMultisampling");
	InsertItem("SetMaxAnisotropicFiltering");
	InsertItem("EnableVSync");
	InsertItem("DisableVSync");
	InsertItem("EnableWaterReflection");
	InsertItem("DisableWaterReflection");
	InsertItem("SetScreenResolution");
	InsertItem("SaveGeneralProperties");
	InsertItem("GetMaxMultisampling");
	InsertItem("GetMaxAnisotropicFiltering");
	InsertItem("IsVSyncEnabled");
	InsertItem("IsWaterReflectionEnabled");
	InsertItem("GetScreenResolution");

	InsertItem("GetVSceneScriptStringVariable");
	InsertItem("GetVSceneScriptBoolVariable");
	InsertItem("GetVSceneScriptIntVariable");
	InsertItem("GetVSceneScriptDoubleVariable");
	InsertItem("SetVSceneScriptStringVariable");
	InsertItem("SetVSceneScriptBoolVariable");
	InsertItem("SetVSceneScriptIntVariable");
	InsertItem("SetVSceneScriptDoubleVariable");

	InsertItem("GetSkyScriptStringVariable");
	InsertItem("GetSkyScriptBoolVariable");
	InsertItem("GetSkyScriptIntVariable");
	InsertItem("GetSkyScriptDoubleVariable");
	InsertItem("SetSkyScriptStringVariable");
	InsertItem("SetSkyScriptBoolVariable");
	InsertItem("SetSkyScriptIntVariable");
	InsertItem("SetSkyScriptDoubleVariable");

	InsertItem("GetTerrainScriptStringVariable");
	InsertItem("GetTerrainScriptBoolVariable");
	InsertItem("GetTerrainScriptIntVariable");
	InsertItem("GetTerrainScriptDoubleVariable");
	InsertItem("SetTerrainScriptStringVariable");
	InsertItem("SetTerrainScriptBoolVariable");
	InsertItem("SetTerrainScriptIntVariable");
	InsertItem("SetTerrainScriptDoubleVariable");

	InsertItem("GetPrefabInstanceScriptStringVariable");
	InsertItem("GetPrefabInstanceScriptBoolVariable");
	InsertItem("GetPrefabInstanceScriptIntVariable");
	InsertItem("GetPrefabInstanceScriptDoubleVariable");
	InsertItem("SetPrefabInstanceScriptStringVariable");
	InsertItem("SetPrefabInstanceScriptBoolVariable");
	InsertItem("SetPrefabInstanceScriptIntVariable");
	InsertItem("SetPrefabInstanceScriptDoubleVariable");

	InsertItem("GetGUIButtonScriptStringVariable");
	InsertItem("GetGUIButtonScriptBoolVariable");
	InsertItem("GetGUIButtonScriptIntVariable");
	InsertItem("GetGUIButtonScriptDoubleVariable");
	InsertItem("SetGUIButtonScriptStringVariable");
	InsertItem("SetGUIButtonScriptBoolVariable");
	InsertItem("SetGUIButtonScriptIntVariable");
	InsertItem("SetGUIButtonScriptDoubleVariable");

	InsertItem("GetTriggerScriptStringVariable");
	InsertItem("GetTriggerScriptBoolVariable");
	InsertItem("GetTriggerScriptIntVariable");
	InsertItem("GetTriggerScriptDoubleVariable");
	InsertItem("SetTriggerScriptStringVariable");
	InsertItem("SetTriggerScriptBoolVariable");
	InsertItem("SetTriggerScriptIntVariable");
	InsertItem("SetTriggerScriptDoubleVariable");

	InsertItem("GetWaterScriptStringVariable");
	InsertItem("GetWaterScriptBoolVariable");
	InsertItem("GetWaterScriptIntVariable");
	InsertItem("GetWaterScriptDoubleVariable");
	InsertItem("SetWaterScriptStringVariable");
	InsertItem("SetWaterScriptBoolVariable");
	InsertItem("SetWaterScriptIntVariable");
	InsertItem("SetWaterScriptDoubleVariable");

	InsertItem("GetVideoScriptStringVariable");
	InsertItem("GetVideoScriptBoolVariable");
	InsertItem("GetVideoScriptIntVariable");
	InsertItem("GetVideoScriptDoubleVariable");
	InsertItem("SetVideoScriptStringVariable");
	InsertItem("SetVideoScriptBoolVariable");
	InsertItem("SetVideoScriptIntVariable");
	InsertItem("SetVideoScriptDoubleVariable");

	InsertItem("GetAmbientSoundScriptStringVariable");
	InsertItem("GetAmbientSoundScriptBoolVariable");
	InsertItem("GetAmbientSoundScriptIntVariable");
	InsertItem("GetAmbientSoundScriptDoubleVariable");
	InsertItem("SetAmbientSoundScriptStringVariable");
	InsertItem("SetAmbientSoundScriptBoolVariable");
	InsertItem("SetAmbientSoundScriptIntVariable");
	InsertItem("SetAmbientSoundScriptDoubleVariable");

	InsertItem("Get3DSoundScriptStringVariable");
	InsertItem("Get3DSoundScriptBoolVariable");
	InsertItem("Get3DSoundScriptIntVariable");
	InsertItem("Get3DSoundScriptDoubleVariable");
	InsertItem("Set3DSoundScriptStringVariable");
	InsertItem("Set3DSoundScriptBoolVariable");
	InsertItem("Set3DSoundScriptIntVariable");
	InsertItem("Set3DSoundScriptDoubleVariable");

	InsertItem("GetLightScriptStringVariable");
	InsertItem("GetLightScriptBoolVariable");
	InsertItem("GetLightScriptIntVariable");
	InsertItem("GetLightScriptDoubleVariable");
	InsertItem("SetLightScriptStringVariable");
	InsertItem("SetLightScriptBoolVariable");
	InsertItem("SetLightScriptIntVariable");
	InsertItem("SetLightScriptDoubleVariable");

	InsertItem("GetCameraScriptStringVariable");
	InsertItem("GetCameraScriptBoolVariable");
	InsertItem("GetCameraScriptIntVariable");
	InsertItem("GetCameraScriptDoubleVariable");
	InsertItem("SetCameraScriptStringVariable");
	InsertItem("SetCameraScriptBoolVariable");
	InsertItem("SetCameraScriptIntVariable");
	InsertItem("SetCameraScriptDoubleVariable");

	InsertItem("GetMainCharacterScriptStringVariable");
	InsertItem("GetMainCharacterScriptBoolVariable");
	InsertItem("GetMainCharacterScriptIntVariable");
	InsertItem("GetMainCharacterScriptDoubleVariable");
	InsertItem("SetMainCharacterScriptStringVariable");
	InsertItem("SetMainCharacterScriptBoolVariable");
	InsertItem("SetMainCharacterScriptIntVariable");
	InsertItem("SetMainCharacterScriptDoubleVariable");

	InsertItem("ShowGUIButton");
	InsertItem("HideGUIButton");
	InsertItem("ShowGUIImage");
	InsertItem("HideGUIImage");
	InsertItem("ShowGUIText");
	InsertItem("HideGUIText");
	InsertItem("ScaleGUIButton");
	InsertItem("ScaleGUIImage");

	InsertItem("SetGUIButtonPosition");
	InsertItem("SetGUIImagePosition");
	InsertItem("SetGUITextPosition");
	InsertItem("GetGUIButtonPosition");
	InsertItem("GetGUIImagePosition");
	InsertItem("GetGUITextPosition");

	InsertItem("SetGUIPosition");
	InsertItem("GetGUIPosition");

	InsertItem("AddForceToCharacterController");
	InsertItem("AddForceToPrefabInstance");
	InsertItem("AddTorqueToPrefabInstance");

	InsertItem("GetPhysicsActorGroup");
	InsertItem("SetPhysicsCollisionFlags");

	InsertItem("GeneratePrefabInstance");
	InsertItem("DeletePrefabInstance");

	InsertItem("AttachPrefabInstanceToWater");
	InsertItem("DetachPrefabInstanceFromWater");

	InsertItem("PlayVideoLoop");
	InsertItem("PlayVideoOnce");
	InsertItem("StopVideo");

	InsertItem("SetSoundVolume");
	InsertItem("SetSoundPitch");
	InsertItem("SetSoundPlay");
	InsertItem("SetSoundLoop");
	InsertItem("SetSoundPosition");
	InsertItem("SetSoundRollOff");
	InsertItem("SetSoundReferenceDistance");
	InsertItem("SetSoundMaxDistance");

	InsertItem("GetSoundVolume");
	InsertItem("GetSoundPitch");
	InsertItem("GetSoundPlay");
	InsertItem("GetSoundLoop");
	InsertItem("GetSoundPosition");
	InsertItem("GetSoundRollOff");
	InsertItem("GetSoundReferenceDistance");
	InsertItem("GetSoundMaxDistance");

	InsertItem("SetGlobalSoundVolume");
	InsertItem("GetGlobalSoundVolume");
	
	InsertItem("SetVideoPlay");
	InsertItem("SetVideoLoop");
	InsertItem("SetVideoVolume");
	InsertItem("GetVideoPlay");
	InsertItem("GetVideoLoop");
	InsertItem("GetVideoVolume");
	InsertItem("GetVideoDuration");

	m_listFunctions.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
	m_listFunctions.SetSelectionMark(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CVoid CScriptEditorAddFunction::InsertItem(CChar* name)
{
	m_index++;
	int index = m_index;
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
	lvItem.iItem = index;
	lvItem.iImage = 0;
	lvItem.iSubItem = 0;
	lvItem.pszText = name;
	m_listFunctions.InsertItem(&lvItem);

	m_listFunctions.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);
	m_listFunctions.EnsureVisible(index, FALSE);
	m_listFunctions.UpdateWindow();
}

void CScriptEditorAddFunction::OnBnClickedCancel()
{
	if (g_multipleView->m_enableTimer)
		g_multipleView->EnableTimer(CTrue);
	CDialog::OnCancel();
}
