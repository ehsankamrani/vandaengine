//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "VandaEngine1Win32.h"
#include "inputEngine/input.h"
#include "timerEngine/timer.h"
#include "graphicsEngine/render.h"
#include "graphicsEngine/OpenGL.h"
#include "graphicsEngine/Fog.h"
#include "graphicsEngine/Water.h"
#include "graphicsEngine/Scene.h"
#include "graphicsEngine/Bloom.h"
#include "graphicsEngine/Sky.h"
#include "graphicsEngine/terrain.h"
//#include "graphicsEngine/imagelib.h"
#include "graphicsEngine/shadowMap.h"
#include "graphicsEngine/particleSystem.h"
#include "graphicsEngine/dof.h"
#include "graphicsEngine/simpleFont.h"
#include "PhysXEngine/Nx.h"
#include "AudioEngine/openal.h"
#include "AudioEngine/OpenALSystem.h"
#include "AudioEngine/OpenALSoundBuffer.h"
#include "AudioEngine/OpenALSoundSource.h"
#include "AudioEngine/StaticSound.h"
#include "AudioEngine/AmbientSound.h"
#include "Icon.h"

struct CPhysXVariables
{
	CBool m_applyDirectionalForce;
	NxVec3 m_forceDirectionVector;
	CFloat m_forceSpeedValue;
	CFloat m_forceDecreaseValue;

	CPhysXVariables()
	{
		m_applyDirectionalForce = CFalse;
		m_forceDecreaseValue = 0.0f;
		m_forceSpeedValue = 0.0f;
		m_forceDirectionVector = NxVec3( 0.0f, 0.0f, 0.0f );
	}
	~CPhysXVariables()
	{
	}
};

class CMain
{
public:
	CMain();
	~CMain();
	void RemoveSelectedScene(CChar* szBuffer, CChar* sceneId);
	CBool Init();
	CBool Render();
	CVoid CalculateDistnces(CBool force = CFalse);
	CVoid ResetData();
	CVoid Release();
	CVoid DrawGrid(CVoid);
	CBool InsertPrefab(CPrefab* prefab);
	CBool Load( CChar* pathName );
	CBool Reset();
	CVoid ResetTimer();
	CParticleSystem* m_particleSystem;
	CBool m_bQuery;
	CBool m_renderQuery;
	std::vector<CFloat> distance_vector;
	std::vector<CInstancePrefab*> sorted_prefabs;
	CBool m_calculateDistance;
	CImage* m_menuCursorImg;
	CChar m_strMenuCursorImg[MAX_NAME_SIZE];

	//shadow
	float cam_proj[16];
	float cam_modelview[16];
	float cam_inverse_modelview[16];
	float cam_pos[3];
	float cam_dir[3];
	float far_bound[MAX_SPLITS];
	CVec3f free_dae_cam_pos, free_dae_cam_at;

	CVoid RenderTerrain();
	CVoid RenderQueries(CBool init = CFalse);
	CVoid RenderBakedOctree3DModels();
	CVoid Render3DModels(CBool sceneManager, CChar* parentTreeNameOfGeometries, CBool checkVisibility = CFalse, CBool drawGeometry = CTrue);
	CVoid Render3DModelsForWater(CWater* water, CBool sceneManager, CChar* parentTreeNameOfGeometries);
	CVoid Render3DAnimatedModels(CBool sceneManager);
	CVoid RenderCharacter(CBool sceneManager);
	CVoid Render3DAnimatedModelsForWater(CWater* water, CBool sceneManager);
	CVoid Render3DModelsControlledByPhysX(CBool sceneManager = CTrue);
	CVoid Render3DModelsControlledByPhysXForWater(CWater* water, CBool sceneManager = CTrue);

	CVoid GenerateMenuCursorTexture(char* fileName);
	CVoid DeleteMenuCursorTexture();

	CVoid UpdateAnimations(CBool init = CFalse);
	CVoid UpdateDynamicPhysicsObjects();
	CVoid DrawGUI();
	void ResetPhysX(CBool releasActors = CTrue);

	CVoid ManageLODs();
	CVoid Draw3DObjects();
	CVoid SetDefaultLight();

	CVoid BlendFogWithScene();
	CVoid ResetPhysXCounts();
	CVoid UpdatePrefabInstanceBB();

	CVoid InitGUISelection();
	CUInt GetSelectedGUI();
	CVoid FinishGUISelection();

	CVoid EnableIdleAnimations();

	CVec2f m_mousePosition; //Mouse position when the user clicks left mouse button
	CFloat GetElapsedTime() { return elapsedTime; }

	CImage* GetMenuCursorImage() { return m_menuCursorImg; }
	CIcon* GetCursorIcon() { return m_cursorIcon; }

	CVoid SetExitGame(CBool set) { m_exitGame = set; }
	CBool GetExitGame() { return m_exitGame; }
public:
	CVoid	ApplyForce( /*NxVec3 forceDirection, */CInt moveDirection, CFloat elapsedTime);

	CIcon* m_cursorIcon;
	CPhysXVariables m_physXVariables;

	//Audio variables 
	ALfloat m_ambientSourcePos[3];
	// Velocity of the source sound.
	ALfloat m_ambientSourceVel[3];
	// Position of the listener.
	ALfloat m_listenerPos[3];
	// Velocity of the listener.
	ALfloat m_listenerVel[3];
	// Orientation of the listener. (first 3 elements are "at", second 3 are "up")
	ALfloat m_listenerOri[6];
	CAmbientSound * m_ambientSound;
	COpenALSystem* m_soundSystem;
	CFloat elapsedTime;
	__int64 m_timerCounter; //To get FPS
	CFloat m_totalElapsedTime; //To get FPS
	CFloat m_cameraInverse[16];

	CUInt m_mFboID; //multisample FBO 
	CUInt m_rbDepthID; //attach a render buffer to the depth buffer of multisample FBO
	CUInt m_rbColorID[eGBUFFER_NUM_TEXTURES]; //attach a render buffer to the color buffers of multisample FBO

	CUInt m_mFboID2; //multisample FBO 
	CUInt m_rbDepthMID2; //attach a render buffer to the depth buffer of multisample FBO
	CUInt m_rbColorID2; //attach a render buffer to the color buffers of multisample FBO

	CUInt m_fboID; //each texture has its own FBO ID
	CUInt m_textureTarget[eGBUFFER_NUM_TEXTURES];
	CUInt m_rbDepthID2; //It's used when multisampling is disabled

	CUInt m_fboID2; //each texture has its own FBO ID
	CUInt m_textureTargetSwapLights;
	CUInt m_rbDepthIDSwapLights; //It's used when multisampling is disabled

	CUInt m_fboIDSum; //each texture has its own FBO ID
	CUInt m_textureTargetSumLighting;

	CUInt m_fboIDFogDof;
	CUInt m_textureFogDof;
	CUInt m_rbDepthIDFogDof;

	CUInt m_rbColorIDFogDof;
	CUInt m_mFboIDFogDof;
	CUInt m_rbMDepthIDFogDof;

	CBool InitFBOs( CInt channels, CInt type );
	CVoid InitDynamicShadowMap(CVec3f lightPos, CVec3f atPos );
	CVoid SetInstanceCamera(CInstanceCamera * inst, CFloat sWidth, CFloat sHeight, CFloat fov, CFloat zNear, CFloat zFar);

	std::vector<std::string> m_tempAllPlayingSoundSources;

private:
	CBool ProcessInputs();
	CBool ManageCharacterBlends(CChar* animationType, CChar* IdleAnimationName = NULL);
	CBool GetJumpCurrentEndDuration(CFloat& duration);
	CBool IsJumping(CBool &isInList);
	COpenALSoundBuffer* GetSoundBuffer( const CChar * name );
	
	GLuint *m_guiPtr, m_guiMinZ, m_guiSelectedName, m_guiBuffer[MAX_NAME_SIZE];//gui selection
private:
	CBool m_showHelpInfo;
	CBool m_previousRightButtonDown;
	CBool m_previousLeftButtonDown;
	CChar m_previousCharacterAnimationType[MAX_NAME_SIZE];
	CBool m_publishDebug;
	CBool m_exitGame;

	CUInt m_selectedGUIIndex;
	CUInt m_previuosSelectedGUIIndex;

	CFloat m_fSelectionDistance;
	CBool m_bSelectionDistance;
	CChar m_selectedPrefabInstanceName[MAX_NAME_SIZE];

	GLuint *ptr, minZ, selectedName, Buffer[MAX_NAME_SIZE], m_selectedPrefabName;//selection

public:
	CBool m_lockInput;
	CBool m_loadScene;
	CBool m_prevLoadScene;
	CCameraType m_cameraType;
	CCameraType m_cameraTypeOfPreviousFrame;
	CShadowMap* m_dynamicShadowMap;
	CDOF m_dof;
	CFloat m_previousCharacterRotation;
	CBool m_characterRotationTransition;
	CFloat m_idleCounter;
	static CBool firstIdle;
	static CChar currentIdleName[MAX_NAME_SIZE];

	CVoid SetSelectionDistance(CFloat distance) { m_fSelectionDistance = distance;  m_bSelectionDistance = CTrue; }
	CFloat GetSelectionDistance() { return m_fSelectionDistance; }
	CChar* SelectPrefabInstances(CDouble mouseXPos, CDouble mouseYPos, CDouble selectionWidth, CDouble selectionHeight);
	CVoid InitPrefabSelection(CDouble mouseXPos, CDouble mouseYPos, CDouble selectionWidth, CDouble selectionHeight);
	CVoid FinishPrefabSelection();

	CFloat GetCursorX();
	CFloat GetCursorY();
};
