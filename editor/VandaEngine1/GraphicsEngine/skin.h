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
#include "base.h"
#include "Matrix.h"

class CSkinWeight
{
public:
	CUInt m_numWeights;
	CFloat*	m_weights;
	CUInt* m_joints; 
	
	CSkinWeight()
	{
		m_numWeights = 0;
		m_weights = NULL;
		m_joints = NULL;
	}

	// temp data for parsing 
	CUInt* m_weightIndices; 
	CUInt* m_jointIndices; 

	inline CVoid FreeTempData() 
	{
		CDeleteData( m_weightIndices );
		CDeleteData( m_jointIndices ); 		
	}

	inline CVoid FreeWeightData()
	{
		CDeleteData( m_weights ); 
		CDeleteData( m_joints ); 
	}

	CVoid SortWeights();
};

class CWeight
{
public:
	CUInt m_numInfluences;
	CFloat*	m_weights;
	CUInt* m_joints; 

	CWeight()
	{	
		m_numInfluences = 0; 
		m_weights = NULL;
		m_joints = NULL; 
	}

	~CWeight()
	{
		Delete(); 
	}

	CVoid Copy( CSkinWeight * weight )
	{
		m_numInfluences = weight->m_numWeights; 

		if ( m_numInfluences )
		{
			CDeleteData( m_weights );
			CDeleteData( m_joints );
			// allocate weights and joints 
			m_weights = CNewData( CFloat, m_numInfluences ); 
			m_joints = CNewData( CUInt, m_numInfluences ); 

			for (CUInt i = 0; i < m_numInfluences; i++)
			{
				m_weights[i] = weight->m_weights[i];
				m_joints[i] = weight->m_joints[i]; 
			}
		}
	}

	CVoid Copy( CWeight * weight )
	{
		m_numInfluences = weight->m_numInfluences; 

		if ( m_numInfluences )
		{
			CDeleteData( m_weights );
			CDeleteData( m_joints );

			// allocate weights and joints 
			m_weights = CNewData( CFloat, m_numInfluences ); 
			m_joints = CNewData( CUInt, m_numInfluences ); 

			for (CUInt i = 0; i < m_numInfluences; i++)
			{
				m_weights[i] = weight->m_weights[i];
				m_joints[i] = weight->m_joints[i]; 
			}		
		}
	}

	inline CBool Compare( CWeight * weight )
	{	
		if ( m_numInfluences != weight->m_numInfluences )
			return CFalse; 

		for (CUInt i = 0; i < m_numInfluences; i ++)
		{
			if ( m_weights[i] != weight->m_weights[i] )
				return CFalse;
			if ( m_joints[i] != weight->m_joints[i] )
				return CFalse; 
		}

		return CTrue; 
	}	

	CVoid  Delete()
	{
		CDeleteData( m_weights ); 
		CDeleteData( m_joints ); 
	}
};

class CNode; 

class CJoint
{
public:
	CChar m_name[MAX_NAME_SIZE];	
	CNode* m_jointNode;	
	enum CJointsType { CJointsType_SID, CJointsType_ID};
};

class CGeometry; 

class CController: public CBase 
{
protected:

	CChar m_bindPosId[MAX_NAME_SIZE];
	CChar m_bindNormId[MAX_NAME_SIZE];
	CChar m_jointWeightId[MAX_NAME_SIZE];

	CChar m_targetId[MAX_NAME_SIZE];

	CChar m_id[MAX_NAME_SIZE];
	CJoint*	m_joints;
	CJoint::CJointsType	m_jointsType;
	CBool m_renderReady;
	CSkinWeight* m_weights;
	CVec3f* m_bindPoints;
	CVec3f* m_bindNormals; 

	CMatrix m_bindShapeMats;
	CMatrix* m_iBindMats;
	CMatrix* m_skinningMats; 
	CMatrix3x4* m_skinningMats3x4;

	CInt m_weightCount; 
	CInt m_jointCount;
	CInt m_bindPointsCount;
	CInt m_bindNormalsCount; 
	CInt m_iBindMatCount;
	CGeometry* m_geometry;
	
	friend class CGeometry; 
	friend class CScene; 
public:
	CController()
	{
		m_weightCount = 0; 
		m_jointCount = 0; 
		m_bindPointsCount = 0; 
		m_bindNormalsCount = 0; 
		m_iBindMatCount = 0; 
		m_renderReady = CFalse;
		m_joints = NULL; 
		m_weights = NULL; 
		m_bindPoints = NULL; 
		m_bindNormals = NULL; 
		CMatrixLoadIdentity(m_bindShapeMats); 
		m_iBindMats = NULL; 
		m_skinningMats = NULL; 
		m_skinningMats3x4 = NULL; 

		m_bindPosId[0] = 0;
		m_bindNormId[0] = 0; 
		m_jointWeightId[0] = 0; 
		m_targetId[0] = 0; 
		m_id[0] = 0; 

		m_geometry = NULL; 
	}

	~CController()
	{
		CDeleteData( m_joints ); 
		CDeleteData( m_bindPoints );
		CDeleteData( m_bindNormals ); 
		CDeleteData( m_iBindMats ); 
		CDeleteData( m_skinningMats ); 
		CDeleteData( m_weights ); 
	}

	inline CVoid	SetBindPosId( const CChar * bindPosId )	{ Cpy(m_bindPosId, bindPosId);} 
	inline CVoid	SetBindNormId( const CChar * bindNormId )	{ Cpy(m_bindNormId, bindNormId);} 
	inline CVoid	SetJntWtId( const CChar * jntWtId )	{ Cpy(m_jointWeightId, jntWtId);}
	inline CVoid	SetTargetId( const CChar * target )	{ Cpy(m_targetId, target);} 
	inline CChar *GetTargetId()	{ return m_targetId; }
	inline CGeometry *GetGeometry() { return m_geometry; } 
	inline CBool GetRenderReady() { return m_renderReady;} 
	CVoid AddBindPos( CChar * BindPosArray, CInt nValues );
	CVoid AddIBindMats( CMatrix * iBindMatArray, CInt nValues );
	CVoid FindJointNodes( CNode * sceneRoot ); 
	CNode* FindJointNode( CNode * sceneRoot, CChar * name );
	CVoid UpdateCombinedMats(); 
	
	inline CSkinWeight*	GetWeight( CInt id )
	{	
		if ( m_weights ) 
			return &m_weights[id]; 
		return NULL;
	}
	
	inline CInt	GetWeightCount()	{ return m_weightCount; }
	inline CVec3f *GetBindPoints()	{ return m_bindPoints; }
	inline CVec3f *GetBindNormals()	{ return m_bindNormals; }
	inline CJoint *GetJoints()		{ return m_joints; }
	inline CInt GetNumBindPoints()	{ return m_bindPointsCount; } 
	inline CInt GetNumBindNormals() { return m_bindNormalsCount; }	
	inline CInt	GetJointCount()		{ return m_jointCount; } 
};

