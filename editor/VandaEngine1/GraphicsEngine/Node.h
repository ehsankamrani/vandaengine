/*
 * Copyright 2006 Sony Computer Entertainment Inc.
 *
 * Licensed under the SCEA Shared Source License, Version 1.0 (the "License"); you may not use this 
 * file except in compliance with the License. You may obtain a copy of the License at:
 * http://research.scea.com/scea_shared_source_license.html
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License 
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
 * implied. See the License for the specific language governing permissions and limitations under the 
 * License. 
 */

#pragma once

#include <vector>
#include "Orient.h"
#include "geometry.h"
//#include "water.h"
#include "../common/utility.h"
#include "../physXEngine/nx.h"
class CCamera;
class CInstanceCamera;
class CGeometry;
class CLight;
class CInstanceLight;
class CInstanceGeometry;
class CInstanceController;
class CInstancePrefab;
class CWater;
const CInt MAX_ANIMS = 50; 

class CNode: public COrient 
{
	CChar m_name[MAX_NAME_SIZE];
	CChar m_id[MAX_NAME_SIZE];
	CChar m_sid[MAX_NAME_SIZE];
	CNode *m_next;
	//CInstanceCamera *m_instanceCamera;	// REFACTOR IN PROGRESS needs to support multiple instances
	//CInstanceLight *m_instanceLight;		// REFACTOR IN PROGRESS needs to support multiple instances
	CInstanceLight *m_nearistInstanceLight;
	//CGeometry *m_geometry;			// REFACTOR IN PROGRESS needs to support multiple instances
	CAnimation *m_animations[MAX_ANIMS];
	CInt m_numAnimations; 
	CNode *m_parent; 
	CNode *m_children;
	CInt32 m_numChildren;
	CBool m_usedForSkinning; 
	CBool m_inverseBindMatrixReady; 
	CBool m_orientReady;
	CInt m_idx; 
	CInt m_parentIdx; 
	CInt m_depth; 
	CScene* m_scene;
public:
	//std::vector <CInstanceCamera*> m_instanceCameras;  
	std::vector <CInstanceGeometry *> m_instanceGeometries;  
	std::vector <CInstanceController *> m_instanceControllers;
	std::vector <CInstanceLight *> m_instanceLights;
	CUpAxis m_upAxis;
	CBool m_usedForSkeleton; 

public:
	CNode():
	m_next(NULL),
	m_nearistInstanceLight(NULL),
	m_numAnimations(0),
	m_parent(NULL),
	m_children(NULL),
	m_numChildren(0),
	m_usedForSkinning(CFalse),
	m_inverseBindMatrixReady(CFalse),
	m_orientReady(CFalse),
	m_usedForSkeleton(CFalse),
	m_idx(-1),
	m_parentIdx(-1),
	m_depth(0)
	{
		m_name[0] = 0;
		m_id[0] = 0;
		m_sid[0] = 0;
	}

	~CNode()
	{
		Destroy(); 
	}


	CVoid Destroy()
	{
		for( std::vector<CInstanceGeometry *>::iterator it = m_instanceGeometries.begin(); it != m_instanceGeometries.end();it++ )
		{
			CDelete( *it );
		}
		m_instanceGeometries.clear();
	
		//we destroy CInstanceLight class insied CScene destructor
		m_instanceLights.clear();

		for( std::vector<CInstanceController *>::iterator it = m_instanceControllers.begin(); it != m_instanceControllers.end();it++ )
		{
			CDelete( *it );
		}
		//we destroy CInstanceController class insied CScene destructor
		m_instanceControllers.clear();

		// need to delete any children or siblings
		if (m_children)
			CDelete( m_children ); 		
		if (m_next)
			CDelete( m_next ); 
	}
	CVoid SetUpAxis( CUpAxis up ) { m_upAxis = up;}

protected:
	friend class CScene; 
	friend class CController;

	inline CNode *SetNext( CNode * next ) { m_next = next; return this;}
	inline CVoid	SetName( const CChar * n ) { Cpy( m_name, n ); }
	inline CVoid	SetId( const CChar * n ) { Cpy( m_id, n ); }
	inline CVoid	SetSid( const CChar * n ) { Cpy( m_sid, n ); }
	inline CVoid	SetParent( CNode * node) { m_parent = node; };

	CVoid SetChild( CNode * );
	CVoid AddObjectReference( CChar * name ); 	

	CVoid AddChild( CNode * node )
	{
		if (!m_children )
		{
			m_children = node; 
		}
		else
		{
			node->SetNext( m_children ); 
			m_children = node; 
		}
		m_numChildren++; 
	}

	//inline CVoid SetGeometry( CGeometry * geo ) { Geometry = geo; }
	inline CVoid	SetAnimation( CAnimation * anim ) { m_animations[m_numAnimations] = anim; m_numAnimations += 1; }
	inline CVoid	SetUsedForSkinning() { m_usedForSkinning = CTrue; } 
	inline CVoid	SetUsedForSkeleton() { m_usedForSkeleton = CTrue; } 
	
	inline CVoid	SetIdx( CInt id ){ m_idx = id; }
	inline CVoid	SetParentIdx( CInt id ){ m_idx = id; }
	inline CVoid	SetInverseBindMatrix( CMatrix imat )
	{
		memcpy( m_inverseBindMatrix, imat, sizeof( CMatrix ) ) ;
		m_inverseBindMatrixReady = CTrue; 
	}
	
	CVoid DrawLineToChildren(); 
	CNode* GetNodeParent() { return m_parent; } 

public:

	//---------------------- External interfaces ---------------------------------//	
	// After you get the SceneRoot from the CScene.GetSceneRoot 
	// got throught he nodes and just check the type 
	// if the type is C_Geo the GetGeometry(); 
	// from there you will need to get the GeoGroups which will contain the materials,
	// Points, Normals, and the rest of the Geo data.  
	// To get the next sibling it's simply node = node->GetNext();  
	// until the node is null.  
	// Node there may also be animation attached to the node as well as geometry
	// so Do a GetAnimation to check for animation attached.  If not null try and get 
	// the Animation keys.  
	// Currently Animation refactoring isn't done but hope to have that completed soon. 
	// Finaly to get the orient check COrient definition.  It describes 
	// how to handle getting a camera orient verse getting a regular node orient.  

	inline CNode* GetNext() { return m_next; }
	inline CChar* GetName(){ return m_name; }
	inline CChar* GetId(){ return m_id; }
	inline CChar* GetSid(){ return m_sid; }
	//inline CNode*	GetParent(){ return m_parent; }
	inline CNode* GetChild(){ return m_children; }
	
	//inline CGeometry*	GetGeometry(){ return m_geometry; }
	inline CInt GetNumAnimations(){ return m_numAnimations; } 
	inline CAnimation* GetAnimation( CInt i){return m_animations[i]; }
	inline CInt GetIdx(){ return m_idx; } 
	//inline CInt GetParentIdx(){ return ParentIdx; }
	inline CInt GetDepth(){ return m_depth; }
	inline CBool GetIsUsedForSkinning(){ return m_usedForSkinning; } 
		
	inline CInt GetNumChildren()
	{
		CInt num = 0; 
		CNode* child = m_children; 
		while( child )
		{
			num++;
			child = child->GetNext(); 
		}
		return num; 
	}
	CVoid Update(CFloat time, CBool updateOrient);
	CVoid UpdateOrient( CFloat time); 
	CVoid UpdateBoundingBox( CInstanceGeometry* geometry, CInstancePrefab* prefab = NULL);
	CVoid UpdatePhysX( CInstanceGeometry* geometry );
	CVoid BuildLWMatrix( CFloat time );
	CVoid SetScene( CScene* scene );
	CScene* GetScene();
	CVoid RenderAABBWithLines(CBool animatedGeo); //It's used to draw AABBs
	CVoid RenderAABBWithQuads(); //It's used to draw the AABB objects in selection mode 
	CVoid RenderSelectionMode(CNode* sceneRoot); //It's used to draw the actual geometries in selection mode
	CVoid Render( CBool sceneManager, CChar* parentTreeNameOfGeometries, CBool renderController = CFalse ); 
	CVoid RenderAnimatedModels( CBool sceneManager, CNode* root, CBool renderController );
	CVoid RenderModelsControlledByPhysX(CBool sceneManager, CNode* sceneRoot );
	CVoid RenderGrass(CBool sceneManager, CChar* parentTreeNameOfGeometries );
	CVoid CreateTrigger(CNovodex* nx);
	CVoid SetupDiffuseTexture();
	CVoid SetupNormalTexture();
	CVoid SetupDirtTexture();
	CVoid SetupGlossTexture();
	CVoid EnableShader(CInstanceGeometry* instanceGeometry);

	//---------------------- End External interfaces ---------------------------------//	
};
