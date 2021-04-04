//Copyright (C) 2021 Ehsan Kamrani 
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
	//deprecate
	CBool m_loopAnimationAtStartup, m_playAnimation, m_alwaysVisible, m_castShadow;
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
	CInt GeneratePhysX( CPhysXAlgorithm algorithm, CFloat density, CInt percentage, CBool isTrigger, CBool isInvisible, CInstanceGeometry* m_instanceGeo, CBool loadFromFile = CFalse, CInstancePrefab* prefab = NULL)
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
		if( !loadFromFile)
		{
			if( m_instanceGeo->m_abstractGeometry->m_collapseMap.num == 0 && (algorithm == eLOD_LENGTH_CURVATURE || algorithm == eLOD_LENGTH ) )
			{
				//PrintInfo( "\nCalculating LOD..." );
				m_instanceGeo->m_abstractGeometry->CalculateLODInfo(algorithm);
			}
			else
			{
				if( (algorithm == eLOD_LENGTH_CURVATURE || algorithm == eLOD_LENGTH ) && (m_instanceGeo->m_prevLodAlgorithm == eLOD_LENGTH_CURVATURE ||
				m_instanceGeo->m_prevLodAlgorithm == eLOD_LENGTH ) )
				{
					if( m_instanceGeo->m_prevLodAlgorithm != algorithm ) //regenerate PhysX informations
					{
						//PrintInfo( "\nRegenerating LOD..." );
						m_instanceGeo->m_abstractGeometry->CalculateLODInfo(algorithm);
					}

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
		//Scale and Rotation and Translation Matrices for Convex Hulls
		CMatrix ZUpRotationForSkins;
		CMatrixLoadIdentity(ZUpRotationForSkins);

		CNode* tempParentNode = m_instanceGeo->m_node;
		CBool foundTarget = CFalse;

		CMatrix convexLocalToWorld;
		const CMatrix *convex_ltow;
		if (prefab)
			convex_ltow = prefab->GetInstanceMatrix();
		else
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

		CVec3f convexPosition( convexLocalToWorld[12], convexLocalToWorld[13], convexLocalToWorld[14] );

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
			if( !g_nx->CreateTriangleMesh( (CInt)(vertices_temp.size()/3), (CInt)(triangles_temp.size()/3), vertices, triangles, isTrigger, m_instanceGeo->m_physXName ) )
				failed = CTrue;
			else
				sprintf( m_instanceGeo->m_physXName, "%s%s%d", g_currentInstancePrefab->GetName(), "_PhysX_mesh_", m_instanceGeo->m_nameIndex );

		}
		else if( vertices != NULL && algorithm == eLOD_CONVEX_HULL )
		{
			if( !g_nx->CreateConvexMesh( (CInt)(vertices_temp.size()/3), vertices, NxVec3(convexPosition.x, convexPosition.y, convexPosition.z), NxConvexMat33Rotation, density, m_instanceGeo->m_physXName, isTrigger,  m_instanceGeo->m_abstractGeometry->m_hasAnimation ) )
				failed = CTrue;
			else
				sprintf(m_instanceGeo->m_physXName, "%s%s%d", g_currentInstancePrefab->GetName(), "_PhysX_mesh_", m_instanceGeo->m_nameIndex);
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
				g_nx->CreateBox(  NxVec3(PosX,PosY,PosZ), NxVec3( DimX, DimY, DimZ), density, NxConvexMat33Rotation, m_instanceGeo->m_physXName, isTrigger, m_instanceGeo->m_abstractGeometry->m_hasAnimation );
			else
				g_nx->CreateTriggerBox(  NxVec3(PosX,PosY,PosZ), NxVec3( DimX, DimY, DimZ), NxConvexMat33Rotation, m_instanceGeo->m_physXName, m_instanceGeo->m_abstractGeometry->m_hasAnimation );
			sprintf(m_instanceGeo->m_physXName, "%s%s%d", g_currentInstancePrefab->GetName(), "_PhysX_mesh_", m_instanceGeo->m_nameIndex);
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
		else if( algorithm == eLOD_SPHERE)
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
			g_nx->CreateSphere( NxVec3( PosX, PosY, PosZ ), radius, density, m_instanceGeo->m_physXName, isTrigger, m_instanceGeo->m_abstractGeometry->m_hasAnimation );
			sprintf(m_instanceGeo->m_physXName, "%s%s%d", g_currentInstancePrefab->GetName(), "_PhysX_mesh_", m_instanceGeo->m_nameIndex);
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

			g_nx->CreateCapsule( NxVec3( PosX, PosY, PosZ), height, radius, density, NxCapsuleMat33Rotation, m_instanceGeo->m_physXName, isTrigger, m_instanceGeo->m_abstractGeometry->m_hasAnimation );
			sprintf(m_instanceGeo->m_physXName, "%s%s%d", g_currentInstancePrefab->GetName(), "_PhysX_mesh_", m_instanceGeo->m_nameIndex);
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
	}

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