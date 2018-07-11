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

#include "stdafx.h"
#include "skin.h"
#include "material.h"
#include "node.h"
#include "render.h"
CVoid CSkinWeight::SortWeights()
{
	// need to sort if the number of weights is greater than 4 
	// just to prepare for the cg program 
	if ( m_numWeights > 4 )
	{
		CFloat wTemp = 0;
		CInt iTemp = 0; 

		// need to sort the weights with the biggest words the top 
		for (CUInt s = m_numWeights-1; s > 0; s-- )
		{
			for (CUInt w = m_numWeights-1; w > 0; w-- )
			{
				// if the current weight has a higher value than next swap the two 
				if ( m_weights[w] > m_weights[w-1] )
				{
					wTemp = m_weights[w]; 
					iTemp = m_joints[w]; 
					m_weights[w] = m_weights[w-1];
					m_joints[w] = m_joints[w-1];
					m_weights[w-1] = wTemp;
					m_joints[w-1] = iTemp; 
				}
			}
		}

		/// Test here just to make sure
		for (CUInt i = 0; i <  m_numWeights - 1; i++ )
		{
			//CAssert("Weight Indices werern't sorted properly \n",	m_weights[i] >= m_weights[i+1]) ;
		}	
	}
}

CVoid CController::FindJointNodes( CNode * sceneRoot ) 
{

	for ( CInt i = 0; i < m_jointCount; i++)
	{
		m_joints[i].m_jointNode = FindJointNode( sceneRoot, m_joints[i].m_name ); 

		//CChar temp[MAX_NAME_SIZE];
		if ( m_joints[i].m_jointNode )
		{
			m_joints[i].m_jointNode->SetUsedForSkinning(); 	
			m_joints[i].m_jointNode->SetInverseBindMatrix( m_iBindMats[i] );
			//sprintf( temp, " Skin Controller (%s) joint binding made to node (%s) \n", m_name, m_joints[i].m_name );
			//PrintInfo( temp, COLOR_WHITE ); 
			CNode* node = m_joints[i].m_jointNode;
			for(;;)
			{
				if( node->m_parent == sceneRoot )
				{
					node->SetUsedForSkeleton();
					break;
				}
				node = node->m_parent;
			}

		}
		else
		{
			//sprintf( temp, "Failed to make joint binding for Controller %s for Joint %s\n", m_name, m_joints[i].m_name );
			//PrintInfo( temp, COLOR_RED ); 
			return;
		}
	}
	m_renderReady = CTrue;
}

CNode * CController::FindJointNode( CNode * node, CChar * name )
{
	if (m_jointsType == CJoint::CJointsType_ID)
	{
		if (node->GetId()[0])
			if ( ICmp( node->GetId(), name ) )
				return node;
			else if (node->GetSid()[0])  // test sid
			if ( ICmp( node->GetSid(), name ) )
				return node;

	} else if (m_jointsType == CJoint::CJointsType_SID)
	{
		if (node->GetSid()[0])
			if ( ICmp( node->GetSid(), name ) )
				return node;
	}
	// update any children 
	CNode * children = node->GetChild();

	while ( children )
	{
		CNode * node = FindJointNode( children, name );
		if ( node )
			return node; 
		children = children->GetNext(); 
	}

	return NULL; 
}

CVoid CController::AddIBindMats( CMatrix * iBindMatArray, CInt nMats )
{
	m_iBindMatCount = nMats; 

	// allocate for inverse bind matrices 
	m_iBindMats = CNewData( CMatrix, m_iBindMatCount );
	
	// allocate for combined matrix list as well 
	m_skinningMats = CNewData( CMatrix, m_iBindMatCount ); 
	// need to move to useing this 3x4 so we can allow for more bones 
	m_skinningMats3x4 = CNewData( CMatrix3x4, m_iBindMatCount ); 

	for ( CInt i = 0; i < m_iBindMatCount; i++)
	{
		CMatrixCopy( iBindMatArray[i], m_iBindMats[i]);
	}	
}

CVoid CController::UpdateCombinedMats()
{
	// update the combined matrix from each joint 
	// into this centeralized combined matrix list. 
	
	for ( CInt i = 0; i < m_jointCount; i++)
	{
		if (m_joints[i].m_jointNode==NULL) continue;
		CMatrixCopy( m_joints[i].m_jointNode->GetSkinMatrix(), m_skinningMats[i] );
		if ( g_render.UsingCg() )
		{
			CMatrixTranspose3x4( m_skinningMats[i], m_skinningMats3x4[i] ); 
		}
	}

}

