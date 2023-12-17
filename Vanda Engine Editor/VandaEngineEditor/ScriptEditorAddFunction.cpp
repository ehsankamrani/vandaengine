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
	Cpy(PlaySoundLoop, "PlaySoundLoop(string soundObjectName1, string soundObjectName2, ..., string soundObjectNameN)");
	Cpy(PlaySoundOnce, "PlaySoundOnce(string soundObjectName1, string soundObjectName2, ..., string soundObjectNameN)");
	Cpy(PlaySound, "PlaySound(string soundObjectName1, string soundObjectName2, ..., string soundObjectNameN)");
	Cpy(PauseSound, "PauseSound(string soundObjectName1, string soundObjectName2, ..., string soundObjectNameN)");
	Cpy(StopSound, "StopSound(string soundObjectName1, string soundObjectName2, ..., string soundObjectNameN)");

	Cpy(ExecuteCyclicAnimation, "ExecuteCyclicAnimation(string prefabInstanceName, string animationClipName, float weightTarget, float delayIn)");
	Cpy(RemoveCyclicAnimation, "RemoveCyclicAnimation(string prefabInstanceName, string animationClipName, float delayOut)");
	Cpy(ExecuteNonCyclicAnimation, "ExecuteNonCyclicAnimation(string prefabInstanceName, string animationClipName, float delayIn, float delayOut, float weightTarget, bool lock)");
	Cpy(ReverseExecuteNonCyclicAnimation, "ReverseExecuteNonCyclicAnimation(string prefabInstanceName, string animationClipName)");
	Cpy(RemoveNonCyclicAnimation, "RemoveNonCyclicAnimation(string prefabInstanceName, string animationClipName)");
	Cpy(GetAnimationClipDurationOfPrefabInstance, "double GetAnimationClipDurationOfPrefabInstance(string prefabInstanceName, string animationClipName)");
	Cpy(PausePrefabInstanceAnimations, "PausePrefabInstanceAnimations(string prefabInstanceName)");
	Cpy(ResumePrefabInstanceAnimations, "ResumePrefabInstanceAnimations(string prefabInstanceName)");

	Cpy(LoadVScene, "LoadVScene(string VSceneName)");
	Cpy(ExitGame, "ExitGame()");

	Cpy(ActivateThirdPersonCamera, "ActivateThirdPersonCamera()");
	Cpy(ActivateFirstPersonCamera, "ActivateFirstPersonCamera()");
	Cpy(ActivateImportedCamera, "ActivateImportedCamera(string importedCameraFullName, float endTime[optional])");
	Cpy(ActivateImportedCameraOfPrefabInstance, "ActivateImportedCameraOfPrefabInstance(string prefabInstanceName, string prefabCameraName, float endTime[optional])");
	Cpy(ActivateEngineCamera, "ActivateEngineCamera(string engineCameraName, float endTime[optional])");
	Cpy(SetPhysicsCameraAngle, "SetPhysicsCameraAngle(float angleDegree)");
	Cpy(GetPhysicsCameraAngle, "double GetPhysicsCameraAngle()");
	Cpy(SetPhysicsCameraTilt, "SetPhysicsCameraTilt(float tiltDegree)");
	Cpy(SetPhysicsCameraMaxTilt, "SetPhysicsCameraMaxTilt(float maxTiltDegree)");
	Cpy(SetPhysicsCameraMinTilt, "SetPhysicsCameraMinTilt(float minTiltDegree)");
	Cpy(GetPhysicsCameraTilt, "double GetPhysicsCameraTilt()");
	Cpy(GetPhysicsCameraMaxTilt, "double GetPhysicsCameraMaxTilt()");
	Cpy(GetPhysicsCameraMinTilt, "double GetPhysicsCameraMinTilt()");
	Cpy(SetPhysicsCameraYaw, "SetPhysicsCameraYaw(float yawDegree)");
	Cpy(GetPhysicsCameraYaw, "double GetPhysicsCameraYaw()");

	Cpy(LoadResource, "LoadResource(string resourceDirectoryName, string resourceFileName)");
	Cpy(DeleteResource, "DeleteResource(string resourceDirectoryName, string resourceFileName)");
	Cpy(DeleteAllResources, "DeleteAllResources()");
	Cpy(PlayResourceSound, "PlayResourceSound(string resourceDirectoryName_resourceFileName.ogg)");
	Cpy(PlayResourceSoundLoop, "PlayResourceSoundLoop(string resourceDirectoryName_resourceFileName.ogg)");
	Cpy(PlayResourceSoundOnce, "PlayResourceSoundOnce(string resourceDirectoryName_resourceFileName.ogg)");
	Cpy(StopResourceSound, "StopResourceSound(string resourceDirectoryName_resourceFileName.ogg)");
	Cpy(PauseResourceSound, "PauseResourceSound(string resourceDirectoryName_resourceFileName.ogg)");
	Cpy(ShowCursorIcon, "ShowCursorIcon(string resourceDirectoryName_resourceFileName.dds, float cursorSize)");
	Cpy(HideCursorIcon, "HideCursorIcon(string resourceDirectoryName_resourceFileName.dds)");

	Cpy(PrintConsole, "PrintConsole(string message)");

	Cpy(ShowGUI, "ShowGUI(string guiName)");
	Cpy(HideGUI, "HideGUI(string guiName)");

	Cpy(IsKeyDown, "bool IsKeyDown(string DirectInputKeyCode)");

	Cpy(ShowPrefabInstance, "ShowPrefabInstance(string prefabInstanceName)");
	Cpy(HidePrefabInstance, "HidePrefabInstance(string prefabInstanceName)");

	Cpy(SetSelectionDistance, "SetSelectionDistance(float selectionDistance)");
	Cpy(GetSelectionDistance, "double GetSelectionDistance()");
	Cpy(SelectPrefabInstances , "SelectPrefabInstances(double mousePositionX, double mousePositionY, double selectionWidthSize, double selectionHeightSize)");
	Cpy(GetScreenWidth, "int GetScreenWidth()");
	Cpy(GetScreenHeight, "int GetScreenHeight()");
	Cpy(GetCursorX, "double GetCursorX()");
	Cpy(GetCursorY, "double GetCursorY()");
	Cpy(IsCharacterControllerLocked, "bool IsCharacterControllerLocked()");
	Cpy(GetElapsedTime, "double GetElapsedTime()");
	Cpy(GetPrefabInstanceNameFromActor, "string GetPrefabInstanceNameFromActor(string physicsActorName)");

	Cpy(TranslatePrefabInstance, "TranslatePrefabInstance(string prefabInstanceName, float XPosition, float YPosition, float ZPosition)");
	Cpy(RotatePrefabInstance, "RotatePrefabInstance(string prefabInstanceName, float XRotationAngle, float YRotationAngle, float ZRotationAngle)");
	Cpy(ScalePrefabInstance, "ScalePrefabInstance(string prefabInstanceName, float XScale, float YScale, float ZScale)");

	Cpy(GetPrefabInstanceTranslate, "double,double,double GetPrefabInstanceTranslate(string prefabInstanceName)");
	Cpy(GetPrefabInstanceRotate, "double,double,double GetPrefabInstanceRotate(string prefabInstanceName)");
	Cpy(GetPrefabInstanceScale, "double,double,double GetPrefabInstanceScale(string prefabInstanceName)");

	Cpy(GetPrefabInstanceRadius, "double GetPrefabInstanceRadius(string prefabInstanceName)");
	Cpy(GetDistanceOfPrefabInstanceFromPhysicsCamera, "double GetDistanceOfPrefabInstanceFromPhysicsCamera(string prefabInstanceName)");

	Cpy(EnableDepthOfField, "EnableDepthOfField()");
	Cpy(DisableDepthOfField, "DisableDepthOfField()");
	Cpy(SetDepthOfFieldFocalDistance, "SetDepthOfFieldFocalDistance(float focalDistance)");
	Cpy(SetDepthOfFieldFocalRange, "SetDepthOfFieldFocalRange(float focalRange)");

	Cpy(GetDepthOfFieldFocalDistance, "double GetDepthOfFieldFocalDistance()");
	Cpy(GetDepthOfFieldFocalRange, "double GetDepthOfFieldFocalRange()");

	Cpy(EnableFog, "EnableFog()");
	Cpy(DisableFog, "DisableFog()");
	Cpy(SetFogColor, "SetFogColor(float red, float green, float blue)");
	Cpy(SetFogDensity, "SetFogDensity(float density)");

	Cpy(GetFogColor, "double, double, double GetFogColor()");
	Cpy(GetFogDensity, "double GetFogDensity()");

	Cpy(EnableBloom, "EnableBloom()");
	Cpy(DisableBloom, "DisableBloom()");
	Cpy(SetBloomColor, "SetBloomColor(float red, float green, float blue)");
	Cpy(SetBloomIntensity, "SetBloomIntensity(float intensity)");

	Cpy(GetBloomColor, "double, double, double GetBloomColor()");
	Cpy(GetBloomIntensity, "double GetBloomIntensity()");

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

	Cpy(GetLightAmbient, "double,double,double GetLightAmbient(string lightObjectName)");
	Cpy(GetLightDiffuse, "double,double,double GetLightDiffuse(string lightObjectName)");
	Cpy(GetLightSpecular, "double,double,double GetLightSpecular(string lightObjectName)");
	Cpy(GetLightShininess, "double GetLightShininess(string lightObjectName)");

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
	Cpy(SetPhysicsGroundHeight, "SetPhysicsGroundHeight(float height)");
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
	Cpy(GetCharacterControllerPosition, "double,double,double GetCharacterControllerPosition()");

	Cpy(GetDistanceBetweenPhysicsCameraAndCharacterController, "double GetDistanceBetweenPhysicsCameraAndCharacterController()");

	Cpy(GetCharacterControllerCapsuleRadius, "double GetCharacterControllerCapsuleRadius()");
	Cpy(GetCharacterControllerCapsuleHeight, "double GetCharacterControllerCapsuleHeight()");
	Cpy(GetCharacterControllerForcePower, "double GetCharacterControllerForcePower()");
	Cpy(GetCharacterControllerWalkSpeed, "double GetCharacterControllerWalkSpeed()");
	Cpy(GetCharacterControllerRunSpeed, "double GetCharacterControllerRunSpeed()");
	Cpy(GetCharacterControllerStepOffset, "double GetCharacterControllerStepOffset()");
	Cpy(GetCharacterControllerJumpPower, "double GetCharacterControllerJumpPower()");

	Cpy(GetPhysicsDefaultRestitution, "double GetPhysicsDefaultRestitution()");
	Cpy(GetPhysicsDefaultSkinWidth, "double GetPhysicsDefaultSkinWidth()");
	Cpy(GetPhysicsDefaultStaticFriction, "double GetPhysicsDefaultStaticFriction()");
	Cpy(GetPhysicsDefaultDynamicFriction, "double GetPhysicsDefaultDynamicFriction()");
	Cpy(GetPhysicsGravity, "double, double, double GetPhysicsGravity()");
	Cpy(GetPhysicsGroundHeight, "double GetPhysicsGroundHeight()");
	Cpy(GetPhysicsCollisionFlags, "bool GetPhysicsCollisionFlags(string group1, string group2)");

	Cpy(SetMultisamplingValue, "SetMultisamplingValue(int numSamples)");
	Cpy(SetAnisotropicFilteringValue, "SetAnisotropicFilteringValue(int value)");
	Cpy(EnableVSync, "EnableVSync()");
	Cpy(DisableVSync, "DisableVSync()");
	Cpy(EnableGeneralWaterReflection, "EnableGeneralWaterReflection()");
	Cpy(DisableGeneralWaterReflection, "DisableGeneralWaterReflection()");
	Cpy(SetScreenResolution, "SetScreenResolution(int screenWidth)");
	Cpy(SaveGeneralProperties, "SaveGeneralProperties()");
	Cpy(GetMultisamplingValue, "int GetMultisamplingValue()");
	Cpy(GetAnisotropicFilteringValue, "int GetAnisotropicFilteringValue()");
	Cpy(IsVSyncEnabled, "bool IsVSyncEnabled()");
	Cpy(IsGeneralWaterReflectionEnabled, "bool IsGeneralWaterReflectionEnabled()");
	Cpy(GetScreenResolution, "int GetScreenResolution()");

	Cpy(GetVSceneScriptStringVariable, "string GetVSceneScriptStringVariable(string variable)");
	Cpy(GetVSceneScriptBoolVariable, "bool GetVSceneScriptBoolVariable(string variable)");
	Cpy(GetVSceneScriptIntVariable, "int GetVSceneScriptIntVariable(string variable)");
	Cpy(GetVSceneScriptDoubleVariable, "double GetVSceneScriptDoubleVariable(string variable)");
	Cpy(SetVSceneScriptStringVariable, "SetVSceneScriptStringVariable(string variable, string value)");
	Cpy(SetVSceneScriptBoolVariable, "SetVSceneScriptBoolVariable(string variable, bool value)");
	Cpy(SetVSceneScriptIntVariable, "SetVSceneScriptIntVariable(string variable, int value)");
	Cpy(SetVSceneScriptDoubleVariable, "SetVSceneScriptDoubleVariable(string variable, double value)");

	Cpy(GetSkyScriptStringVariable, "string GetSkyScriptStringVariable(string variable)");
	Cpy(GetSkyScriptBoolVariable, "bool GetSkyScriptBoolVariable(string variable)");
	Cpy(GetSkyScriptIntVariable, "int GetSkyScriptIntVariable(string variable)");
	Cpy(GetSkyScriptDoubleVariable, "double GetSkyScriptDoubleVariable(string variable)");
	Cpy(SetSkyScriptStringVariable, "SetSkyScriptStringVariable(string variable, string value)");
	Cpy(SetSkyScriptBoolVariable, "SetSkyScriptBoolVariable(string variable, bool value)");
	Cpy(SetSkyScriptIntVariable, "SetSkyScriptIntVariable(string variable, int value)");
	Cpy(SetSkyScriptDoubleVariable, "SetSkyScriptDoubleVariable(string variable, double value)");

	Cpy(GetTerrainScriptStringVariable, "string GetTerrainScriptStringVariable(string variable)");
	Cpy(GetTerrainScriptBoolVariable, "bool GetTerrainScriptBoolVariable(string variable)");
	Cpy(GetTerrainScriptIntVariable, "int GetTerrainScriptIntVariable(string variable)");
	Cpy(GetTerrainScriptDoubleVariable, "double GetTerrainScriptDoubleVariable(string variable)");
	Cpy(SetTerrainScriptStringVariable, "SetTerrainScriptStringVariable(string variable, string value)");
	Cpy(SetTerrainScriptBoolVariable, "SetTerrainScriptBoolVariable(string variable, bool value)");
	Cpy(SetTerrainScriptIntVariable, "SetTerrainScriptIntVariable(string variable, int value)");
	Cpy(SetTerrainScriptDoubleVariable, "SetTerrainScriptDoubleVariable(string variable, double value)");

	Cpy(GetPrefabInstanceScriptStringVariable, "string GetPrefabInstanceScriptStringVariable(string prefabInstanceName, string variable)");
	Cpy(GetPrefabInstanceScriptBoolVariable, "bool GetPrefabInstanceScriptBoolVariable(string prefabInstanceName, string variable)");
	Cpy(GetPrefabInstanceScriptIntVariable, "int GetPrefabInstanceScriptIntVariable(string prefabInstanceName, string variable)");
	Cpy(GetPrefabInstanceScriptDoubleVariable, "double GetPrefabInstanceScriptDoubleVariable(string prefabInstanceName, string variable)");
	Cpy(SetPrefabInstanceScriptStringVariable, "SetPrefabInstanceScriptStringVariable(string prefabInstanceName, string variable, string value)");
	Cpy(SetPrefabInstanceScriptBoolVariable, "SetPrefabInstanceScriptBoolVariable(string prefabInstanceName, string variable, bool value)");
	Cpy(SetPrefabInstanceScriptIntVariable, "SetPrefabInstanceScriptIntVariable(string prefabInstanceName, string variable, int value)");
	Cpy(SetPrefabInstanceScriptDoubleVariable, "SetPrefabInstanceScriptDoubleVariable(string prefabInstanceName, string variable, double value)");

	Cpy(GetGUIButtonScriptStringVariable, "string GetGUIButtonScriptStringVariable(string GUIName, string buttonName, string variable)");
	Cpy(GetGUIButtonScriptBoolVariable, "bool GetGUIButtonScriptBoolVariable(string GUIName, string buttonName, string variable)");
	Cpy(GetGUIButtonScriptIntVariable, "int GetGUIButtonScriptIntVariable(string GUIName, string buttonName, string variable)");
	Cpy(GetGUIButtonScriptDoubleVariable, "double GetGUIButtonScriptDoubleVariable(string GUIName, string buttonName, string variable)");
	Cpy(SetGUIButtonScriptStringVariable, "SetGUIButtonScriptStringVariable(string GUIName, string buttonName, string variable, string value)");
	Cpy(SetGUIButtonScriptBoolVariable, "SetGUIButtonScriptBoolVariable(string GUIName, string buttonName, string variable, bool value)");
	Cpy(SetGUIButtonScriptIntVariable, "SetGUIButtonScriptIntVariable(string GUIName, string buttonName, vstring variable, int value)");
	Cpy(SetGUIButtonScriptDoubleVariable, "SetGUIButtonScriptDoubleVariable(string GUIName, string buttonName, string variable, double value)");

	Cpy(GetTriggerScriptStringVariable, "string GetTriggerScriptStringVariable(string triggerName, string variable)");
	Cpy(GetTriggerScriptBoolVariable, "bool GetTriggerScriptBoolVariable(string triggerName, string variable)");
	Cpy(GetTriggerScriptIntVariable, "int GetTriggerScriptIntVariable(string triggerName, string variable)");
	Cpy(GetTriggerScriptDoubleVariable, "double GetTriggerScriptDoubleVariable(string triggerName, string variable)");
	Cpy(SetTriggerScriptStringVariable, "SetTriggerScriptStringVariable(string triggerName, string variable, string value)");
	Cpy(SetTriggerScriptBoolVariable, "SetTriggerScriptBoolVariable(string triggerName, string variable, bool value)");
	Cpy(SetTriggerScriptIntVariable, "SetTriggerScriptIntVariable(string triggerName, string variable, int value)");
	Cpy(SetTriggerScriptDoubleVariable, "SetTriggerScriptDoubleVariable(string triggerName, string variable, double value)");

	Cpy(GetWaterScriptStringVariable, "string GetWaterScriptStringVariable(string waterName, string variable)");
	Cpy(GetWaterScriptBoolVariable, "bool GetWaterScriptBoolVariable(string waterName, string variable)");
	Cpy(GetWaterScriptIntVariable, "int GetWaterScriptIntVariable(string waterName, string variable)");
	Cpy(GetWaterScriptDoubleVariable, "double GetWaterScriptDoubleVariable(string waterName, string variable)");
	Cpy(SetWaterScriptStringVariable, "SetWaterScriptStringVariable(string waterName, string variable, string value)");
	Cpy(SetWaterScriptBoolVariable, "SetWaterScriptBoolVariable(string waterName, string variable, bool value)");
	Cpy(SetWaterScriptIntVariable, "SetWaterScriptIntVariable(string waterName, string variable, int value)");
	Cpy(SetWaterScriptDoubleVariable, "SetWaterScriptDoubleVariable(string waterName, string variable, double value)");

	Cpy(GetVideoScriptStringVariable, "string GetVideoScriptStringVariable(string videoName, string variable)");
	Cpy(GetVideoScriptBoolVariable, "bool GetVideoScriptBoolVariable(string videoName, string variable)");
	Cpy(GetVideoScriptIntVariable, "int GetVideoScriptIntVariable(string videoName, string variable)");
	Cpy(GetVideoScriptDoubleVariable, "double GetVideoScriptDoubleVariable(string videoName, string variable)");
	Cpy(SetVideoScriptStringVariable, "SetVideoScriptStringVariable(string videoName, string variable, string value)");
	Cpy(SetVideoScriptBoolVariable, "SetVideoScriptBoolVariable(string videoName, string variable, bool value)");
	Cpy(SetVideoScriptIntVariable, "SetVideoScriptIntVariable(string videoName, string variable, int value)");
	Cpy(SetVideoScriptDoubleVariable, "SetVideoScriptDoubleVariable(string videoName, string variable, double value)");

	Cpy(GetAmbientSoundScriptStringVariable, "string GetAmbientSoundScriptStringVariable(string ambientSoundName, string variable)");
	Cpy(GetAmbientSoundScriptBoolVariable, "bool GetAmbientSoundScriptBoolVariable(string ambientSoundName, string variable)");
	Cpy(GetAmbientSoundScriptIntVariable, "int GetAmbientSoundScriptIntVariable(string ambientSoundName, string variable)");
	Cpy(GetAmbientSoundScriptDoubleVariable, "double GetAmbientSoundScriptDoubleVariable(string ambientSoundName, string variable)");
	Cpy(SetAmbientSoundScriptStringVariable, "SetAmbientSoundScriptStringVariable(string ambientSoundName, string variable, string value)");
	Cpy(SetAmbientSoundScriptBoolVariable, "SetAmbientSoundScriptBoolVariable(string ambientSoundName, string variable, bool value)");
	Cpy(SetAmbientSoundScriptIntVariable, "SetAmbientSoundScriptIntVariable(string ambientSoundName, string variable, int value)");
	Cpy(SetAmbientSoundScriptDoubleVariable, "SetAmbientSoundScriptDoubleVariable(string ambientSoundName, string variable, double value)");

	Cpy(Get3DSoundScriptStringVariable, "string Get3DSoundScriptStringVariable(string 3DSoundName, string variable)");
	Cpy(Get3DSoundScriptBoolVariable, "bool Get3DSoundScriptBoolVariable(string 3DSoundName, string variable)");
	Cpy(Get3DSoundScriptIntVariable, "int Get3DSoundScriptIntVariable(string 3DSoundName, string variable)");
	Cpy(Get3DSoundScriptDoubleVariable, "double Get3DSoundScriptDoubleVariable(string 3DSoundName, string variable)");
	Cpy(Set3DSoundScriptStringVariable, "Set3DSoundScriptStringVariable(string 3DSoundName, string variable, string value)");
	Cpy(Set3DSoundScriptBoolVariable, "Set3DSoundScriptBoolVariable(string 3DSoundName, string variable, bool value)");
	Cpy(Set3DSoundScriptIntVariable, "Set3DSoundScriptIntVariable(string 3DSoundName, string variable, int value)");
	Cpy(Set3DSoundScriptDoubleVariable, "Set3DSoundScriptDoubleVariable(string 3DSoundName, string variable, double value)");

	Cpy(GetLightScriptStringVariable, "string GetLightScriptStringVariable(string lightName, string variable)");
	Cpy(GetLightScriptBoolVariable, "bool GetLightScriptBoolVariable(string lightName, string variable)");
	Cpy(GetLightScriptIntVariable, "int GetLightScriptIntVariable(string lightName, string variable)");
	Cpy(GetLightScriptDoubleVariable, "double GetLightScriptDoubleVariable(string lightName, string variable)");
	Cpy(SetLightScriptStringVariable, "SetLightScriptStringVariable(string lightName, string variable, string value)");
	Cpy(SetLightScriptBoolVariable, "SetLightScriptBoolVariable(string lightName, string variable, bool value)");
	Cpy(SetLightScriptIntVariable, "SetLightScriptIntVariable(string lightName, string variable, int value)");
	Cpy(SetLightScriptDoubleVariable, "SetLightScriptDoubleVariable(string lightName, string variable, double value)");

	Cpy(GetCameraScriptStringVariable, "string GetCameraScriptStringVariable(string cameraName, string variable)");
	Cpy(GetCameraScriptBoolVariable, "bool GetCameraScriptBoolVariable(string cameraName, string variable)");
	Cpy(GetCameraScriptIntVariable, "int GetCameraScriptIntVariable(string cameraName, string variable)");
	Cpy(GetCameraScriptDoubleVariable, "double GetCameraScriptDoubleVariable(string cameraName, string variable)");
	Cpy(SetCameraScriptStringVariable, "SetCameraScriptStringVariable(string cameraName, string variable, string value)");
	Cpy(SetCameraScriptBoolVariable, "SetCameraScriptBoolVariable(string cameraName, string variable, bool value)");
	Cpy(SetCameraScriptIntVariable, "SetCameraScriptIntVariable(string cameraName, string variable, int value)");
	Cpy(SetCameraScriptDoubleVariable, "SetCameraScriptDoubleVariable(string cameraName, string variable, double value)");

	Cpy(GetMainCharacterScriptStringVariable, "string GetMainCharacterScriptStringVariable(string variable)");
	Cpy(GetMainCharacterScriptBoolVariable, "bool GetMainCharacterScriptBoolVariable(string variable)");
	Cpy(GetMainCharacterScriptIntVariable, "int GetMainCharacterScriptIntVariable(string variable)");
	Cpy(GetMainCharacterScriptDoubleVariable, "double GetMainCharacterScriptDoubleVariable(string variable)");
	Cpy(SetMainCharacterScriptStringVariable, "SetMainCharacterScriptStringVariable(string variable, string value)");
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
	Cpy(GetGUIButtonPosition, "int,int GetGUIButtonPosition(string GUIName, string buttonName)");
	Cpy(GetGUIImagePosition, "int,int GetGUIImagePosition(string GUIName, string imageName)");
	Cpy(GetGUITextPosition, "int,int GetGUITextPosition(string GUIName, string textName)");

	Cpy(SetGUIPosition, "SetGUIPosition(string GUIName, int x, int y)");
	Cpy(GetGUIPosition, "int,int GetGUIPosition(string GUIName)");

	Cpy(AddForceToCharacterController, "AddForceToCharacterController(float forceX, float forceY, float forceZ, float forceSpeed, float forceDecreaseValue)");
	Cpy(AddForceToPrefabInstance, "AddForceToPrefabInstance(string prefabInstanceName, float forceX, float forceY, float forceZ, float forcePower)");
	Cpy(AddTorqueToPrefabInstance, "AddTorqueToPrefabInstance(string prefabInstanceName, float torqueX, float torqueY, float torqueZ, float torquePower)");

	Cpy(GetPhysicsActorGroup, "string GetPhysicsActorGroup(string physicsActorName)");
	Cpy(SetPhysicsCollisionFlags, "SetPhysicsCollisionFlags(string group1, string group2, bool flag)");

	Cpy(GeneratePrefabInstance, "GeneratePrefabInstance(string prefabName, float XPos, float YPos, float ZPos, float XRot, float YRot, float ZRot, float XScale, float YScale, float ZScale)");
	Cpy(DeletePrefabInstance, "DeletePrefabInstance(string prefabInstanceName)");

	Cpy(AttachPrefabInstanceToWater, "AttachPrefabInstanceToWater(string prefabInstanceName, string waterObjectName)");
	Cpy(DetachPrefabInstanceFromWater, "DetachPrefabInstanceFromWater(string prefabInstanceName, string waterObjectName)");
	Cpy(PauseWaterAnimation, "PauseWaterAnimation(string waterObjectName)");
	Cpy(ResumeWaterAnimation, "ResumeWaterAnimation(string waterObjectName)");

	Cpy(SetSoundVolume, "SetSoundVolume(string soundObjectName, float volume)");
	Cpy(SetSoundPitch, "SetSoundPitch(string soundObjectName, float pitch)");
	Cpy(SetSoundLoop, "SetSoundLoop(string soundObjectName, bool loop)");
	Cpy(SetSoundPosition, "SetSoundPosition(string 3DSoundObjectName, float x, float y, float z)");
	Cpy(SetSoundRollOff, "SetSoundRollOff(string 3DSoundObjectName, float rollOff)");
	Cpy(SetSoundReferenceDistance, "SetSoundReferenceDistance(string 3DSoundObjectName, float distance)");
	Cpy(SetSoundMaxDistance, "SetSoundMaxDistance(string 3DSoundObjectName, float maxDistance)");

	Cpy(GetSoundVolume, "double GetSoundVolume(string soundObjectName)");
	Cpy(GetSoundPitch, "double GetSoundPitch(string soundObjectName)");
	Cpy(GetSoundPlay, "bool GetSoundPlay(string soundObjectName)");
	Cpy(GetSoundLoop, "bool GetSoundLoop(string soundObjectName)");
	Cpy(GetSoundPosition, "double,double,double GetSoundPosition(string 3DSoundObjectName)");
	Cpy(GetSoundRollOff, "double GetSoundRollOff(string 3DSoundObjectName)");
	Cpy(GetSoundReferenceDistance, "double GetSoundReferenceDistance(string 3DSoundObjectName)");
	Cpy(GetSoundMaxDistance, "double GetSoundMaxDistance(string 3DSoundObjectName)");

	Cpy(SetGlobalSoundVolume, "SetGlobalSoundVolume(float volume)");
	Cpy(GetGlobalSoundVolume, "double GetGlobalSoundVolume()");

	Cpy(PlayVideo, "PlayVideo(string videoName)");
	Cpy(PlayVideoLoop, "PlayVideoLoop(string videoName)");
	Cpy(PlayVideoOnce, "PlayVideoOnce(string videoName)");
	Cpy(StopVideo, "StopVideo(string videoName)");

	Cpy(SetVideoLoop, "SetVideoLoop(string videoName, bool loop)");
	Cpy(SetVideoVolume, "SetVideoVolume(string videoName, float volume)");

	Cpy(GetVideoPlay, "bool GetVideoPlay(string videoName)");
	Cpy(GetVideoLoop, "bool GetVideoLoop(string videoName)");
	Cpy(GetVideoVolume, "double GetVideoVolume(string videoName)");
	Cpy(GetVideoDuration, "double GetVideoDuration(string videoName)");

	//Stop Sounds
	Cpy(StopAllSounds, "StopAllSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(StopAllAmbientSounds, "StopAllAmbientSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(StopAll3DSounds, "StopAll3DSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(StopAllResourceSounds, "StopAllResourceSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	//Play Sounds
	Cpy(PlayAllSounds, "PlayAllSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllAmbientSounds, "PlayAllAmbientSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAll3DSounds, "PlayAll3DSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllResourceSounds, "PlayAllResourceSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllPausedSounds, "PlayAllPausedSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllPausedAmbientSounds, "PlayAllPausedAmbientSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllPaused3DSounds, "PlayAllPaused3DSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllPausedResourceSounds, "PlayAllPausedResourceSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllStoppedSounds, "PlayAllStoppedSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllStoppedAmbientSounds, "PlayAllStoppedAmbientSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllStopped3DSounds, "PlayAllStopped3DSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllStoppedResourceSounds, "PlayAllStoppedResourceSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	
	//Play Sounds loop
	Cpy(PlayAllSoundsLoop, "PlayAllSoundsLoop([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllAmbientSoundsLoop, "PlayAllAmbientSoundsLoop([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAll3DSoundsLoop, "PlayAll3DSoundsLoop([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllResourceSoundsLoop, "PlayAllResourceSoundsLoop([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllPausedSoundsLoop, "PlayAllPausedSoundsLoop([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllPausedAmbientSoundsLoop, "PlayAllPausedAmbientSoundsLoop([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllPaused3DSoundsLoop, "PlayAllPaused3DSoundsLoop([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllPausedResourceSoundsLoop, "PlayAllPausedResourceSoundsLoop([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllStoppedSoundsLoop, "PlayAllStoppedSoundsLoop([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllStoppedAmbientSoundsLoop, "PlayAllStoppedAmbientSoundsLoop([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllStopped3DSoundsLoop, "PlayAllStopped3DSoundsLoop([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllStoppedResourceSoundsLoop, "PlayAllStoppedResourceSoundsLoop([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");

	//Play Sounds once
	Cpy(PlayAllSoundsOnce, "PlayAllSoundsOnce([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllAmbientSoundsOnce, "PlayAllAmbientSoundsOnce([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAll3DSoundsOnce, "PlayAll3DSoundsOnce([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllResourceSoundsOnce, "PlayAllResourceSoundsOnce([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllPausedSoundsOnce, "PlayAllPausedSoundsOnce([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllPausedAmbientSoundsOnce, "PlayAllPausedAmbientSoundsOnce([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllPaused3DSoundsOnce, "PlayAllPaused3DSoundsOnce([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllPausedResourceSoundsOnce, "PlayAllPausedResourceSoundsOnce([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllStoppedSoundsOnce, "PlayAllStoppedSoundsOnce([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllStoppedAmbientSoundsOnce, "PlayAllStoppedAmbientSoundsOnce([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllStopped3DSoundsOnce, "PlayAllStopped3DSoundsOnce([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PlayAllStoppedResourceSoundsOnce, "PlayAllStoppedResourceSoundsOnce([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");

	//Pause Sounds
	Cpy(PauseAllSounds, "PauseAllSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PauseAllAmbientSounds, "PauseAllAmbientSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PauseAll3DSounds, "PauseAll3DSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PauseAllResourceSounds, "PauseAllResourceSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");

	//Pause game 
	Cpy(PauseGame, "PauseGame()");
	Cpy(PauseAllAnimationsOfPrefabInstances, "PauseAllAnimationsOfPrefabInstances([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PauseMainCharacterAnimations, "PauseMainCharacterAnimations()");
	Cpy(PausePhysics, "PausePhysics()");
	Cpy(PauseAnimationOfAllWaters, "PauseAnimationOfAllWaters([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");

	//resume game
	Cpy(ResumeGame, "ResumeGame()");
	Cpy(ResumeAllAnimationsOfPrefabInstances, "ResumeAllAnimationsOfPrefabInstances([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(ResumeMainCharacterAnimations, "ResumeMainCharacterAnimations()");
	Cpy(ResumePhysics, "ResumePhysics()");
	Cpy(ResumeAnimationOfAllWaters, "ResumeAnimationOfAllWaters([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");

	//lock/unlock character
	Cpy(LockCharacterController, "LockCharacterController()");
	Cpy(UnlockCharacterController, "UnlockCharacterController()");

	//menu cursor
	Cpy(ShowMenuCursor, "ShowMenuCursor([optional] int cursorSize)");
	Cpy(HideMenuCursor, "HideMenuCursor()");
	Cpy(SetMenuCursorSize, "SetMenuCursorSize(int cursorSize)");
	Cpy(GetMenuCursorSize, "int GetMenuCursorSize()");

	//Pause script Update event of game objects
	Cpy(PauseAllUpdateEvents, "PauseAllUpdateEvents([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PauseUpdateEventOfAllPrefabInstances, "PauseUpdateEventOfAllPrefabInstances([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PauseUpdateEventOfVSceneScript, "PauseUpdateEventOfVSceneScript()");
	Cpy(PauseUpdateEventOfSky, "PauseUpdateEventOfSky()");
	Cpy(PauseUpdateEventOfAllWaters, "PauseUpdateEventOfAllWaters([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PauseUpdateEventOfAllLights, "PauseUpdateEventOfAllLights([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PauseUpdateEventOfAll3DSounds, "PauseUpdateEventOfAll3DSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PauseUpdateEventOfAllAmbientSounds, "PauseUpdateEventOfAllAmbientSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(PauseUpdateEventOfMainCharacter, "PauseUpdateEventOfMainCharacter()");
	Cpy(PauseUpdateEventOfTerrain, "PauseUpdateEventOfTerrain()");
	Cpy(PauseUpdateEventOfAllEngineCameras, "PauseUpdateEventOfAllEngineCameras([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");

	//Resume script Update event of game objects
	Cpy(ResumeAllUpdateEvents, "ResumeAllUpdateEvents([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(ResumeUpdateEventOfAllPrefabInstances, "ResumeUpdateEventOfAllPrefabInstances([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(ResumeUpdateEventOfVSceneScript, "ResumeUpdateEventOfVSceneScript()");
	Cpy(ResumeUpdateEventOfSky, "ResumeUpdateEventOfSky()");
	Cpy(ResumeUpdateEventOfAllWaters, "ResumeUpdateEventOfAllWaters([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(ResumeUpdateEventOfAllLights, "ResumeUpdateEventOfAllLights([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(ResumeUpdateEventOfAll3DSounds, "ResumeUpdateEventOfAll3DSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(ResumeUpdateEventOfAllAmbientSounds, "ResumeUpdateEventOfAllAmbientSounds([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");
	Cpy(ResumeUpdateEventOfMainCharacter, "ResumeUpdateEventOfMainCharacter()");
	Cpy(ResumeUpdateEventOfTerrain, "ResumeUpdateEventOfTerrain()");
	Cpy(ResumeUpdateEventOfAllEngineCameras, "ResumeUpdateEventOfAllEngineCameras([optional] string exception_1, [optional] string exception_2,..., [optional] string exception_n)");

	//Pause script Update event of individual game objects
	Cpy(PauseUpdateEventOfPrefabInstance, "PauseUpdateEventOfPrefabInstance(string prefabInstanceName)");
	Cpy(PauseUpdateEventOfWater, "PauseUpdateEventOfWater(string waterName)");
	Cpy(PauseUpdateEventOfLight, "PauseUpdateEventOfLight(string lightName)");
	Cpy(PauseUpdateEventOf3DSound, "PauseUpdateEventOf3DSound(string 3DSoundName)");
	Cpy(PauseUpdateEventOfAmbientSound, "PauseUpdateEventOfAmbientSound(string ambientSoundName)");
	Cpy(PauseUpdateEventOfEngineCamera, "PauseUpdateEventOfEngineCamera(string engineCameraName)");

	//Resume script Update event of individual game objects
	Cpy(ResumeUpdateEventOfPrefabInstance, "ResumeUpdateEventOfPrefabInstance(string prefabInstanceName)");
	Cpy(ResumeUpdateEventOfWater, "ResumeUpdateEventOfWater(string waterName)");
	Cpy(ResumeUpdateEventOfLight, "ResumeUpdateEventOfLight(string lightName)");
	Cpy(ResumeUpdateEventOf3DSound, "ResumeUpdateEventOf3DSound(string 3DSoundName)");
	Cpy(ResumeUpdateEventOfAmbientSound, "ResumeUpdateEventOfAmbientSound(string ambientSoundName)");
	Cpy(ResumeUpdateEventOfEngineCamera, "ResumeUpdateEventOfEngineCamera(string engineCameraName)");

	//Terrain
	Cpy(SetTerrainAmbient, "SetTerrainAmbient(float red, float green, float blue)");
	Cpy(SetTerrainDiffuse, "SetTerrainDiffuse(float red, float green, float blue)");
	Cpy(SetTerrainSpecular, "SetTerrainSpecular(float red, float green, float blue)");
	Cpy(SetTerrainShininess, "SetTerrainShininess(float shininess)");

	Cpy(GetTerrainAmbient, "double,double,double GetTerrainAmbient()");
	Cpy(GetTerrainDiffuse, "double,double,double GetTerrainDiffuse()");
	Cpy(GetTerrainSpecular, "double,double,double GetTerrainSpecular()");
	Cpy(GetTerrainShininess, "double GetTerrainShininess()");

	//Engine Camera
	Cpy(SetEngineCameraPosition, "SetEngineCameraPosition(string engineCameraName, float x, float y, float z)");
	Cpy(SetEngineCameraPan, "SetEngineCameraPan(string engineCameraName, float pan)");
	Cpy(SetEngineCameraTilt, "SetEngineCameraTilt(string engineCameraName, float tilt)");
	Cpy(SetEngineCameraNearClipPlane, "SetEngineCameraNearClipPlane(string engineCameraName, float nearClipPlane)");
	Cpy(SetEngineCameraFarClipPlane, "SetEngineCameraFarClipPlane(string engineCameraName, float farClipPlane)");
	Cpy(SetEngineCameraAngle, "SetEngineCameraAngle(string engineCameraName, float angle)");

	Cpy(GetEngineCameraPosition, "double,double,double GetEngineCameraPosition(string engineCameraName)");
	Cpy(GetEngineCameraPan, "double GetEngineCameraPan(string engineCameraName)");
	Cpy(GetEngineCameraTilt, "double GetEngineCameraTilt(string engineCameraName)");
	Cpy(GetEngineCameraNearClipPlane, "double GetEngineCameraNearClipPlane(string engineCameraName)");
	Cpy(GetEngineCameraFarClipPlane, "double GetEngineCameraFarClipPlane(string engineCameraName)");
	Cpy(GetEngineCameraAngle, "double GetEngineCameraAngle(string engineCameraName)");

	//Water
	Cpy(SetWaterPosition, "SetWaterPosition(string waterName, float x, float y, float z)");
	Cpy(SetWaterRotation, "SetWaterRotation(string waterName, float rotationY)");
	Cpy(SetWaterScale, "SetWaterScale(string waterName, float scaleX, float scaleZ)");
	Cpy(SetWaterLightPosition, "SetWaterLightPosition(string waterName, float lx, float ly, float lz)");
	Cpy(SetWaterUnderwaterColor, "SetWaterUnderwaterColor(string waterName, float red, float green, float blue)");
	Cpy(SetWaterUnderwaterFogDensity, "SetWaterUnderwaterFogDensity(string waterName, float density)");
	Cpy(SetWaterTransparency, "SetWaterTransparency(string waterName, float transparency)");
	Cpy(SetWaterFlowSpeed, "SetWaterFlowSpeed(string waterName, float speed)");
	Cpy(SetWaterUV, "SetWaterUV(string waterName, float UV)");
	Cpy(SetWaterVisible, "SetWaterVisible(string waterName)");
	Cpy(SetWaterInvisible, "SetWaterInvisible(string waterName)");
	Cpy(EnableWaterShadow, "EnableWaterShadow(string waterName)");
	Cpy(DisableWaterShadow, "DisableWaterShadow(string waterName)");
	Cpy(EnableWaterSunReflection, "EnableWaterSunReflection(string waterName)");
	Cpy(DisableWaterSunReflection, "DisableWaterSunReflection(string waterName)");

	Cpy(GetWaterPosition, "double,double,double GetWaterPosition(string waterName)");
	Cpy(GetWaterRotation, "double GetWaterRotation(string waterName)");
	Cpy(GetWaterScale, "double,double GetWaterScale(string waterName)");
	Cpy(GetWaterLightPosition, "double,double,double GetWaterLightPosition(string waterName)");
	Cpy(GetWaterUnderwaterColor, "double,double,double GetWaterUnderwaterColor(string waterName)");
	Cpy(GetWaterUnderwaterFogDensity, "double GetWaterUnderwaterFogDensity(string waterName)");
	Cpy(GetWaterTransparency, "double GetWaterTransparency(string waterName)");
	Cpy(GetWaterFlowSpeed, "double GetWaterFlowSpeed(string waterName)");
	Cpy(GetWaterUV, "double GetWaterUV(string waterName)");
	Cpy(IsWaterVisible, "bool IsWaterVisible(string waterName)");
	Cpy(IsWaterShadowEnabled, "bool IsWaterShadowEnabled(string waterName)");
	Cpy(IsWaterSunReflectionEnabled, "bool IsWaterSunReflectionEnabled(string waterName)");

	//Sky
	Cpy(SetSkyPosition, "SetSkyPosition(float x, float y, float z)");
	Cpy(EnableSkyFog, "EnableSkyFog()");
	Cpy(DisableSkyFog, "DisableSkyFog()");

	Cpy(GetSkyPosition, "double,double,double GetSkyPosition()");
	Cpy(IsSkyFogEnabled, "bool IsSkyFogEnabled()");

	//Save/Load
	Cpy(CreateFolder, "CreateFolder(string folderPath)");
	Cpy(RemoveFolder, "RemoveFolder(string folderPath)");
	Cpy(RemoveFile, "RemoveFile(string filePath)");
	Cpy(OpenFileForReading, "OpenFileForReading(string filePath)");
	Cpy(OpenFileForWriting, "OpenFileForWriting(string filePath)");
	Cpy(CloseFile, "CloseFile(string filePath)");
	Cpy(ReadBoolVariableFromFile, "bool ReadBoolVariableFromFile()");
	Cpy(WriteBoolVariableToFile, "WriteBoolVariableToFile(bool value)");
	Cpy(ReadFloatVariableFromFile, "float ReadFloatVariableFromFile()");
	Cpy(WriteFloatVariableToFile, "WriteFloatVariableToFile(float value)");
	Cpy(ReadIntVariableFromFile, "int ReadIntVariableFromFile()");
	Cpy(WriteIntVariableToFile, "WriteIntVariableToFile(int value)");
	Cpy(ReadStringVariableFromFile, "string ReadStringVariableFromFile()");
	Cpy(WriteStringVariableToFile, "WriteStringVariableToFile(string value)");
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
		else if (Cmp(szBuffer, "ExecuteCyclicAnimation"))
		{
			m_richFunctionName.SetWindowTextA(ExecuteCyclicAnimation);
		}
		else if (Cmp(szBuffer, "RemoveCyclicAnimation"))
		{
			m_richFunctionName.SetWindowTextA(RemoveCyclicAnimation);
		}
		else if (Cmp(szBuffer, "ExecuteNonCyclicAnimation"))
		{
			m_richFunctionName.SetWindowTextA(ExecuteNonCyclicAnimation);
		}
		else if (Cmp(szBuffer, "ReverseExecuteNonCyclicAnimation"))
		{
			m_richFunctionName.SetWindowTextA(ReverseExecuteNonCyclicAnimation);
		}
		else if (Cmp(szBuffer, "RemoveNonCyclicAnimation"))
		{
			m_richFunctionName.SetWindowTextA(RemoveNonCyclicAnimation);
		}
		else if (Cmp(szBuffer, "GetAnimationClipDurationOfPrefabInstance"))
		{
			m_richFunctionName.SetWindowTextA(GetAnimationClipDurationOfPrefabInstance);
		}
		else if (Cmp(szBuffer, "PausePrefabInstanceAnimations"))
		{
			m_richFunctionName.SetWindowTextA(PausePrefabInstanceAnimations);
		}
		else if (Cmp(szBuffer, "ResumePrefabInstanceAnimations"))
		{
			m_richFunctionName.SetWindowTextA(ResumePrefabInstanceAnimations);
		}
		else if (Cmp(szBuffer, "LoadVScene"))
		{
			m_richFunctionName.SetWindowTextA(LoadVScene);
		}
		else if (Cmp(szBuffer, "ExitGame"))
		{
			m_richFunctionName.SetWindowTextA(ExitGame);
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
		else if (Cmp(szBuffer, "PlayResourceSound"))
		{
			m_richFunctionName.SetWindowTextA(PlayResourceSound);
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
		else if (Cmp(szBuffer, "IsCharacterControllerLocked"))
		{
			m_richFunctionName.SetWindowTextA(IsCharacterControllerLocked);
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
		else if (Cmp(szBuffer, "GetDepthOfFieldFocalDistance"))
		{
			m_richFunctionName.SetWindowTextA(GetDepthOfFieldFocalDistance);
		}
		else if (Cmp(szBuffer, "GetDepthOfFieldFocalRange"))
		{
			m_richFunctionName.SetWindowTextA(GetDepthOfFieldFocalRange);
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
		else if (Cmp(szBuffer, "GetFogColor"))
		{
			m_richFunctionName.SetWindowTextA(GetFogColor);
		}
		else if (Cmp(szBuffer, "GetFogDensity"))
		{
			m_richFunctionName.SetWindowTextA(GetFogDensity);
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
		else if (Cmp(szBuffer, "GetBloomColor"))
		{
			m_richFunctionName.SetWindowTextA(GetBloomColor);
		}
		else if (Cmp(szBuffer, "GetBloomIntensity"))
		{
			m_richFunctionName.SetWindowTextA(GetBloomIntensity);
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
		else if (Cmp(szBuffer, "GetLightAmbient"))
		{
			m_richFunctionName.SetWindowTextA(GetLightAmbient);
		}
		else if (Cmp(szBuffer, "GetLightDiffuse"))
		{
			m_richFunctionName.SetWindowTextA(GetLightDiffuse);
		}
		else if (Cmp(szBuffer, "GetLightSpecular"))
		{
			m_richFunctionName.SetWindowTextA(GetLightSpecular);
		}
		else if (Cmp(szBuffer, "GetLightShininess"))
		{
			m_richFunctionName.SetWindowTextA(GetLightShininess);
		}
		if (Cmp(szBuffer, "SetPrefabInstanceAmbient"))
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
		else if (Cmp(szBuffer, "SetPhysicsGroundHeight"))
		{
			m_richFunctionName.SetWindowTextA(SetPhysicsGroundHeight);
		}
		else if (Cmp(szBuffer, "SetDistanceBetweenPhysicsCameraAndCharacterController"))
		{
			m_richFunctionName.SetWindowTextA(SetDistanceBetweenPhysicsCameraAndCharacterController);
		}
		else if (Cmp(szBuffer, "GetDistanceBetweenPhysicsCameraAndCharacterController"))
		{
			m_richFunctionName.SetWindowTextA(GetDistanceBetweenPhysicsCameraAndCharacterController);
		}
		else if (Cmp(szBuffer, "GetPhysicsDefaultRestitution"))
		{
			m_richFunctionName.SetWindowTextA(GetPhysicsDefaultRestitution);
		}
		else if (Cmp(szBuffer, "GetPhysicsDefaultSkinWidth"))
		{
			m_richFunctionName.SetWindowTextA(GetPhysicsDefaultSkinWidth);
		}
		else if (Cmp(szBuffer, "GetPhysicsDefaultStaticFriction"))
		{
			m_richFunctionName.SetWindowTextA(GetPhysicsDefaultStaticFriction);
		}
		else if (Cmp(szBuffer, "GetPhysicsDefaultDynamicFriction"))
		{
			m_richFunctionName.SetWindowTextA(GetPhysicsDefaultDynamicFriction);
		}
		else if (Cmp(szBuffer, "GetPhysicsGravity"))
		{
			m_richFunctionName.SetWindowTextA(GetPhysicsGravity);
		}
		else if (Cmp(szBuffer, "GetPhysicsGroundHeight"))
		{
			m_richFunctionName.SetWindowTextA(GetPhysicsGroundHeight);
		}
		else if (Cmp(szBuffer, "GetPhysicsCollisionFlags"))
		{
			m_richFunctionName.SetWindowTextA(GetPhysicsCollisionFlags);
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
		else if (Cmp(szBuffer, "SetCharacterControllerPosition"))
		{
			m_richFunctionName.SetWindowTextA(SetCharacterControllerPosition);
		}
		else if (Cmp(szBuffer, "GetCharacterControllerPosition"))
		{
			m_richFunctionName.SetWindowTextA(GetCharacterControllerPosition);
		}
		else if (Cmp(szBuffer, "SetMultisamplingValue"))
		{
			m_richFunctionName.SetWindowTextA(SetMultisamplingValue);
		}
		else if (Cmp(szBuffer, "SetAnisotropicFilteringValue"))
		{
			m_richFunctionName.SetWindowTextA(SetAnisotropicFilteringValue);
		}
		else if (Cmp(szBuffer, "EnableVSync"))
		{
			m_richFunctionName.SetWindowTextA(EnableVSync);
		}
		else if (Cmp(szBuffer, "DisableVSync"))
		{
			m_richFunctionName.SetWindowTextA(DisableVSync);
		}
		else if (Cmp(szBuffer, "EnableGeneralWaterReflection"))
		{
			m_richFunctionName.SetWindowTextA(EnableGeneralWaterReflection);
		}
		else if (Cmp(szBuffer, "DisableGeneralWaterReflection"))
		{
			m_richFunctionName.SetWindowTextA(DisableGeneralWaterReflection);
		}
		else if (Cmp(szBuffer, "SetScreenResolution"))
		{
			m_richFunctionName.SetWindowTextA(SetScreenResolution);
		}
		else if (Cmp(szBuffer, "SaveGeneralProperties"))
		{
			m_richFunctionName.SetWindowTextA(SaveGeneralProperties);
		}
		else if (Cmp(szBuffer, "GetMultisamplingValue"))
		{
			m_richFunctionName.SetWindowTextA(GetMultisamplingValue);
		}
		else if (Cmp(szBuffer, "GetAnisotropicFilteringValue"))
		{
			m_richFunctionName.SetWindowTextA(GetAnisotropicFilteringValue);
		}
		else if (Cmp(szBuffer, "IsVSyncEnabled"))
		{
			m_richFunctionName.SetWindowTextA(IsVSyncEnabled);
		}
		else if (Cmp(szBuffer, "IsGeneralWaterReflectionEnabled"))
		{
			m_richFunctionName.SetWindowTextA(IsGeneralWaterReflectionEnabled);
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
		else if (Cmp(szBuffer, "PauseWaterAnimation"))
		{
			m_richFunctionName.SetWindowTextA(PauseWaterAnimation);
		}
		else if (Cmp(szBuffer, "ResumeWaterAnimation"))
		{
			m_richFunctionName.SetWindowTextA(ResumeWaterAnimation);
		}

		if (Cmp(szBuffer, "SetSoundVolume"))
		{
			m_richFunctionName.SetWindowTextA(SetSoundVolume);
		}
		else if (Cmp(szBuffer, "SetSoundPitch"))
		{
			m_richFunctionName.SetWindowTextA(SetSoundPitch);
		}
		else if (Cmp(szBuffer, "PlaySound"))
		{
			m_richFunctionName.SetWindowTextA(PlaySound);
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
		else if (Cmp(szBuffer, "PlayVideo"))
		{
			m_richFunctionName.SetWindowTextA(PlayVideo);
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
		else if (Cmp(szBuffer, "StopAllSounds"))
		{
			m_richFunctionName.SetWindowTextA(StopAllSounds);
		}
		else if (Cmp(szBuffer, "StopAllAmbientSounds"))
		{
			m_richFunctionName.SetWindowTextA(StopAllAmbientSounds);
		}
		else if (Cmp(szBuffer, "StopAll3DSounds"))
		{
			m_richFunctionName.SetWindowTextA(StopAll3DSounds);
		}
		else if (Cmp(szBuffer, "StopAllResourceSounds"))
		{
			m_richFunctionName.SetWindowTextA(StopAllResourceSounds);
		}
		else if (Cmp(szBuffer, "PlayAllSounds"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllSounds);
		}
		else if (Cmp(szBuffer, "PlayAllPausedSounds"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllPausedSounds);
		}
		else if (Cmp(szBuffer, "PlayAllStoppedSounds"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllStoppedSounds);
		}
		else if (Cmp(szBuffer, "PlayAllAmbientSounds"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllAmbientSounds);
		}
		else if (Cmp(szBuffer, "PlayAll3DSounds"))
		{
			m_richFunctionName.SetWindowTextA(PlayAll3DSounds);
		}
		else if (Cmp(szBuffer, "PlayAllResourceSounds"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllResourceSounds);
		}
		else if (Cmp(szBuffer, "PlayAllStoppedAmbientSounds"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllStoppedAmbientSounds);
		}
		else if (Cmp(szBuffer, "PlayAllStopped3DSounds"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllStopped3DSounds);
		}
		else if (Cmp(szBuffer, "PlayAllStoppedResourceSounds"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllStoppedResourceSounds);
		}
		else if (Cmp(szBuffer, "PlayAllPausedAmbientSounds"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllPausedAmbientSounds);
		}
		else if (Cmp(szBuffer, "PlayAllPaused3DSounds"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllPaused3DSounds);
		}
		else if (Cmp(szBuffer, "PlayAllPausedResourceSounds"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllPausedResourceSounds);
		}
		else if (Cmp(szBuffer, "PlayAllSoundsLoop"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllSoundsLoop);
		}
		else if (Cmp(szBuffer, "PlayAllPausedSoundsLoop"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllPausedSoundsLoop);
		}
		else if (Cmp(szBuffer, "PlayAllStoppedSoundsLoop"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllStoppedSoundsLoop);
		}
		else if (Cmp(szBuffer, "PlayAllAmbientSoundsLoop"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllAmbientSoundsLoop);
		}
		else if (Cmp(szBuffer, "PlayAll3DSoundsLoop"))
		{
			m_richFunctionName.SetWindowTextA(PlayAll3DSoundsLoop);
		}
		else if (Cmp(szBuffer, "PlayAllResourceSoundsLoop"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllResourceSoundsLoop);
		}
		else if (Cmp(szBuffer, "PlayAllStoppedAmbientSoundsLoop"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllStoppedAmbientSoundsLoop);
		}
		else if (Cmp(szBuffer, "PlayAllStopped3DSoundsLoop"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllStopped3DSoundsLoop);
		}
		else if (Cmp(szBuffer, "PlayAllStoppedResourceSoundsLoop"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllStoppedResourceSoundsLoop);
		}
		else if (Cmp(szBuffer, "PlayAllPausedAmbientSoundsLoop"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllPausedAmbientSoundsLoop);
		}
		else if (Cmp(szBuffer, "PlayAllPaused3DSoundsLoop"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllPaused3DSoundsLoop);
		}
		else if (Cmp(szBuffer, "PlayAllPausedResourceSoundsLoop"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllPausedResourceSoundsLoop);
		}
		else if (Cmp(szBuffer, "PlayAllSoundsOnce"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllSoundsOnce);
		}
		else if (Cmp(szBuffer, "PlayAllPausedSoundsOnce"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllPausedSoundsOnce);
		}
		else if (Cmp(szBuffer, "PlayAllStoppedSoundsOnce"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllStoppedSoundsOnce);
		}
		else if (Cmp(szBuffer, "PlayAllAmbientSoundsOnce"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllAmbientSoundsOnce);
		}
		else if (Cmp(szBuffer, "PlayAll3DSoundsOnce"))
		{
			m_richFunctionName.SetWindowTextA(PlayAll3DSoundsOnce);
		}
		else if (Cmp(szBuffer, "PlayAllResourceSoundsOnce"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllResourceSoundsOnce);
		}
		else if (Cmp(szBuffer, "PlayAllStoppedAmbientSoundsOnce"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllStoppedAmbientSoundsOnce);
		}
		else if (Cmp(szBuffer, "PlayAllStopped3DSoundsOnce"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllStopped3DSoundsOnce);
		}
		else if (Cmp(szBuffer, "PlayAllStoppedResourceSoundsOnce"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllStoppedResourceSoundsOnce);
		}
		else if (Cmp(szBuffer, "PlayAllPausedAmbientSoundsOnce"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllPausedAmbientSoundsOnce);
		}
		else if (Cmp(szBuffer, "PlayAllPaused3DSoundsOnce"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllPaused3DSoundsOnce);
		}
		else if (Cmp(szBuffer, "PlayAllPausedResourceSoundsOnce"))
		{
			m_richFunctionName.SetWindowTextA(PlayAllPausedResourceSoundsOnce);
		}
		else if (Cmp(szBuffer, "PauseAllSounds"))
		{
			m_richFunctionName.SetWindowTextA(PauseAllSounds);
		}
		else if (Cmp(szBuffer, "PauseAllAmbientSounds"))
		{
			m_richFunctionName.SetWindowTextA(PauseAllAmbientSounds);
		}
		else if (Cmp(szBuffer, "PauseAll3DSounds"))
		{
			m_richFunctionName.SetWindowTextA(PauseAll3DSounds);
		}
		else if (Cmp(szBuffer, "PauseAllResourceSounds"))
		{
			m_richFunctionName.SetWindowTextA(PauseAllResourceSounds);
		}
		else if (Cmp(szBuffer, "PauseGame"))
		{
			m_richFunctionName.SetWindowTextA(PauseGame);
		}
		else if (Cmp(szBuffer, "PauseAllAnimationsOfPrefabInstances"))
		{
			m_richFunctionName.SetWindowTextA(PauseAllAnimationsOfPrefabInstances);
		}
		else if (Cmp(szBuffer, "PauseMainCharacterAnimations"))
		{
			m_richFunctionName.SetWindowTextA(PauseMainCharacterAnimations);
		}
		else if (Cmp(szBuffer, "PausePhysics"))
		{
			m_richFunctionName.SetWindowTextA(PausePhysics);
		}
		else if (Cmp(szBuffer, "PauseAnimationOfAllWaters"))
		{
			m_richFunctionName.SetWindowTextA(PauseAnimationOfAllWaters);
		}
		else if (Cmp(szBuffer, "ResumeGame"))
		{
			m_richFunctionName.SetWindowTextA(ResumeGame);
		}
		else if (Cmp(szBuffer, "ResumeAllAnimationsOfPrefabInstances"))
		{
			m_richFunctionName.SetWindowTextA(ResumeAllAnimationsOfPrefabInstances);
		}
		else if (Cmp(szBuffer, "ResumeMainCharacterAnimations"))
		{
			m_richFunctionName.SetWindowTextA(ResumeMainCharacterAnimations);
		}
		else if (Cmp(szBuffer, "ResumePhysics"))
		{
			m_richFunctionName.SetWindowTextA(ResumePhysics);
		}
		else if (Cmp(szBuffer, "ResumeAnimationOfAllWaters"))
		{
			m_richFunctionName.SetWindowTextA(ResumeAnimationOfAllWaters);
		}
		else if (Cmp(szBuffer, "LockCharacterController"))
		{
			m_richFunctionName.SetWindowTextA(LockCharacterController);
		}
		else if (Cmp(szBuffer, "UnlockCharacterController"))
		{
			m_richFunctionName.SetWindowTextA(UnlockCharacterController);
		}
		else if (Cmp(szBuffer, "ShowMenuCursor"))
		{
			m_richFunctionName.SetWindowTextA(ShowMenuCursor);
		}
		else if (Cmp(szBuffer, "HideMenuCursor"))
		{
			m_richFunctionName.SetWindowTextA(HideMenuCursor);
		}
		else if (Cmp(szBuffer, "SetMenuCursorSize"))
		{
			m_richFunctionName.SetWindowTextA(SetMenuCursorSize);
		}
		else if (Cmp(szBuffer, "GetMenuCursorSize"))
		{
			m_richFunctionName.SetWindowTextA(GetMenuCursorSize);
		}
		else if (Cmp(szBuffer, "PauseAllUpdateEvents"))
		{
			m_richFunctionName.SetWindowTextA(PauseAllUpdateEvents);
		}
		else if (Cmp(szBuffer, "PauseUpdateEventOfAllPrefabInstances"))
		{
			m_richFunctionName.SetWindowTextA(PauseUpdateEventOfAllPrefabInstances);
		}
		else if (Cmp(szBuffer, "PauseUpdateEventOfVSceneScript"))
		{
			m_richFunctionName.SetWindowTextA(PauseUpdateEventOfVSceneScript);
		}
		else if (Cmp(szBuffer, "PauseUpdateEventOfSky"))
		{
			m_richFunctionName.SetWindowTextA(PauseUpdateEventOfSky);
		}
		else if (Cmp(szBuffer, "PauseUpdateEventOfAllWaters"))
		{
			m_richFunctionName.SetWindowTextA(PauseUpdateEventOfAllWaters);
		}
		else if (Cmp(szBuffer, "PauseUpdateEventOfAllLights"))
		{
			m_richFunctionName.SetWindowTextA(PauseUpdateEventOfAllLights);
		}
		else if (Cmp(szBuffer, "PauseUpdateEventOfAll3DSounds"))
		{
			m_richFunctionName.SetWindowTextA(PauseUpdateEventOfAll3DSounds);
		}
		else if (Cmp(szBuffer, "PauseUpdateEventOfAllAmbientSounds"))
		{
			m_richFunctionName.SetWindowTextA(PauseUpdateEventOfAllAmbientSounds);
		}
		else if (Cmp(szBuffer, "PauseUpdateEventOfMainCharacter"))
		{
			m_richFunctionName.SetWindowTextA(PauseUpdateEventOfMainCharacter);
		}
		else if (Cmp(szBuffer, "PauseUpdateEventOfTerrain"))
		{
			m_richFunctionName.SetWindowTextA(PauseUpdateEventOfTerrain);
		}
		else if (Cmp(szBuffer, "PauseUpdateEventOfAllEngineCameras"))
		{
			m_richFunctionName.SetWindowTextA(PauseUpdateEventOfAllEngineCameras);
		}
		else if (Cmp(szBuffer, "ResumeAllUpdateEvents"))
		{
			m_richFunctionName.SetWindowTextA(ResumeAllUpdateEvents);
		}
		else if (Cmp(szBuffer, "ResumeUpdateEventOfAllPrefabInstances"))
		{
			m_richFunctionName.SetWindowTextA(ResumeUpdateEventOfAllPrefabInstances);
		}
		else if (Cmp(szBuffer, "ResumeUpdateEventOfVSceneScript"))
		{
			m_richFunctionName.SetWindowTextA(ResumeUpdateEventOfVSceneScript);
		}
		else if (Cmp(szBuffer, "ResumeUpdateEventOfSky"))
		{
			m_richFunctionName.SetWindowTextA(ResumeUpdateEventOfSky);
		}
		else if (Cmp(szBuffer, "ResumeUpdateEventOfAllWaters"))
		{
			m_richFunctionName.SetWindowTextA(ResumeUpdateEventOfAllWaters);
		}
		else if (Cmp(szBuffer, "ResumeUpdateEventOfAllLights"))
		{
			m_richFunctionName.SetWindowTextA(ResumeUpdateEventOfAllLights);
		}
		else if (Cmp(szBuffer, "ResumeUpdateEventOfAll3DSounds"))
		{
			m_richFunctionName.SetWindowTextA(ResumeUpdateEventOfAll3DSounds);
		}
		else if (Cmp(szBuffer, "ResumeUpdateEventOfAllAmbientSounds"))
		{
			m_richFunctionName.SetWindowTextA(ResumeUpdateEventOfAllAmbientSounds);
		}
		else if (Cmp(szBuffer, "ResumeUpdateEventOfMainCharacter"))
		{
			m_richFunctionName.SetWindowTextA(ResumeUpdateEventOfMainCharacter);
		}
		else if (Cmp(szBuffer, "ResumeUpdateEventOfTerrain"))
		{
			m_richFunctionName.SetWindowTextA(ResumeUpdateEventOfTerrain);
		}
		else if (Cmp(szBuffer, "ResumeUpdateEventOfAllEngineCameras"))
		{
			m_richFunctionName.SetWindowTextA(ResumeUpdateEventOfAllEngineCameras);
		}
		if (Cmp(szBuffer, "PauseUpdateEventOfPrefabInstance"))
		{
			m_richFunctionName.SetWindowTextA(PauseUpdateEventOfPrefabInstance);
		}
		else if (Cmp(szBuffer, "PauseUpdateEventOfWater"))
		{
			m_richFunctionName.SetWindowTextA(PauseUpdateEventOfWater);
		}
		else if (Cmp(szBuffer, "PauseUpdateEventOfLight"))
		{
			m_richFunctionName.SetWindowTextA(PauseUpdateEventOfLight);
		}
		else if (Cmp(szBuffer, "PauseUpdateEventOf3DSound"))
		{
			m_richFunctionName.SetWindowTextA(PauseUpdateEventOf3DSound);
		}
		else if (Cmp(szBuffer, "PauseUpdateEventOfAmbientSound"))
		{
			m_richFunctionName.SetWindowTextA(PauseUpdateEventOfAmbientSound);
		}
		else if (Cmp(szBuffer, "PauseUpdateEventOfEngineCamera"))
		{
			m_richFunctionName.SetWindowTextA(PauseUpdateEventOfEngineCamera);
		}
		else if (Cmp(szBuffer, "ResumeUpdateEventOfPrefabInstance"))
		{
			m_richFunctionName.SetWindowTextA(ResumeUpdateEventOfPrefabInstance);
		}
		else if (Cmp(szBuffer, "ResumeUpdateEventOfWater"))
		{
			m_richFunctionName.SetWindowTextA(ResumeUpdateEventOfWater);
		}
		else if (Cmp(szBuffer, "ResumeUpdateEventOfLight"))
		{
			m_richFunctionName.SetWindowTextA(ResumeUpdateEventOfLight);
		}
		else if (Cmp(szBuffer, "ResumeUpdateEventOf3DSound"))
		{
			m_richFunctionName.SetWindowTextA(ResumeUpdateEventOf3DSound);
		}
		else if (Cmp(szBuffer, "ResumeUpdateEventOfAmbientSound"))
		{
			m_richFunctionName.SetWindowTextA(ResumeUpdateEventOfAmbientSound);
		}
		else if (Cmp(szBuffer, "ResumeUpdateEventOfEngineCamera"))
		{
			m_richFunctionName.SetWindowTextA(ResumeUpdateEventOfEngineCamera);
		}
		else if (Cmp(szBuffer, "SetTerrainAmbient"))
		{
			m_richFunctionName.SetWindowTextA(SetTerrainAmbient);
		}
		else if (Cmp(szBuffer, "SetTerrainDiffuse"))
		{
			m_richFunctionName.SetWindowTextA(SetTerrainDiffuse);
		}
		else if (Cmp(szBuffer, "SetTerrainSpecular"))
		{
			m_richFunctionName.SetWindowTextA(SetTerrainSpecular);
		}
		else if (Cmp(szBuffer, "SetTerrainShininess"))
		{
			m_richFunctionName.SetWindowTextA(SetTerrainShininess);
		}
		else if (Cmp(szBuffer, "GetTerrainAmbient"))
		{
			m_richFunctionName.SetWindowTextA(GetTerrainAmbient);
		}
		else if (Cmp(szBuffer, "GetTerrainDiffuse"))
		{
			m_richFunctionName.SetWindowTextA(GetTerrainDiffuse);
		}
		else if (Cmp(szBuffer, "GetTerrainSpecular"))
		{
			m_richFunctionName.SetWindowTextA(GetTerrainSpecular);
		}
		else if (Cmp(szBuffer, "GetTerrainShininess"))
		{
			m_richFunctionName.SetWindowTextA(GetTerrainShininess);
		}
		else if (Cmp(szBuffer, "SetEngineCameraPosition"))
		{
			m_richFunctionName.SetWindowTextA(SetEngineCameraPosition);
		}
		else if (Cmp(szBuffer, "SetEngineCameraPan"))
		{
			m_richFunctionName.SetWindowTextA(SetEngineCameraPan);
		}
		else if (Cmp(szBuffer, "SetEngineCameraTilt"))
		{
			m_richFunctionName.SetWindowTextA(SetEngineCameraTilt);
		}
		else if (Cmp(szBuffer, "SetEngineCameraNearClipPlane"))
		{
			m_richFunctionName.SetWindowTextA(SetEngineCameraNearClipPlane);
		}
		else if (Cmp(szBuffer, "SetEngineCameraFarClipPlane"))
		{
			m_richFunctionName.SetWindowTextA(SetEngineCameraFarClipPlane);
		}
		else if (Cmp(szBuffer, "SetEngineCameraAngle"))
		{
			m_richFunctionName.SetWindowTextA(SetEngineCameraAngle);
		}
		else if (Cmp(szBuffer, "GetEngineCameraPosition"))
		{
			m_richFunctionName.SetWindowTextA(GetEngineCameraPosition);
		}
		else if (Cmp(szBuffer, "GetEngineCameraPan"))
		{
			m_richFunctionName.SetWindowTextA(GetEngineCameraPan);
		}
		else if (Cmp(szBuffer, "GetEngineCameraTilt"))
		{
			m_richFunctionName.SetWindowTextA(GetEngineCameraTilt);
		}
		else if (Cmp(szBuffer, "GetEngineCameraNearClipPlane"))
		{
			m_richFunctionName.SetWindowTextA(GetEngineCameraNearClipPlane);
		}
		else if (Cmp(szBuffer, "GetEngineCameraFarClipPlane"))
		{
			m_richFunctionName.SetWindowTextA(GetEngineCameraFarClipPlane);
		}
		else if (Cmp(szBuffer, "GetEngineCameraAngle"))
		{
			m_richFunctionName.SetWindowTextA(GetEngineCameraAngle);
		}
		else if (Cmp(szBuffer, "SetWaterPosition"))
		{
			m_richFunctionName.SetWindowTextA(SetWaterPosition);
		}
		else if (Cmp(szBuffer, "SetWaterRotation"))
		{
			m_richFunctionName.SetWindowTextA(SetWaterRotation);
		}
		else if (Cmp(szBuffer, "SetWaterScale"))
		{
			m_richFunctionName.SetWindowTextA(SetWaterScale);
		}
		else if (Cmp(szBuffer, "SetWaterLightPosition"))
		{
			m_richFunctionName.SetWindowTextA(SetWaterLightPosition);
		}
		else if (Cmp(szBuffer, "SetWaterUnderwaterColor"))
		{
			m_richFunctionName.SetWindowTextA(SetWaterUnderwaterColor);
		}
		else if (Cmp(szBuffer, "SetWaterUnderwaterFogDensity"))
		{
			m_richFunctionName.SetWindowTextA(SetWaterUnderwaterFogDensity);
		}
		else if (Cmp(szBuffer, "SetWaterTransparency"))
		{
			m_richFunctionName.SetWindowTextA(SetWaterTransparency);
		}
		else if (Cmp(szBuffer, "SetWaterFlowSpeed"))
		{
			m_richFunctionName.SetWindowTextA(SetWaterFlowSpeed);
		}
		else if (Cmp(szBuffer, "SetWaterUV"))
		{
			m_richFunctionName.SetWindowTextA(SetWaterUV);
		}
		else if (Cmp(szBuffer, "SetWaterVisible"))
		{
			m_richFunctionName.SetWindowTextA(SetWaterVisible);
		}
		else if (Cmp(szBuffer, "SetWaterInvisible"))
		{
			m_richFunctionName.SetWindowTextA(SetWaterInvisible);
		}
		else if (Cmp(szBuffer, "EnableWaterShadow"))
		{
			m_richFunctionName.SetWindowTextA(EnableWaterShadow);
		}
		else if (Cmp(szBuffer, "DisableWaterShadow"))
		{
			m_richFunctionName.SetWindowTextA(DisableWaterShadow);
		}
		else if (Cmp(szBuffer, "EnableWaterSunReflection"))
		{
			m_richFunctionName.SetWindowTextA(EnableWaterSunReflection);
		}
		else if (Cmp(szBuffer, "DisableWaterSunReflection"))
		{
			m_richFunctionName.SetWindowTextA(DisableWaterSunReflection);
		}
		else if (Cmp(szBuffer, "GetWaterPosition"))
		{
			m_richFunctionName.SetWindowTextA(GetWaterPosition);
		}
		else if (Cmp(szBuffer, "GetWaterRotation"))
		{
			m_richFunctionName.SetWindowTextA(GetWaterRotation);
		}
		else if (Cmp(szBuffer, "GetWaterScale"))
		{
			m_richFunctionName.SetWindowTextA(GetWaterScale);
		}
		else if (Cmp(szBuffer, "GetWaterLightPosition"))
		{
			m_richFunctionName.SetWindowTextA(GetWaterLightPosition);
		}
		else if (Cmp(szBuffer, "GetWaterUnderwaterColor"))
		{
			m_richFunctionName.SetWindowTextA(GetWaterUnderwaterColor);
		}
		else if (Cmp(szBuffer, "GetWaterUnderwaterFogDensity"))
		{
			m_richFunctionName.SetWindowTextA(GetWaterUnderwaterFogDensity);
		}
		else if (Cmp(szBuffer, "GetWaterTransparency"))
		{
			m_richFunctionName.SetWindowTextA(GetWaterTransparency);
		}
		else if (Cmp(szBuffer, "GetWaterFlowSpeed"))
		{
			m_richFunctionName.SetWindowTextA(GetWaterFlowSpeed);
		}
		else if (Cmp(szBuffer, "GetWaterUV"))
		{
			m_richFunctionName.SetWindowTextA(GetWaterUV);
		}
		else if (Cmp(szBuffer, "IsWaterVisible"))
		{
			m_richFunctionName.SetWindowTextA(IsWaterVisible);
		}
		else if (Cmp(szBuffer, "IsWaterShadowEnabled"))
		{
			m_richFunctionName.SetWindowTextA(IsWaterShadowEnabled);
		}
		else if (Cmp(szBuffer, "IsWaterSunReflectionEnabled"))
		{
			m_richFunctionName.SetWindowTextA(IsWaterSunReflectionEnabled);
		}
		else if (Cmp(szBuffer, "SetSkyPosition"))
		{
			m_richFunctionName.SetWindowTextA(SetSkyPosition);
		}
		else if (Cmp(szBuffer, "EnableSkyFog"))
		{
			m_richFunctionName.SetWindowTextA(EnableSkyFog);
		}
		else if (Cmp(szBuffer, "DisableSkyFog"))
		{
			m_richFunctionName.SetWindowTextA(DisableSkyFog);
		}
		else if (Cmp(szBuffer, "GetSkyPosition"))
		{
			m_richFunctionName.SetWindowTextA(GetSkyPosition);
		}
		else if (Cmp(szBuffer, "IsSkyFogEnabled"))
		{
			m_richFunctionName.SetWindowTextA(IsSkyFogEnabled);
		}
		else if (Cmp(szBuffer, "CreateFolder"))
		{
			m_richFunctionName.SetWindowTextA(CreateFolder);
		}
		else if (Cmp(szBuffer, "RemoveFolder"))
		{
			m_richFunctionName.SetWindowTextA(RemoveFolder);
		}
		else if (Cmp(szBuffer, "RemoveFile"))
		{
			m_richFunctionName.SetWindowTextA(RemoveFile);
		}
		else if (Cmp(szBuffer, "OpenFileForReading"))
		{
			m_richFunctionName.SetWindowTextA(OpenFileForReading);
		}
		else if (Cmp(szBuffer, "OpenFileForWriting"))
		{
			m_richFunctionName.SetWindowTextA(OpenFileForWriting);
		}
		else if (Cmp(szBuffer, "CloseFile"))
		{
			m_richFunctionName.SetWindowTextA(CloseFile);
		}
		else if (Cmp(szBuffer, "ReadBoolVariableFromFile"))
		{
			m_richFunctionName.SetWindowTextA(ReadBoolVariableFromFile);
		}
		else if (Cmp(szBuffer, "WriteBoolVariableToFile"))
		{
			m_richFunctionName.SetWindowTextA(WriteBoolVariableToFile);
		}
		else if (Cmp(szBuffer, "ReadFloatVariableFromFile"))
		{
			m_richFunctionName.SetWindowTextA(ReadFloatVariableFromFile);
		}
		else if (Cmp(szBuffer, "WriteFloatVariableToFile"))
		{
			m_richFunctionName.SetWindowTextA(WriteFloatVariableToFile);
		}
		else if (Cmp(szBuffer, "ReadIntVariableFromFile"))
		{
			m_richFunctionName.SetWindowTextA(ReadIntVariableFromFile);
		}
		else if (Cmp(szBuffer, "WriteIntVariableToFile"))
		{
			m_richFunctionName.SetWindowTextA(WriteIntVariableToFile);
		}
		else if (Cmp(szBuffer, "ReadStringVariableFromFile"))
		{
			m_richFunctionName.SetWindowTextA(ReadStringVariableFromFile);
		}
		else if (Cmp(szBuffer, "WriteStringVariableToFile"))
		{
			m_richFunctionName.SetWindowTextA(WriteStringVariableToFile);
		}
		else if (Cmp(szBuffer, "GetCharacterControllerCapsuleRadius"))
		{
			m_richFunctionName.SetWindowTextA(GetCharacterControllerCapsuleRadius);
		}
		else if (Cmp(szBuffer, "GetCharacterControllerCapsuleHeight"))
		{
			m_richFunctionName.SetWindowTextA(GetCharacterControllerCapsuleHeight);
		}
		else if (Cmp(szBuffer, "GetCharacterControllerForcePower"))
		{
			m_richFunctionName.SetWindowTextA(GetCharacterControllerForcePower);
		}
		else if (Cmp(szBuffer, "GetCharacterControllerWalkSpeed"))
		{
			m_richFunctionName.SetWindowTextA(GetCharacterControllerWalkSpeed);
		}
		else if (Cmp(szBuffer, "GetCharacterControllerRunSpeed"))
		{
			m_richFunctionName.SetWindowTextA(GetCharacterControllerRunSpeed);
		}
		else if (Cmp(szBuffer, "GetCharacterControllerStepOffset"))
		{
			m_richFunctionName.SetWindowTextA(GetCharacterControllerStepOffset);
		}
		else if (Cmp(szBuffer, "GetCharacterControllerJumpPower"))
		{
			m_richFunctionName.SetWindowTextA(GetCharacterControllerJumpPower);
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

	InsertItem("ExecuteCyclicAnimation");
	InsertItem("RemoveCyclicAnimation");
	InsertItem("ExecuteNonCyclicAnimation");
	InsertItem("ReverseExecuteNonCyclicAnimation");
	InsertItem("RemoveNonCyclicAnimation");
	InsertItem("GetAnimationClipDurationOfPrefabInstance");
	InsertItem("PausePrefabInstanceAnimations");
	InsertItem("ResumePrefabInstanceAnimations");

	InsertItem("LoadVScene");
	InsertItem("ExitGame");

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
	InsertItem("PlayResourceSound");
	InsertItem("PlayResourceSoundLoop");
	InsertItem("PlayResourceSoundOnce");
	InsertItem("StopResourceSound");
	InsertItem("PauseResourceSound");
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
	InsertItem("IsCharacterControllerLocked");
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

	InsertItem("GetDepthOfFieldFocalDistance");
	InsertItem("GetDepthOfFieldFocalRange");

	InsertItem("EnableFog");
	InsertItem("DisableFog");
	InsertItem("SetFogColor");
	InsertItem("SetFogDensity");

	InsertItem("GetFogColor");
	InsertItem("GetFogDensity");

	InsertItem("EnableBloom");
	InsertItem("DisableBloom");
	InsertItem("SetBloomColor");
	InsertItem("SetBloomIntensity");

	InsertItem("GetBloomColor");
	InsertItem("GetBloomIntensity");

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

	InsertItem("GetLightAmbient");
	InsertItem("GetLightDiffuse");
	InsertItem("GetLightSpecular");
	InsertItem("GetLightShininess");

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
	InsertItem("SetPhysicsGroundHeight");
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

	InsertItem("GetDistanceBetweenPhysicsCameraAndCharacterController");

	InsertItem("GetCharacterControllerCapsuleRadius");
	InsertItem("GetCharacterControllerCapsuleHeight");
	InsertItem("GetCharacterControllerForcePower");
	InsertItem("GetCharacterControllerWalkSpeed");
	InsertItem("GetCharacterControllerRunSpeed");
	InsertItem("GetCharacterControllerStepOffset");
	InsertItem("GetCharacterControllerJumpPower");

	InsertItem("GetPhysicsDefaultRestitution");
	InsertItem("GetPhysicsDefaultSkinWidth");
	InsertItem("GetPhysicsDefaultStaticFriction");
	InsertItem("GetPhysicsDefaultDynamicFriction");
	InsertItem("GetPhysicsGravity");
	InsertItem("GetPhysicsGroundHeight");
	InsertItem("GetPhysicsCollisionFlags");

	InsertItem("SetMultisamplingValue");
	InsertItem("SetAnisotropicFilteringValue");
	InsertItem("EnableVSync");
	InsertItem("DisableVSync");
	InsertItem("EnableGeneralWaterReflection");
	InsertItem("DisableGeneralWaterReflection");
	InsertItem("SetScreenResolution");
	InsertItem("SaveGeneralProperties");
	InsertItem("GetMultisamplingValue");
	InsertItem("GetAnisotropicFilteringValue");
	InsertItem("IsVSyncEnabled");
	InsertItem("IsGeneralWaterReflectionEnabled");
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
	InsertItem("PauseWaterAnimation");
	InsertItem("ResumeWaterAnimation");

	InsertItem("PlayVideo");
	InsertItem("PlayVideoLoop");
	InsertItem("PlayVideoOnce");
	InsertItem("StopVideo");

	InsertItem("SetVideoLoop");
	InsertItem("SetVideoVolume");
	InsertItem("GetVideoPlay");
	InsertItem("GetVideoLoop");
	InsertItem("GetVideoVolume");
	InsertItem("GetVideoDuration");

	InsertItem("SetSoundVolume");
	InsertItem("SetSoundPitch");
	InsertItem("PlaySound");
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
	
	//Stop Sounds
	InsertItem("StopAllSounds");
	InsertItem("StopAllAmbientSounds");
	InsertItem("StopAll3DSounds");
	InsertItem("StopAllResourceSounds");

	//Play Sounds
	InsertItem("PlayAllSounds");
	InsertItem("PlayAllAmbientSounds");
	InsertItem("PlayAll3DSounds");
	InsertItem("PlayAllResourceSounds");
	InsertItem("PlayAllPausedSounds");
	InsertItem("PlayAllPausedAmbientSounds");
	InsertItem("PlayAllPaused3DSounds");
	InsertItem("PlayAllPausedResourceSounds");
	InsertItem("PlayAllStoppedSounds");
	InsertItem("PlayAllStoppedAmbientSounds");
	InsertItem("PlayAllStopped3DSounds");
	InsertItem("PlayAllStoppedResourceSounds");
	//Play Sounds loop
	InsertItem("PlayAllSoundsLoop");
	InsertItem("PlayAllPausedSoundsLoop");
	InsertItem("PlayAllStoppedSoundsLoop");
	InsertItem("PlayAllAmbientSoundsLoop");
	InsertItem("PlayAll3DSoundsLoop");
	InsertItem("PlayAllResourceSoundsLoop");
	InsertItem("PlayAllStoppedAmbientSoundsLoop");
	InsertItem("PlayAllStopped3DSoundsLoop");
	InsertItem("PlayAllStoppedResourceSoundsLoop");
	InsertItem("PlayAllPausedAmbientSoundsLoop");
	InsertItem("PlayAllPaused3DSoundsLoop");
	InsertItem("PlayAllPausedResourceSoundsLoop");
	//Play Sounds once
	InsertItem("PlayAllSoundsOnce");
	InsertItem("PlayAllPausedSoundsOnce");
	InsertItem("PlayAllStoppedSoundsOnce");
	InsertItem("PlayAllAmbientSoundsOnce");
	InsertItem("PlayAll3DSoundsOnce");
	InsertItem("PlayAllResourceSoundsOnce");
	InsertItem("PlayAllStoppedAmbientSoundsOnce");
	InsertItem("PlayAllStopped3DSoundsOnce");
	InsertItem("PlayAllStoppedResourceSoundsOnce");
	InsertItem("PlayAllPausedAmbientSoundsOnce");
	InsertItem("PlayAllPaused3DSoundsOnce");
	InsertItem("PlayAllPausedResourceSoundsOnce");

	//Pause Sounds
	InsertItem("PauseAllSounds");
	InsertItem("PauseAllAmbientSounds");
	InsertItem("PauseAll3DSounds");
	InsertItem("PauseAllResourceSounds");

	//Pause game 
	InsertItem("PauseGame");
	InsertItem("PauseAllAnimationsOfPrefabInstances");
	InsertItem("PauseMainCharacterAnimations");
	InsertItem("PausePhysics");
	InsertItem("PauseAnimationOfAllWaters");

	//resume game
	InsertItem("ResumeGame");
	InsertItem("ResumeAllAnimationsOfPrefabInstances");
	InsertItem("ResumeMainCharacterAnimations");
	InsertItem("ResumePhysics");
	InsertItem("ResumeAnimationOfAllWaters");

	//lock/unlock character
	InsertItem("LockCharacterController");
	InsertItem("UnlockCharacterController");

	//menu cursor
	InsertItem("ShowMenuCursor");
	InsertItem("HideMenuCursor");
	InsertItem("SetMenuCursorSize");
	InsertItem("GetMenuCursorSize");

	//Pause script Update event of game objects
	InsertItem("PauseAllUpdateEvents");
	InsertItem("PauseUpdateEventOfAllPrefabInstances");
	InsertItem("PauseUpdateEventOfVSceneScript");
	InsertItem("PauseUpdateEventOfSky");
	InsertItem("PauseUpdateEventOfAllWaters");
	InsertItem("PauseUpdateEventOfAllLights");
	InsertItem("PauseUpdateEventOfAll3DSounds");
	InsertItem("PauseUpdateEventOfAllAmbientSounds");
	InsertItem("PauseUpdateEventOfMainCharacter");
	InsertItem("PauseUpdateEventOfTerrain");
	InsertItem("PauseUpdateEventOfAllEngineCameras");

	//Resume script Update event of game objects
	InsertItem("ResumeAllUpdateEvents");
	InsertItem("ResumeUpdateEventOfAllPrefabInstances");
	InsertItem("ResumeUpdateEventOfVSceneScript");
	InsertItem("ResumeUpdateEventOfSky");
	InsertItem("ResumeUpdateEventOfAllWaters");
	InsertItem("ResumeUpdateEventOfAllLights");
	InsertItem("ResumeUpdateEventOfAll3DSounds");
	InsertItem("ResumeUpdateEventOfAllAmbientSounds");
	InsertItem("ResumeUpdateEventOfMainCharacter");
	InsertItem("ResumeUpdateEventOfTerrain");
	InsertItem("ResumeUpdateEventOfAllEngineCameras");
	
	//Pause script Update event of individual game objects
	InsertItem("PauseUpdateEventOfPrefabInstance");
	InsertItem("PauseUpdateEventOfWater");
	InsertItem("PauseUpdateEventOfLight");
	InsertItem("PauseUpdateEventOf3DSound");
	InsertItem("PauseUpdateEventOfAmbientSound");
	InsertItem("PauseUpdateEventOfEngineCamera");

	//Resume script Update event of individual game objects
	InsertItem("ResumeUpdateEventOfPrefabInstance");
	InsertItem("ResumeUpdateEventOfWater");
	InsertItem("ResumeUpdateEventOfLight");
	InsertItem("ResumeUpdateEventOf3DSound");
	InsertItem("ResumeUpdateEventOfAmbientSound");
	InsertItem("ResumeUpdateEventOfEngineCamera");

	//terrain
	InsertItem("SetTerrainAmbient");
	InsertItem("SetTerrainDiffuse");
	InsertItem("SetTerrainSpecular");
	InsertItem("SetTerrainShininess");
	InsertItem("GetTerrainAmbient");
	InsertItem("GetTerrainDiffuse");
	InsertItem("GetTerrainSpecular");
	InsertItem("GetTerrainShininess");

	//Engine Camera
	InsertItem("SetEngineCameraPosition");
	InsertItem("SetEngineCameraPan");
	InsertItem("SetEngineCameraTilt");
	InsertItem("SetEngineCameraNearClipPlane");
	InsertItem("SetEngineCameraFarClipPlane");
	InsertItem("SetEngineCameraAngle");
	InsertItem("GetEngineCameraPosition");
	InsertItem("GetEngineCameraPan");
	InsertItem("GetEngineCameraTilt");
	InsertItem("GetEngineCameraNearClipPlane");
	InsertItem("GetEngineCameraFarClipPlane");
	InsertItem("GetEngineCameraAngle");

	//Water
	InsertItem("SetWaterPosition");
	InsertItem("SetWaterRotation");
	InsertItem("SetWaterScale");
	InsertItem("SetWaterLightPosition");
	InsertItem("SetWaterUnderwaterColor");
	InsertItem("SetWaterUnderwaterFogDensity");
	InsertItem("SetWaterTransparency");
	InsertItem("SetWaterFlowSpeed");
	InsertItem("SetWaterUV");
	InsertItem("SetWaterVisible");
	InsertItem("SetWaterInvisible");
	InsertItem("EnableWaterShadow");
	InsertItem("DisableWaterShadow");
	InsertItem("EnableWaterSunReflection");
	InsertItem("DisableWaterSunReflection");
	InsertItem("GetWaterPosition");
	InsertItem("GetWaterRotation");
	InsertItem("GetWaterScale");
	InsertItem("GetWaterLightPosition");
	InsertItem("GetWaterUnderwaterColor");
	InsertItem("GetWaterUnderwaterFogDensity");
	InsertItem("GetWaterTransparency");
	InsertItem("GetWaterFlowSpeed");
	InsertItem("GetWaterUV");
	InsertItem("IsWaterVisible");
	InsertItem("IsWaterShadowEnabled");
	InsertItem("IsWaterSunReflectionEnabled");

	//Sky
	InsertItem("SetSkyPosition");
	InsertItem("EnableSkyFog");
	InsertItem("DisableSkyFog");
	InsertItem("GetSkyPosition");
	InsertItem("IsSkyFogEnabled");

	//Save/Load
	InsertItem("CreateFolder");
	InsertItem("RemoveFolder");
	InsertItem("RemoveFile");
	InsertItem("OpenFileForReading");
	InsertItem("OpenFileForWriting");
	InsertItem("CloseFile");
	InsertItem("ReadBoolVariableFromFile");
	InsertItem("WriteBoolVariableToFile");
	InsertItem("ReadFloatVariableFromFile");
	InsertItem("WriteFloatVariableToFile");
	InsertItem("ReadIntVariableFromFile");
	InsertItem("WriteIntVariableToFile");
	InsertItem("ReadStringVariableFromFile");
	InsertItem("WriteStringVariableToFile");
	
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
