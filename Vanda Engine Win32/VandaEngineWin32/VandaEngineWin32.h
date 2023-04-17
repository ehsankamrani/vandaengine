//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

#include "GraphicsEngine/Window.h"
#include "GraphicsEngine/Render.h"
#include "graphicsEngine/render.h"
#include "GraphicsEngine/image.h"
#include "GraphicsEngine/shadowMap.h"
#include "GraphicsEngine/simplefont.h"
#include "GraphicsEngine/geometry.h"
#include "inputEngine/input.h"
#include "timerEngine/timer.h"
#include "physXEngine/nx.h"
#include "physXEngine/Trigger.h"
#include "GraphicsEngine/camera.h"
#include "scenemanagerEngine/octree.h"
#include "ScriptEngine/luaForCpp.h"
#include "Common/prefab.h"
#include "Common/VSceneScript.h"
#include "physXEngine\MainCharacter.h"
#include "AudioEngine/openAL.h"
#include "AudioEngine/OpenALSystem.h"
#include "AudioEngine/OpenALSoundBuffer.h"
#include "AudioEngine/OpenALSoundSource.h"
#include "AudioEngine/3DSound.h"
#include "VideoEngine/Video.h"
#include "GUIEngine/GUIImage.h"
#include "GUIEngine/GUIButton.h"
#include "GUIEngine/GUIText.h"
#include "GUIEngine/GUI.h"
#include "ResourceFile.h"
#include "resource.h"
#include <vector>

class CInstanceLight;
class CWater;
class C3DSound;
class CScene;
class CImage;
class CBloom;
class CSkyDome;
class CTerrain;
class COctree;
class CMain;
struct CUpdateCamera;
class COpenALSoundBuffer;
class CInstanceCamera;
class CGUIButton;
class CGUIImage;
class CGUIText;
//Edition.MaxVersion.MinVersion.BugFixes;
//For example: RTI.1.0.0
extern CInt g_version;
extern CChar g_edition[MAX_NAME_SIZE];
extern CScene* g_currentScene; //current scene that we are working on it.
extern CInstancePrefab* g_currentInstancePrefab;
extern CMainCharacter* g_mainCharacter;
extern CChar g_currentVSceneName[MAX_NAME_SIZE]; //save functions
extern CChar g_currentPrefabPackagePath[MAX_NAME_SIZE];
extern CChar g_currentPrefabName[MAX_NAME_SIZE];
extern CChar g_currentVSceneNameViaScript[MAX_NAME_SIZE];
extern CChar g_currentPrefabAndSceneName[MAX_NAME_SIZE]; //save functions
extern CChar g_currentZipFileName[MAX_NAME_SIZE]; //save functions
extern CChar g_currentInstancePrefabName[MAX_NAME_SIZE];
extern CBool g_loadSceneViaScript;
extern CChar g_currentPassword[MAX_NAME_SIZE];
extern std::vector<CScene*> g_scene;
extern std::vector<CPrefab*> g_prefab;
extern std::vector<CPrefab*> g_resourcePrefab;
extern std::vector<CGeometry *> g_geometries;
extern std::vector<CInstancePrefab*>g_instancePrefab;
extern std::vector<CGUIButton*> g_guiButtons;
extern std::vector<CGUIImage*> g_guiImages;
extern std::vector<CGUIText*> g_guiTexts;
extern std::vector<CGUI*> g_guis;

extern std::vector<CInstanceLight*> g_engineLights; //these aren't collada lights, they are specified via the editor
extern std::vector<CTrigger*> g_triggers;
extern std::vector<CWater*> g_engineWaters; //We may use multiple water surfaces in our engine
extern std::vector<C3DSound*>g_engine3DSounds;
extern std::vector<CAmbientSound*> g_engineAmbientSounds;
extern std::vector<CVideo*> g_engineVideos;
extern CUpdateCamera *g_camera;
extern CVSceneScript* g_VSceneScript;
extern COctree* g_octree;
extern CShadowMap* g_dynamicShadowMap;
extern GLuint g_shaderType;
extern CSkyDome *g_skyDome;   //Currently each map has just one sky, But I may decide to add extra layers later
extern CTerrain *g_terrain;
extern CBool g_renderShadow;
extern CFloat g_maxInstancePrefabRadius; //maximum radius of prefabs: currently used for the max radius of dynamic shadow

extern CBool g_clickedOpen;
extern CBool g_clickedNew;
extern CCameraType g_currentCameraType;
extern CBool g_renderForWater;
extern CBloom*	g_bloom;
extern std::vector<CImage*>g_images; // This variable holds the information of all the images of Engine
extern std::vector<CImage*>g_waterImages; // This variable holds the information of water images of Engine
extern CInt g_numLights;
extern CInt g_totalLights;
extern CWindow g_window; 
extern HINSTANCE g_instance;
extern CInputSystem g_input;
extern CTimer* g_timer;
extern CNovodex* g_nx;
extern CFont* g_font;
extern CInt g_width;                   //default g_width of our screen
extern CInt g_height;                   //default Height of our screen
extern CBool g_useOldRenderingStyle;
extern CFloat g_elapsedTime;
extern CBool g_updateOctree;
extern CMain* g_main;
extern CBool g_useGlobalAmbientColor;
extern CColor4f g_globalAmbientColor;
extern COpenALSystem* g_soundSystem;
extern std::vector<CInstanceCamera*> g_importedCameraInstances;
extern std::vector<CInstanceCamera*> g_engineCameraInstances;
extern std::vector<CResourceFile*> g_resourceFiles;
struct COptions
{
	CBool m_useCurrentResolution;
	CInt m_width;
	CInt m_height;
	CInt m_numSamples;
	CInt m_anisotropy;
	CBool m_showStartupDialog;
	CBool m_disableVSync;
	CBool m_enableWaterReflection;
	CBool m_enableShader;
	CBool m_enableFBO;
	CBool m_enableVBO;
	CBool m_fullScreen;

	COptions()
	{
		m_useCurrentResolution = CTrue;
		m_width = 800;
		m_height = 600;
		m_numSamples = 4;
		m_anisotropy = 4;
		m_showStartupDialog = CTrue;
		m_disableVSync = CTrue;
		m_enableWaterReflection = CTrue;
		m_enableShader = CTrue;
		m_enableFBO = CTrue;
		m_enableVBO = CTrue;
		m_fullScreen = CTrue;
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
	CChar m_videoPath[MAX_NAME_SIZE];

	CPathProperties()
	{
		Cpy( m_meshOtherTexturesPath, "Assets/Textures/Extra/" );
		Cpy( m_meshDiffuseTexturePath, "Assets/Textures/Diffuse/" );
		Cpy( m_skyPath, "Assets/Textures/sky/" );
		Cpy( m_waterPath, "Assets/Textures/water/" );
		Cpy( m_meshPath, "Assets/meshes/" );
		Cpy( m_soundPath, "Assets/sounds/" );
		Cpy( m_physXPath, "Assets/physx/" );
		Cpy(m_terrainPath, "Assets/Engine/Textures/Terrain/");
		Cpy(m_videoPath, "Assets/Engine/Video/");
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
		Cpy(m_videoPath, "Assets/Engine/Video/");
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
	CBool m_lockCharacterController;
	CInt m_menuCursorSize;
	CBool m_pauseGame;
	CFloat m_globalSoundVolume;

	CCurrentVSceneProperties()
	{
		m_lockCharacterController = CFalse;
		m_pauseGame = CFalse;
		m_menuCursorSize = 5;
		m_globalSoundVolume = 1.0f;
	}

	CVoid Reset()
	{
		m_lockCharacterController = CFalse;
		m_pauseGame = CFalse;
		m_menuCursorSize = 5;
		m_globalSoundVolume = 1.0f;
	}
};

struct CCharacterBlendingProperties
{
	CFloat m_idleDelayIn;
	CFloat m_walkDelayIn;
	CFloat m_runDelayIn;
	CFloat m_jumpDelayIn;
	CFloat m_jumpDelayOut;

	CCharacterBlendingProperties()
	{
		m_idleDelayIn = 0.5f;
		m_walkDelayIn = 0.5f;
		m_runDelayIn = 0.5f;
		m_jumpDelayIn = 0.5f;
		m_jumpDelayOut = 0.5f;

	}

	CVoid Reset()
	{
		m_idleDelayIn = 0.5f;
		m_walkDelayIn = 0.5f;
		m_runDelayIn = 0.5f;
		m_jumpDelayIn = 0.5f;
		m_jumpDelayOut = 0.5f;
	}

	CVoid SetZero()
	{
		m_idleDelayIn = 0.0f;
		m_walkDelayIn = 0.0f;
		m_runDelayIn = 0.0f;
		m_jumpDelayIn = 0.0f;
		m_jumpDelayOut = 0.0f;
	}
};

struct CCharacterSoundProperties
{
	CChar m_walkSound[MAX_URI_SIZE];
	CChar m_runSound[MAX_URI_SIZE];
	CChar m_jumpSound[MAX_URI_SIZE];
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
		m_shadowFarClipPlane = 70.0f;
		m_shadowType = eSHADOW_PCF_GAUSSIAN;
		m_shadowSplits = eSHADOW_4_SPLITS; //4 splits
		m_shadowResolution = eSHADOW_4096;
		m_intensity = 0.5f;
		m_enable = CFalse;
		Cpy( m_directionalLightName, "\n" );
	}
};

struct CPhysXProperties
{
	CFloat m_fDefaultRestitution;
	CFloat m_fDefaultStaticFriction;
	CFloat m_fDefaultSkinWidth;
	CFloat m_fDefaultDynamicFriction;
	CFloat m_fGroundHeight;
	CFloat m_fGravityX;
	CFloat m_fGravityY;
	CFloat m_fGravityZ;
	CFloat m_fCameraCharacterDistance;
	CFloat m_fCapsuleRadius;
	CFloat m_fCapsuleHeight;
	CFloat m_fCharacterPower;
	CFloat m_fCharacterWalkSpeed;
	CFloat m_fCharacterRunSpeed;
	CFloat m_fCharacterSlopeLimit;
	CFloat m_fCharacterStepOffset;
	CFloat m_fCharacterSkinWidth;
	CFloat m_fJumpPower;
	CBool m_bDebugMode;
	CBool m_bJumping;
	CBool m_bApplyGravity;
	CBool m_bGroundPlane;

	CPhysXProperties()
	{
		m_fDefaultRestitution = 0.3f;
		m_fDefaultStaticFriction = 0.5f;
		m_fDefaultDynamicFriction = 0.5f;
		m_fDefaultSkinWidth = 0.01f;
		m_fGroundHeight = 0.0f;
		m_fGravityX = 0.0f;
		m_fGravityY = -9.8f;
		m_fGravityZ = 0.0f;
		m_fCameraCharacterDistance = 3.0f;
		m_fCapsuleRadius = 0.4;
		m_fCapsuleHeight = 1.2f;
		m_fCharacterPower = 3.0f;
		m_fCharacterWalkSpeed = 2.0f;
		m_fCharacterRunSpeed = 3.0f;
		m_fJumpPower = 7.0f;
		m_fCharacterSlopeLimit = 45.0f;
		m_fCharacterStepOffset = 0.1f;
		m_fCharacterSkinWidth = 0.01f;

		m_bDebugMode = CFalse;
		m_bJumping = m_bApplyGravity = CTrue;
		m_bGroundPlane = CTrue;
	}

	CVoid Reset()
	{
		m_fDefaultRestitution = 0.3f;
		m_fDefaultStaticFriction = 0.5f;
		m_fDefaultDynamicFriction = 0.5f;
		m_fDefaultSkinWidth = 0.01f;
		m_fGroundHeight = 0.0f;
		m_fGravityX = 0.0f;
		m_fGravityY = -9.8f;
		m_fGravityZ = 0.0f;
		m_fCameraCharacterDistance = 3.0f;
		m_fCapsuleRadius = 0.4f;
		m_fCapsuleHeight = 1.2f;
		m_fCharacterPower = 3.0f;
		m_fCharacterWalkSpeed = 2.0f;
		m_fCharacterRunSpeed = 3.0f;
		m_fJumpPower = 7.0f;
		m_fCharacterSlopeLimit = 45.0f;
		m_fCharacterStepOffset = 0.1f;
		m_fCharacterSkinWidth = 0.01f;

		m_bDebugMode = CFalse;
		m_bJumping = m_bApplyGravity = CTrue;
		m_bGroundPlane = CTrue;
	}
};

struct CPhysXCollisionFlags
{
	CBool m_kinematicDynamic;
	CBool m_dynamicDynamic;
	CBool m_dynamicStatic;
	CBool m_dynamicGround;
	CBool m_triggerTrigger;
	CBool m_triggerKinematic;
	CBool m_triggerStatic;
	CBool m_triggerDynamic;
	CBool m_triggerGround;

	CPhysXCollisionFlags()
	{
		m_kinematicDynamic = CTrue;
		m_dynamicDynamic = CTrue;
		m_dynamicStatic = CTrue;
		m_dynamicGround = CTrue;
		m_triggerTrigger = CTrue;
		m_triggerKinematic = CTrue;
		m_triggerStatic = CTrue;
		m_triggerDynamic = CTrue;
		m_triggerGround = CFalse;
	}

	CVoid Reset()
	{
		m_kinematicDynamic = CTrue;
		m_dynamicDynamic = CTrue;
		m_dynamicStatic = CTrue;
		m_dynamicGround = CTrue;
		m_triggerTrigger = CTrue;
		m_triggerKinematic = CTrue;
		m_triggerStatic = CTrue;
		m_triggerDynamic = CTrue;
		m_triggerGround = CFalse;
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

struct CDatabaseVariables
{
	CBool m_useShader; //deprecate
	CBool m_multisampling; //deprecate
	CBool m_fog; //deprecate	
	CBool m_dof; //deprecate
	CBool m_showPerspectiveGrids;
	CBool m_showLightPositions;
	CBool m_showSoundPositions;
	CBool m_showPrefabBoundingBox;
	CBool m_showTerrainBoundingBox;
	CBool m_showOctree;
	CBool m_showStatistics;
	CBool m_enableDynamicShadow; //deprecate
	CBool m_insertAndShowSky;
	CBool m_insertAndShowTerrain;
	CBool m_insertVSceneScript;
	CBool m_insertCharacter;
	CDatabaseVariables()
	{
		m_useShader = CTrue;
		m_multisampling = CTrue;
		m_fog = CTrue;

		m_showPerspectiveGrids = CFalse;
		m_showLightPositions = CFalse;
		m_showSoundPositions = CFalse;
		m_showPrefabBoundingBox = CFalse;
		m_showTerrainBoundingBox = CFalse;
		m_showOctree = CFalse;
		m_showStatistics = CFalse;
		m_enableDynamicShadow = CFalse;
		m_insertAndShowSky = CFalse;
		m_insertAndShowTerrain = CFalse;
		m_insertVSceneScript = CFalse;
		m_dof = CFalse;
		m_insertCharacter = CFalse;
	}

	CVoid Reset()
	{
		m_useShader = CTrue;
		m_multisampling = CTrue;
		m_fog = CTrue;

		m_showPerspectiveGrids = CFalse;
		m_showLightPositions = CFalse;
		m_showSoundPositions = CFalse;
		m_showPrefabBoundingBox = CFalse;
		m_showTerrainBoundingBox = CFalse;
		m_showOctree = CFalse;
		m_showStatistics = CFalse;
		m_enableDynamicShadow = CTrue;
		m_insertAndShowSky = CFalse;
		m_insertVSceneScript = CFalse;
		m_dof = CFalse;
		m_insertCharacter = CFalse;
	}

};

extern CDatabaseVariables g_databaseVariables;
extern CShadowProperties g_shadowProperties;
extern CPhysXProperties g_physXProperties;
extern CPhysXCollisionFlags g_physXCollisionFlags;
extern CDOFProperties g_dofProperties;
extern CFogProperties g_fogProperties;
extern CFogProperties g_waterFogProperties;
extern CBloomProperties g_bloomProperties;
extern CLightProperties g_lightProperties;
extern CCurrentVSceneProperties g_currentVSceneProperties;
extern CCharacterBlendingProperties g_characterBlendingProperties;
extern CPathProperties g_pathProperties;
extern CExtraTexturesNamingConventions g_extraTexturesNamingConventions;
extern COptions g_options;
extern CVec4f g_defaultDirectionalLight;
extern CInstanceLight* g_currentInstanceLight;
extern CBool g_firstPass;
extern CInt g_sceneManagerObjectsPerSplit;
extern CLODProperties g_instancePrefabLODPercent;
extern CPrefabProperties g_prefabProperties;
extern CCameraProperties g_cameraProperties;
