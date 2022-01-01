//Original Work: Copyright 2006 Sony Computer Entertainment Inc.
//Modified Work: Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "..//VandaEngine1Dlg.h"
#include "base.h"
#include "image.h"
#include "effect.h"
#include "material.h"
//#include "animation.h"
#include "geometry.h"
#include "light.h"
#include "node.h"
#include "skin.h"
#include "dae.h"
#include "camera.h"
#include "../common/list.h"
#include "dom/domConstants.h"
#include "dom/domCOLLADA.h"
#include "../common/DecomposeMatrix.h"
#include "../common/minizip.h"
#include <stdio.h>

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
	CInt WriteZipFile(CChar* zipFile, CChar* fileInZip, CChar* fileInZipPath, const CChar* password );
	int GetFileCrc(const char* filenameinzip,void*buf,unsigned long size_buf,unsigned long* result_crc);
	CBool Load(CChar * fileName, CChar* clipName = NULL, CInt clipIndex = 0, CScene* otherScene = NULL, CBool reportWarningsAndErrors = CTrue, CBool readFromBuffer = CFalse );
	CVoid Destroy();
	CImage* GetImage( const CChar * name );
	CEffect* GetEffect( const CChar* name, const CChar* DocURI);
	CAnimation* GetAnimation( const CChar* name, const CChar* DocURI);
	CMaterial* GetMaterial( const CChar * name, const CChar * DocURI);
	CGeometry* GetGeometry( const CChar * name, const CChar * DocURI);
	CVoid UpdateDynamicPhysicsObjects();
	CVoid Render(CBool sceneManager, CChar* parentTreeNameOfGeometries = NULL, CBool renderController = CFalse, CBool checkVisibility = CFalse, CBool drawGeometry = CTrue );
	CVoid RenderAnimatedModels(CBool sceneManager, CBool renderController);
	CVoid ResetSkinData();
	CVoid RenderModelsControlledByPhysX(CBool sceneManager);
	CVoid CalculateDistances();
	CVoid SetUpdateBB(CBool update);
	CBool GetUpdateBB();
	CVoid RenderAABBWithLines( CBool animatedGeo = CFalse);
	CVoid RenderAABBWithQuads();
	CVoid RenderSelectionMode();
	CVoid Update( CFloat elapsedTime = 0.0f, CBool updateOrient = CTrue, CBool resetTime = CTrue );
	CVoid UpdateBlendCycleList(CFloat elapsedTime, CBool resetTimer);
	CVoid UpdateExecuteActionList(CFloat elapsedTime, CBool &updateExecuteActionList);
	CVoid CreateTrigger( CNovodex* nx );
	CVoid SetupDiffuseTexture();
	CVoid SetupNormalTexture();
	CVoid SetupDirtTexture();
	CVoid SetupGlossTexture();
	CInt Triangulate(DAE * _dae);
	CVoid CreateTrianglesFromPolylist( domMesh *thisMesh, domPolylist *thisPolylist );
	CVoid CreateTrianglesFromPolygons( domMesh *thisMesh, domPolygons *thisPolygons );
	CUInt GetMaxOffset( domInputLocalOffset_Array &input_array );
	CVoid SetCalculateDynamicBoundingBox(CBool set) { m_calculateDynamicBoundingBox = set; }
	CBool GetCalculateDynamicBoundingBox() { return m_calculateDynamicBoundingBox; }
	CBool CastShadow() { return m_castShadow; }
	CBool IsTransformable() { return m_isTransformable; }
	CBool isSelectable() { return m_isSelectable; }

	//deprecate
	CBool m_loopAnimationAtStartup, m_playAnimation, m_alwaysVisible, m_castShadow, m_isTransformable, m_isSelectable;
	CBool m_updateBoundingBox;
	//new way
	std::vector<std::string>m_executeActionList;
	std::vector<std::string>m_blendCycleList;
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

	CBool m_compress; //save functions

	//std::vector<std::map<std::string, CBool>> m_VSceneList; //List of all VScenes created via the editor, save functions
	std::vector<std::map<std::string, CBool>> m_prefabList; //List of all prefabs created via the editor, save functions
	std::vector<std::string>m_textureList; //list of textures of all of the groups of current scene, save functions
	std::vector<std::string>m_animationSceneNames;

	CAnimationStatus GetAnimationStatus() { return m_animationStatus; }
	CVoid SetAnimationStatus(CAnimationStatus status) { m_animationStatus = status; }

	inline CVoid AddTextureToList(std::string textureName) //save functions
	{
		m_textureList.push_back(textureName);
	}
	inline CBool IsInTextureList(std::string textureName)
	{
		for( CUInt i = 0; i < m_textureList.size(); i++ )
		{
			if( m_textureList[i] == textureName )
				return CTrue;
		}
		AddTextureToList(textureName);
		return CFalse;
	}
	//inline CVoid AddVSceneToList(std::string vSceneName, CBool writeToZip) //save functions
	//{
	//	std::map<std::string, CBool> tempVScene;
	//	tempVScene[vSceneName] = writeToZip;
	//	m_VSceneList.push_back( tempVScene );
	//}
	//inline CBool IsInVSceneList( std::string vSceneName, CBool content, CBool reverseTheContent ) //save functions
	//{
	//	for( CUInt i = 0; i < m_VSceneList.size(); i++ )
	//	{
	//		if( m_VSceneList[i].begin()->first == vSceneName )
	//		{
	//			if( m_VSceneList[i].begin()->second == content) //found the target
	//			{
	//				if( reverseTheContent )
	//					m_VSceneList[i].begin()->second = !content;
	//				return CTrue;
	//			}
	//			else
	//				return CFalse;
	//		}
	//	}
	//	if( reverseTheContent )
	//		AddVSceneToList( vSceneName, !content );
	//	else
	//		AddVSceneToList( vSceneName, content );
	//	return CTrue;
	//}

	inline CVoid AddPrefabToList(std::string prefabName, CBool writeToZip) //save functions
	{
		std::map<std::string, CBool> tempPrefab;
		tempPrefab[prefabName] = writeToZip;
		m_prefabList.push_back(tempPrefab);
	}
	inline CBool IsInPrefabList(std::string prefabName, CBool content, CBool reverseTheContent) //save functions
	{
		for (CUInt i = 0; i < m_prefabList.size(); i++)
		{
			if (m_prefabList[i].begin()->first == prefabName)
			{
				if (m_prefabList[i].begin()->second == content) //found the target
				{
					if (reverseTheContent)
						m_prefabList[i].begin()->second = !content;
					return CTrue;
				}
				else
					return CFalse;
			}
		}
		if (reverseTheContent)
			AddPrefabToList(prefabName, !content);
		else
			AddPrefabToList(prefabName, content);
		return CTrue;
	}

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

	//Generate and remove physics actors
	CBool RemovePhysX();
	CInt GeneratePhysX(CPhysXAlgorithm algorithm, CFloat density, CInt percentage, CBool isTrigger, CBool isInvisible, CPhysXMaterial physicsMaterial, CInstanceGeometry* m_instanceGeo, CBool loadFromFile = CFalse, CInstancePrefab* prefab = NULL);
	CInt GeneratePhysX(CPhysXAlgorithm algorithm, CFloat density, CInt percentage, CBool isTrigger, CBool isInvisible, CPhysXMaterial physicsMaterial);
	////////////////////////

	inline CBool CScene::SetDiffuse( const CChar * path )
	{
		if( g_selectedName != -1 )
		{
			CBool m_setGeoName = CFalse;
			for( CUInt i = 0; i < m_instanceGeometries.size(); i++ )
			{
				CGeometry* m_geo = m_instanceGeometries[i]->m_abstractGeometry;
				CBool selected = CFalse;
				if( m_instanceGeometries[i]->m_nameIndex == g_selectedName )
				{
					selected = CTrue;
				}

				for( CUInt j = 0; j < m_geo->m_groups.size(); j++ )
				{
					if( g_menu.m_geometryBasedSelection )
					{
						if( selected )
						{
							if( !m_geo->m_groups[j]->SetDiffuse( path ) )
								return CFalse;
							CChar temp[MAX_NAME_SIZE];
							Cpy( temp, path );
							GetAfterPath( temp );
							GetWithoutDot( temp );
							Cpy( m_geo->m_strDiffuse, temp );
							m_geo->m_hasDiffuse = CTrue;

							g_updateTextureViaEditor = CFalse; //save functions
							for(CUInt index = 0; index < g_allPrefabNames.size(); index++ )
							{
								IsInPrefabList(g_allPrefabNames[index].c_str(), CFalse, CTrue );
							}
						}
					}
					else //material based selection 
					{
						if( m_geo->m_groups[j]->m_nameIndex == g_selectedName )
						{
							if( !m_geo->m_groups[j]->SetDiffuse( path ) )
								return CFalse;
							m_setGeoName = CTrue;

							g_updateTextureViaEditor = CFalse; //save functions
							for (CUInt index = 0; index < g_allPrefabNames.size(); index++)
							{
								IsInPrefabList(g_allPrefabNames[index].c_str(), CFalse, CTrue);
							}

						}
					}
				}
			}

			if( !g_menu.m_geometryBasedSelection )
			{
				//whether all the groups use the same texture or not? 
				CGeometry* tempGeo = NULL;
				CBool m_foundTarget = CFalse;
				CBool m_foundGeo = CFalse;
				for( CUInt i = 0; i < m_geometries.size(); i++ )
				{
					CGeometry* m_geo = m_geometries[i];
					for( CUInt j = 0; j < m_geo->m_groups.size(); j++ )
					{
						if( m_geo->m_groups[j]->m_nameIndex == g_selectedName )
						{
							m_foundGeo = CTrue;
							tempGeo = m_geo;
						}
						if( m_foundGeo )
							break;
					}
					if( m_foundGeo )
						break;
				}
				if( m_foundGeo )
				{
					for( CUInt i = 0; i < tempGeo->m_groups.size(); i++ )
					{
						for( CUInt j = 0; j < tempGeo->m_groups.size(); j++ )
						{
							if( !Cmp( tempGeo->m_groups[i]->m_strDiffuse, tempGeo->m_groups[j]->m_strDiffuse ) ) //if these materials are not equal
							{
								m_foundTarget = CTrue;
							}
							if( m_foundTarget )
								break;
						}
						if( m_foundTarget )
							break;
					}
					if( m_foundTarget )
					{
						Cpy( tempGeo->m_strDiffuse, "*Different Textures*" );
						tempGeo->m_hasDiffuse = CTrue;
					}
					else //same materials
					{
						Cpy( tempGeo->m_strDiffuse, tempGeo->m_groups[0]->m_strDiffuse );
						tempGeo->m_hasDiffuse = CTrue;
					}
				}
			}
		}
		return CTrue;
	}

	inline CBool CScene::SetGlossMap( const CChar * path )
	{
		if( g_selectedName != -1 )
		{
			CBool m_setGeoName = CFalse;
			for( CUInt i = 0; i < m_instanceGeometries.size(); i++ )
			{
				CGeometry* m_geo = m_instanceGeometries[i]->m_abstractGeometry;
				CBool selected = CFalse;
				if( m_instanceGeometries[i]->m_nameIndex == g_selectedName )
				{
					selected = CTrue;
				}

				for( CUInt j = 0; j < m_geo->m_groups.size(); j++ )
				{
					if( g_menu.m_geometryBasedSelection )
					{
						if( selected )
						{
							if( !m_geo->m_groups[j]->SetGlossMap( path ) )
								return CFalse;
							CChar temp[MAX_NAME_SIZE];
							Cpy( temp, path );
							GetAfterPath( temp );
							GetWithoutDot( temp );
							Cpy( m_geo->m_strGlossMap, temp );
							m_geo->m_hasGlossMap = CTrue;

							g_updateTextureViaEditor = CFalse; //save functions
							for (CUInt index = 0; index < g_allPrefabNames.size(); index++)
							{
								IsInPrefabList(g_allPrefabNames[index].c_str(), CFalse, CTrue);
							}

						}
					}
					else //material based selection 
					{
						if( m_geo->m_groups[j]->m_nameIndex == g_selectedName )
						{
							if( !m_geo->m_groups[j]->SetGlossMap( path ) )
								return CFalse;
							m_setGeoName = CTrue;

							g_updateTextureViaEditor = CFalse; //save functions
							for (CUInt index = 0; index < g_allPrefabNames.size(); index++)
							{
								IsInPrefabList(g_allPrefabNames[index].c_str(), CFalse, CTrue);
							}

						}
					}
				}
			}

			if( !g_menu.m_geometryBasedSelection )
			{
				//whether all the groups use the same texture or not? 
				CGeometry* tempGeo = NULL;
				CBool m_foundTarget = CFalse;
				CBool m_foundGeo = CFalse;
				for( CUInt i = 0; i < m_geometries.size(); i++ )
				{
					CGeometry* m_geo = m_geometries[i];
					for( CUInt j = 0; j < m_geo->m_groups.size(); j++ )
					{
						if( m_geo->m_groups[j]->m_nameIndex == g_selectedName )
						{
							m_foundGeo = CTrue;
							tempGeo = m_geo;
						}
						if( m_foundGeo )
							break;
					}
					if( m_foundGeo )
						break;
				}
				if( m_foundGeo )
				{
					for( CUInt i = 0; i < tempGeo->m_groups.size(); i++ )
					{
						for( CUInt j = 0; j < tempGeo->m_groups.size(); j++ )
						{
							if( !Cmp( tempGeo->m_groups[i]->m_strGlossMap, tempGeo->m_groups[j]->m_strGlossMap ) ) //if these materials are not equal
							{
								m_foundTarget = CTrue;
							}
							if( m_foundTarget )
								break;
						}
						if( m_foundTarget )
							break;
					}
					if( m_foundTarget )
					{
						Cpy( tempGeo->m_strGlossMap, "*Different Textures*" );
						tempGeo->m_hasGlossMap = CTrue;
					}
					else //same materials
					{
						Cpy( tempGeo->m_strGlossMap, tempGeo->m_groups[0]->m_strGlossMap );
						tempGeo->m_hasGlossMap = CTrue;
					}
				}
			}
		}
		return CTrue;
	}

	inline CBool CScene::SetNormalMap( CString path, CFloat bias, CFloat scale, CBool setBias, CBool setScale )
	{
		if( g_selectedName != -1 )
		{
			CBool m_setGeoName = CFalse;
			for( CUInt i = 0; i < m_instanceGeometries.size(); i++ )
			{
				CGeometry* m_geo = m_instanceGeometries[i]->m_abstractGeometry;
				CBool selected = CFalse;
				if( m_instanceGeometries[i]->m_nameIndex == g_selectedName )
				{
					selected = CTrue;
				}

				for( CUInt j = 0; j < m_geo->m_groups.size(); j++ )
				{
					if( g_menu.m_geometryBasedSelection )
					{
						if( selected )
						{

							if( (m_geo->m_tangents && m_geo->m_bNormals ))
							{
								if( setBias )
									m_geo->m_parallaxMapBias = bias;
								if( setScale )
									m_geo->m_parallaxMapScale = scale;

								if( m_geo->m_groups[j]->SetNormalMap( path, bias, scale ) )
								{
									CChar temp[MAX_NAME_SIZE];
									Cpy( temp, path );
									GetAfterPath( temp );
									GetWithoutDot( temp );
									Cpy( m_geo->m_strNormalMap, temp );
									m_geo->m_hasNormalMap = CTrue;

									g_updateTextureViaEditor = CFalse; //save functions
									for (CUInt index = 0; index < g_allPrefabNames.size(); index++)
									{
										IsInPrefabList(g_allPrefabNames[index].c_str(), CFalse, CTrue);
									}

								}
							}
							else
							{
								MessageBox( NULL, "In order to set normal map, you must export tangent and binormal for COLLADA model", "VandaEngine Error", MB_OK | MB_ICONERROR );
								return CFalse;
							}
						}
					}
					else //material based selection 
					{
						if( m_geo->m_groups[j]->m_nameIndex == g_selectedName )
						{

							if( m_geo->m_tangents && m_geo->m_bNormals )
							{
								if( !m_geo->m_groups[j]->SetNormalMap( path, bias, scale ) )
									return CFalse;
								m_setGeoName = CTrue;

								g_updateTextureViaEditor = CFalse; //save functions
								for (CUInt index = 0; index < g_allPrefabNames.size(); index++)
								{
									IsInPrefabList(g_allPrefabNames[index].c_str(), CFalse, CTrue);
								}

							}
							else
								MessageBox( NULL, "In order to set normal map, you must export tangent and binormal for COLLADA model", "VandaEngine Error", MB_OK | MB_ICONERROR);
						}
					}
				}
			}

			if( !g_menu.m_geometryBasedSelection )
			{
				//whether all the groups use the same texture or not? 
				CGeometry* tempGeo = NULL;
				CBool m_foundTarget = CFalse;
				CBool m_foundGeo = CFalse;
				for( CUInt i = 0; i < m_geometries.size(); i++ )
				{
					CGeometry* m_geo = m_geometries[i];
					for( CUInt j = 0; j < m_geo->m_groups.size(); j++ )
					{
						if( m_geo->m_groups[j]->m_nameIndex == g_selectedName )
						{
							if( m_geometries[i]->m_tangents && m_geometries[i]->m_bNormals )
							{
								m_foundGeo = CTrue;
								tempGeo = m_geo;
							}
						}
						if( m_foundGeo )
							break;
					}
					if( m_foundGeo )
						break;
				}
				if( m_foundGeo )
				{
					for( CUInt i = 0; i < tempGeo->m_groups.size(); i++ )
					{
						for( CUInt j = 0; j < tempGeo->m_groups.size(); j++ )
						{
							if( !Cmp( tempGeo->m_groups[i]->m_strNormalMap, tempGeo->m_groups[j]->m_strNormalMap ) ) //if these materials are not equal
							{
								m_foundTarget = CTrue;
							}
							if( m_foundTarget )
								break;
						}
						if( m_foundTarget )
							break;
					}
					if( m_foundTarget )
					{
						Cpy( tempGeo->m_strNormalMap, "*Different Textures*" );
						tempGeo->m_hasNormalMap = CTrue;
					}
					else //same materials
					{
						Cpy( tempGeo->m_strNormalMap, tempGeo->m_groups[0]->m_strNormalMap );
						tempGeo->m_hasNormalMap = CTrue;
					}
				}
			}
		}
		return CTrue;
	}

	inline CBool CScene::SetDirtMap( CString path )
	{
		if( g_selectedName != -1 )
		{
			CBool m_setGeoName = CFalse;
			for( CUInt i = 0; i < m_instanceGeometries.size(); i++ )
			{
				CGeometry* m_geo = m_instanceGeometries[i]->m_abstractGeometry;
				CBool selected = CFalse;
				if( m_instanceGeometries[i]->m_nameIndex == g_selectedName )
				{
					selected = CTrue;
				}

				for( CUInt j = 0; j < m_geo->m_groups.size(); j++ )
				{
					if( g_menu.m_geometryBasedSelection )
					{
						if( selected)
						{
							if (m_geo->m_texCoords[1])
							{
								if( !m_geo->m_groups[j]->SetDirtMap( path ) )
									return CFalse;
								CChar temp[MAX_NAME_SIZE];
								Cpy( temp, path );
								GetAfterPath( temp );
								GetWithoutDot( temp );
								Cpy( m_geo->m_strDirtMap, temp );
								m_geo->m_hasDirtMap = CTrue;

								g_updateTextureViaEditor = CFalse; //save functions
								for (CUInt index = 0; index < g_allPrefabNames.size(); index++)
								{
									IsInPrefabList(g_allPrefabNames[index].c_str(), CFalse, CTrue);
								}

							}
							else
							{
								//MessageBox( NULL, "In order to set dirt map, you must export UV set 2 for COLLADA model", "VandaEngine Error", MB_OK | MB_ICONERROR);
								return CFalse;
							}
						}
					}
					else //material based selection 
					{
						if( m_geo->m_groups[j]->m_nameIndex == g_selectedName )
						{
							if( m_geo->m_texCoords[1] )
							{
								if( !m_geo->m_groups[j]->SetDirtMap( path ) )
									return CFalse;
								m_setGeoName = CTrue;

								g_updateTextureViaEditor = CFalse; //save functions
								for (CUInt index = 0; index < g_allPrefabNames.size(); index++)
								{
									IsInPrefabList(g_allPrefabNames[index].c_str(), CFalse, CTrue);
								}

							}
							else
							{
								//MessageBox(NULL, "In order to use dirt map, you must export UV set 2 for COLLADA model", "VandaEngine Error", MB_OK | MB_ICONERROR);
								return CFalse;
							}
						}
					}
				}
			}

			if( !g_menu.m_geometryBasedSelection )
			{
				//whether all the groups use the same texture or not? 
				CGeometry* tempGeo = NULL;
				CBool m_foundTarget = CFalse;
				CBool m_foundGeo = CFalse;
				for( CUInt i = 0; i < m_geometries.size(); i++ )
				{
					CGeometry* m_geo = m_geometries[i];
					for( CUInt j = 0; j < m_geo->m_groups.size(); j++ )
					{
						if( m_geo->m_groups[j]->m_nameIndex == g_selectedName )
						{
							if( m_geometries[i]->m_texCoords[1] )
							{
								m_foundGeo = CTrue;
								tempGeo = m_geo;
							}
						}
						if( m_foundGeo )
							break;
					}
					if( m_foundGeo )
						break;
				}
				if( m_foundGeo )
				{
					for( CUInt i = 0; i < tempGeo->m_groups.size(); i++ )
					{
						for( CUInt j = 0; j < tempGeo->m_groups.size(); j++ )
						{
							if( !Cmp( tempGeo->m_groups[i]->m_strDirtMap, tempGeo->m_groups[j]->m_strDirtMap ) ) //if these materials are not equal
							{
								m_foundTarget = CTrue;
							}
							if( m_foundTarget )
								break;
						}
						if( m_foundTarget )
							break;
					}
					if( m_foundTarget )
					{
						Cpy( tempGeo->m_strDirtMap, "*Different Textures*" );
						tempGeo->m_hasDirtMap = CTrue;
					}
					else //same materials
					{
						Cpy( tempGeo->m_strDirtMap, tempGeo->m_groups[0]->m_strDirtMap );
						tempGeo->m_hasDirtMap = CTrue;
					}
				}
			}
		}
		return CTrue;
	}


	inline CBool CScene::SetHeightMap( CString path )
	{
		if( g_selectedName != -1 )
		{
			for( CUInt i = 0; i < m_geometries.size(); i++ )
			{
				if( m_geometries[i]->m_nameIndex == g_selectedName )
					m_geometries[i]->SetHeightMap( path );
			}
		}
		return CTrue;
	}

	inline CVoid CScene::RemoveDiffuse()
	{
		if( g_selectedName != -1 )
		{
			if( g_menu.m_geometryBasedSelection )
			{
				for( CUInt i = 0; i < m_instanceGeometries.size(); i++ )
				{
					CBool selected = CFalse;
					if( m_instanceGeometries[i]->m_nameIndex == g_selectedName )
					{
						selected = CTrue;
					}

					if( selected )
					{
						for( CUInt j = 0; j < m_instanceGeometries[i]->m_abstractGeometry->m_groups.size(); j++ )
						{
							m_instanceGeometries[i]->m_abstractGeometry->RemoveDiffuse();
							m_instanceGeometries[i]->m_abstractGeometry->m_groups[j]->RemoveDiffuse();
						}
					}
				}
			}
			else //material based selection
			{
				for( CUInt i = 0; i < m_geometries.size(); i++ )
				{
					for( CUInt j = 0; j < m_geometries[i]->m_groups.size(); j++ )
					{
						if( m_geometries[i]->m_groups[j]->m_nameIndex == g_selectedName )
							m_geometries[i]->m_groups[j]->RemoveDiffuse();
					}
				} 
				CUInt numGroups = 0;
				CGeometry* m_geo = NULL;
				CBool foundGeo = CFalse;
				for( CUInt i = 0; i < m_geometries.size(); i++ )
				{
					for( CUInt j = 0; j < m_geometries[i]->m_groups.size(); j++ )
					{
						if( m_geometries[i]->m_groups[j]->m_nameIndex == g_selectedName )
						{
							m_geo = m_geometries[i];
							foundGeo = CTrue;

							for( CUInt k = 0; k < m_geometries[i]->m_groups.size(); k++ )
							{
								if( !m_geometries[i]->m_groups[k]->m_hasDiffuse )
								{
									numGroups++;
								}
							}
						}
						if( foundGeo )
							break;
					}
					if( foundGeo )
						break;
				}
				if( foundGeo )
				{
					if ( CUInt( m_geo->m_groups.size() ) == numGroups )
					{
						m_geo->RemoveDiffuse();
					}
					else
					{
						Cpy( m_geo->m_strDiffuse, "*Different Textures*" );
						m_geo->m_hasDiffuse = CTrue;
					}
				}
			}
		}
	}

	inline CVoid CScene::RemoveGlossMap()
	{
		if( g_selectedName != -1 )
		{
			if( g_menu.m_geometryBasedSelection )
			{
				for( CUInt i = 0; i < m_instanceGeometries.size(); i++ )
				{
					CBool selected = CFalse;
					if( m_instanceGeometries[i]->m_nameIndex == g_selectedName )
					{
						selected = CTrue;
					}

					if( selected )
					{
						for( CUInt j = 0; j < m_instanceGeometries[i]->m_abstractGeometry->m_groups.size(); j++ )
						{
							m_instanceGeometries[i]->m_abstractGeometry->RemoveGlossMap();
							m_instanceGeometries[i]->m_abstractGeometry->m_groups[j]->RemoveGlossMap();
						}
					}
				}
			}
			else //material based selection
			{
				for( CUInt i = 0; i < m_geometries.size(); i++ )
				{
					for( CUInt j = 0; j < m_geometries[i]->m_groups.size(); j++ )
					{
						if( m_geometries[i]->m_groups[j]->m_nameIndex == g_selectedName )
							m_geometries[i]->m_groups[j]->RemoveGlossMap();
					}
				} 
				CUInt numGroups = 0;
				CGeometry* m_geo = NULL;
				CBool foundGeo = CFalse;
				for( CUInt i = 0; i < m_geometries.size(); i++ )
				{
					for( CUInt j = 0; j < m_geometries[i]->m_groups.size(); j++ )
					{
						if( m_geometries[i]->m_groups[j]->m_nameIndex == g_selectedName )
						{
							m_geo = m_geometries[i];
							foundGeo = CTrue;

							for( CUInt k = 0; k < m_geometries[i]->m_groups.size(); k++ )
							{
								if( !m_geometries[i]->m_groups[k]->m_hasGlossMap )
								{
									numGroups++;
								}
							}
						}
						if( foundGeo )
							break;
					}
					if( foundGeo )
						break;
				}
				if( foundGeo )
				{
					if ( CUInt( m_geo->m_groups.size() ) == numGroups )
					{
					m_geo->RemoveGlossMap();
					}
					else
					{
						Cpy( m_geo->m_strGlossMap, "*Different Textures*" );
						m_geo->m_hasGlossMap = CTrue;
					}
				}
			}
		}
	}

	inline CVoid CScene::RemoveNormalMap()
	{
		if( g_selectedName != -1 )
		{
			if( g_menu.m_geometryBasedSelection )
			{
				for( CUInt i = 0; i < m_instanceGeometries.size(); i++ )
				{
					CBool selected = CFalse;
					if( m_instanceGeometries[i]->m_nameIndex == g_selectedName )
					{
						selected = CTrue;
					}

					if( selected )
					{
						for( CUInt j = 0; j < m_instanceGeometries[i]->m_abstractGeometry->m_groups.size(); j++ )
						{
							m_instanceGeometries[i]->m_abstractGeometry->RemoveNormalMap();
							m_instanceGeometries[i]->m_abstractGeometry->m_groups[j]->RemoveNormalMap();
						}
					}
				}
			}
			else //material based selection
			{
				for( CUInt i = 0; i < m_geometries.size(); i++ )
				{
					for( CUInt j = 0; j < m_geometries[i]->m_groups.size(); j++ )
					{
						if( m_geometries[i]->m_groups[j]->m_nameIndex == g_selectedName )
							m_geometries[i]->m_groups[j]->RemoveNormalMap();
					}
				} 
				CUInt numGroups = 0;
				CGeometry* m_geo = NULL;
				CBool foundGeo = CFalse;
				for( CUInt i = 0; i < m_geometries.size(); i++ )
				{
					for( CUInt j = 0; j < m_geometries[i]->m_groups.size(); j++ )
					{
						if( m_geometries[i]->m_groups[j]->m_nameIndex == g_selectedName )
						{
							m_geo = m_geometries[i];
							foundGeo = CTrue;

							for( CUInt k = 0; k < m_geometries[i]->m_groups.size(); k++ )
							{
								if( !m_geometries[i]->m_groups[k]->m_hasNormalMap )
								{
									numGroups++;
								}
							}
						}
						if( foundGeo )
							break;
					}
					if( foundGeo )
						break;
				}
				if( foundGeo )
				{
					if ( CUInt( m_geo->m_groups.size() ) == numGroups )
					{
					m_geo->RemoveNormalMap();
					}
					else
					{
						Cpy( m_geo->m_strNormalMap, "*Different Textures*" );
						m_geo->m_hasNormalMap = CTrue;
					}
				}
			}
		}
	}

	inline CVoid CScene::RemoveDirtMap()
	{
		if( g_selectedName != -1 )
		{
			if( g_menu.m_geometryBasedSelection )
			{
				for( CUInt i = 0; i < m_instanceGeometries.size(); i++ )
				{
					CBool selected = CFalse;
					if( m_instanceGeometries[i]->m_nameIndex == g_selectedName )
					{
						selected = CTrue;
					}

					if( selected )
					{
						for( CUInt j = 0; j < m_instanceGeometries[i]->m_abstractGeometry->m_groups.size(); j++ )
						{
							m_instanceGeometries[i]->m_abstractGeometry->RemoveDirtMap();
							m_instanceGeometries[i]->m_abstractGeometry->m_groups[j]->RemoveDirtMap();
						}
					}
				}
			}
			else //material based selection
			{
				for( CUInt i = 0; i < m_geometries.size(); i++ )
				{
					for( CUInt j = 0; j < m_geometries[i]->m_groups.size(); j++ )
					{
						if( m_geometries[i]->m_groups[j]->m_nameIndex == g_selectedName )
							m_geometries[i]->m_groups[j]->RemoveDirtMap();
					}
				} 
				CUInt numGroups = 0;
				CGeometry* m_geo = NULL;
				CBool foundGeo = CFalse;
				for( CUInt i = 0; i < m_geometries.size(); i++ )
				{
					for( CUInt j = 0; j < m_geometries[i]->m_groups.size(); j++ )
					{
						if( m_geometries[i]->m_groups[j]->m_nameIndex == g_selectedName )
						{
							m_geo = m_geometries[i];
							foundGeo = CTrue;

							for( CUInt k = 0; k < m_geometries[i]->m_groups.size(); k++ )
							{
								if( !m_geometries[i]->m_groups[k]->m_hasDirtMap )
								{
									numGroups++;
								}
							}
						}
						if( foundGeo )
							break;
					}
					if( foundGeo )
						break;
				}
				if( foundGeo )
				{
					if ( CUInt( m_geo->m_groups.size() ) == numGroups )
					{
					m_geo->RemoveDirtMap();
					}
					else
					{
						Cpy( m_geo->m_strDirtMap, "*Different Textures*" );
						m_geo->m_hasDirtMap = CTrue;
					}
				}
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
			for( CUInt i = 0; i < m_instanceGeometries.size(); i++ )
			{
				if( m_instanceGeometries[i]->m_nameIndex == g_selectedName )
					m_instanceGeometries[i]->m_abstractGeometry->SetCullFace( cullFace );
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
	std::vector<CNode*> m_allNodes;
	std::vector<CInstanceCamera *> m_cameraInstances;
	std::vector<CInstanceLight *>	m_lightInstances;

	CNode* m_sceneRoot;

	//CGcontext m_cgContext;
	std::vector<std::string> m_lodSceneList;
	CBool m_isLODScene; //is this scene a LOD scene?
	CScene* m_baseOfLODScene; //If it's a LOD scene, it has a base. Otherwise, base is NULL

private:
	CBool ReadImageLibrary( domLibrary_imagesRef lib );
	CImage *ReadImage( domImageRef lib );

	CBool ReadEffectLibrary( domLibrary_effectsRef lib );
	CEffect *ReadEffect( domEffectRef lib ); 

	CBool ReadMaterialLibrary( domLibrary_materialsRef lib );
	CMaterial *ReadMaterial( domMaterialRef lib ); 

	CBool ReadAnimationLibrary( domLibrary_animationsRef lib, CBool loadTempAnimations = CFalse );
	CAnimation *ReadAnimation( domAnimationRef lib, CBool loadTempAnimations = CFalse );
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

	CBool ReadScene( domVisual_sceneRef scene, CUpAxis up);
	CNode* ReadNode( domNodeRef node, CNode * parentNode );
	CBool ReadNodeTransforms( CNode * tempNode, domNodeRef node );
	CNode * GetNode( const CChar * name );
	CInstanceGeometry * ReadInstanceGeometry( domInstance_geometryRef lib);
	CInstanceMaterial *ReadInstanceMaterial( domInstance_materialRef lib);

	CGeometry *ReadGeometry( domGeometryRef lib , CController * controller = 0 );
	CTriangles *BuildTriangles(domTriangles * dom_triangles, CGeometry * geometry, CController* controller, CUInt i );

public:
    CVoid CalculateTangentArray(CGeometry* newGeo);
	CVoid DeindexMesh( CUInt initialVertexCount, CUInt totalVertexCount, CGeometry* geometry, CPolyGroup* triangles );

	CInt GetClipIndexForStartup();
	CVoid SetClipIndexForStartup( CInt index );
	CVoid SetClipIndex( CInt index, CBool loopAnimation = CTrue );
	CVoid SetCurrentClipIndex(CInt index);
	CVoid SetNextAnimation();
	CVoid SetPrevAnimation();
	CVoid SetCurrentClipIndex();
	CInt GetCurrentClipIndex();
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