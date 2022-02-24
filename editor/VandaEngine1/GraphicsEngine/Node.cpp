//Original Work: Copyright 2006 Sony Computer Entertainment Inc.
//Modified Work: Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "node.h"
#include "Animation.h"
//#include "Geometry.h"
#include "Light.h"
#include "Matrix.h"
#include "Scene.h"
#include <float.h>

CVoid 	CNode::Update( 	CFloat time, CBool updateOrient )
{
	// Update orientation matrices for this node
	if (updateOrient)
		UpdateOrient( time );

	for(CUInt i=0; i< m_instanceGeometries.size(); i++)
	{
		if (g_multipleView->IsPlayGameMode())
		{
			//CGeometry * geometry = m_instanceGeometries[i]->m_abstractGeometry;
			if (!(m_instanceGeometries[i]->m_hasPhysX && m_instanceGeometries[i]->m_physXDensity > 0)) //objects controlled by PhysX are updated in RenderModelControlledByPhysX()
				UpdateBoundingBox(m_instanceGeometries[i]);
			if (m_instanceGeometries[i]->m_abstractGeometry->m_hasAnimation && m_instanceGeometries[i]->m_hasPhysX)
				UpdatePhysX(m_instanceGeometries[i]);
		}
		else
		{
			UpdateBoundingBox(m_instanceGeometries[i]);
		}
	}

	for(CUInt i=0; i< m_instanceControllers.size(); i++)
	{
		CInstanceGeometry * geometry = m_instanceControllers[i]->m_instanceGeometry;

		if (g_render.GetScene()->m_animationClips[g_render.GetScene()->GetCurrentClipIndex()]->GetCalculateDynamicBoundingBox())
		{
			geometry->m_abstractGeometry->ComputeAABB_Center();
		}
		UpdateBoundingBox(geometry, g_currentInstancePrefab);

		if (g_multipleView->IsPlayGameMode())
		{
			if (geometry->m_abstractGeometry->m_hasAnimation && geometry->m_hasPhysX)
				UpdatePhysX(geometry);
		}
	}

	// Update all the child nodes
	CNode * kids = m_children;
	while( kids )
	{
		kids->Update( time, updateOrient ); 
		kids = kids->GetNext(); 
	}

	// Create matrices that are later used by shaders, these updates should probably eventually be made lazy
	// NOTE: Because CMatrix3x4Invert doesn't copy over the last row to the output matrix, we have to do it.
	//m_inverseLocalToWorldMatrix[M30] = m_inverseLocalToWorldMatrix[M31] = m_inverseLocalToWorldMatrix[M32] = 0.0;
	//m_inverseLocalToWorldMatrix[M33] = 1.0;
	//CMatrix3x4Invert( m_localToWorldMatrix, m_inverseLocalToWorldMatrix);
	//CMatrixTranspose( m_inverseLocalToWorldMatrix, m_inverseTransposeLocalToWorldMatrix );

}

CVoid CNode::UpdatePhysX( CInstanceGeometry* geometry )
{
	if( gPhysXscene )
	{
		for (CUInt j = 0; j < gPhysXscene->getNbActors(); j++)
		{
			//if (!gPhysXscene->getActors()[j]->isSleeping())
			//{
				CChar actorName[MAX_NAME_SIZE];
				if (!gPhysXscene->getActors()[j]->getName()) continue;
				Cpy(actorName, gPhysXscene->getActors()[j]->getName());
				if (!Cmp(geometry->m_physXName, "\n") && Cmp(actorName, geometry->m_physXName))
				{
					//Scale, Rotation and Translation Matrices for Convex Hulls, Box, Sphere, and Cylinder
					CMatrix ZUpRotationForSkins;
					CMatrixLoadIdentity(ZUpRotationForSkins);
					CNode* tempParentNode = geometry->m_node;
					CBool foundTarget = CFalse;

					CMatrix convexLocalToWorld;
					const CMatrix *convex_ltow;
					convex_ltow = /*geometry->m_node->GetLocalToWorldMatrix();*/&(geometry->m_localToWorldMatrix);
					CMatrixCopy(*convex_ltow, convexLocalToWorld);
					CMatrix4x4Mult(convexLocalToWorld, ZUpRotationForSkins);
					CMatrixCopy(ZUpRotationForSkins, convexLocalToWorld);

					//decomp_affine;
					AffineParts *parts = CNew(AffineParts);
					HMatrix A;
					CUInt k = 0;
					for (CUInt i = 0; i < 4; i++)
						for (CUInt j = 0; j < 4; j++)
						{
							A[j][i] = convexLocalToWorld[k];
							k++;
						}
					decomp_affine(A, parts);
					//rotation
					CMatrix rotationMatrix;
					CQuat qRotation(parts->q.x, parts->q.y, parts->q.z, parts->q.w);
					CMatrixLoadIdentity(rotationMatrix);
					CQuaternionToMatrix(&qRotation, rotationMatrix);

					if (geometry->m_lodAlgorithm == eLOD_CAPSULE_METHOD1)
					{
						CVec4f rot(1.0, .0, 0.0, 90.0);
						CMatrix4x4RotateAngleAxis(rotationMatrix, rot);
					}
					else if (geometry->m_lodAlgorithm == eLOD_CAPSULE_METHOD3)//second method
					{
						CVec4f rot(0.0, 0.0, 1.0, 90.0);
						CMatrix4x4RotateAngleAxis(rotationMatrix, rot);
					}

					NxVec3 row0(rotationMatrix[0], rotationMatrix[4], rotationMatrix[8]);
					NxVec3 row1(rotationMatrix[1], rotationMatrix[5], rotationMatrix[9]);
					NxVec3 row2(rotationMatrix[2], rotationMatrix[6], rotationMatrix[10]);
					NxMat33 mat33(row0, row1, row2);
					//position
					CFloat PosX, PosY, PosZ;

					if (geometry->m_lodAlgorithm == eLOD_CONVEX_HULL)
					{
						PosX = parts->t.x; PosY = parts->t.y, PosZ = parts->t.z;
					}
					else
					{
						PosX = (geometry->m_maxLocalToWorldAABB.x + geometry->m_minLocalToWorldAABB.x) / 2.f;
						PosY = (geometry->m_maxLocalToWorldAABB.y + geometry->m_minLocalToWorldAABB.y) / 2.f;
						PosZ = (geometry->m_maxLocalToWorldAABB.z + geometry->m_minLocalToWorldAABB.z) / 2.f;
					}
					NxVec3 globalPos(PosX, PosY, PosZ);
					//remove decomposed data
					CDelete(parts);
					//////

					gPhysXscene->getActors()[j]->moveGlobalPosition(globalPos);
					gPhysXscene->getActors()[j]->moveGlobalOrientation(mat33);
				}
			//}
		}
	}

}

CVoid CNode::UpdateBoundingBox( CInstanceGeometry* geometry, CInstancePrefab* prefab)
{
	CGeometry* tempGeometry = geometry->m_abstractGeometry;

	CMatrix combined;
	CMatrixCopy(m_localToWorldMatrix, combined);

	if (prefab)
	{
		CMatrixMult(combined, *(g_currentInstancePrefab->GetInstanceMatrix()), combined);
	}

	CVec3f src[8];
	src[0].x = tempGeometry->m_minAABB.m_i; src[0].y = tempGeometry->m_minAABB.m_j; src[0].z = tempGeometry->m_minAABB.m_k;
	src[1].x = tempGeometry->m_maxAABB.m_i; src[1].y = tempGeometry->m_minAABB.m_j; src[1].z = tempGeometry->m_maxAABB.m_k;
	src[2].x = tempGeometry->m_maxAABB.m_i; src[2].y = tempGeometry->m_minAABB.m_j; src[2].z = tempGeometry->m_minAABB.m_k;
	src[3].x = tempGeometry->m_minAABB.m_i; src[3].y = tempGeometry->m_minAABB.m_j; src[3].z = tempGeometry->m_maxAABB.m_k;
	src[4].x = tempGeometry->m_maxAABB.m_i; src[4].y = tempGeometry->m_maxAABB.m_j; src[4].z = tempGeometry->m_minAABB.m_k;
	src[5].x = tempGeometry->m_minAABB.m_i; src[5].y = tempGeometry->m_maxAABB.m_j; src[5].z = tempGeometry->m_minAABB.m_k;
	src[6].x = tempGeometry->m_minAABB.m_i; src[6].y = tempGeometry->m_maxAABB.m_j; src[6].z = tempGeometry->m_maxAABB.m_k;
	src[7].x = tempGeometry->m_maxAABB.m_i; src[7].y = tempGeometry->m_maxAABB.m_j; src[7].z = tempGeometry->m_maxAABB.m_k;

	CMatrixTransform(combined, src[0], geometry->m_localToWorldVertex[0]);
	CMatrixTransform(combined, src[1], geometry->m_localToWorldVertex[1]);
	CMatrixTransform(combined, src[2], geometry->m_localToWorldVertex[2]);
	CMatrixTransform(combined, src[3], geometry->m_localToWorldVertex[3]);
	CMatrixTransform(combined, src[4], geometry->m_localToWorldVertex[4]);
	CMatrixTransform(combined, src[5], geometry->m_localToWorldVertex[5]);
	CMatrixTransform(combined, src[6], geometry->m_localToWorldVertex[6]);
	CMatrixTransform(combined, src[7], geometry->m_localToWorldVertex[7]);

	CVec3f m_minLocalToWorld;
	CVec3f m_maxLocalToWorld;
	m_minLocalToWorld.x = m_minLocalToWorld.y = m_minLocalToWorld.z = 100000000.0f;
	m_maxLocalToWorld.x = m_maxLocalToWorld.y = m_maxLocalToWorld.z = -100000000.0f;

	for( CUInt i = 0; i < 8; i++ )
	{
		if(  geometry->m_localToWorldVertex[i].x > m_maxLocalToWorld.x )
			m_maxLocalToWorld.x =  geometry->m_localToWorldVertex[i].x;
		if(  geometry->m_localToWorldVertex[i].y > m_maxLocalToWorld.y )
			m_maxLocalToWorld.y =  geometry->m_localToWorldVertex[i].y;
		if(  geometry->m_localToWorldVertex[i].z > m_maxLocalToWorld.z )
			m_maxLocalToWorld.z =  geometry->m_localToWorldVertex[i].z;

		if(  geometry->m_localToWorldVertex[i].x < m_minLocalToWorld.x )
			m_minLocalToWorld.x =  geometry->m_localToWorldVertex[i].x;
		if(  geometry->m_localToWorldVertex[i].y < m_minLocalToWorld.y )
			m_minLocalToWorld.y =  geometry->m_localToWorldVertex[i].y;
		if(  geometry->m_localToWorldVertex[i].z < m_minLocalToWorld.z)
			m_minLocalToWorld.z =  geometry->m_localToWorldVertex[i].z;
	}
	geometry->m_minLocalToWorldAABB = m_minLocalToWorld;
	geometry->m_maxLocalToWorldAABB = m_maxLocalToWorld;
	geometry->m_center = (m_minLocalToWorld + m_maxLocalToWorld ) * 0.5f;
	geometry->m_radius = sqrt( pow( geometry->m_minLocalToWorldAABB.x - geometry->m_center.x, 2) + 
		pow( geometry->m_minLocalToWorldAABB.y - geometry->m_center.y, 2) +
		pow( geometry->m_minLocalToWorldAABB.z - geometry->m_center.z, 2) );

	for( CUInt i = 0; i < 16; i++ )
		geometry->m_localToWorldMatrix[i] = combined[i];

	//It's used for saving the kinematic instance geometries.
	if( geometry->m_firstUpdate )
	{
		for( CUInt i = 0; i < 16; i++ )
			geometry->m_firstLocalToWorldMatrix[i] = m_localToWorldMatrix[i];
		geometry->m_firstUpdate = CFalse;
	}
}

CVoid CNode::SetupGlossTexture()
{
	for(CUInt i=0; i< m_instanceGeometries.size(); i++)
	{
		CGeometry * geometry = m_instanceGeometries[i]->m_abstractGeometry;
		geometry->SetupGlossTexture( this, m_instanceGeometries[i] );
	}
	for(CUInt i=0; i< m_instanceControllers.size(); i++)
	{
		CGeometry * geometry = m_instanceControllers[i]->m_instanceGeometry->m_abstractGeometry;
		geometry->SetupGlossTexture( this, m_instanceControllers[i] );
	}

	// Update all the child nodes
	CNode * kids = m_children;
	while( kids )
	{
		kids->SetupGlossTexture(); 
		kids = kids->GetNext(); 
	}

}

CVoid CNode::SetupDirtTexture()
{
	for(CUInt i=0; i< m_instanceGeometries.size(); i++)
	{
		CGeometry * geometry = m_instanceGeometries[i]->m_abstractGeometry;
		if( geometry->m_texCoords[1] )
			geometry->SetupDirtTexture( this, m_instanceGeometries[i] );
	}
	for(CUInt i=0; i< m_instanceControllers.size(); i++)
	{
		CGeometry * geometry = m_instanceControllers[i]->m_instanceGeometry->m_abstractGeometry;
		if( geometry->m_texCoords[1] )
			geometry->SetupDirtTexture( this, m_instanceControllers[i] );
	}

	// Update all the child nodes
	CNode * kids = m_children;
	while( kids )
	{
		kids->SetupDirtTexture(); 
		kids = kids->GetNext(); 
	}

}

CVoid CNode::SetupNormalTexture()
{
	for(CUInt i=0; i< m_instanceGeometries.size(); i++)
	{
		CGeometry * geometry = m_instanceGeometries[i]->m_abstractGeometry;
		geometry->SetupNormalTexture( this, m_instanceGeometries[i] );
	}
	for(CUInt i=0; i< m_instanceControllers.size(); i++)
	{
		CGeometry * geometry = m_instanceControllers[i]->m_instanceGeometry->m_abstractGeometry;
		geometry->SetupNormalTexture( this, m_instanceControllers[i] );
	}

	// Update all the child nodes
	CNode * kids = m_children;
	while( kids )
	{
		kids->SetupNormalTexture(); 
		kids = kids->GetNext(); 
	}

}

CVoid CNode::SetupDiffuseTexture()
{
	for(CUInt i=0; i< m_instanceGeometries.size(); i++)
	{
		CGeometry * geometry = m_instanceGeometries[i]->m_abstractGeometry;
		geometry->SetupDiffuseTexture( this, m_instanceGeometries[i] );
	}
	for(CUInt i=0; i< m_instanceControllers.size(); i++)
	{
		CGeometry * geometry = m_instanceControllers[i]->m_instanceGeometry->m_abstractGeometry;
		geometry->SetupDiffuseTexture( this, m_instanceControllers[i] );
	}

	// Update all the child nodes
	CNode * kids = m_children;
	while( kids )
	{
		kids->SetupDiffuseTexture(); 
		kids = kids->GetNext(); 
	}

}

CVoid CNode::CreateTrigger(CNovodex* nx)
{
	//triggers are static objects and have no animation	
	CPhysXMaterial physicsMaterial;

	for(CUInt i=0; i< m_instanceGeometries.size(); i++)
	{
		GetScene()->GeneratePhysX(eLOD_TRIGGER, 0, 100, CTrue, CFalse, physicsMaterial, m_instanceGeometries[i] );
	}

	// Update all the child nodes
	CNode * kids = m_children;
	while( kids )
	{
		kids->CreateTrigger( nx ); 
		kids = kids->GetNext(); 
	}


}

CVoid CNode::BuildLWMatrix( CFloat time )
{
	// Update all the transforms that have animations (if any) 
	if ( m_numAnimations > 0 )
	{
		for ( CUInt t = 0; t < m_sumTransforms.size(); t++)
		{
			CVec4f V( 0.0f, 0.0f, 0.0f, 0.0f );
			CMatrix M;
			for( CUInt i = 0; i < 16; i++ )
				M[i] = 0.0f;
			m_sumTransforms[t]->SetVector( V ); //set the sum to default
			m_sumTransforms[t]->SetMatrix( M );
			m_sumWeights[t] = 0.0f;
		}

		m_updateLocalMatrix = CTrue; // force update if there were animations

		std::vector<std::string>animationList;
		CUInt blendListCount = 0;
		for( CUInt i = 0; i < g_render.GetScene()->m_blendCycleList.size(); i++ )
		{
			animationList.push_back( g_render.GetScene()->m_blendCycleList[i] );
		}
		blendListCount = (CUInt)g_render.GetScene()->m_blendCycleList.size();

		for( CUInt i = 0; i < g_render.GetScene()->m_executeActionList.size(); i++ )
		{
			animationList.push_back(  g_render.GetScene()->m_executeActionList[i] );
		}

		for( CUInt j= 0; j < animationList.size(); j++ )
		{
			CChar animationName[MAX_NAME_SIZE];
			Cpy( animationName, animationList[j].c_str() );
			CInt clipIndex = 0;
			//Find the animation clip 
			for( CInt ac = 0; ac < g_render.GetScene()->GetNumClips(); ac++ )
			{
				if( Cmp( g_render.GetScene()->m_animationClips[ac]->GetName(), animationName ) )
				{
					clipIndex = ac;
					break;
				}
			}

			//make sure that we use correct values for execute action
			CFloat currentTime = g_render.GetScene()->m_animationClips[clipIndex]->GetCurrentAnimationTime();
			if( j >= blendListCount )
			{
				if( g_render.GetScene()->m_animationClips[clipIndex]->GetCurrentAnimationTime() > g_render.GetScene()->m_animationClips[clipIndex]->GetEnd() )
					currentTime = g_render.GetScene()->m_animationClips[clipIndex]->GetEnd();
				else if( g_render.GetScene()->m_animationClips[clipIndex]->GetCurrentAnimationTime() < g_render.GetScene()->m_animationClips[clipIndex]->GetStart() )
					currentTime = g_render.GetScene()->m_animationClips[clipIndex]->GetStart();

			}

			// update each animated transform 
			for ( CUInt t = 0; t < m_transforms[clipIndex].size(); t++)
			{
				if( !( j >= blendListCount && g_render.GetScene()->m_animationClips[clipIndex]->GetLock() ) )
				{
					if(  g_render.GetScene()->m_animationClips[clipIndex]->GetCurrentWeight() == 0.0f )
					{
						//set to default
						m_transforms[clipIndex][t]->SetVector( m_transforms[g_render.GetScene()->GetNumClips()][t]->GetVecTrans() );
						m_transforms[clipIndex][t]->SetMatrix( m_transforms[g_render.GetScene()->GetNumClips()][t]->GetMatrix() );
						continue;
					}
				}
				for( CUInt q = 0; q < m_transforms[clipIndex][t]->GetNumAnimations(); q++ )
				{
					if ( m_transforms[clipIndex][t]->GetAnimation(q) && Cmp( m_transforms[clipIndex][t]->GetAnimation(q)->GetClipTarget()->GetName(), animationName ) )
					{
						CAnimation * Anim = m_transforms[clipIndex][t]->GetAnimation(q); 

						// a single transform may have serveral animated channels attached 
						for ( CUInt c = 0; c < m_transforms[clipIndex][t]->GetNumChannels(q); c++)
						{
							CUInt animSet = 0;
							CUInt channelIdx = m_transforms[clipIndex][t]->GetChannelId(q, c); 
							for( CUInt index = 0; index < channelIdx; index++ )
							{
								animSet += Anim->m_channels[index]->GetNumElementTargets(); 
							}

							// interpolates the value based on the element that is to be targeted and the key frame info attached at load time
							Anim->AnimateChannel( m_transforms[clipIndex][t]->GetVecTrans(), m_transforms[clipIndex][t]->GetMatrix(), Anim->m_channels[channelIdx]->GetTargetElement2(), animSet, currentTime );

							if( j >= blendListCount && currentTime > ( g_render.GetScene()->m_animationClips[clipIndex]->GetEnd() - g_render.GetScene()->m_animationClips[clipIndex]->GetTargetDelayOut() ) && g_render.GetScene()->m_animationClips[clipIndex]->GetLock() )
							{
								//We should lock to last keyframe. So find last key frame
								Anim->AnimateChannel( m_transforms[g_render.GetScene()->GetNumClips() + 2][t]->GetVecTrans(), m_transforms[g_render.GetScene()->GetNumClips() + 2][t]->GetMatrix(), Anim->m_channels[channelIdx]->GetTargetElement2(), animSet, g_render.GetScene()->m_animationClips[clipIndex]->GetEnd() );
							}
						}
					}
				}

				if( j >= blendListCount && currentTime > ( g_render.GetScene()->m_animationClips[clipIndex]->GetEnd() - g_render.GetScene()->m_animationClips[clipIndex]->GetTargetDelayOut() ) && g_render.GetScene()->m_animationClips[clipIndex]->GetLock() )
				{
					if( m_sumTransforms[t]->GetType() == eCRotate || m_sumTransforms[t]->GetType() == eCTranslate || m_sumTransforms[t]->GetType() == eCScale )
					{
						m_sumTransforms[t]->SumVector(m_transforms[clipIndex][t]->GetVecTrans() * g_render.GetScene()->m_animationClips[clipIndex]->GetCurrentWeight() );
						m_sumTransforms[t]->SumVector(m_transforms[g_render.GetScene()->GetNumClips() + 2][t]->GetVecTrans() * (g_render.GetScene()->m_animationClips[clipIndex]->GetTargetWeight() - g_render.GetScene()->m_animationClips[clipIndex]->GetCurrentWeight() ));
					}
					else if( m_sumTransforms[t]->GetType() == eCMatrix )
					{
						m_sumTransforms[t]->AddMatrix(m_transforms[clipIndex][t]->GetMatrix(),  g_render.GetScene()->m_animationClips[clipIndex]->GetCurrentWeight()); 
						m_sumTransforms[t]->AddMatrix(m_transforms[g_render.GetScene()->GetNumClips() + 2][t]->GetMatrix(),  g_render.GetScene()->m_animationClips[clipIndex]->GetTargetWeight() -  g_render.GetScene()->m_animationClips[clipIndex]->GetCurrentWeight()); 
					}
					m_sumWeights[t] += g_render.GetScene()->m_animationClips[clipIndex]->GetTargetWeight();

				}
				else
				{
					if( m_sumTransforms[t]->GetType() == eCRotate || m_sumTransforms[t]->GetType() == eCTranslate || m_sumTransforms[t]->GetType() == eCScale )
						m_sumTransforms[t]->SumVector(m_transforms[clipIndex][t]->GetVecTrans() * g_render.GetScene()->m_animationClips[clipIndex]->GetCurrentWeight() );
					else if( m_sumTransforms[t]->GetType() == eCMatrix )
						m_sumTransforms[t]->AddMatrix(m_transforms[clipIndex][t]->GetMatrix(),  g_render.GetScene()->m_animationClips[clipIndex]->GetCurrentWeight()); 
					m_sumWeights[t] += g_render.GetScene()->m_animationClips[clipIndex]->GetCurrentWeight();
				}

			} //for all of the transforms

		} //for all of the blendcycle elements
	} 
	else //this node has no animation. set the sum to the default values. weight of default value will be 1
	{
		for ( CUInt t = 0; t < m_sumTransforms.size(); t++)
		{
			m_sumTransforms[t]->SetVector(m_transforms[g_render.GetScene()->GetNumClips()][t]->GetVecTrans()); //set the sum to default
			m_sumTransforms[t]->SetMatrix(m_transforms[g_render.GetScene()->GetNumClips()][t]->GetMatrix());
			m_sumWeights[t] = 1.0f;
		}
	}
	
	// Process all the transforms in this node down into a single local transform matrix
	//if we aren't animating, this doesn't need to be calculated every time.

	if(m_updateLocalMatrix)
	{
		CMatrixLoadIdentity( m_localMatrix ); 
		for ( CUInt t = 0; t < m_sumTransforms.size(); t++)
		{
			CVec4f defaultV;
			CFloat defaultVWeight = 0.0f;
			switch ( m_sumTransforms[t]->GetType() )
			{
			case eCRotate:
				if( m_sumWeights[t] < 1 )
				{
					defaultV = m_transforms[g_render.GetScene()->GetNumClips()][t]->GetVecTrans() * ( 1 - m_sumWeights[t] );
					defaultVWeight = 1 - m_sumWeights[t];
				}
				CMatrix4x4RotateAngleAxis( m_localMatrix, (m_sumTransforms[t]->GetVecTrans() + defaultV )* (1.f / (m_sumWeights[t] + defaultVWeight )) );	
				break;

			case eCTranslate:
				if( m_sumWeights[t] < 1 )
				{
					defaultV = m_transforms[g_render.GetScene()->GetNumClips()][t]->GetVecTrans() * ( 1 - m_sumWeights[t] );
					defaultVWeight = 1 - m_sumWeights[t];
				}
				CMatrix4x4Translate( m_localMatrix, (m_sumTransforms[t]->GetVecTrans() + defaultV )* (1.f / (m_sumWeights[t] + defaultVWeight )) );	
				break;

			case eCScale:
				if( m_sumWeights[t] < 1 )
				{
					defaultV = m_transforms[g_render.GetScene()->GetNumClips()][t]->GetVecTrans() * ( 1 - m_sumWeights[t] );
					defaultVWeight = 1 - m_sumWeights[t];
				}
				CMatrix4x4Scale( m_localMatrix, (m_sumTransforms[t]->GetVecTrans() + defaultV )* (1.f / (m_sumWeights[t] + defaultVWeight )) );	
				break;
			case eCMatrix:
				if( m_sumWeights[t] < 1 )
				{
					m_sumTransforms[t]->AddMatrix(m_transforms[g_render.GetScene()->GetNumClips()][t]->GetMatrix(),  1.0f - m_sumWeights[t] ); 
					defaultVWeight = 1 - m_sumWeights[t];
				}
				CMatrix dstMtx;
				CMatrix4x4Mult( (CFloat *) m_sumTransforms[t]->GetMatrix(), dstMtx, 1.f / (m_sumWeights[t] + defaultVWeight ) );
				CMatrix4x4Mult( dstMtx, m_localMatrix );
				break;
			case eCSkew:
			case eCLookAt:
			case eCTFormUnknown:
			default:
				break; 
			}
		}
		m_updateLocalMatrix = CFalse;
	}

	if ( m_parent )
	{
		if( m_parent->m_upAxis == eCZUp && Cmp( m_parent->GetName(), "vanda_engine_scene_root" ) ) 		//I just rotate static objects
		{
			CVec4f rot(1.0, 0.0, 0.0, -90.0);
			CMatrixCopy(m_parent->m_localMatrix, m_parent->m_localToWorldMatrix);
			CMatrix4x4RotateAngleAxis(m_parent->m_localToWorldMatrix, rot);
		}

		// The node has a parent, concatenate the local transform matrix with it to form our local-to-world
		//If we had a "parent is dirty" flag we could avoid this multiply a lot of the time
		CMatrixMult( m_localMatrix, m_parent->m_localToWorldMatrix, m_localToWorldMatrix); 
	}
	else
	{
		// The node doesn't have a parent, so the local transform matrix is our local-to-world
		CMatrixCopy( m_localMatrix, m_localToWorldMatrix ); 	
	}

	// if this node is used for skinning need to update the combined 
	// bind inverse local to world matrix with the current local to world matrix 			
	if ( m_usedForSkinning )
	{
		CMatrixMult(m_inverseBindMatrix, m_localToWorldMatrix, m_combinedSkinMatrix);
	}
	else
		m_orientReady = CTrue; 
}

CVoid CNode::UpdateOrient( CFloat time )
{
	BuildLWMatrix(time); 
	return;  
}

CVoid CNode::EnableShader(CInstanceGeometry* instanceGeometry)
{
	if (g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader)
	{
		if (g_fogBlurPass)
			g_shaderType = g_render.m_fogBlurProgram;
		else if (g_materialChannels != eCHANNELS_ALL)//render layers in editor (View | Layers menu). this piece of code is not available in Win32 project
		{
			switch (g_materialChannels)
			{
			case eCHANNELS_DIFFUSE:
				g_shaderType = g_render.m_shaderColorMapLayerProgram;
				break;
			case eCHANNELS_NORMALMAP:
				g_shaderType = g_render.m_shaderNormalMapLayerProgram;
				break;
			case eCHANNELS_DIRTMAP:
				g_shaderType = g_render.m_shaderDirtMapLayerProgram;
				break;
			case eCHANNELS_GLOSSMAP:
				g_shaderType = g_render.m_shaderGlossMapLayerProgram;
				break;
			case eCHANNELS_ALPHAMAP:
				g_shaderType = g_render.m_shaderAlphaMapLayerProgram;
				break;
			case eCHANNELS_POSITION:
				g_shaderType = g_render.m_shaderPositionLayerProgram;
				break;
			case eCHANNELS_NORMAL:
				g_shaderType = g_render.m_shaderNormalLayerProgram;
				break;
			}
		}
		else if (g_renderForWater)
		{
			g_shaderType = g_render.m_waterShaderProgram; //currently I support low quality water reflection
		}
		else if (g_shadowProperties.m_enable && g_render.UsingShadowShader() && g_render.m_useDynamicShadowMap && !Cmp(g_shadowProperties.m_directionalLightName, "\n"))
		{
			if (instanceGeometry->m_abstractGeometry->m_hasNormalMap)
			{
				switch (g_shadowProperties.m_shadowType)
				{
				case eSHADOW_SINGLE_HL:
					g_shaderType = g_render.m_shad_single_hl_normal_prog;
					break;
				case eSHADOW_SINGLE:
					g_shaderType = g_render.m_shad_single_normal_prog;
					break;
				case eSHADOW_MULTI_LEAK:
					g_shaderType = g_render.m_shad_multi_normal_prog;
					break;
				case eSHADOW_MULTI_NOLEAK:
					g_shaderType = g_render.m_shad_multi_noleak_normal_prog;
					break;
				case eSHADOW_PCF:
					g_shaderType = g_render.m_shad_pcf_normal_prog;
					break;
				case eSHADOW_PCF_TRILIN:
					g_shaderType = g_render.m_shad_pcf_trilin_normal_prog;
					break;
				case eSHADOW_PCF_4TAP:
					g_shaderType = g_render.m_shad_pcf_4tap_normal_prog;
					break;
				case eSHADOW_PCF_8TAP:
					g_shaderType = g_render.m_shad_pcf_8tap_normal_prog;
					break;
				case eSHADOW_PCF_GAUSSIAN:
					g_shaderType = g_render.m_shad_pcf_gaussian_normal_prog;
					break;
				}
			}
			else
			{
				switch (g_shadowProperties.m_shadowType)
				{
				case eSHADOW_SINGLE_HL:
					g_shaderType = g_render.m_shad_single_hl_prog;
					break;
				case eSHADOW_SINGLE:
					g_shaderType = g_render.m_shad_single_prog;
					break;
				case eSHADOW_MULTI_LEAK:
					g_shaderType = g_render.m_shad_multi_prog;
					break;
				case eSHADOW_MULTI_NOLEAK:
					g_shaderType = g_render.m_shad_multi_noleak_prog;
					break;
				case eSHADOW_PCF:
					g_shaderType = g_render.m_shad_pcf_prog;
					break;
				case eSHADOW_PCF_TRILIN:
					g_shaderType = g_render.m_shad_pcf_trilin_prog;
					break;
				case eSHADOW_PCF_4TAP:
					g_shaderType = g_render.m_shad_pcf_4tap_prog;
					break;
				case eSHADOW_PCF_8TAP:
					g_shaderType = g_render.m_shad_pcf_8tap_prog;
					break;
				case eSHADOW_PCF_GAUSSIAN:
					g_shaderType = g_render.m_shad_pcf_gaussian_prog;
					break;
				}
			}
		}
		else if (instanceGeometry->m_abstractGeometry->m_hasNormalMap)
			g_shaderType = g_render.m_shader_normalProgram;
		else
			g_shaderType = g_render.m_shaderProgram;

		glUseProgram(g_shaderType);
		glUniform1i(glGetUniformLocation(g_shaderType, "stex"), 7); // depth-maps
		glUniform4fv(glGetUniformLocation(g_shaderType, "far_d"), 1, g_multipleView->far_bound);
		glUniform2f(glGetUniformLocation(g_shaderType, "texSize"), (float)g_multipleView->m_dynamicShadowMap->depth_size, 1.0f / (float)g_multipleView->m_dynamicShadowMap->depth_size);
		glUniform1f(glGetUniformLocation(g_shaderType, "shadow_intensity"), g_shadowProperties.m_intensity);
		glUniformMatrix4fv(glGetUniformLocation(g_shaderType, "camera_inverse_matrix"), 1, CFalse, g_multipleView->cam_inverse_modelview);

		CInt num_point_lights = 0;
		CInt num_spot_lights = 0;
		CInt num_dir_lights = 0;
		//I support up to NR_DIR_LIGHTS directional light, up to NR_POINT_LIGHTS point lights, and up to NR_SPOT_LIGHT spot lights for each object
		if (g_engineLights.size() == 0 || g_editorMode == eMODE_PREFAB)
		{
			glUniform1f(glGetUniformLocation(g_shaderType, "point_light_radius[0]"), 1000000);
			glUniform1i(glGetUniformLocation(g_shaderType, "nr_dir_lights"), 0);
			glUniform1i(glGetUniformLocation(g_shaderType, "nr_point_lights"), 1);
			glUniform1i(glGetUniformLocation(g_shaderType, "nr_spot_lights"), 0);

		}
		else
		{
			for (CUInt i = 0; i < g_currentInstancePrefab->GetTotalLights(); i++)
			{
				CInstanceLight *instanceLight = g_currentInstancePrefab->m_lights[i];
				g_currentInstanceLight = instanceLight;

				if (instanceLight->m_abstractLight->GetType() == eLIGHTTYPE_DIRECTIONAL)
				{
					if (Cmp(g_shadowProperties.m_directionalLightName, instanceLight->m_abstractLight->GetName()))
						glUniform1i(glGetUniformLocation(g_shaderType, "defaultDirLightIndex"), i);

					num_dir_lights++;
				}
				if (instanceLight->m_abstractLight->GetType() == eLIGHTTYPE_POINT)
				{
					num_point_lights++;
					if (num_point_lights == 1)
						glUniform1f(glGetUniformLocation(g_shaderType, "point_light_radius[0]"), g_currentInstanceLight->GetRadius());
					else if (num_point_lights == 2)
						glUniform1f(glGetUniformLocation(g_shaderType, "point_light_radius[1]"), g_currentInstanceLight->GetRadius());
					else if (num_point_lights == 3)
						glUniform1f(glGetUniformLocation(g_shaderType, "point_light_radius[2]"), g_currentInstanceLight->GetRadius());
					else if (num_point_lights == 4)
						glUniform1f(glGetUniformLocation(g_shaderType, "point_light_radius[3]"), g_currentInstanceLight->GetRadius());
				}

				if (instanceLight->m_abstractLight->GetType() == eLIGHTTYPE_SPOT)
				{
					num_spot_lights++;
					if (num_spot_lights == 1)
						glUniform1f(glGetUniformLocation(g_shaderType, "spot_light_radius[0]"), g_currentInstanceLight->GetRadius());
				}

			}
			glUniform1i(glGetUniformLocation(g_shaderType, "nr_dir_lights"), num_dir_lights);
			glUniform1i(glGetUniformLocation(g_shaderType, "nr_point_lights"), num_point_lights);
			glUniform1i(glGetUniformLocation(g_shaderType, "nr_spot_lights"), num_spot_lights);
		}

		if (g_fogBlurPass)
		{
			glUniform1f(glGetUniformLocation(g_shaderType, "focalDistance"), g_multipleView->m_dof.m_focalDistance);
			glUniform1f(glGetUniformLocation(g_shaderType, "focalRange"), g_multipleView->m_dof.m_focalRange);

			CBool useFog;
			if (g_polygonMode != ePOLYGON_FILL || (g_dofProperties.m_enable && g_dofProperties.m_debug) || (g_shadowProperties.m_shadowType == eSHADOW_SINGLE_HL && g_shadowProperties.m_enable && g_render.UsingShadowShader()))
				useFog = CFalse;
			else
				useFog = CTrue;

			if (g_fogProperties.m_enable && useFog)
				glUniform1i(glGetUniformLocation(g_shaderType, "enableFog"), CTrue);
			else
				glUniform1i(glGetUniformLocation(g_shaderType, "enableFog"), CFalse);

		}
	}
	else
	{
		glUseProgram(0);
	}

}

CVoid CNode::UpdateDynamicPhysicsObjects(CNode* sceneRoot)
{
	for (CUInt i = 0; i< m_instanceGeometries.size(); i++)
	{
		CGeometry * geometry = m_instanceGeometries[i]->m_abstractGeometry;
		geometry->m_currentInstanceGeometry = m_instanceGeometries[i]; //used for selection color
		if (!geometry->m_hasAnimation && m_instanceGeometries[i]->m_hasPhysX && m_instanceGeometries[i]->m_physXDensity > 0.0f )
		{
			if (gPhysXscene)
			{
				for (CUInt j = 0; j < gPhysXscene->getNbActors(); j++)
				{
					CChar actorName[MAX_URI_SIZE];
					if (!gPhysXscene->getActors()[j]->getName()) continue;
					Cpy(actorName, gPhysXscene->getActors()[j]->getName());
					if (!Cmp(m_instanceGeometries[i]->m_physXName, "\n") && Cmp(actorName, m_instanceGeometries[i]->m_physXName))
					{
						if (m_instanceGeometries[i]->m_physXCount == 0)
						{
							if (!gPhysXscene->getActors()[j]->isSleeping())
							{
								GetScene()->SetUpdateBB(CTrue);

								NxVec3 pos;
								CFloat rot[4];
								pos = gPhysXscene->getActors()[j]->getGlobalPosition();
								gPhysXscene->getActors()[j]->getGlobalOrientationQuat().getWXYZ(rot);
								CMatrix rotationMatrix;
								CMatrixLoadIdentity(rotationMatrix);
								CMatrix translationMatrix;
								CMatrixLoadIdentity(translationMatrix);
								CQuat q(rot[1], rot[2], rot[3], rot[0]);
								CQuaternionToMatrix(&q, rotationMatrix);
								CMatrix4x4Translate(translationMatrix, CVec4f(pos.x, pos.y, pos.z, 0.0f));
								CMatrixLoadIdentity(m_instanceGeometries[i]->m_localToWorldMatrixControlledByPhysX);

								CMatrix4x4Mult(translationMatrix, m_instanceGeometries[i]->m_localToWorldMatrixControlledByPhysX);
								CMatrix4x4Mult(rotationMatrix, m_instanceGeometries[i]->m_localToWorldMatrixControlledByPhysX);
								CMatrix4x4Mult(m_instanceGeometries[i]->m_localToWorldMatrix/*m_localToWorldMatrix*/, m_instanceGeometries[i]->m_localToWorldMatrixControlledByPhysX);

								CGeometry* tempGeometry = m_instanceGeometries[i]->m_abstractGeometry;
								CVec3f src[8];
								src[0].x = tempGeometry->m_minAABB.m_i; src[0].y = tempGeometry->m_minAABB.m_j; src[0].z = tempGeometry->m_minAABB.m_k;
								src[1].x = tempGeometry->m_maxAABB.m_i; src[1].y = tempGeometry->m_minAABB.m_j; src[1].z = tempGeometry->m_maxAABB.m_k;
								src[2].x = tempGeometry->m_maxAABB.m_i; src[2].y = tempGeometry->m_minAABB.m_j; src[2].z = tempGeometry->m_minAABB.m_k;
								src[3].x = tempGeometry->m_minAABB.m_i; src[3].y = tempGeometry->m_minAABB.m_j; src[3].z = tempGeometry->m_maxAABB.m_k;
								src[4].x = tempGeometry->m_maxAABB.m_i; src[4].y = tempGeometry->m_maxAABB.m_j; src[4].z = tempGeometry->m_minAABB.m_k;
								src[5].x = tempGeometry->m_minAABB.m_i; src[5].y = tempGeometry->m_maxAABB.m_j; src[5].z = tempGeometry->m_minAABB.m_k;
								src[6].x = tempGeometry->m_minAABB.m_i; src[6].y = tempGeometry->m_maxAABB.m_j; src[6].z = tempGeometry->m_maxAABB.m_k;
								src[7].x = tempGeometry->m_maxAABB.m_i; src[7].y = tempGeometry->m_maxAABB.m_j; src[7].z = tempGeometry->m_maxAABB.m_k;

								CMatrixTransform(m_instanceGeometries[i]->m_localToWorldMatrixControlledByPhysX, src[0], m_instanceGeometries[i]->m_localToWorldVertex[0]);
								CMatrixTransform(m_instanceGeometries[i]->m_localToWorldMatrixControlledByPhysX, src[1], m_instanceGeometries[i]->m_localToWorldVertex[1]);
								CMatrixTransform(m_instanceGeometries[i]->m_localToWorldMatrixControlledByPhysX, src[2], m_instanceGeometries[i]->m_localToWorldVertex[2]);
								CMatrixTransform(m_instanceGeometries[i]->m_localToWorldMatrixControlledByPhysX, src[3], m_instanceGeometries[i]->m_localToWorldVertex[3]);
								CMatrixTransform(m_instanceGeometries[i]->m_localToWorldMatrixControlledByPhysX, src[4], m_instanceGeometries[i]->m_localToWorldVertex[4]);
								CMatrixTransform(m_instanceGeometries[i]->m_localToWorldMatrixControlledByPhysX, src[5], m_instanceGeometries[i]->m_localToWorldVertex[5]);
								CMatrixTransform(m_instanceGeometries[i]->m_localToWorldMatrixControlledByPhysX, src[6], m_instanceGeometries[i]->m_localToWorldVertex[6]);
								CMatrixTransform(m_instanceGeometries[i]->m_localToWorldMatrixControlledByPhysX, src[7], m_instanceGeometries[i]->m_localToWorldVertex[7]);

								CVec3f m_minLocalToWorld;
								CVec3f m_maxLocalToWorld;
								m_minLocalToWorld.x = m_minLocalToWorld.y = m_minLocalToWorld.z = 100000000.0f;
								m_maxLocalToWorld.x = m_maxLocalToWorld.y = m_maxLocalToWorld.z = -100000000.0f;

								for (CUInt k = 0; k< 8; k++)
								{
									if (m_instanceGeometries[i]->m_localToWorldVertex[k].x > m_maxLocalToWorld.x)
										m_maxLocalToWorld.x = m_instanceGeometries[i]->m_localToWorldVertex[k].x;
									if (m_instanceGeometries[i]->m_localToWorldVertex[k].y > m_maxLocalToWorld.y)
										m_maxLocalToWorld.y = m_instanceGeometries[i]->m_localToWorldVertex[k].y;
									if (m_instanceGeometries[i]->m_localToWorldVertex[k].z > m_maxLocalToWorld.z)
										m_maxLocalToWorld.z = m_instanceGeometries[i]->m_localToWorldVertex[k].z;

									if (m_instanceGeometries[i]->m_localToWorldVertex[k].x < m_minLocalToWorld.x)
										m_minLocalToWorld.x = m_instanceGeometries[i]->m_localToWorldVertex[k].x;
									if (m_instanceGeometries[i]->m_localToWorldVertex[k].y < m_minLocalToWorld.y)
										m_minLocalToWorld.y = m_instanceGeometries[i]->m_localToWorldVertex[k].y;
									if (m_instanceGeometries[i]->m_localToWorldVertex[k].z < m_minLocalToWorld.z)
										m_minLocalToWorld.z = m_instanceGeometries[i]->m_localToWorldVertex[k].z;
								}
								m_instanceGeometries[i]->m_minLocalToWorldAABBControlledByPhysX = m_minLocalToWorld;
								m_instanceGeometries[i]->m_maxLocalToWorldAABBControlledByPhysX = m_maxLocalToWorld;
								m_instanceGeometries[i]->m_center = (m_instanceGeometries[i]->m_minLocalToWorldAABBControlledByPhysX + m_instanceGeometries[i]->m_maxLocalToWorldAABBControlledByPhysX) * 0.5f;
							}
							m_instanceGeometries[i]->m_physXCount++;
						}
					}
				}
			}
		}
	}


	// Update All Children 
	if (m_children)
		m_children->UpdateDynamicPhysicsObjects(sceneRoot);
	// Update All Siblings 
	if (m_next)
		m_next->UpdateDynamicPhysicsObjects(sceneRoot);
}

CVoid CNode::RenderModelsControlledByPhysX(CBool sceneManager, CNode* sceneRoot )
{
	for(CUInt i=0; i< m_instanceGeometries.size(); i++)
	{
		if (g_multipleView->IsPlayGameMode())
			if (m_instanceGeometries[i]->m_isInvisible)
				continue;

		CGeometry * geometry = m_instanceGeometries[i]->m_abstractGeometry;
		geometry->m_currentInstanceGeometry = m_instanceGeometries[i]; //used for selection color
		CBool renderPhysXForFreeCamera = CFalse;
		if (!g_multipleView->IsPlayGameMode() && g_editorMode == eMODE_VSCENE)
		{
			if (!geometry->m_hasAnimation && m_instanceGeometries[i]->m_hasPhysX && m_instanceGeometries[i]->m_physXDensity > 0.0f)
			{
				renderPhysXForFreeCamera = CTrue;
			}
		}
		if (!geometry->m_hasAnimation && m_instanceGeometries[i]->m_hasPhysX && m_instanceGeometries[i]->m_physXDensity > 0.0f &&!renderPhysXForFreeCamera)
		{
			if (g_editorMode == eMODE_PREFAB || (g_editorMode == eMODE_VSCENE && g_currentInstancePrefab->GetRenderForQuery()) || (g_editorMode == eMODE_VSCENE && g_renderShadow))
			{
				g_render.ModelViewMatrix();
				g_render.PushMatrix();
				g_render.MultMatrix(m_instanceGeometries[i]->m_localToWorldMatrixControlledByPhysX);
				//EnableShader(m_instanceGeometries[i]);

				if (sceneManager)
				{
					if (g_camera->m_cameraManager->IsBoxInFrustum(&m_instanceGeometries[i]->m_localToWorldVertex[0], 8))
					{
						geometry->Draw(this, m_instanceGeometries[i]);
						g_numVerts += geometry->m_vertexcount;
					}
				}
				else
				{
					geometry->Draw(this, m_instanceGeometries[i]);
					g_numVerts += geometry->m_vertexcount;
				}
				//PrintInfo(" %s Rendering Children \n", Name ); 
				g_render.PopMatrix();
			}  //if (g_currentInstancePrefab->GetRenderForQuery())
		}
		else if (m_instanceGeometries[i]->m_renderWithPhysX || renderPhysXForFreeCamera)// render without octree. Make sure that we don't render meshes controlled by PhysX
		{
			if (g_editorMode == eMODE_PREFAB || (g_editorMode == eMODE_VSCENE && g_currentInstancePrefab->GetRenderForQuery()) || (g_editorMode == eMODE_VSCENE && g_renderShadow))
			{
				if (!m_instanceGeometries[i]->m_abstractGeometry->m_hasAnimation)
				{
					g_render.ModelViewMatrix();
					g_render.PushMatrix();
					g_render.MultMatrix(/*m_localToWorldMatrix*/m_instanceGeometries[i]->m_localToWorldMatrix);
					g_render.SetCurrentLMMat(/*m_localToWorldMatrix*/m_instanceGeometries[i]->m_localToWorldMatrix);

					if (sceneManager && (!(m_instanceGeometries[i]->m_physXDensity && m_instanceGeometries[i]->m_hasPhysX) || renderPhysXForFreeCamera))
					{
						if (g_camera->m_cameraManager->IsBoxInFrustum(&m_instanceGeometries[i]->m_localToWorldVertex[0], 8))
						{
							//EnableShader(m_instanceGeometries[i]);

							geometry->Draw(this, m_instanceGeometries[i]);
							g_numVerts += geometry->m_vertexcount;
						}
					}
					else if (!(m_instanceGeometries[i]->m_physXDensity && m_instanceGeometries[i]->m_hasPhysX) || renderPhysXForFreeCamera)
					{
						//EnableShader(m_instanceGeometries[i]);

						geometry->Draw(this, m_instanceGeometries[i]);
						g_numVerts += geometry->m_vertexcount;
					}
					g_render.PopMatrix();

				}
			} //if (g_currentInstancePrefab->GetRenderForQuery())
		} //else

	}


    // Render All Children 
	if (m_children)
		m_children->RenderModelsControlledByPhysX(sceneManager, sceneRoot );
	// Render All Siblings 
	if (m_next)
		m_next->RenderModelsControlledByPhysX(sceneManager, sceneRoot); 
}

CVoid CNode::RenderAnimatedModels( CBool sceneManager, CNode* sceneRoot, CBool renderController )
{
	if ( renderController && m_usedForSkinning && (g_polygonMode == ePOLYGON_LINE || g_polygonMode == ePOLYGON_POINT))
	{
		glPushAttrib(GL_CURRENT_BIT);
		glUseProgram(0);

		CVec3f v; v.x = v.y = v.z = 0.0f;
		CVec3f tv1;
		CVec3f tv2;
		CMatrixTransform(m_parent->m_localToWorldMatrix, v, tv1);
		CMatrixTransform(m_localToWorldMatrix, v, tv2);
		CBool root = CFalse;
		if (tv1.x == 0 && tv1.y == 0 && tv1.z == 0)
			root = CTrue;
		if (!root)
		{

			glColor3f(1.0, 1.0, 0.0);

			glBegin(GL_LINES);
			glVertex3f(tv1.x, tv1.y, tv1.z);
			glVertex3f(tv2.x, tv2.y, tv2.z);
			glEnd();
		}
		glColor3f(1.0, 0.0, 0.0);

		glPointSize(5.0);
		glPushMatrix();
		glMultMatrixf( m_localToWorldMatrix );
		glBegin( GL_POINTS );
		glVertex3f(0,0,0);
		glEnd();
		glPopMatrix();
		glPopAttrib();
		glPointSize(1.0);
	}
	if (!renderController)
	{
		for (CUInt i = 0; i < m_instanceGeometries.size(); i++)
		{
			if (g_multipleView->IsPlayGameMode())
				if (m_instanceGeometries[i]->m_isInvisible)
					continue;

			g_render.ModelViewMatrix();
			g_render.PushMatrix();

			g_render.MultMatrix(m_localToWorldMatrix);
			//g_render.SetCurrentLMMat( m_localToWorldMatrix ); 

			CGeometry * geometry = m_instanceGeometries[i]->m_abstractGeometry;
			geometry->m_currentInstanceGeometry = m_instanceGeometries[i]; //used for selection color

			if (geometry->m_hasAnimation)
			{
				//EnableShader(m_instanceGeometries[i]);

				if (sceneManager)
				{
					if (g_camera->m_cameraManager->IsBoxInFrustum(&m_instanceGeometries[i]->m_localToWorldVertex[0], 8))
					{
						geometry->Draw(this, m_instanceGeometries[i]);
						g_numVerts += geometry->m_vertexcount;
					}
				}
				else
				{
					geometry->Draw(this, m_instanceGeometries[i]);
					g_numVerts += geometry->m_vertexcount;
				}
			}
			glPopMatrix();
		}
	}
	else
	{

		for (CUInt i = 0; i < m_instanceControllers.size(); i++)
		{
			CGeometry * geometry = m_instanceControllers[i]->m_instanceGeometry->m_abstractGeometry;
			CController * controller = m_instanceControllers[i]->m_abstractController;
			geometry->m_currentInstanceGeometry = m_instanceControllers[i]->m_instanceGeometry; //used for selection color

			if (controller->GetRenderReady() == CTrue)
			{
				//EnableShader(geometry->m_currentInstanceGeometry);

				g_render.ModelViewMatrix();
				g_render.PushMatrix();

				g_render.MultMatrix(m_localToWorldMatrix);

				if (sceneManager)
				{
					if (g_camera->m_cameraManager->IsBoxInFrustum(&m_instanceControllers[i]->m_instanceGeometry->m_localToWorldVertex[0], 8))
					{
						geometry->Draw(this, m_instanceControllers[i]);
						g_numVerts += geometry->m_vertexcount;
					}
				}
				else
				{
					geometry->Draw(this, m_instanceControllers[i]);
					g_numVerts += geometry->m_vertexcount;
				}
				glPopMatrix();
			}
		}
	}

	//PrintInfo(" %s Rendering Children \n", Name ); 

    // Render All Children 
	if (m_children)
		m_children->RenderAnimatedModels(sceneManager, sceneRoot, renderController );
	// Render All Siblings 
	if (m_next)
		m_next->RenderAnimatedModels(sceneManager, sceneRoot, renderController); 

}

CVoid CNode::ResetSkinData()
{
	for (CUInt i = 0; i < m_instanceGeometries.size(); i++)
	{
		CGeometry * geometry = m_instanceGeometries[i]->m_abstractGeometry;
		geometry->SetUpdateSkin(CTrue);
	}
	for (CUInt i = 0; i < m_instanceControllers.size(); i++)
	{
		CGeometry * geometry = m_instanceControllers[i]->m_instanceGeometry->m_abstractGeometry;
		geometry->SetUpdateSkin(CTrue);
	}
	if (m_children)
		m_children->ResetSkinData();
	if (m_next)
		m_next->ResetSkinData();
}

CVoid CNode::Render(CBool sceneManager, CChar* parentTreeNameOfGeometries, CBool renderController, CBool checkVisibility, CBool drawGeometry)
{
	//PrintInfo(" Rendering Node %s Type %d \n", Name, (CInt32)Type ); 
	//if (g_render.GetShowHiearchy() )
	//	DrawLineToChildren();
	//PrintInfo(" Rendering Node %s Type %d \n", Name, (CInt32)Type ); 
	//if (g_render.GetShowHiearchy() )
	//	DrawLineToChildren();
	g_render.ModelViewMatrix();
	// to concate to the camera which should be already set 	
	g_render.PushMatrix();
	g_render.MultMatrix(m_localToWorldMatrix);
	g_render.SetCurrentLMMat( m_localToWorldMatrix ); 
	for(CUInt i=0; i< m_instanceGeometries.size(); i++)
	{
		if (g_multipleView->IsPlayGameMode())
			if (m_instanceGeometries[i]->m_renderWithPhysX)
				continue;

		if (g_multipleView->IsPlayGameMode())
			if (m_instanceGeometries[i]->m_isInvisible)
				continue;

		CGeometry * geometry = m_instanceGeometries[i]->m_abstractGeometry;
		geometry->m_currentInstanceGeometry = m_instanceGeometries[i]; //used for selection color
		if( parentTreeNameOfGeometries )
		{ 
			for ( CUInt j = 0; j < m_instanceGeometries[i]->m_parentTree.size(); j++ )
			{
				if( Cmp( m_instanceGeometries[i]->m_parentTree[j]->GetName(), parentTreeNameOfGeometries ) && m_instanceGeometries[i]->m_renderCount == 0 )
				{
					//if (!checkVisibility)
					//	EnableShader(m_instanceGeometries[i]);
					if( sceneManager )
					{
						if (g_camera->m_cameraManager->IsBoxInFrustum(&m_instanceGeometries[i]->m_localToWorldVertex[0], 8))
						{
							if (checkVisibility)
							{
								if (g_currentInstancePrefab)
								{
									g_currentInstancePrefab->SetRenderForQuery(CTrue);
								}
							}
							else
							{
								if (drawGeometry)
									geometry->Draw(this, m_instanceGeometries[i]);
								g_numVerts += geometry->m_vertexcount;
							}
						}
					}
					else
					{
						if (checkVisibility)
						{
							if (g_currentInstancePrefab)
							{
								g_currentInstancePrefab->SetRenderForQuery(CTrue);
							}
						}
						else
						{
							if (drawGeometry)
								geometry->Draw(this, m_instanceGeometries[i]);
							g_numVerts += geometry->m_vertexcount;
						}
					}
					m_instanceGeometries[i]->m_renderCount++; //make sure that we don't render any geometries more than once
					break;
				}
			}
			
		}
		else // render without octree. Make sure that we don't render meshes controlled by PhysX
		{
			if (!m_instanceGeometries[i]->m_abstractGeometry->m_hasAnimation)
			{
				if (sceneManager  && !(m_instanceGeometries[i]->m_physXDensity && m_instanceGeometries[i]->m_hasPhysX && g_multipleView->IsPlayGameMode()))
				{
					if (g_camera->m_cameraManager->IsBoxInFrustum(&m_instanceGeometries[i]->m_localToWorldVertex[0], 8))
					{
						//if (!checkVisibility)
						//	EnableShader(m_instanceGeometries[i]);

						if (checkVisibility)
						{
							if (g_currentInstancePrefab)
							{
								g_currentInstancePrefab->SetRenderForQuery(CTrue);
							}
						}
						else
						{
							if (drawGeometry)
								geometry->Draw(this, m_instanceGeometries[i]);
							g_numVerts += geometry->m_vertexcount;
						}
					}
				}
				else if (!(m_instanceGeometries[i]->m_physXDensity && m_instanceGeometries[i]->m_hasPhysX && g_multipleView->IsPlayGameMode()))
				{
					//if (!checkVisibility)
					//	EnableShader(m_instanceGeometries[i]);

					if (checkVisibility)
					{
						if (g_currentInstancePrefab)
						{
							g_currentInstancePrefab->SetRenderForQuery(CTrue);
						}
					}
					else
					{
						if (drawGeometry)
							geometry->Draw(this, m_instanceGeometries[i]);
						g_numVerts += geometry->m_vertexcount;
					}
				}
			}

		} //else

	}

	//if( renderController )
	//{
	//	for(CUInt i=0; i< m_instanceControllers.size(); i++)
	//	{
	//		CGeometry * geometry = m_instanceControllers[i]->m_instanceGeometry->m_abstractGeometry;
	//		CController * controller = m_instanceControllers[i]->m_abstractController;
	//		geometry->m_currentInstanceGeometry = m_instanceControllers[i]->m_instanceGeometry; //used for selection color
	//		if (controller->GetRenderReady() == CTrue)
	//		{

	//			if( sceneManager )
	//			{
	//				if( g_camera->m_cameraManager->IsBoxInFrustum( &m_instanceControllers[i]->m_instanceGeometry->m_localToWorldVertex[0], 8 ) )
	//				{
	//					EnableShader(geometry->m_currentInstanceGeometry);

	//					//geometry->ComputeAABB();
	//					geometry->Draw(this, m_instanceControllers[i]);
	//					g_numVerts += geometry->m_vertexcount;
	//				}
	//			}
	//			else 
	//			{
	//				if( g_renderShadow ) //render for shadow
	//				{
	//					if( m_instanceControllers[i]->m_instanceGeometry->m_distanceFromCamera <= g_shadowProperties.m_shadowFarClipPlane )
	//					{
	//						EnableShader(geometry->m_currentInstanceGeometry);

	//						geometry->Draw(this, m_instanceControllers[i]);
	//						g_numVerts += geometry->m_vertexcount;
	//					}
	//				}
	//				else
	//				{
	//					EnableShader(geometry->m_currentInstanceGeometry);

	//					geometry->Draw(this, m_instanceControllers[i]);
	//					g_numVerts += geometry->m_vertexcount;
	//				}
	//			}
	//		}
	//	}
	//}
	//PrintInfo(" %s Rendering Children \n", Name ); 
	g_render.PopMatrix(); 

    // Render All Children 
	if (m_children)
		m_children->Render(sceneManager, parentTreeNameOfGeometries, renderController, checkVisibility, drawGeometry);
	// Render All Siblings 
	if (m_next)
		m_next->Render(sceneManager, parentTreeNameOfGeometries, renderController, checkVisibility, drawGeometry);
}

CVoid CNode::RenderAABBWithLines(CBool animatedGeo)
{
	for( CUInt i = 0; i < m_instanceGeometries.size(); i++ )
	{
		g_render.PushMatrix();
		if (m_instanceGeometries[i]->m_hasPhysX && m_instanceGeometries[i]->m_physXDensity && g_multipleView->IsPlayGameMode() && g_editorMode == eMODE_VSCENE)
			g_render.MultMatrix(m_instanceGeometries[i]->m_localToWorldMatrixControlledByPhysX); 
		else
			g_render.MultMatrix(m_instanceGeometries[i]->m_localToWorldMatrix); 
		g_render.SetCurrentLMMat( m_localToWorldMatrix ); 

		CGeometry *geometry = m_instanceGeometries[i]->m_abstractGeometry;
		if( animatedGeo )
		{
			if( geometry->m_hasAnimation )
				geometry->DrawAABBWithLines(); 
		}
		else
		{
			if( !geometry->m_hasAnimation )
				geometry->DrawAABBWithLines(); 
		}
		g_render.PopMatrix();   
	}
	if( animatedGeo )
	{
		for(CUInt i=0; i< m_instanceControllers.size(); i++)
		{
			g_render.PushMatrix();
			g_render.MultMatrix(m_instanceControllers[i]->m_instanceGeometry->m_localToWorldMatrix);
			g_render.SetCurrentLMMat( m_localToWorldMatrix ); 

			CGeometry * geometry = m_instanceControllers[i]->m_instanceGeometry->m_abstractGeometry;
			CController * controller = m_instanceControllers[i]->m_abstractController;
			if (controller->GetRenderReady() == CTrue)
				geometry->DrawAABBWithLines(); 

			g_render.PopMatrix();
		}
	}

	//Render all childs
	if (m_children)
		m_children->RenderAABBWithLines(animatedGeo);
	// Render All Siblings 
	if (m_next)
		m_next->RenderAABBWithLines(animatedGeo);
}

CVoid CNode::RenderAABBWithQuads()
{
	g_render.PushMatrix();
	g_render.MultMatrix(m_localToWorldMatrix); 
	g_render.SetCurrentLMMat( m_localToWorldMatrix ); 

	for( CUInt i = 0; i < m_instanceGeometries.size(); i++ )
	{
		CGeometry *geometry = m_instanceGeometries[i]->m_abstractGeometry;

		glPushName( geometry->m_nameIndex ); 
		geometry->DrawAABBWithQuads(); 
		glPopName();
	}

	for(CUInt i=0; i< m_instanceControllers.size(); i++)
	{
		CGeometry * geometry = m_instanceControllers[i]->m_instanceGeometry->m_abstractGeometry;
		CController * controller = m_instanceControllers[i]->m_abstractController;
		if (controller->GetRenderReady() == CTrue)
		{
			glPushName( geometry->m_nameIndex ); 
			geometry->DrawAABBWithQuads(); 
			glPopName();
		}
	}

	g_render.PopMatrix(); 
	//Render all childs
	if (m_children)
		m_children->RenderAABBWithQuads();
	// Render All Siblings 
	if (m_next)
		m_next->RenderAABBWithQuads();
}

CVoid CNode::RenderSelectionMode(CNode* sceneRoot)
{
	for( CUInt i = 0; i < m_instanceGeometries.size(); i++ )
	{
		//do not render invisible geometries
		if (g_multipleView->IsPlayGameMode())
			if (m_instanceGeometries[i]->m_isInvisible)
				continue;

		g_render.PushMatrix();
		if (m_instanceGeometries[i]->m_hasPhysX && m_instanceGeometries[i]->m_physXDensity > 0 && g_multipleView->IsPlayGameMode() && g_editorMode == eMODE_VSCENE)
			g_render.MultMatrix(m_instanceGeometries[i]->m_localToWorldMatrixControlledByPhysX );
		else
		{
			g_render.MultMatrix(m_instanceGeometries[i]->m_localToWorldMatrix); 
		}
		g_render.SetCurrentLMMat( m_localToWorldMatrix ); 

		CGeometry *geometry = m_instanceGeometries[i]->m_abstractGeometry;

		if( g_menu.m_geometryBasedSelection )
		{
			glPushName( m_instanceGeometries[i]->m_nameIndex );
			//glPushName( geometry->m_nameIndex );
		}
		geometry->DrawSelectionMode(this, m_instanceGeometries[i]);
		if( g_menu.m_geometryBasedSelection )
			glPopName();

		g_render.PopMatrix(); 

	}

	for(CUInt i=0; i< m_instanceControllers.size(); i++)
	{
		g_render.PushMatrix();
		g_render.MultMatrix(m_localToWorldMatrix); 
		g_render.SetCurrentLMMat( m_localToWorldMatrix ); 

		CGeometry * geometry = m_instanceControllers[i]->m_instanceGeometry->m_abstractGeometry;
		CController * controller = m_instanceControllers[i]->m_abstractController;
		if (controller->GetRenderReady() == CTrue)
		{
			if( g_menu.m_geometryBasedSelection )
			{
				glPushName(m_instanceControllers[i]->m_instanceGeometry->m_nameIndex);
				//glPushName( geometry->m_nameIndex );
			}
			geometry->DrawSelectionMode(this, m_instanceControllers[i]);
			if( g_menu.m_geometryBasedSelection )
				glPopName();
		}
		g_render.PopMatrix(); 

	}

	//Render all childs
	if (m_children)
		m_children->RenderSelectionMode(sceneRoot);
	// Render All Siblings 
	if (m_next)
		m_next->RenderSelectionMode(sceneRoot);
}

CVoid CNode::SetScene( CScene* scene )
{
	m_scene = scene;
}

CScene* CNode::GetScene()
{
	return m_scene;
}
