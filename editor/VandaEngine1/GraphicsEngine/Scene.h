//Copyright (C) 2020 Ehsan Kamrani 
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
	//deprecate
	CBool m_loopAnimationAtStartup, m_playAnimation, m_alwaysVisible, m_castShadow;
	CBool m_updateBoundingBox;
	//new way
	std::vector<std::string>m_executeActionList;
	std::vector<std::string>m_blendCycleList;
	//new way
	CBool BlendCycle(CInt id, CFloat weight, CFloat delay);
	CBool ClearCycle(CInt id, CFloat delay);
	CBool ExecuteAction(CInt id, CFloat delayIn, CFloat delayOut, CFloat weightTarget = 1.0f, CBool autoLock=CFalse);
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

	CBool RemovePhysX()
	{
		if( g_selectedName != -1 )
		{
			CBool m_setGeoName = CFalse;
			for( CUInt geoCounter = 0; geoCounter < m_geometries.size(); geoCounter++ )
			{
				CGeometry* m_geo = m_geometries[geoCounter];
				CBool selected = CFalse;
				CInstanceGeometry* m_instanceGeo;
				for( CUInt k = 0; k < m_geo->m_instanceGeometries.size(); k++ )
				{
					if( m_geo->m_instanceGeometries[k]->m_nameIndex == g_selectedName )
					{
						selected = CTrue;
						m_instanceGeo = m_geo->m_instanceGeometries[k];
						break;
					}
				}
				if( !selected ) //check for controllers
				{
					for( CUInt k = 0; k < m_geo->m_instanceControllers.size(); k++ )
					{
						CInstanceGeometry* tempInstanceGeo = m_geo->m_instanceControllers[k]->m_instanceGeometry;
						if( tempInstanceGeo->m_nameIndex == g_selectedName )
						{
							selected = CTrue;
							m_instanceGeo = tempInstanceGeo;
							break;
						}
					}
				}

				if( selected )
				{
					//Remove PhysX 
					//for( CUInt i = 1; i < gPhysicsSDK->getNbScenes(); i++ )
					//{
						NxScene* tempScene = gPhysXscene/*gPhysicsSDK->getScene(i)*/;
						if( tempScene )
						{
							for( CUInt j = 0; j < tempScene->getNbActors(); j++ )
							{
								CChar actorName[MAX_URI_SIZE];
								if( !tempScene->getActors()[j]->getName() ) continue;
								Cpy( actorName, tempScene->getActors()[j]->getName() );
								if( !Cmp(m_instanceGeo->m_physXName, "\n" ) && Cmp( actorName, m_instanceGeo->m_physXName ) )
								{
									//recomupte bounding box
									CGeometry* tempGeometry = m_instanceGeo->m_abstractGeometry;

									CVec3f src[8];
									src[0].x = tempGeometry->m_minAABB.m_i; src[0].y = tempGeometry->m_minAABB.m_j; src[0].z = tempGeometry->m_minAABB.m_k;
									src[1].x = tempGeometry->m_maxAABB.m_i; src[1].y = tempGeometry->m_minAABB.m_j; src[1].z = tempGeometry->m_maxAABB.m_k;
									src[2].x = tempGeometry->m_maxAABB.m_i; src[2].y = tempGeometry->m_minAABB.m_j; src[2].z = tempGeometry->m_minAABB.m_k;
									src[3].x = tempGeometry->m_minAABB.m_i; src[3].y = tempGeometry->m_minAABB.m_j; src[3].z = tempGeometry->m_maxAABB.m_k;
									src[4].x = tempGeometry->m_maxAABB.m_i; src[4].y = tempGeometry->m_maxAABB.m_j; src[4].z = tempGeometry->m_minAABB.m_k;
									src[5].x = tempGeometry->m_minAABB.m_i; src[5].y = tempGeometry->m_maxAABB.m_j; src[5].z = tempGeometry->m_minAABB.m_k;
									src[6].x = tempGeometry->m_minAABB.m_i; src[6].y = tempGeometry->m_maxAABB.m_j; src[6].z = tempGeometry->m_maxAABB.m_k;
									src[7].x = tempGeometry->m_maxAABB.m_i; src[7].y = tempGeometry->m_maxAABB.m_j; src[7].z = tempGeometry->m_maxAABB.m_k;

									CMatrixTransform( m_instanceGeo->m_localToWorldMatrix, src[0], m_instanceGeo->m_localToWorldVertex[0] );
									CMatrixTransform( m_instanceGeo->m_localToWorldMatrix, src[1], m_instanceGeo->m_localToWorldVertex[1] );
									CMatrixTransform( m_instanceGeo->m_localToWorldMatrix, src[2], m_instanceGeo->m_localToWorldVertex[2] );
									CMatrixTransform( m_instanceGeo->m_localToWorldMatrix, src[3], m_instanceGeo->m_localToWorldVertex[3] );
									CMatrixTransform( m_instanceGeo->m_localToWorldMatrix, src[4], m_instanceGeo->m_localToWorldVertex[4] );
									CMatrixTransform( m_instanceGeo->m_localToWorldMatrix, src[5], m_instanceGeo->m_localToWorldVertex[5] );
									CMatrixTransform( m_instanceGeo->m_localToWorldMatrix, src[6], m_instanceGeo->m_localToWorldVertex[6] );
									CMatrixTransform( m_instanceGeo->m_localToWorldMatrix, src[7], m_instanceGeo->m_localToWorldVertex[7] );
									///////////////////////////

									tempScene->releaseActor( *tempScene->getActors()[j] );
									m_instanceGeo->m_hasPhysX = CFalse;
									Cpy( m_instanceGeo->m_physXName, "\n" );
									if( m_instanceGeo->m_lodAlgorithm == eLOD_LENGTH_CURVATURE || m_instanceGeo->m_lodAlgorithm == eLOD_LENGTH )
										m_instanceGeo->m_prevLodAlgorithm = m_instanceGeo->m_lodAlgorithm;
									m_instanceGeo->m_lodAlgorithm = eLOD_NONE;
									return CTrue;
								}
							}
						}
						else
							return CFalse;
					//}
				}
			} //for all of the geometries
		} //if something was selected
		return CFalse;
	}

	CInt GeneratePhysX(CPhysXAlgorithm algorithm, CFloat density, CInt percentage, CBool isTrigger, CBool isInvisible, CInstanceGeometry* m_instanceGeo, CBool loadFromFile = CFalse, CInstancePrefab* prefab = NULL);

	CInt GeneratePhysX( CPhysXAlgorithm algorithm, CFloat density, CInt percentage, CBool isTrigger, CBool isInvisible )
	{
		if( g_selectedName != -1 )
		{
			for( CUInt geoCounter = 0; geoCounter < m_geometries.size(); geoCounter++ )
			{
				CGeometry* m_geo = m_geometries[geoCounter];
				CBool selected = CFalse;
				CInstanceGeometry* m_instanceGeo;
				for( CUInt k = 0; k < m_geo->m_instanceGeometries.size(); k++ )
				{
					if( m_geo->m_instanceGeometries[k]->m_nameIndex == g_selectedName )
					{
						selected = CTrue;
						m_instanceGeo = m_geo->m_instanceGeometries[k];
						break;
					}
				}
				if( !selected ) //check for controllers
				{
					for( CUInt k = 0; k < m_geo->m_instanceControllers.size(); k++ )
					{
						CInstanceGeometry* tempInstanceGeo = m_geo->m_instanceControllers[k]->m_instanceGeometry;
						if( tempInstanceGeo->m_nameIndex == g_selectedName )
						{
							selected = CTrue;
							m_instanceGeo = tempInstanceGeo;
							break;
						}
					}
				}

				if( selected )
				{
					CGeometry* m_geo = m_instanceGeo->m_abstractGeometry;

					if( m_geo->m_physx_points.size() == 0 )
					{
						CUInt initialVertexCount = 0;
						CUInt totalVertexCount = 0;
						//DeIndex Mesh
						for( CUInt groupCount = 0; groupCount < m_geo->m_groups.size(); groupCount++ )
						{
							CPolyGroup* triangle = m_geo->m_groups[groupCount];
							totalVertexCount += m_geo->m_groups[groupCount]->m_count * 3;
							if( groupCount != 0 )
								initialVertexCount += m_geo->m_groups[groupCount-1]->m_count * 3;


							DeindexMesh( initialVertexCount, totalVertexCount, m_geo, triangle );
						}
					}

					if( m_instanceGeo->m_abstractGeometry->m_collapseMap.num == 0 && (algorithm == eLOD_LENGTH_CURVATURE || algorithm == eLOD_LENGTH ) )
					{
						PrintInfo( "\nCalculating LOD..." );
						m_instanceGeo->m_abstractGeometry->CalculateLODInfo(algorithm);
					}
					else
					{
						if( (algorithm == eLOD_LENGTH_CURVATURE || algorithm == eLOD_LENGTH ) && (m_instanceGeo->m_prevLodAlgorithm == eLOD_LENGTH_CURVATURE ||
							m_instanceGeo->m_prevLodAlgorithm == eLOD_LENGTH ) )
						{
							if( m_instanceGeo->m_prevLodAlgorithm != algorithm ) //regenerate PhysX informations
							{
								PrintInfo( "\nRegenerating LOD..." );
								m_instanceGeo->m_abstractGeometry->CalculateLODInfo(algorithm);
							}

						}

					}
					//Generate PhysX mesh////////////////
					std::vector<CFloat> vertices_temp;
					std::vector<CInt> triangles_temp;
					CInt num_verts;
					if( algorithm == eLOD_LENGTH_CURVATURE || algorithm == eLOD_LENGTH )
					{
						num_verts = CInt( CFloat(m_geo->m_physx_points.size() ) * (CFloat)((CFloat)percentage / 100.0f ) );
						if( num_verts < 3 ) num_verts = 3;
						m_geo->RegenerateIndex(num_verts, triangles_temp );
					}
					else
					{
						num_verts = CInt( m_geo->m_physx_points.size() );
					}
					//Scale, Rotation and Translation Matrices for Convex Hulls, Box, Sphere, and Cylinder
					CMatrix ZUpRotationForSkins;
					CMatrixLoadIdentity(ZUpRotationForSkins);
					CNode* tempParentNode = m_instanceGeo->m_node;
					CBool foundTarget = CFalse;

					CMatrix convexLocalToWorld;
					const CMatrix *convex_ltow;
					convex_ltow = m_instanceGeo->m_node->GetLocalToWorldMatrix();
					CMatrixCopy(*convex_ltow, convexLocalToWorld); 
					CMatrix4x4Mult( convexLocalToWorld, ZUpRotationForSkins );
					CMatrixCopy(ZUpRotationForSkins, convexLocalToWorld); 

					//decomp_affine;
					AffineParts *parts = CNew( AffineParts);
					HMatrix A;
					CUInt k = 0;
					for( CUInt i = 0; i < 4; i++ )
						for( CUInt j = 0; j < 4; j++ )
						{
							A[j][i] = convexLocalToWorld[k];
							k++;
						}
					decomp_affine(A, parts);
					//rotation
					CMatrix convexRotationMatrix;
					CQuat convexQRotation(parts->q.x, parts->q.y, parts->q.z, parts->q.w );
					CMatrixLoadIdentity( convexRotationMatrix );
					CQuaternionToMatrix( &convexQRotation, convexRotationMatrix );

					//////////////////////////SHEARING//////////////////////////////
					CMatrix finalRS;
					CMatrixLoadIdentity( finalRS );
					//rotation scale
					CMatrix convexRotationScaleMatrix;
					CQuat convexQRotationScale( parts->u.x, parts->u.y, parts->u.z, parts->u.w );
					CMatrixLoadIdentity( convexRotationScaleMatrix );
					CQuaternionToMatrix( &convexQRotationScale, convexRotationScaleMatrix );
					//transpose of rotation scale
					CMatrix tConvexRotationScaleMatrix;
					CMatrixLoadIdentity( tConvexRotationScaleMatrix );
					CMatrixTranspose( convexRotationScaleMatrix, tConvexRotationScaleMatrix );
					//scale factor
					CMatrix convexScaleMatrix;
					CVec4f convexScaleFactor( parts->f * parts->k.x, parts->f * parts->k.y, parts->f * parts->k.z, parts->f * parts->k.w );
					CMatrixLoadIdentity( convexScaleMatrix );
					CMatrix4x4Scale( convexScaleMatrix, convexScaleFactor );

					//Compute UK(Ut) for possible shearing
					CMatrix4x4Mult( convexRotationScaleMatrix , finalRS );
					CMatrix4x4Mult( convexScaleMatrix , finalRS );
					CMatrix4x4Mult( tConvexRotationScaleMatrix , finalRS );
					///////////////////////////END OF SHEARING//////////////////////
					CDelete( parts );

					CVec3f convexPosition( convexLocalToWorld[12], convexLocalToWorld[13], convexLocalToWorld[14]);

					NxVec3 NxConvexRow0( convexRotationMatrix[0], convexRotationMatrix[4], convexRotationMatrix[8] );
					NxVec3 NxConvexRow1( convexRotationMatrix[1], convexRotationMatrix[5], convexRotationMatrix[9] );
					NxVec3 NxConvexRow2( convexRotationMatrix[2], convexRotationMatrix[6], convexRotationMatrix[10] );
					NxMat33 NxConvexMat33Rotation( NxConvexRow0, NxConvexRow1, NxConvexRow2 );
					////////////////
					CMatrix PhysXMatrix;
					CMatrixLoadIdentity( PhysXMatrix );
					tempParentNode = m_instanceGeo->m_node;
					foundTarget = CFalse;
					for( CUInt i = 0; i < 16; i++ )
					{
						PhysXMatrix[i] = m_instanceGeo->m_localToWorldMatrix[i];
					}

					for( CUInt i = 0; i < m_geo->m_physx_points.size(); i++ )
					{
						CVec3f v = *(m_geo->m_physx_points[i]);

						if( algorithm == eLOD_LENGTH_CURVATURE || algorithm == eLOD_LENGTH )
						{
							CVec3f tv = *(m_geo->m_physx_points[i]);
							CMatrixTransform(PhysXMatrix, v,  tv);
							vertices_temp.push_back(tv.x);
							vertices_temp.push_back(tv.y);
							vertices_temp.push_back(tv.z);
						}
						else
						{
							CVec3f tv = *(m_geo->m_physx_points[i]);
							CMatrixTransform(finalRS, v,  tv);
							vertices_temp.push_back(tv.x);
							vertices_temp.push_back(tv.y);
							vertices_temp.push_back(tv.z);
						}
					}
					CFloat* vertices = NULL;
					CInt* triangles = NULL;
					if( vertices_temp.size() > 0)
						vertices = &vertices_temp[0];
					if( triangles_temp.size() > 0 )
						triangles = &triangles_temp[0];
						CBool failed = CFalse;
					if( vertices != NULL && triangles != NULL && (algorithm == eLOD_LENGTH_CURVATURE || algorithm == eLOD_LENGTH ) )
					{
						if( !g_multipleView->m_nx->CreateTriangleMesh( (CInt)(vertices_temp.size()/3), (CInt)(triangles_temp.size()/3), vertices, triangles, isTrigger, m_instanceGeo->m_physXName ) )
							failed = CTrue;
						else
							sprintf( m_instanceGeo->m_physXName, "%s%d", "PhysX_mesh_", m_instanceGeo->m_nameIndex );

					}
					else if( vertices != NULL && algorithm == eLOD_CONVEX_HULL )
					{
						if( !g_multipleView->m_nx->CreateConvexMesh( (CInt)(vertices_temp.size()/3), vertices, NxVec3(convexPosition.x, convexPosition.y, convexPosition.z), NxConvexMat33Rotation, density, m_instanceGeo->m_physXName, isTrigger, m_instanceGeo->m_abstractGeometry->m_hasAnimation ) )
							failed = CTrue;
						else
							sprintf( m_instanceGeo->m_physXName, "%s%d", "PhysX_mesh_", m_instanceGeo->m_nameIndex );
					}
					////////////////////////////////////////
					if( algorithm == eLOD_LENGTH_CURVATURE || algorithm == eLOD_LENGTH || algorithm == eLOD_CONVEX_HULL )
					{
						vertices_temp.clear();
						triangles_temp.clear();
						vertices = NULL;
						triangles = NULL;

						if( !failed )
						{
							m_instanceGeo->m_lodAlgorithm = algorithm;
							if( algorithm != eLOD_CONVEX_HULL )
								m_instanceGeo->m_prevLodAlgorithm = algorithm;	
							m_instanceGeo->m_hasPhysX = CTrue;
							m_instanceGeo->m_physXDensity = density;
							m_instanceGeo->m_physXPercentage = percentage;
							m_instanceGeo->m_isTrigger = isTrigger;
							m_instanceGeo->m_isInvisible = isInvisible;

							return m_instanceGeo->m_nameIndex;
						}
						else
							return -1;

					}
					else if( algorithm == eLOD_BOX || algorithm == eLOD_TRIGGER)
					{
						CFloat DimX, DimY, DimZ;
						CFloat PosX, PosY, PosZ;
						PosX = (m_instanceGeo->m_maxLocalToWorldAABB.x + m_instanceGeo->m_minLocalToWorldAABB.x ) / 2.f;
						PosY = (m_instanceGeo->m_maxLocalToWorldAABB.y + m_instanceGeo->m_minLocalToWorldAABB.y )/ 2.f;
						PosZ = (m_instanceGeo->m_maxLocalToWorldAABB.z + m_instanceGeo->m_minLocalToWorldAABB.z )/ 2.f;

						//scale: For all of vertexes of original mesh, multiply the SR matrix by each vertex and find the bouding box
						CVec3f m_minAABB;
						CVec3f m_maxAABB;
						m_minAABB.x = m_minAABB.y = m_minAABB.z = 100000000.0f;
						m_maxAABB.x = m_maxAABB.y = m_maxAABB.z = -100000000.0f;

						for ( CUInt i = 0; i < vertices_temp.size()/3; i++ )
						{
							if( vertices_temp[i * 3] > m_maxAABB.x )
								m_maxAABB.x =  vertices_temp[i * 3];
							if( vertices_temp[(i*3)+1] > m_maxAABB.y )
								m_maxAABB.y = vertices_temp[(i*3)+1];
							if( vertices_temp[(i*3)+2]  > m_maxAABB.z)
								m_maxAABB.z =  vertices_temp[(i*3)+2];

							if( vertices_temp[i * 3] < m_minAABB.x )
								m_minAABB.x =  vertices_temp[i * 3];
							if( vertices_temp[(i*3)+1] < m_minAABB.y )
								m_minAABB.y = vertices_temp[(i*3)+1];
							if( vertices_temp[(i*3)+2]  < m_minAABB.z)
								m_minAABB.z =  vertices_temp[(i*3)+2];
						}


						CVec3f min( m_minAABB.x, m_minAABB.y, m_minAABB.z );
						CVec3f max( m_maxAABB.x, m_maxAABB.y, m_maxAABB.z );

						DimX = fabs(max.x - min.x ) / 2.f;
						DimY = fabs(max.y - min.y )/ 2.f;
						DimZ = fabs(max.z - min.z )/ 2.f;
						////////////////
						if( algorithm == eLOD_BOX )
							g_multipleView->m_nx->CreateBox(  NxVec3(PosX,PosY,PosZ), NxVec3( DimX, DimY, DimZ), density, NxConvexMat33Rotation, m_instanceGeo->m_physXName, isTrigger, m_instanceGeo->m_abstractGeometry->m_hasAnimation );
						else
							g_multipleView->m_nx->CreateTriggerBox(  NxVec3(PosX,PosY,PosZ), NxVec3( DimX, DimY, DimZ), NxConvexMat33Rotation, m_instanceGeo->m_physXName, m_instanceGeo->m_abstractGeometry->m_hasAnimation );
						sprintf( m_instanceGeo->m_physXName, "%s%d", "PhysX_mesh_", m_instanceGeo->m_nameIndex );
						m_instanceGeo->m_lodAlgorithm = algorithm;	
						m_instanceGeo->m_hasPhysX = CTrue;
						m_instanceGeo->m_physXDensity = density;
						m_instanceGeo->m_physXPercentage = percentage;
						m_instanceGeo->m_isTrigger = isTrigger;
						m_instanceGeo->m_isInvisible = isInvisible;

						vertices_temp.clear();
						triangles_temp.clear();
						vertices = NULL;
						triangles = NULL;

						return m_instanceGeo->m_nameIndex;
					}
					else if( algorithm == eLOD_SPHERE )
					{
						CFloat PosX, PosY, PosZ;
						PosX = (m_instanceGeo->m_maxLocalToWorldAABB.x + m_instanceGeo->m_minLocalToWorldAABB.x ) / 2.f;
						PosY = (m_instanceGeo->m_maxLocalToWorldAABB.y + m_instanceGeo->m_minLocalToWorldAABB.y )/ 2.f;
						PosZ = (m_instanceGeo->m_maxLocalToWorldAABB.z + m_instanceGeo->m_minLocalToWorldAABB.z )/ 2.f;

						CFloat radius = 0.0f;
						for ( CUInt i = 0; i < vertices_temp.size()/3; i++ )
						{
							CVec3f cPos(0,0,0);
							CVec3f vPos;
							vPos.x = vertices_temp[i * 3]; vPos.y = vertices_temp[(i*3)+1]; vPos.z = vertices_temp[(i*3)+2] ;
							CFloat length = (vPos - cPos).Size();
							if( radius < length )
								radius = length;
						}
			
						g_multipleView->m_nx->CreateSphere( NxVec3( PosX, PosY, PosZ ), radius, density, m_instanceGeo->m_physXName, isTrigger, m_instanceGeo->m_abstractGeometry->m_hasAnimation );
						sprintf( m_instanceGeo->m_physXName, "%s%d", "PhysX_mesh_", m_instanceGeo->m_nameIndex );
						m_instanceGeo->m_lodAlgorithm = algorithm;	
						m_instanceGeo->m_hasPhysX = CTrue;
						m_instanceGeo->m_physXDensity = density;
						m_instanceGeo->m_physXPercentage = percentage;
						m_instanceGeo->m_isTrigger = isTrigger;
						m_instanceGeo->m_isInvisible = isInvisible;

						vertices_temp.clear();
						triangles_temp.clear();
						vertices = NULL;
						triangles = NULL;

						return m_instanceGeo->m_nameIndex;
					}
					else if( algorithm == eLOD_CAPSULE_METHOD1 || algorithm == eLOD_CAPSULE_METHOD2 || algorithm == eLOD_CAPSULE_METHOD3 )
					{
						//For all of vertexes of original mesh, find the bouding box
						CVec3f m_minAABB;
						CVec3f m_maxAABB;
						m_minAABB.x = m_minAABB.y = m_minAABB.z = 100000000.0f;
						m_maxAABB.x = m_maxAABB.y = m_maxAABB.z = -100000000.0f;

						for ( CUInt i = 0; i < vertices_temp.size()/3; i++ )
						{
							if( vertices_temp[i * 3] > m_maxAABB.x )
								m_maxAABB.x =  vertices_temp[i * 3];
							if( vertices_temp[(i*3)+1] > m_maxAABB.y )
								m_maxAABB.y = vertices_temp[(i*3)+1];
							if( vertices_temp[(i*3)+2]  > m_maxAABB.z)
								m_maxAABB.z =  vertices_temp[(i*3)+2];

							if( vertices_temp[i * 3] < m_minAABB.x )
								m_minAABB.x =  vertices_temp[i * 3];
							if( vertices_temp[(i*3)+1] < m_minAABB.y )
								m_minAABB.y = vertices_temp[(i*3)+1];
							if( vertices_temp[(i*3)+2]  < m_minAABB.z)
								m_minAABB.z =  vertices_temp[(i*3)+2];
						}


						CFloat radius, height, PosX, PosY, PosZ;
						if( algorithm == eLOD_CAPSULE_METHOD1 )
						{
							CVec4f rot( 1.0, .0, 0.0, 90.0 );
							CMatrix4x4RotateAngleAxis( convexRotationMatrix, rot );

							radius = fabs(m_maxAABB.x - m_minAABB.x ) / 2.f;
							if( radius < fabs(m_maxAABB.y - m_minAABB.y )/ 2.f )
								radius = fabs(m_maxAABB.y - m_minAABB.y )/ 2.f;

							height = fabs( fabs(m_maxAABB.z - m_minAABB.z ) - radius );
						}
						else if( algorithm == eLOD_CAPSULE_METHOD2 )//second method
						{
							radius = fabs(m_maxAABB.x - m_minAABB.x ) / 2.f;
							if( radius < fabs(m_maxAABB.z - m_minAABB.z )/ 2.f )
								radius = fabs(m_maxAABB.z - m_minAABB.z )/ 2.f;

							height = fabs( fabs(m_maxAABB.y - m_minAABB.y ) - radius );
						}
						else if( algorithm == eLOD_CAPSULE_METHOD3 )//second method
						{
							CVec4f rot( 0.0, 0.0, 1.0, 90.0 );
							CMatrix4x4RotateAngleAxis( convexRotationMatrix, rot );

							radius = fabs(m_maxAABB.y - m_minAABB.y ) / 2.f;
							if( radius < fabs(m_maxAABB.z - m_minAABB.z )/ 2.f )
								radius = fabs(m_maxAABB.z - m_minAABB.z )/ 2.f;

							height = fabs( fabs(m_maxAABB.x - m_minAABB.x ) - radius );
						}
						NxVec3 NxCapsuleRow0( convexRotationMatrix[0], convexRotationMatrix[4], convexRotationMatrix[8] );
						NxVec3 NxCapsuleRow1( convexRotationMatrix[1], convexRotationMatrix[5], convexRotationMatrix[9] );
						NxVec3 NxCapsuleRow2( convexRotationMatrix[2], convexRotationMatrix[6], convexRotationMatrix[10] );
						NxMat33 NxCapsuleMat33Rotation( NxCapsuleRow0, NxCapsuleRow1, NxCapsuleRow2 );

						PosX = (m_instanceGeo->m_maxLocalToWorldAABB.x + m_instanceGeo->m_minLocalToWorldAABB.x ) / 2.f;
						PosY = (m_instanceGeo->m_maxLocalToWorldAABB.y + m_instanceGeo->m_minLocalToWorldAABB.y )/ 2.f;
						PosZ = (m_instanceGeo->m_maxLocalToWorldAABB.z + m_instanceGeo->m_minLocalToWorldAABB.z )/ 2.f;
						g_multipleView->m_nx->CreateCapsule( NxVec3( PosX, PosY, PosZ), height, radius, density, NxCapsuleMat33Rotation, m_instanceGeo->m_physXName, isTrigger, m_instanceGeo->m_abstractGeometry->m_hasAnimation );
						sprintf( m_instanceGeo->m_physXName, "%s%d", "PhysX_mesh_", m_instanceGeo->m_nameIndex );
						m_instanceGeo->m_lodAlgorithm = algorithm;	
						m_instanceGeo->m_hasPhysX = CTrue;
						m_instanceGeo->m_physXDensity = density;
						m_instanceGeo->m_physXPercentage = percentage;
						m_instanceGeo->m_isTrigger = isTrigger;
						m_instanceGeo->m_isInvisible = isInvisible;

						vertices_temp.clear();
						triangles_temp.clear();
						vertices = NULL;
						triangles = NULL;

						return m_instanceGeo->m_nameIndex;
					}
					vertices_temp.clear();
					triangles_temp.clear();
					vertices = NULL;
					triangles = NULL;
					
					return -1;

				} //if selected
			}
			return -1; //didn't find an instance geometry
		}
		return -1; //nothing selected
	}

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
};