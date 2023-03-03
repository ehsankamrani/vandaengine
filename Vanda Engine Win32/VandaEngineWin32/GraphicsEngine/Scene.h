//Original Work: Copyright 2006 Sony Computer Entertainment Inc.
//Modified Work: Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

#include "base.h"
#include "image.h"
#include "effect.h"
#include "material.h"
#include "geometry.h"
#include "light.h"
#include "node.h"
#include "skin.h"
#include "dae.h"
#include "camera.h"
#include "../common/list.h"
#include "dom/domConstants.h"
#include "dom/domCOLLADA.h"
#include <stdio.h>
#include "../common/DecomposeMatrix.h"
#include "../common/minizip.h"
//#include "cfxLoader.h"
//#include "cfxEffect.h"
//#include "cfxSurface.h"
//#include "cfxPlatform.h"

//#include "cg.h"

#include <set>
#include <map>
#include <vector>

// Forward declares for the DOM
class CAnimation;
class CAnimationClip;
class CAnimSrc;
class CAnimSampler;
class CAnimChannel;
class CShaderElements;
class daeElement; 
class domLight;
class domCamera; 
class domMaterial; 
class domGeometry;
class domImage;
class domEffect; 
class domTexture; 
class domAnimation; 
class domController; 
class domScene;
class domNode; 
class domMesh;
class domTriangles;
class domTristrips;
class domLines;
class domLinestrips;
class domPolygons;
class domPolylist;
class domLibrary_lights;
class domLibrary_cameras;
class domLibrary_materials;
class domLibrary_geometries;
class domLibrary_images;
class domLibrary_animations;
class domLibrary_controllers;
class domLibrary_effects;
class domCOLLADA;
class domVisual_scene;
class domExtra;
class domProfile_COMMON;
class domCommon_newparam_type;
class domSource;
template<class T> class daeSmartRef;
typedef daeElement domElement; 
typedef class daeSmartRef<domLight> domLightRef;
typedef class daeSmartRef<domCamera> domCameraRef;
typedef class daeSmartRef<domMaterial> domMaterialRef;
typedef class daeSmartRef<domImage> domImageRef;
typedef class daeSmartRef<domEffect> domEffectRef;
typedef class daeSmartRef<domTexture> domTextureRef;
typedef class daeSmartRef<domAnimation> domAnimationRef;
typedef class daeSmartRef<domAnimation_clip> domAnimationClipRef;
typedef class daeSmartRef<domController> domControllerRef;
typedef class daeSmartRef<domSource> domSourceRef;
typedef class daeSmartRef<domScene> domSceneRef;
typedef class daeSmartRef<domNode> domNodeRef;
typedef class daeSmartRef<domGeometry> domGeometryRef;
typedef class daeSmartRef<domLibrary_lights> domLibrary_lightsRef;
typedef class daeSmartRef<domLibrary_cameras> domLibrary_camerasRef;
typedef class daeSmartRef<domLibrary_effects> domLibrary_effectsRef;
typedef class daeSmartRef<domLibrary_materials> domLibrary_materialsRef;
typedef class daeSmartRef<domLibrary_geometries> domLibrary_geometriesRef;
typedef class daeSmartRef<domLibrary_images> domLibrary_imagesRef;
typedef class daeSmartRef<domLibrary_animations> domLibrary_animationsRef;
typedef class daeSmartRef<domLibrary_animation_clips> domLibrary_animationClipsRef;
typedef class daeSmartRef<domLibrary_controllers> domLibrary_controllersRef;
typedef class daeSmartRef<domVisual_scene> domVisual_sceneRef;
typedef class daeSmartRef<domExtra> domExtraRef;
template<class T> class daeTArray; 
typedef class daeTArray<domNodeRef> domNode_Array;
typedef class daeTArray<domExtraRef> domExtra_Array;
class domInstance_geometry;
typedef daeSmartRef<domInstance_geometry> domInstance_geometryRef;
typedef daeTArray<domInstance_geometryRef> domInstance_geometry_Array;
class domInstance_light;
typedef daeSmartRef<domInstance_light> domInstance_lightRef;
typedef daeTArray<domInstance_lightRef> domInstance_light_Array;
class domInstance_material;
typedef daeSmartRef<domInstance_material> domInstance_materialRef;
typedef daeTArray<domInstance_materialRef> domInstance_material_Array;
class domInstance_camera;
typedef daeSmartRef<domInstance_camera> domInstance_cameraRef;
typedef daeTArray<domInstance_cameraRef> domInstance_camera_Array;
class domInstance_controller;
typedef daeSmartRef<domInstance_controller> domInstance_controllerRef;
typedef daeTArray<domInstance_controllerRef> domInstance_controller_Array;
class domInputLocalOffset;
typedef daeSmartRef<domInputLocalOffset> domInputLocalOffsetRef;
typedef daeTArray<domInputLocalOffsetRef> domInputLocalOffset_Array;
class domCommon_color_or_texture_type;
typedef daeSmartRef<domCommon_color_or_texture_type> domCommon_color_or_texture_typeRef;
class domCommon_float_or_param_type;
typedef daeSmartRef<domCommon_float_or_param_type> domCommon_float_or_param_typeRef;
class domSampler;
typedef daeSmartRef<domSampler> domSamplerRef;
class domChannel;
typedef daeSmartRef<domChannel> domChannelRef;
/**
 * The CrtScene class is the root of a scene that has been loaded from a collada file, all the parts
 * of the scene eventually link back here.
 */

class CScene : public CBase 
{
private:
	CAnimationStatus m_animationStatus; //Play or Pause

public:
	CScene();
	~CScene();

	std::string ReadZipFile(CChar* zipFile, CChar* fileInZip);
	CBool Load(CChar * fileName, CChar* clipName = NULL, CInt clipIndex = 0, CScene* otherScene = NULL );
	CVoid Destroy();
	CImage* GetImage( const CChar * name );
	CEffect* GetEffect( const CChar* name, const CChar* DocURI);
	CAnimation* GetAnimation( const CChar* name, const CChar* DocURI);
	CMaterial* GetMaterial( const CChar * name, const CChar * DocURI);
	CGeometry* GetGeometry( const CChar * name, const CChar * DocURI);
	CVoid UpdateDynamicPhysicsObjects();
	CVoid Render(CBool sceneManager, CChar* parentTreeNameOfGeometries = NULL, CBool checkVisibility = CFalse, CBool drawGeometry = CTrue);
	CVoid CalculateDistances();
	CVoid RenderAnimatedModels(CBool sceneManager, CBool renderController);
	CVoid ResetSkinData();
	CVoid RenderModelsControlledByPhysX(CBool sceneManager);
	CVoid SetUpdateBB(CBool update);
	CBool GetUpdateBB();
	CVoid RenderAABBWithLines( CBool animatedGeo = CFalse);
	CVoid RenderAABBWithQuads();
	CVoid RenderSelectionMode();
	CVoid CreateTrigger( CNovodex* nx );
	CVoid Update( CFloat elapsedTime = 0.0f, CBool initialUpdate = CFalse, CBool updateOrient = CTrue, CBool resetTimer = CTrue );
	CVoid UpdateBlendCycleList(CFloat elapsedTime, CBool resetTimer);
	CVoid UpdateExecuteActionList(CFloat elapsedTime, CBool &updateExecuteActionList);
	CBool CastShadow() { return m_castShadow; }
	CBool IsTransformable() { return m_isTransformable; }
	CBool isSelectable() { return m_isSelectable; }
	//deprecate
	CBool m_loopAnimationAtStartup, m_playAnimation, m_alwaysVisible, m_castShadow, m_isTransformable, m_isSelectable;
	CBool m_updateBoundingBox;
	//new way
	std::vector<std::string>m_executeActionList;
	std::vector<std::string>m_blendCycleList;

	CAnimationStatus GetAnimationStatus() { return m_animationStatus; }
	CVoid SetAnimationStatus(CAnimationStatus status) { m_animationStatus = status; }

	//new way
	CBool BlendCycle(CInt id, CFloat weight, CFloat delay);
	CBool ClearCycle(CInt id, CFloat delay);
	CBool ExecuteAction(CInt id, CFloat delayIn, CFloat delayOut, CFloat weightTarget, CBool autoLock);
	CBool ReverseExecuteAction(CInt id );
	CBool RemoveAction(CInt id);
	CBool UpdateAnimationLists() { return m_updateAnimationLists; }

	CBool m_hasAnimation; //Has this scene any animations?
	CBool m_updateAnimation;
	CBool m_updateAnimationLists;
	CBool m_update;
	std::vector<std::string>m_animationSceneNames;

	CBool m_isTrigger;
	CUpAxis upAxis;
	CBool m_isVisible;

	//inline CVoid SetLoadDefaultCamera( CBool b ) { m_loadDefaultCamera = b; }
	CChar m_fileName[ MAX_NAME_SIZE ];  /**< File where the scene was loaded from */
	CChar m_pureFileName[ MAX_NAME_SIZE ];  /**<Pure File name where the scene was loaded from */
	inline	CChar* GetFileName(){return m_fileName; }

	inline CInstanceCamera *GetCameraInstance(CUInt num)
	{
		if(num < m_cameraInstances.size())
			return m_cameraInstances[num];
		else 
			return (NULL);
	}
	inline CUInt GetCameraInstanceCount(){return (CUInt) m_cameraInstances.size();}
	inline CUInt GetLightInstanceCount(){return (CUInt) m_lightInstances.size();}
	inline CInstanceLight * GetLightInstances(CUInt num)
	{
		if(num < m_lightInstances.size())
			return m_lightInstances[num];
		else 
			return (NULL);
	}
	CInt GeneratePhysX(CPhysXAlgorithm algorithm, CFloat density, CInt percentage, CBool isTrigger, CBool isInvisible, CPhysXMaterial physicsMaterial, CInstanceGeometry* m_instanceGeo, CBool loadFromFile = CFalse, CInstancePrefab* prefab = NULL);

	inline CVoid CScene::SetDiffuse( const CChar * path )
	{
		//should be updated
		if( g_selectedName != -1 )
		{
			for( CUInt i = 0; i < m_geometries.size(); i++ )
			{
				if( m_geometries[i]->m_nameIndex == g_selectedName )
					m_geometries[i]->SetDiffuse( path );
			}
		}
	}
	inline CVoid CScene::SetNormalMap( const CChar * path )
	{
		//should be updated
		if( g_selectedName != -1 )
		{
			for( CUInt i = 0; i < m_geometries.size(); i++ )
			{
				if( m_geometries[i]->m_nameIndex == g_selectedName )
					m_geometries[i]->SetNormalMap( path );
			}
		}
	}
	inline CVoid CScene::SetDirtMap( const CChar * path )
	{
		//should be updated
		if( g_selectedName != -1 )
		{
			for( CUInt i = 0; i < m_geometries.size(); i++ )
			{
				if( m_geometries[i]->m_nameIndex == g_selectedName )
					m_geometries[i]->SetDirtMap( path );
			}
		}
	}
	inline CVoid CScene::SetGlossMap( const CChar * path )
	{
		//should be updated
		if( g_selectedName != -1 )
		{
			for( CUInt i = 0; i < m_geometries.size(); i++ )
			{
				if( m_geometries[i]->m_nameIndex == g_selectedName )
					m_geometries[i]->SetGlossMap( path );
			}
		}
	}
	inline CVoid CScene::SetHeightMap( const CChar * path )
	{
		if( g_selectedName != -1 )
		{
			for( CUInt i = 0; i < m_geometries.size(); i++ )
			{
				if( m_geometries[i]->m_nameIndex == g_selectedName )
					m_geometries[i]->SetHeightMap( path );
			}
		}
	}

	inline CVoid CScene::RemoveDiffuse()
	{
		//should be updated
		if( g_selectedName != -1 )
		{
			for( CUInt i = 0; i < m_geometries.size(); i++ )
			{
				if( m_geometries[i]->m_nameIndex == g_selectedName )
					m_geometries[i]->RemoveDiffuse();
			}
		}
	}

	inline CVoid CScene::RemoveNormalMap()
	{
		//should be updated
		if( g_selectedName != -1 )
		{
			for( CUInt i = 0; i < m_geometries.size(); i++ )
			{
				if( m_geometries[i]->m_nameIndex == g_selectedName )
					m_geometries[i]->RemoveNormalMap();
			}
		}
	}
	inline CVoid CScene::RemoveDirtMap()
	{
		//should be updated
		if( g_selectedName != -1 )
		{
			for( CUInt i = 0; i < m_geometries.size(); i++ )
			{
				if( m_geometries[i]->m_nameIndex == g_selectedName )
					m_geometries[i]->RemoveDirtMap();
			}
		}
	}
	inline CVoid CScene::RemoveGlossMap()
	{
		//should be updated
		if( g_selectedName != -1 )
		{
			for( CUInt i = 0; i < m_geometries.size(); i++ )
			{
				if( m_geometries[i]->m_nameIndex == g_selectedName )
					m_geometries[i]->RemoveGlossMap();
			}
		}
	}
	inline CVoid CScene::RemoveHeightMap()
	{
		if( g_selectedName != -1 )
		{
			for( CUInt i = 0; i < m_geometries.size(); i++ )
			{
				if( m_geometries[i]->m_nameIndex == g_selectedName )
					m_geometries[i]->RemoveHeightMap();
			}
		}
	}
	inline CVoid CScene::SetCullFace( CBool cullFace )
	{
		if( g_selectedName != -1 )
		{
			for( CUInt i = 0; i < m_geometries.size(); i++ )
			{
				if( m_geometries[i]->m_nameIndex == g_selectedName )
					m_geometries[i]->SetCullFace( cullFace );
			}
		}
	}

public:
	DAE* m_collada;
	std::vector<CImage*>m_images;
	std::vector<CEffect*> m_effects;
	std::vector<CMaterial*> m_materials;
	std::vector<CAnimation *> m_animations;
	std::vector<CAnimation *> m_tempAnimations; //used to load animation clips from different files
	std::vector<CAnimationClip *> m_animationClips;
	std::vector<CGeometry *> m_geometries;
	std::vector<CInstanceGeometry *> m_instanceGeometries;
	std::vector<CLight *> m_lights;
	std::vector<CCamera *> m_cameras;
	std::vector<CController *> m_controllers;

	//std::map<std::string, cfxMaterial*>	m_cfxMaterials;			// Map of collada FX materials by ID
	//std::map<std::string, cfxEffect*> m_cfxEffects;				// Map of collada FX effects by ID
	std::map<std::string, CNode *> m_nodes;
	std::vector<CNode*>m_allNodes;

	std::vector<CInstanceCamera *> m_cameraInstances;
	std::vector<CInstanceLight *>	m_lightInstances;
	
	CNode* m_sceneRoot;
	std::vector<std::string> m_lodSceneList;
	CBool m_isLODScene; //is this scene a LOD scene?
	CScene* m_baseOfLODScene; //If it's a LOD scene, it has a base. Otherwise, base is NULL

	//CGcontext m_cgContext;

private:
	CBool ReadImageLibrary( domLibrary_imagesRef lib );
	CImage *ReadImage( domImageRef lib );

	CBool ReadEffectLibrary( domLibrary_effectsRef lib );
	CEffect *ReadEffect( domEffectRef lib ); 

	CBool ReadMaterialLibrary( domLibrary_materialsRef lib );
	CMaterial *ReadMaterial( domMaterialRef lib ); 

	CBool ReadAnimationLibrary(domLibrary_animationsRef lib, CBool loadTempAnimations = CFalse);
	CAnimation *ReadAnimation(domAnimationRef lib, CBool loadTempAnimations = CFalse);
	CBool ReadAnimationClipLibrary( domLibrary_animationClipsRef lib );
	CVoid ReadAnimationClip( domAnimationClipRef lib );
	CAnimSrc *ReadAnimationSource( domSourceRef source );
	CAnimSampler *ReadAnimationSampler(CAnimation * animation, domSamplerRef sampler);
	CAnimChannel *ReadAnimationChannel(CAnimation * animation, domChannelRef channel);

	CInstanceLight *ReadInstanceLight( domInstance_lightRef lib);
	CLight *ReadLight( domLightRef lib );
	CLight *GetLight( const CChar * name, const CChar * DocURI);

	CInstanceCamera *ReadInstanceCamera( domInstance_cameraRef lib);
	CCamera *ReadCamera( domCameraRef lib );
	CCamera *GetCamera( const CChar * name, const CChar * DocURI);

	CInstanceController *ReadInstanceController( domInstance_controllerRef lib);
	CController	*ReadController( domControllerRef lib ); 


	CImage* GetTextureFromShader( std::map< std::string, domCommon_newparam_type*> &NewParams, domCommon_color_or_texture_type* shader);

	CBool ReadScene( domVisual_sceneRef scene, CUpAxis up );
	CNode* ReadNode( domNodeRef node, CNode * parentNode );
	CBool ReadNodeTransforms( CNode * tempNode, domNodeRef node );
	CNode * GetNode( const CChar * name );
	CInstanceGeometry * ReadInstanceGeometry( domInstance_geometryRef lib);
	CInstanceMaterial *ReadInstanceMaterial( domInstance_materialRef lib);

	CGeometry *ReadGeometry( domGeometryRef lib , CController * controller = 0 );
	CTriangles *BuildTriangles(domTriangles * dom_triangles, CGeometry * geometry, CController* controller, CUInt i );

	CInt Triangulate(DAE * _dae);
	CVoid CreateTrianglesFromPolylist( domMesh *thisMesh, domPolylist *thisPolylist );
	CVoid CreateTrianglesFromPolygons( domMesh *thisMesh, domPolygons *thisPolygons );
	CUInt GetMaxOffset( domInputLocalOffset_Array &input_array );
	CVoid SetCalculateDynamicBoundingBox(CBool set) { m_calculateDynamicBoundingBox = set; }
	CBool GetCalculateDynamicBoundingBox() { return m_calculateDynamicBoundingBox; }

public:
    CVoid CalculateTangentArray(CGeometry* newGeo);
	CVoid DeindexMesh( CUInt initialVertexCount, CUInt totalVertexCount, CGeometry* geometry, CPolyGroup* triangles );
	 CVoid SetNextAnimation(); 
	CVoid SetPrevAnimation();
	CInt GetCurrentClipIndex();
	CInt GetClipIndexForStartup();
	CVoid SetClipIndexForStartup( CInt index );
	CVoid SetClipIndex( CInt index, CBool loopAnimation = CTrue );
	CVoid SetCurrentClipIndex(CInt index);
	CInt GetNumClips();
	CVoid SetNumClips(CInt clips);
	inline CVoid SetLoadAnimation(CBool load) { m_loadAnimation = load; }
	CFloat GetLastKeyTime() { return m_lastKeyTime; }
	CVoid SetLastKeyTime(CFloat time) { m_lastKeyTime = time; }
	CFloat GetFirstKeyTime() { return m_firstKeyTime; }
	CVoid SetFirstKeyTime(CFloat time) { m_firstKeyTime = time; }

	//CBool GetHasScript() { return m_hasScript; }
	//CVoid SetHasScript(CBool set) { m_hasScript = set; }
	//CBool GetUpdateScript() { return m_updateScript; }
	//CVoid SetUpdateScript(CBool set) { m_updateScript = set; }
	//CChar* GetScript() { return m_script; }
	//CVoid SetScript(CChar* script) { Cpy(m_script, script); }

private:
	CBool m_loadAnimation;
	//CBool m_loadDefaultCamera;

	// for animation runtime only
	CFloat m_lastKeyTime; 
	CFloat m_firstKeyTime; 
	CInt m_numAnimatedNodes; 
	CInt m_numClips;

	CInt m_currentClipIndex;
	CInt m_clipIndexForStartup;
	CBool m_calculateDynamicBoundingBox;
	//CBool m_hasScript;
	//CBool m_updateScript;
	//CChar m_script[MAX_NAME_SIZE];
};