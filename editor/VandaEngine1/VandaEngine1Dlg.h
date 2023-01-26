//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// VandaEngine1Dlg.h : header file
//
#pragma once
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#include "resource.h"
#include "afxcmn.h"
#include "graphicsEngine/PerspectiveWindow.h"
#include "graphicsEngine/OpenGLUtility.h"
#include "graphicsEngine/render.h"
#include "common/vector.h"
#include "PrefabDlg.h"
#include "GUIDlg.h"
#include "SavePrefabDlg.h"
#include "SaveGUIDlg.h"
#include "AddTrigger.h"
#include "AddGUIButton.h"
#include "AddGUIImage.h"
#include "AddGUIText.h"
#include "AddLight.h"
#include "AddEngineCamera.h"
#include "AddTerrain.h"
#include "AddWater.h"
#include "AddVSceneScriptObject.h"
#include "AddMultipleAnimations.h"
#include "AddSkyDome.h"
#include "AddAmbientSound.h"
#include "Add3DSound.h"
#include "AddMainCharacter.h"
#include "AddResource.h"
#include "GeneralAmbientColor.h"
#include "ScriptEditor.h"
#include "EditMaterial.h"
#include "EditPrefab.h"
#include "EditGUI.h"
#include "EditPhysX.h"
#include "EditDOF.h"
#include "EditFog.h"
#include "EditBloom.h"
#include "EditOptions.h"
#include "EditLight.h"
#include "EditLOD.h"
#include "EditCamera.h"
#include "EditSceneManager.h"
#include "EditGeneralPhysXProperties.h"
#include "EditProjectProperties.h"
#include "SetCurrentProject.h"
#include "DeleteProject.h"
#include "EditProjectVScenes.h"
#include "EditImportOptions.h"
#include "EditCurrentSceneOptions.h"
#include "EditVSceneName.h"
#include "WelcomeDialog.h"
#include "ShadowDialog.h"
#include "Console.h"
#include "waterAttachment.h"
#include "selectCamera.h"
#include "graphicsEngine/water.h"
#include "graphicsEngine/sky.h"
#include "GraphicsEngine/terrain.h"
#include <vector>
#include "afxwin.h"
#include "AudioEngine/openAL.h"
#include "AudioEngine/OpenALSystem.h"
#include "AudioEngine/OpenALSoundBuffer.h"
#include "AudioEngine/OpenALSoundSource.h"
#include "AudioEngine/3DSound.h"
#include "GUIEngine/GUIImage.h"
#include "GUIEngine/GUIButton.h"
#include "GUIEngine/GUIText.h"
#include "GUIEngine/GUI.h"
#include "ExitEditorDlg.h"
#include "AddPrefabResource.h"
#include "scenemanagerEngine/octree.h"
#include "physXEngine/Trigger.h"
#include "SceneBanner.h"
#include "VsceneMenuCursor.h"
#include "PublishProject.h"
#include "BackupAllProjects.h"
#include "CustomButton.h"
#include "CustomBitmapButton.h"
#include "ScriptEngine/luaforcpp.h"
#include "Common/Prefab.h"
#include "Common/VSceneScript.h"
#include "physXEngine\MainCharacter.h"
#include "PrefabOptions.h"
#include "resourceFile.h"
#include "afxext.h"
class CScene;

struct COptions
{
	CBool m_useCurrentResolution;
	CInt m_width;
	CInt m_height;
	CInt m_numSamples;
	CInt m_anisotropy;
	CBool m_showStartupDialog;
	CBool m_showExitDialog;
	CBool m_disableVSync;
	CBool m_enableWaterReflection;
	CBool m_enableShader;
	CBool m_enableFBO;
	CBool m_enableVBO;

	COptions()
	{
		m_useCurrentResolution = CTrue;
		m_width = 800;
		m_height = 600;
		m_numSamples = 4;
		m_anisotropy = 4;
		m_showStartupDialog = CTrue;
		m_showExitDialog = CTrue;
		m_disableVSync = CTrue;
		m_enableWaterReflection = CTrue;
		m_enableShader = CTrue;
		m_enableFBO = CTrue;
		m_enableVBO = CTrue;
	}

	CVoid Reset()
	{
		m_useCurrentResolution = CTrue;
		m_width = 800;
		m_height = 600;
		m_numSamples = 4;
		m_anisotropy = 4;
		m_showStartupDialog = CTrue;
		m_showExitDialog = CTrue;
		m_disableVSync = CTrue;
		m_enableWaterReflection = CTrue;
		m_enableShader = CTrue;
		m_enableFBO = CTrue;
		m_enableVBO = CTrue;
	}

};

//mainly used in script editor
struct CInstancePrefabNames
{
	CChar m_name[MAX_NAME_SIZE];
	CChar m_packageName[MAX_NAME_SIZE];
	CChar m_prefabName[MAX_NAME_SIZE];
	std::vector<std::string> m_animationNames;
	std::vector<std::string> m_cameraNames;

	CVoid ClearNames()
	{
		m_animationNames.clear();
		m_cameraNames.clear();
	}
};

//mainly used in script editor
struct CPrefabNames
{
	CChar m_name[MAX_NAME_SIZE];
	CChar m_packageName[MAX_NAME_SIZE];
	CChar m_prefabName[MAX_NAME_SIZE];
};

struct CGUINames
{
	CChar m_name[MAX_NAME_SIZE]; //Full GUI name
	CChar m_guiPackageName[MAX_NAME_SIZE]; //Package name of GUI (used for image preview)
	CChar m_guiPureName[MAX_NAME_SIZE]; //Pure GUI name (used for image preview)
	std::vector<std::string> m_buttonNames;
	std::vector<std::string> m_imageNames;
	std::vector<std::string> m_textNames;

	CVoid ClearNames()
	{
		m_buttonNames.clear();
		m_imageNames.clear();
		m_textNames.clear();
	}

};

//mainly used in script editor and to test scripts in Prefab mode
struct CVSceneObjectNames
{
	std::vector<CInstancePrefabNames>m_instancePrefabNames; //Prefab Instances of this VScene
	std::vector<CPrefabNames>m_prefabNames; //Prefab Instances of this VScene
	std::vector<std::string> m_3DSoundsNames; //3D sounds of this VScene
	std::vector<std::string> m_ambientSoundsNames; //ambient sounds of this VScene
	std::vector<std::string> m_importedCameraNames; //imported cameras in dae format of this VScene
	std::vector<std::string> m_engineCameraNames; //camera objects of this VScene
	std::vector<std::string> m_engineLightNames; //light names of this VScene
	std::vector<std::string> m_engineTriggerNames; //Trigger names of this VScene
	std::vector<std::string> m_engineWaterNames; //Water names of this VScene
	std::vector<CGUINames>m_guiNames; //GUIs of this VScene

	CVoid ClearNames()
	{
		for (CUInt i = 0; i < m_instancePrefabNames.size(); i++)
			m_instancePrefabNames[i].ClearNames();
		m_instancePrefabNames.clear();

		m_prefabNames.clear();
		m_3DSoundsNames.clear();
		m_ambientSoundsNames.clear();
		m_importedCameraNames.clear();
		m_engineCameraNames.clear();
		m_engineLightNames.clear();
		m_engineTriggerNames.clear();
		m_engineWaterNames.clear();

		for (CUInt i = 0; i < m_guiNames.size(); i++)
			m_guiNames[i].ClearNames();
		m_guiNames.clear();
	}

};

struct CProjects
{
	CChar m_name[MAX_NAME_SIZE];
	std::vector<std::string> m_sceneNames;
	CBool m_isActive;
	std::vector<CVSceneObjectNames> m_vsceneObjectNames; //mainly used in script editor and to test scripts in Prefab mode
	std::vector<std::vector<std::string>> m_resourceNames;

	CVoid ClearNames()
	{
		//m_sceneNames.clear();
		for (CUInt i = 0; i < m_vsceneObjectNames.size(); i++)
			m_vsceneObjectNames[i].ClearNames();
		m_vsceneObjectNames.clear();
	}
};

struct CExtraTexturesNamingConventions
{
	CChar m_diffuseNameExcept[MAX_NAME_SIZE];
	CChar m_glossMapName[MAX_NAME_SIZE];
	CChar m_normalMapName[MAX_NAME_SIZE];
	CChar m_dirtMapName[MAX_NAME_SIZE];

	CExtraTexturesNamingConventions()
	{
		Cpy( m_diffuseNameExcept, "" );
		Cpy( m_glossMapName, "_g" );
		Cpy( m_normalMapName, "_n" );
		Cpy( m_dirtMapName, "_d" );
	}

	CVoid Reset()
	{
		Cpy( m_diffuseNameExcept, "" );
		Cpy( m_glossMapName, "_g" );
		Cpy( m_normalMapName, "_n" );
		Cpy( m_dirtMapName, "_d" );
	}
};

struct CPathProperties
{
	CChar m_meshPath[MAX_NAME_SIZE];
	CChar m_meshDiffuseTexturePath[MAX_NAME_SIZE];
	CChar m_meshOtherTexturesPath[MAX_NAME_SIZE];
	CChar m_waterPath[MAX_NAME_SIZE];
	CChar m_skyPath[MAX_NAME_SIZE];
	CChar m_soundPath[MAX_NAME_SIZE];
	CChar m_physXPath[MAX_NAME_SIZE];
	CChar m_terrainPath[MAX_NAME_SIZE];

	CPathProperties()
	{
		Cpy( m_meshOtherTexturesPath, "Assets/Textures/Extra/" );
		Cpy( m_meshDiffuseTexturePath, "Assets/Textures/Diffuse/" );
		Cpy( m_skyPath, "Assets/Engine/Textures/Sky/" );
		Cpy( m_waterPath, "Assets/Engine/Textures/Water/" );
		Cpy( m_meshPath, "Assets/Meshes/" );
		Cpy( m_soundPath, "Assets/Engine/Sounds/" );
		Cpy( m_physXPath, "Assets/Engine/PhysX/" );
		Cpy(m_terrainPath, "Assets/Engine/Textures/Terrain/");
	}

	CVoid Reset()
	{
		Cpy( m_meshOtherTexturesPath, "Assets/Textures/Extra/" );
		Cpy( m_meshDiffuseTexturePath, "Assets/Textures/Diffuse/" );
		Cpy( m_skyPath, "Assets/Engine/Textures/Sky/" );
		Cpy( m_waterPath, "Assets/Engine/Textures/Water/" );
		Cpy( m_meshPath, "Assets/Meshes/" );
		Cpy( m_soundPath, "Assets/Engine/Sounds/" );
		Cpy( m_physXPath, "Assets/Engine/PhysX/" );
		Cpy(m_terrainPath, "Assets/Engine/Textures/Terrain/");
	}

};

struct CLightProperties
{
	CFloat m_ambientColor[4];
	CFloat m_specularColor[4];
	CFloat m_shininess;
	CFloat m_tolerance;

	CLightProperties()
	{
		for(CInt i = 0; i < 3; i++ )
		{
			m_ambientColor[i] = 1.0f;
			m_specularColor[i] = 0.6f;
		}
		m_ambientColor[3] = m_specularColor[3] = 1.0;
		m_tolerance = 0.2f;
		m_shininess = 50.0f;
	}

	CVoid Reset()
	{
		for(CInt i = 0; i < 3; i++ )
		{
			m_ambientColor[i] = 1.0f;
			m_specularColor[i] = 0.6f;
		}
		m_ambientColor[3] = m_specularColor[3] = 1.0;
		m_tolerance = 0.2f;
		m_shininess = 50.0f;
	}

};

struct CCurrentVSceneProperties
{
	CChar m_strBanner[MAX_NAME_SIZE]; // I use CVSceneBanner class to save banner
	CChar m_strCursorImage[MAX_NAME_SIZE];
	CBool m_isMenu;
	CInt m_cursorSize;
	CBool m_isPause;
	CFloat m_globalSoundVolume;

	CCurrentVSceneProperties()
	{
		m_isMenu = CFalse;
		m_isPause = CFalse;
		m_cursorSize = 5;
		m_globalSoundVolume = 1.0f;
	}

	CVoid Reset()
	{
		m_isMenu = CFalse;
		m_isPause = CFalse;
		m_cursorSize = 5;
		m_globalSoundVolume = 1.0f;
	}
};

struct CShadowProperties
{
	CFloat m_shadowSplitWeight;
	CFloat m_shadowNearClipPlane;
	CFloat m_shadowFarClipPlane;
	CShadowType m_shadowType;
	CShadowSplits m_shadowSplits;
	CShadowResolution m_shadowResolution;
	CFloat m_intensity;
	CBool m_enable;
	CChar m_directionalLightName[MAX_NAME_SIZE];

	CShadowProperties()
	{
		m_shadowSplitWeight = 0.3f;
		m_shadowNearClipPlane = 0.1f;
		m_shadowFarClipPlane = 70.f;
		m_shadowType = eSHADOW_PCF_GAUSSIAN;
		m_shadowSplits = eSHADOW_4_SPLITS; //4 splits
		m_shadowResolution = eSHADOW_4096;
		m_intensity = 0.5f;
		m_enable = CFalse;
		Cpy( m_directionalLightName, "\n" );
	}

	CVoid Reset()
	{
		m_shadowSplitWeight = 0.3f;
		m_shadowNearClipPlane = 0.1f;
		m_shadowFarClipPlane = 70.f;
		m_shadowType = eSHADOW_PCF_GAUSSIAN;
		m_shadowSplits = eSHADOW_4_SPLITS; //4 splits
		m_shadowResolution = eSHADOW_4096;
		m_intensity = 0.5f;
		m_enable = CFalse;
		Cpy( m_directionalLightName, "\n" );
	}

};

struct CDOFProperties
{
	CBool m_enable;
	CFloat m_dofFocalDistance;
	CFloat m_dofFocalRange;
	CBool m_debug;

	CDOFProperties()
	{
		m_dofFocalDistance = 5.0f;
		m_dofFocalRange = 3.0f;
		m_enable = CFalse;
		m_debug = CFalse;
	}

	CVoid Reset()
	{
		m_dofFocalDistance = 5.0f;
		m_dofFocalRange = 3.0f;
		m_enable = CFalse;
		m_debug = CFalse;
	}

};

struct CFogProperties
{
	CBool m_enable;
	CFloat m_fogDensity;
	CFloat m_fogColor[4];

	CFogProperties()
	{
		m_enable = CFalse;
		m_fogDensity = 0.1f;
		for( CInt i = 0; i < 4; i++ )
		{
			if( i < 3 )
				m_fogColor[i] = 0.5f;
			else
				m_fogColor[i] = 1.0f;
		}
	}

	CVoid Reset()
	{
		m_enable = CFalse;
		m_fogDensity = 0.1f;
		for( CInt i = 0; i < 4; i++ )
		{
			if( i < 3 )
				m_fogColor[i] = 0.5f;
			else
				m_fogColor[i] = 1.0f;
		}
	}

};

struct CBloomProperties
{
	CBool m_enable;
	CFloat m_bloomIntensity;
	CFloat m_bloomColor[3];

	CBloomProperties()
	{
		m_enable = CTrue;
		m_bloomIntensity = 1.0f;
		for( CInt i = 0; i < 3; i++ )
		{
			m_bloomColor[i] = 1.0f;
		}
	}

	CVoid Reset()
	{
		m_enable = CTrue;
		m_bloomIntensity = 1.0f;
		for( CInt i = 0; i < 3; i++ )
		{
			m_bloomColor[i] = 1.0f;
		}
	}

};

struct CMenuVariables
{
	CBool m_justPerspective;
	CBool m_useShader; //deprecate; Moved to COptions::m_enableShader
	CBool m_multisampling; //deprecate; Moved to COptions::m_numSamples
	CBool m_fog; //deprecate; Moved to CFogProperties::m_enable
	CBool m_dof; //deprecate; Moved to CDOFProperties::m_enable
	CBool m_showPerspectiveGrids;
	CBool m_showLightIcons;
	CBool m_showSoundIcons;
	CBool m_showWaterIcons;
	CBool m_showSkyIcon;
	CBool m_showPrefabBoundingBox;
	CBool m_showPhysicsBoundingBox;
	CBool m_showTerrainBoundingBox;
	CBool m_showOctree;
	CBool m_showDynamicShadowDepthTexture;
	CBool m_enableDynamicShadow; //deprecate; Moved to CShadowProperties::m_enable
	CBool m_insertAndShowSky;
	CBool m_insertAndShowTerrain;
	CBool m_insertVSceneScript;
	CBool m_geometryBasedSelection;
	CBool m_showStatistics;
	CBool m_showCameraIcons;
	CBool m_insertCharacter;
	CMenuVariables()
	{
		m_justPerspective = CTrue;  
		m_useShader = CTrue;
		m_multisampling = CTrue;
		m_fog = CFalse;
		m_dof = CFalse;

		m_showPerspectiveGrids = CTrue;
		m_showLightIcons = CTrue;
		m_showSoundIcons = CTrue;
		m_showWaterIcons = CTrue;
		m_showSkyIcon = CTrue;
		m_showCameraIcons = CTrue;
		m_showPrefabBoundingBox = CFalse;
		m_showPhysicsBoundingBox = CFalse;
		m_showTerrainBoundingBox = CFalse;
		m_showOctree = CFalse;
		m_showDynamicShadowDepthTexture = CFalse;
		m_enableDynamicShadow = CTrue;
		m_insertAndShowSky = CFalse;
		m_insertAndShowTerrain = CFalse;
		m_insertVSceneScript = CFalse;
		m_geometryBasedSelection = CTrue;

		m_showStatistics = CFalse;
		m_insertCharacter = CFalse;
	}
};

struct CCameraProperties
{
	//free Perspective Camera
	CFloat m_freePerspectiveFOV; //field of view
	CFloat m_freePerspectiveNCP; //near clip plane
	CFloat m_freePerspectiveFCP; //far clip plane

	//Perspective Camera of Play Mode
	CFloat m_playModePerspectiveFOV; //field of view
	CFloat m_playModePerspectiveMaxFOV; //used for zoom
	CFloat m_playModePerspectiveMinFOV; //used for zoom
	CFloat m_playModePerspectiveNCP; //near clip plane
	CFloat m_playModePerspectiveFCP; //far clip plane

	//COLLADA Camera
	CBool m_readDAECameraFOVFromFile;
	CBool m_readDAECameraNCPFromFile;
	CBool m_readDAECameraFCPFromFile;

	CFloat m_daeCameraFOV; //field of view
	CFloat m_daeCameraNCP; //near clip plane
	CFloat m_daeCameraFCP; //far clip plane

	CCameraProperties()
	{
		m_playModePerspectiveFOV = 54.f;
		m_playModePerspectiveMaxFOV = 65.f;
		m_playModePerspectiveMinFOV = 45.f;
		m_playModePerspectiveNCP = 0.01f;
		m_playModePerspectiveFCP = 5000.f;

		m_freePerspectiveFOV = 54.f;
		m_freePerspectiveNCP = 0.1f;
		m_freePerspectiveFCP = 10000.0f;

		//COLLADA Camera
		m_readDAECameraFOVFromFile = CTrue;
		m_readDAECameraNCPFromFile = CFalse;
		m_readDAECameraFCPFromFile = CFalse;

		m_daeCameraFOV = 54.0f; //field of view
		m_daeCameraNCP = 0.1f; //near clip plane
		m_daeCameraFCP = 1000.f; //far clip plane

	}

	CVoid Reset()
	{
		m_playModePerspectiveFOV = 54.f;
		m_playModePerspectiveMaxFOV = 65.f;
		m_playModePerspectiveMinFOV = 45.f;
		m_playModePerspectiveNCP = 0.01f;
		m_playModePerspectiveFCP = 5000.f;

		m_freePerspectiveFOV = 54.f;
		m_freePerspectiveNCP = 0.1f;
		m_freePerspectiveFCP = 10000.0f;

		//COLLADA Camera
		m_readDAECameraFOVFromFile = CTrue;
		m_readDAECameraNCPFromFile = CFalse;
		m_readDAECameraFCPFromFile = CFalse;

		m_daeCameraFOV = 54.0f; //field of view
		m_daeCameraNCP = 0.1f; //near clip plane
		m_daeCameraFCP = 1000.f; //far clip plane
	}
};

struct CLODProperties
{
	CFloat m_lod1;
	CFloat m_lod1MinObjectCameraDistance;
	CVec2f m_lod2;
	CVec2f m_lod3;
	CFloat m_lod4;
	CFloat m_lod4ObjectCameraDistance;
	CFloat m_waterReflectionPercents;
	CFloat m_waterReflectionCameraDistance;
	CFloat m_waterInvisiblePercent;
	CFloat m_waterInvisibleCameraDistance;
	CLODProperties()
	{
		//initialize LOD numbers
		m_lod1 = 12.0f;
		m_lod1MinObjectCameraDistance = 20.0f;
		m_lod2.x = 2.0f;
		m_lod2.y = 10.0f;
		m_lod3.x = 0.03f;
		m_lod3.y = 1.9f;
		m_lod4 = 0.003f;
		m_lod4ObjectCameraDistance = 80.f;
		m_waterReflectionPercents = 0.2f;
		m_waterReflectionCameraDistance = 40.0f;
		m_waterInvisiblePercent = 0.003f;
		m_waterInvisibleCameraDistance = 120.0f;
	}

	CVoid Reset()
	{
		//initialize LOD numbers
		m_lod1 = 12.0f;
		m_lod1MinObjectCameraDistance = 20.0f;
		m_lod2.x = 2.0f;
		m_lod2.y = 10.0f;
		m_lod3.x = 0.03f;
		m_lod3.y = 1.9f;
		m_lod4 = 0.003f;
		m_lod4ObjectCameraDistance = 80.0f;
		m_waterReflectionPercents = 0.2f;
		m_waterReflectionCameraDistance = 40.0f;
		m_waterInvisiblePercent = 0.003f;
		m_waterInvisibleCameraDistance = 120.0f;
	}
};

struct CPrefabProperties
{
	CInt m_clipIndex;
	std::vector<std::string> m_names;
	CChar m_scriptPath[MAX_URI_SIZE];
	CBool m_updateScript;
	CBool m_hasScript;
	CBool m_loopAnimationAtStart;
	CBool m_playAnimationAtStart;
	CBool m_alwaysVisible;
	CBool m_castShadow;
	CBool m_isSelectable;
	CBool m_isTransformable;

	CPrefabProperties()
	{
		m_clipIndex = 0;
		m_loopAnimationAtStart = CTrue;
		m_playAnimationAtStart = CTrue;
		m_alwaysVisible = CFalse;
		m_castShadow = CTrue;
		Cpy(m_scriptPath, "\n");
		m_updateScript = CFalse;
		m_hasScript = CFalse;
		m_isSelectable = CFalse;
		m_isTransformable = CFalse;
	}

	CVoid Reset()
	{
		m_clipIndex = 0;
		m_names.clear();
		m_loopAnimationAtStart = CTrue;
		m_playAnimationAtStart = CTrue;
		m_alwaysVisible = CFalse;
		m_castShadow = CTrue;
		Cpy(m_scriptPath, "\n");
		m_updateScript = CFalse;
		m_hasScript = CFalse;
		m_isSelectable = CFalse;
		m_isTransformable = CFalse;
 	}
};

// CVandaEngine1Dlg dialog
class CVandaEngine1Dlg : public CDialog
{
// Construction
public:
	CVandaEngine1Dlg(CWnd* pParent = NULL);	// standard constructor
	~CVandaEngine1Dlg();
// Dialog Data
	enum { IDD = IDD_VANDAENGINE_DIALOG };

	protected:
	virtual CVoid DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg CVoid OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg CVoid OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	CBrush m_brush; // used to specify the colors of controls

	CToolTipCtrl* m_pToolTip;
private:
	std::vector<C3DSound*>m_engine3DSounds;
	std::vector<CAmbientSound*>m_engineAmbientSounds;
	std::vector<CInstancePrefab*> m_instancePrefab;
	std::vector<CPrefab*> m_prefab;
	CCurrentVSceneProperties m_currentVSceneProperties;
	std::vector<CGUI*> m_guis;
	CBloomProperties m_bloomProperties;
	CDOFProperties m_dofProperties;
	CFogProperties m_fogProperties;
	CShadowProperties m_shadowProperties;
	CPhysXProperties m_physicsProperties;
	std::vector<CInstanceLight*>m_engineLights;
	std::vector<CGUIButton*> m_guiButtons;
	std::vector<CGUIImage*> m_guiImages;
	std::vector<CGUIText*> m_guiTexts;
	CUpdateCamera* m_camera;
	COptions m_options;
	CAddPrefabResource *m_dlgAddPrefabResource;
	std::vector<CWater*> m_water;
	CFloat m_globalSoundVolume;
public:
	CRichEditCtrl m_rich;
	CBool OnMenuClickedNew( CBool askQuestion );
	CBool OnMenuClickedOpenVScene( CBool askQuestion = CTrue);
	CBool OnMenuClickedOpenPrefab();
	CBool OnMenuClickedInsertPrefab(CPrefab* prefab = NULL, CChar* packageName = NULL, CChar* prefabName = NULL); //if prefab is not null, we are loading from vin file
	CBool OnMenuClickedOpenGUI();
	CBool OnMenuClickedInsertGUI();
	CVoid OnMenuClickedSaveAs(CBool askQuestion = CTrue);
	CVoid OnMenuClickedSavePrefabAs(CBool askQuestion = CTrue);
	CVoid OnMenuClickedSaveGUIAs(CBool askQuestion = CTrue);
	CVoid OnMenuClickedImportColladaMultipleAnimations(CChar* baseModelName, std::vector<std::string>animations);
	CVoid OnMenuClickedPrefab();
	CVoid LoadObjectNames();
	CVoid ClearObjectNames();

	HCURSOR m_progressCursor;

protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	CVoid OnMenuClickedImportCollada();
	CVoid OnMenuClickedInsertLight();
	CVoid OnMenuClickedInsert3DSound();
	CVoid OnMenuClickedInsertSkyDome();
	CVoid OnMenuClickedInsertVSceneScript();
	CVoid OnMenuClickedInsertTerrain();
	CVoid OnMenuClickedInsertEngineCamera();
	CVoid OnMenuClickedInsertVideo();
	CVoid OnMenuClickedWaterAttachment();
	CVoid OnMenuClickedInsertWater();
	CVoid OnMenuClickedInsertAmbientSound();
	CVoid OnMenuClickedSelectCamera();
	CVoid OnMenuClickedGeneralOptions();
	CVoid OnMenuClickedSceneOptions();
	CVoid OnMenuClickedCurrentSceneOptions();
	CVoid OnMenuClickedEditMaterial();
	CVoid OnMenuClickedEditPhysX();
	CVoid OnMenuClickedGeneralAmbientColor();
	CVoid SortButtons();
	CVoid OnMenuClickedGUI();

	CString m_fileName;
	CString m_savePathName; //It's used for save button
	CChar m_strNewPrefabPackageName[MAX_NAME_SIZE];
	CChar m_strNewPrefabName[MAX_NAME_SIZE];
	CChar m_strNewPackageAndPrefabName[MAX_NAME_SIZE];
	CChar m_strNewPassword[MAX_NAME_SIZE];

	CBool m_askRemoveEngineObject;
	CBool m_askRemoveScene;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	CVoid OnBnClickedCullFace();

	CChar m_strNewGUIPackageName[MAX_NAME_SIZE];
	CChar m_strNewGUIName[MAX_NAME_SIZE];
	CChar m_strNewPackageAndGUIName[MAX_NAME_SIZE];

public:
	afx_msg CVoid OnBnClickedBtnRemoveScene();
	CVoid SortSceneList(CInt selectedIndex);
	CVoid SortPhysXList();
public:
	afx_msg CVoid OnBnClickedBtnRemoveObject();
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:

	CVoid InsertItemToSceneList( CChar * sceneName );
	CVoid InsertItemToObjectList( char * objectName, int imageIndex = 0 );
	CVoid InsertItemToEngineObjectList( char * objectName, int imageIndex  = 0 );
	CVoid InsertItemToPhysXList( CChar * physXObjectName, int imageIndex = 0 );
	CVoid InsertItemToGUIList(char * objectName, int imageIndex);
	CVoid SortGUIList();
	CInt m_engineObjectListIndex;
	CInt m_guiListIndex;
	CInt m_sceneListIndex;
	CInt m_objectListIndex;
	CInt m_physXElementListIndex;
	CImageList m_objectListImage;
	CImageList m_engineObjectListImage;
	CImageList m_physXElementListImage;
	CImageList m_guiListImage;

	CVoid ChangeLightProperties(CInstanceLight* light );
	CVoid ChangeEngineCameraProperties(CInstanceCamera* cam);
	CVoid ChangeWaterProperties( CWater* water);
	CVoid Change3DSoundProperties(C3DSound* ThreeDSound);
	CVoid ChangeAmbientSoundProperties(CAmbientSound* sound);
	CVoid ChangeSkyDomeProperties();
	CVoid ChangeTerrainProperties();
	CVoid ChangeVSceneScriptProperties();
	CVoid FindGeometryInstancesRenderedByPhysics();

public:
	CWaterAttachment* m_dlgWaterAttachment;
	CAddTrigger* m_dlgAddTrigger;
	CAddGUIButton* m_dlgAddGUIButton;
	CAddGUIImage* m_dlgAddGUIImage;
	CAddGUIText* m_dlgAddGUIText;
	CAddLight* m_dlgAddLight;
	CAddEngineCamera* m_dlgAddEngineCamera;
	CAddTerrain* m_dlgAddTerrain;
	CAddWater* m_dlgAddWater;
	CAddMultipleAnimations* m_dlgAddMultipleAnimations;
	CPublishProject* m_dlgPublishProject;
	CAdd3DSound* m_dlgAdd3DSound;
	CAddSkyDome* m_dlgAddSkyDome;
	CAddAmbientSound* m_dlgAddAmbientSound;
	CGeneralAmbientColor* m_dlgGeneralAmbientColor;
	CSelectCamera* m_dlgSelectCamera;
	CEditMaterial* m_dlgEditMaterial;
	CEditPhysX* m_dlgEditPhysX;
	CAddMainCharacter* m_dlgMainCharacter;
	CEditBloom* m_dlgEditBloom;
	CEditLight* m_dlgEditLight;
	CEditLOD* m_dlgEditLOD;
	CEditCamera* m_dlgEditCamera;
	CEditSceneManager* m_dlgEditSceneManager;
	CEditGeneralPhysXProperties* m_dlgEditGeneralPhysXProperties;
	CEditShadow* m_dlgEditShadow;
	CEditOptions* m_dlgOptions;
	CEditImportOptions* m_dlgImportOptions;
	CEditCurrentSceneOptions* m_dlgCurrentSceneOptions;
	CWelcomeDialog m_dlgWelcome;
	CEditDOF* m_dlgEditDOF;
	CEditFog* m_dlgEditFog;
	CConsole* m_dlgConsole;
	CPrefabDlg* m_dlgPrefabs;
	CGUIDlg* m_dlgGUIs;
	CSavePrefabDlg *m_dlgSavePrefabs;
	CSaveGUIDlg *m_dlgSaveGUIs;
	NxExtendedVec3 m_currentCharacterPos;
	CVec4f m_initCharacterRotate;
	CVec3f m_initCharacterTranslate;
	std::vector<std::string> m_deletedTriggerObjects;
	std::vector<std::string> m_deletedWaterObjects;
	std::vector<std::string> m_deletedAmbientSoundObjects;
	std::vector<std::string> m_deleted3DSoundObjects;
	std::vector<std::string> m_deletedCameraObjects;
	std::vector<std::string> m_deletedLightObjects;
protected:
	virtual void OnCancel();
public:
	CListCtrl m_listBoxScenes;
public:
	CListCtrl m_listBoxObjects;
public:
	CCustomBitmapButton m_btnRemoveScene;
public:
	CCustomBitmapButton m_btnRemoveObject;
public:
	CListCtrl m_listBoxEngineObjects;
public:
	CCustomBitmapButton m_btnRemoveEngineObject;
public:
	CCustomBitmapButton m_btnEngineObjectProperties;
public:
	afx_msg void OnBnClickedBtnRemoveEngineObject();
	CVoid SortEngineObjectList(CInt selectedIndex);
public:
	afx_msg void OnBnClickedBtnEngineObjectProperties();
public:
	afx_msg void OnClose();
public:
	afx_msg BOOL CVandaEngine1Dlg::PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnBnClickedBtnNew();
public:
	afx_msg void OnBnClickedBtnSave();
public:
	CCustomBitmapButton m_mainBtnSave;
public:
	CCustomBitmapButton m_mainBtnImportCollada;
public:
	CCustomBitmapButton m_mainBtnNew;
public:
	afx_msg void OnBnClickedBtnCollada();
//public:
	//CCustomBitmapButton m_mainBtnImportPhysX; removed in version 1.4 or later
//public:
	//afx_msg void OnBnClickedBtnPhysx(); 
public:
	CCustomBitmapButton m_mainBtnPrevAnim;
public:
	afx_msg void OnBnClickedBtnAnimPrev();
public:
	CCustomBitmapButton m_mainBtnOpen;
public:
	afx_msg void OnBnClickedBtnOpen();
public:
	CCustomBitmapButton m_mainBtnSaveAs;
public:
	afx_msg void OnBnClickedBtnSaveas();
public:
	CCustomBitmapButton m_mainBtnPlayAnim;
public:
	CCustomBitmapButton m_mainBtnNextAnim;
public:
	afx_msg void OnBnClickedBtnAnimNext();
public:
	afx_msg void OnBnClickedBtnAnimPlay();
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	CCustomBitmapButton m_mainBtnTimer;
public:
	CCustomBitmapButton m_mainBtnMaterial;
public:
	afx_msg void OnBnClickedBtnTimer();
public:
	CCustomBitmapButton m_mainBtnPauseAnim;
public:
	afx_msg void OnBnClickedBtnAnimPause();
public:
	CCustomBitmapButton m_mainBtnWeb;
public:
	afx_msg void OnBnClickedBtnWeb();
public:
	CCustomBitmapButton m_mainBtnFacebook;

	CVoid RemoveEngineObject();
public:

	afx_msg void OnBnClickedBtnFacebook();
	CRichEditCtrl m_staticSelectedObject;
	afx_msg void OnBnClickedBtnMaterial();
	CCustomBitmapButton m_mainBtnSky;
	CCustomBitmapButton m_mainBtnWater;
	CCustomBitmapButton m_mainBtn3DSound;
	CCustomBitmapButton m_mainBtnAmbientSound;
	CCustomBitmapButton m_mainBtnPlayer;
	CCustomBitmapButton m_mainBtnLight;
	afx_msg void OnBnClickedBtnLight();
	afx_msg void OnBnClickedBtnWater();
	afx_msg void OnBnClickedBtnAmbientsound();
	afx_msg void OnBnClickedBtn3DSound();
	afx_msg void OnBnClickedBtnSky();
	afx_msg void OnBnClickedBtnPlayer();

	CInt m_horizontalSizeOfLeftCulomn;
	CInt m_horizontalSizeOfRightCulomn;
	CInt m_horizontalPointFivePercent;
	CInt m_startLeftButtons;
	long previousColumn1, previousColumn2, previousColumn3, previousColumn4;
	CCustomBitmapButton m_mainBtnConsole;
	afx_msg void OnBnClickedBtnConsole();
//	afx_msg void OnHdnItemclickListScenes(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListEngineObjects(NMHDR *pNMHDR, LRESULT *pResult);

	void ResetPhysX(CBool releaseActors = CTrue);
	CListCtrl m_listBoxPhysXElements;
	CCustomBitmapButton m_btnRemovePhysX;
	CCustomBitmapButton m_btnVandaText;
	CCustomBitmapButton m_mainBtnTwitter;
	afx_msg void OnBnClickedBtnTwitter();
	CCustomBitmapButton m_mainBtnYoutube;
	afx_msg void OnBnClickedBtnYoutube();
	afx_msg void OnLvnItemchangedListPhysxElements(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnPublishSolution();
	void OnBnClickedBtnBackupAllProjects();
	afx_msg void OnBnClickedBtnScriptManager();
	CCustomBitmapButton m_mainBtnPublishSolution;
	CCustomBitmapButton m_mainBtnScriptManager;
	CCustomBitmapButton m_mainBtnFreeCamera;
	afx_msg void OnBnClickedBtnCameraRenderingManager();
	CCustomBitmapButton m_btnVandaVersion;
	CCustomBitmapButton m_btnSceneProperties;
	afx_msg void OnBnClickedBtnSceneProperties();
	CCustomBitmapButton m_mainBtnPhysXEditor;
	afx_msg void OnBnClickedBtnPhysxEditor();
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnLvnItemchangedListScenes(NMHDR *pNMHDR, LRESULT *pResult);
	CCustomBitmapButton m_mainBtnPrefab;
	afx_msg void OnBnClickedBtnPrefabs();
	void RemoveSelectedScene(CChar* szBuffer, CChar* sceneId = NULL);
	CCustomBitmapButton m_mainBtnTranslate;
	CCustomBitmapButton m_mainBtnRotate;
	CCustomBitmapButton m_mainBtnScale;
	CCustomBitmapButton m_mainBtnTimerPause;
	afx_msg void OnBnClickedBtnTimerPause();
	CCustomBitmapButton m_mainBtnTestActive;
	CCustomBitmapButton m_mainBtnTestDeactive;
	afx_msg void OnBnClickedBtnPlayActive();
	afx_msg void OnBnClickedBtnPlayDeactive();
	afx_msg void OnBnClickedBtnTranslate();
	afx_msg void OnBnClickedBtnRotate();
	afx_msg void OnBnClickedBtnScale();
	void PumpMessages();
	CRichEditCtrl m_editX;
	CRichEditCtrl m_editY;
	CRichEditCtrl m_editZ;
	afx_msg void OnEnChangeEditX();
	afx_msg void OnEnChangeEditY();
	afx_msg void OnEnChangeEditZ();
	CCustomBitmapButton m_mainBtnWaterAttach;
	afx_msg void OnBnClickedBtnWaterAttach();
	CCustomBitmapButton m_mainBtnTrigger;
	afx_msg void OnBnClickedBtnTrigger();
	CCustomBitmapButton m_mainBtnImportColladaMultipleAnimations;
	afx_msg void OnBnClickedBtnColladaMultipleAnimations();
	CCustomBitmapButton m_mainBtnGUIButton;
	afx_msg void OnBnClickedBtnGuiButton();
	afx_msg void OnBnClickedBtnGuiImages();
	afx_msg void OnBnClickedBtnGuiText();
	CCustomBitmapButton m_mainBtnGUIImage;
	CCustomBitmapButton m_mainBtnGUIText;
	CListCtrl m_listBoxGUIElements;
	afx_msg void OnBnClickedBtnRemoveGui();
	afx_msg void OnBnClickedBtnGuiProperties();

	CBool m_askRemoveGUIElement;
	CVoid ChangeGUIButtonProperties(CGUIButton* button);
	CVoid ChangeGUIImageProperties(CGUIImage* image);
	CVoid ChangeGUITextProperties(CGUIText* text);

	CCustomBitmapButton m_btnRemoveGUI;
	CCustomBitmapButton m_btnGUIProperties;
	CCustomBitmapButton m_mainBtnGUIEditor;
	afx_msg void OnBnClickedBtnGuiPackage();
	afx_msg void OnLvnItemchangedListGuiElements(NMHDR *pNMHDR, LRESULT *pResult);
	CVoid SavePrefabFiles();
	CVoid SaveGUIFiles();
	CCustomBitmapButton m_mainBtnVSceneScript;
	afx_msg void OnBnClickedBtnVSceneScript();
	CCustomBitmapButton m_mainBtnTerrain;
	afx_msg void OnBnClickedInsertTerrain();
	CCustomBitmapButton m_mainBtnEngineCamera;
	afx_msg void OnBnClickedBtnEngineCamera();
	afx_msg void OnLvnItemchangingListScenes(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangingListEngineObjects(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangingListGuiElements(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangingListPhysxElements(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangingListObjects(NMHDR *pNMHDR, LRESULT *pResult);
	CCustomBitmapButton m_mainBtnPrefabSettings;
	afx_msg void OnBnClickedBtnPrefabSettings();
	CRichEditCtrl m_richSelectedObjectName;
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnDestroy();
	CCustomBitmapButton m_mainBtnVideo;
	afx_msg void OnBnClickedBtnVideo();
	afx_msg void OnBnClickedBtnRemovePhysx();
};

//Edition.MaxVersion.MinVersion.BugFixes;
//For example: RTI.1.0.0
extern CInt g_maxVersion;
extern CInt g_minVersion;
extern CInt g_bugFixesVersion;
extern CChar g_edition[MAX_NAME_SIZE];
extern CBool g_useOriginalPathOfDAETextures;
extern CBool g_updateTextureViaEditor;
extern CChar g_currentVSceneName[MAX_NAME_SIZE]; //save functions
extern std::vector<std::string> g_VSceneNamesOfCurrentProject; //save functions
extern std::vector<std::string> g_VSceneNamesOfCurrentProjectToBePublished; //save functions
extern std::vector<std::string> g_allPrefabNames;
extern std::vector<std::string> g_allGUINames; //save functions
extern std::vector<std::string> g_characterProfiles;
extern std::string g_firstSceneNameToBeLoaded; //save functions
extern CChar g_projectsPath[MAX_NAME_SIZE];
extern CChar g_currentProjectPath[MAX_NAME_SIZE];
extern CChar g_currentPackageAndPrefabName[MAX_NAME_SIZE]; //save functions
extern CChar g_currentPrefabPackageName[MAX_NAME_SIZE]; //save functions
extern CChar g_currentPrefabName[MAX_NAME_SIZE]; //save functions
extern CChar g_currentPrefabPackagePath[MAX_NAME_SIZE]; //save functions

extern CChar g_currentGUIPackageName[MAX_NAME_SIZE]; //save functions
extern CChar g_currentPackageAndGUIName[MAX_NAME_SIZE]; //save functions
extern CChar g_currentGUIName[MAX_NAME_SIZE];
extern CChar g_currentGUIPackagePath[MAX_NAME_SIZE]; //save functions

extern CChar g_currentPrefabAndSceneName[MAX_NAME_SIZE]; //save functions
extern CChar g_currentZipFileName[MAX_NAME_SIZE]; //save functions
extern CChar g_currentInstancePrefabName[MAX_NAME_SIZE];
extern CTFormType g_currentTransformType;
extern CBool g_shareGeometriesBetweenScenes;
extern CBool g_openNewPrefabFromList;
extern CBool g_openNewGUIFromList;
extern CScene* g_currentScene; //current scene that we are working on it.
extern CInstancePrefab* g_currentInstancePrefab;
extern CMainCharacter* g_mainCharacter;
extern CChar g_currentPassword[MAX_NAME_SIZE];
extern CBool g_vandaDemo;
extern CBool g_admin;
extern CBool g_importCOLLADA;
extern CBool g_openVINFile;
extern CChar g_fileNameInCommandLine[MAX_NAME_SIZE];

extern CRichEditCtrl *ex_pRichEdit; // rich edit pointer
extern CRichEditCtrl *ex_pRichEditScript;
extern CVandaEngine1Dlg* ex_pVandaEngine1Dlg;
extern CAddMainCharacter* ex_pMainCharacterDlg;
extern CPrefabDlg* ex_pDlgPrefabs;
extern CGUIDlg* ex_pDlgGUIs;
extern CRichEditCtrl *ex_pStaticSelectedObject;

extern CMenu *ex_pMenu; //pointer to menu ( used for cull face check mark )

extern CEditMaterial *ex_pEditMaterial; //extern
extern CEditPhysX *ex_pEditPhysX;
extern CButton* ex_pBtnPrevAnim;
extern CButton* ex_pBtnPlayAnim;
extern CButton* ex_pBtnPauseAnim;
extern CButton* ex_pBtnNextAnim;
extern CButton* ex_pBtnTimerPlay;
extern CButton* ex_pBtnTimerPause;
extern CButton* ex_pBtnScriptEditor;
extern CButton* ex_pBtnTestModeActive;
extern CButton* ex_pBtnTestModeDeactive;
extern CButton* ex_pBtnPhysXEditor;
extern std::vector<CScene*> g_scene;
extern std::vector<CPrefab*> g_prefab;
extern std::vector<CPrefab*> g_resourcePrefab;
extern std::vector<CGeometry *> g_geometries;
extern std::vector<CInstancePrefab*>g_instancePrefab;
extern CBool g_importPrefab;
extern CScene* g_translateArrow;
extern CScene* g_scaleArrow;
extern CScene* g_rotateArrow;
extern CScene* g_negativeZArrow;
extern CScene* g_centerArrowScene;
extern CVec3f g_arrowPosition;
extern CVec3f g_arrowRotate;
extern CVec3f g_arrowScale;
extern CLODProperties g_instancePrefabLODPercent;
extern CPrefabProperties g_prefabProperties;
extern CCameraProperties g_cameraProperties;

extern CBool g_showArrow;
extern COpenGLUtility g_glUtil;
extern CImage* g_soundImg;
extern CImage* g_pointLightImg;
extern CImage* g_directionalLightImg;
extern CImage* g_spotLightImg;
extern CImage* g_pointLightCOLLADAImg;
extern CImage* g_directionalLightCOLLADAImg;
extern CImage* g_spotLightCOLLADAImg;
extern CImage* g_skyImg;
extern CImage* g_waterImg;
extern CImage* g_cameraImg;
extern CColor4f g_globalAmbientColor;
extern CBool g_useGlobalAmbientColor;
extern CVec4f g_defaultDirectionalLight;

extern std::vector<CGUIButton*> g_guiButtons;
extern std::vector<CGUIImage*> g_guiImages;
extern std::vector<CGUIText*> g_guiTexts;
extern std::vector<CGUI*> g_guis;

extern std::vector<CInstanceLight*> g_engineLights; //these aren't collada lights, they are specified via the editor
extern std::vector<CTrigger*> g_triggers;
extern std::vector<CWater*> g_engineWaters; //We may use multiple water surfaces in our engine
extern std::vector<CInstanceCamera*> g_importedCameraInstances;
extern std::vector<CInstanceCamera*> g_engineCameraInstances;
extern std::vector<CResourceFile*> g_resourceFiles;
extern std::vector<C3DSound*> g_engine3DSounds;
extern std::vector<CAmbientSound*> g_engineAmbientSounds;
extern COpenALSystem* g_soundSystem;
extern std::vector<std::string> g_engineObjectNames;
extern std::vector<std::string> g_guiNames;
extern CUpdateCamera *g_camera;
extern CVSceneScript* g_VSceneScript;
extern GLuint g_shaderType;
extern CSkyDome *g_skyDome;   //Currently each map has just one sky, But I may decide to add extra layers later
extern CTerrain *g_terrain;
extern NxExtendedVec3 g_characterPos; //default camera attached to character controller
extern CVec3f g_cameraInstancePos; //default free camera
extern CVec2f g_cameraInstancePanTilt; //default free camera
extern 	CBloom*	g_bloom;
extern CVSceneBanner g_sceneBanner;
extern CVSceneMenuCursor g_vsceneMenuCursor;
extern std::vector<CImage*>g_images; // This variable holds the information of all the images of Engine
extern std::vector<CImage*>g_waterImages; // This variable holds the information of water images of Engine
extern CShadowMap* g_dynamicShadowMap;
extern COctree* g_octree;
extern CMultipleWindows *g_multipleView;
extern CInt numErrors, numWarnings, totalErrors, totalWarnings, ReportLineCounter; //number of warning, errors and lines used by richedit 22

extern CBool g_updateOctree;
extern CBool g_useOldRenderingStyle;
extern CFloat g_elapsedTime;
extern CInt g_width;
extern CInt g_height;
extern CMenuVariables g_menu;
extern CShadowProperties g_shadowProperties;
extern CPhysXProperties g_physXProperties;
extern CPhysXCollisionFlags g_physXCollisionFlags;
extern CDOFProperties g_dofProperties;
extern CLightProperties g_lightProperties;
extern CCurrentVSceneProperties g_currentVSceneProperties;
extern CCharacterBlendingProperties g_characterBlendingProperties;
extern CFogProperties g_fogProperties;
extern CFogProperties g_waterFogProperties;
extern CPathProperties g_pathProperties;
extern CExtraTexturesNamingConventions g_extraTexturesNamingConventions;
extern CBloomProperties g_bloomProperties;
extern COptions g_options;
extern std::vector<CProjects*> g_projects;
extern CPolygonMode g_polygonMode;
extern CBool g_firstPass;
extern CMaterialChannels g_materialChannels;
extern CInstanceLight* g_currentInstanceLight;
extern CInt g_sceneManagerObjectsPerSplit;
extern lua_State* g_lua;
extern CBool g_testScript;
extern CBool g_renderShadow;
extern CFloat g_maxInstancePrefabRadius; //maximum radius of prefabs: currently used for the max radius of dynamic shadow

extern CEditorMode g_editorMode;

extern CBool g_clickedOpen;
extern CBool g_clickedNew;

extern CCameraType g_currentCameraType;
extern CBool g_renderForWater;
extern std::vector<std::vector<std::string>> g_prefabPackagesAndNames;
extern std::vector<std::vector<std::string>> g_guiPackagesAndNames;
extern std::vector<std::vector<std::string>> g_projectResourceNames;
DWORD __stdcall MEditStreamOutCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
DWORD __stdcall MEditStreamInCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);


CVoid CheckCullFace( CCullFaceTypeForMenu type ); // cull face check mark
CVoid SetDialogData( CBool selected, CInstanceGeometry* instanceGeo = NULL, CGeometry* geo = NULL, CBool engineObject = CFalse, CBool showDialog = CTrue );
CVoid SetDialogData2( CBool selected, CPolyGroup* group = NULL, CBool engineObject = CFalse, CBool showDialog = CTrue );
CVoid SetDialogData3(CBool selected, CInstancePrefab* instancePrefab = NULL);
CVoid SetDialogData4(CChar* name, CFloat x, CFloat y, CFloat z, CBool showXYZ = CTrue, CBool showArrow = CTrue);
