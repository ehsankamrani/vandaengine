//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "octree.h"
#include "..\graphicsEngine\render.h"
#include "..\graphicsEngine\scene.h"
#include "..\VandaEngine1Win32.h"
#include "..\main.h"
COctree::COctree()
{
	Init();
}

CVoid COctree::Init()
{
	m_minAABB.x = m_minAABB.y = m_minAABB.z = 100000000.0f;
	m_maxAABB.x = m_maxAABB.y = m_maxAABB.z = -100000000.0f;

	for ( CUInt i = 0; i < 8; i++ )
		m_pSubNode[i] = 0;

	m_geoCount = 0;
	m_leaf = CFalse;
	memset(m_name, 0, MAX_NAME_SIZE);
}

COctree::~COctree()
{
	for( CUInt i = 0; i < 8; i++ )
		CDelete( m_pSubNode[i] );
}

CVoid COctree::SetName( CChar* name )
{
	Cpy( m_name, name );
}

CVoid COctree::SetDimentions( CVec3f min, CVec3f max )
{
	m_minAABB = min;
	m_maxAABB = max;
	m_center = ( min + max ) * 0.5f;
}

CVoid COctree::SetLevel( CInt level )
{
	m_level = level;
}

CVoid COctree::Render(CBool checkVisibility, CBool drawGeometry)
{
	CBool renderScene = CFalse;
	CVector temp_min( m_minAABB.x, m_minAABB.y, m_minAABB.z );
	CVector temp_max( m_maxAABB.x, m_maxAABB.y, m_maxAABB.z );
	CVec3f m_point[8];
	m_point[0].x = temp_min.m_i; m_point[0].y = temp_min.m_j; m_point[0].z = temp_min.m_k;
	m_point[1].x = temp_max.m_i; m_point[1].y = temp_max.m_j; m_point[1].z = temp_max.m_k;
	m_point[2].x = temp_max.m_i; m_point[2].y = temp_min.m_j; m_point[2].z = temp_min.m_k;
	m_point[3].x = temp_min.m_i; m_point[3].y = temp_max.m_j; m_point[3].z = temp_max.m_k;
	m_point[4].x = temp_max.m_i; m_point[4].y = temp_max.m_j; m_point[4].z = temp_min.m_k;
	m_point[5].x = temp_max.m_i; m_point[5].y = temp_min.m_j; m_point[5].z = temp_max.m_k;
	m_point[6].x = temp_min.m_i; m_point[6].y = temp_max.m_j; m_point[6].z = temp_min.m_k;
	m_point[7].x = temp_min.m_i; m_point[7].y = temp_min.m_j; m_point[7].z = temp_max.m_k;
	CInt visiblePoints = 0;
	for( CUInt i = 0; i < 8; i++ )
		if( g_camera->m_cameraManager->IsBoxInFrustum( &m_point[i], 1 ) )
			visiblePoints++;

	if( g_camera->m_cameraManager->IsBoxInFrustum( &m_point[0], 8 ) )
	{
		if( visiblePoints == 8 && m_geoCount > 0 )
		{
			//render all the geometries attached to this node
			//scene manager = False
			renderScene = CTrue;
			g_main->Render3DModels(CFalse, m_name, checkVisibility, drawGeometry);

			//debug mode
			if( g_databaseVariables.m_showOctree )
			{
				CVector color( 0.0, 1.0, 0.0 );
				m_glUtil.DrawCWBoxWithLines( temp_min, temp_max, color );
			}
		}
		else
		{
			if( m_leaf )
			{
				for ( CUInt i = 0; i < 8; i++ )
					if( m_pSubNode[i] )
						m_pSubNode[i]->Render(checkVisibility, drawGeometry);
			}
			else
			{
				if( m_geoCount > 0 )
				{
					//frustum culling
					//render the geometry
					renderScene = CTrue;
					g_main->Render3DModels(CTrue, m_name, checkVisibility, drawGeometry);
					//debug mode
					if( g_databaseVariables.m_showOctree )
					{
						CVector color( 1.0, 0.0, 1.0 );
						m_glUtil.DrawCWBoxWithLines( temp_min, temp_max, color );
					}
				}
			}
		}
	}
	//if( !renderScene)
	//{
	//	g_main->UpdateAnimations();
	//}
}

CVoid COctree::GetWorldDimensions()
{
	for( CUInt i = 0 ; i < g_scene.size(); i++ )
	{
		g_render.SetScene( g_scene[i] );
		if( !g_render.GetScene()->m_isTrigger )
		{
			//if (g_scene[i]->m_hasAnimation)
			//	continue;

			for( CUInt j = 0; j < g_scene[i]->m_instanceGeometries.size(); j++ )
			{
				//do not calculate trigger dimensions
				if (g_scene[i]->m_instanceGeometries[j]->m_isTrigger || g_scene[i]->m_instanceGeometries[j]->m_isInvisible || g_scene[i]->m_instanceGeometries[j]->m_renderWithPhysX || g_scene[i]->m_instanceGeometries[j]->m_abstractGeometry->m_hasAnimation)
					continue;
				CInstanceGeometry* m_tempGeo = g_scene[i]->m_instanceGeometries[j];
				if( !m_tempGeo->m_abstractGeometry->m_hasAnimation &&!( m_tempGeo->m_hasPhysX && m_tempGeo->m_physXDensity ) )
				{
					if( m_tempGeo->m_maxLocalToWorldAABB.x > m_maxAABB.x )
						m_maxAABB.x = m_tempGeo->m_maxLocalToWorldAABB.x;
					if( m_tempGeo->m_maxLocalToWorldAABB.y > m_maxAABB.y )
						m_maxAABB.y = m_tempGeo->m_maxLocalToWorldAABB.y;
					if( m_tempGeo->m_maxLocalToWorldAABB.z > m_maxAABB.z )
						m_maxAABB.z = m_tempGeo->m_maxLocalToWorldAABB.z;

					if( m_tempGeo->m_minLocalToWorldAABB.x < m_minAABB.x )
						m_minAABB.x = m_tempGeo->m_minLocalToWorldAABB.x;
					if( m_tempGeo->m_minLocalToWorldAABB.y < m_minAABB.y )
						m_minAABB.y = m_tempGeo->m_minLocalToWorldAABB.y;
					if( m_tempGeo->m_minLocalToWorldAABB.z < m_minAABB.z )
						m_minAABB.z = m_tempGeo->m_minLocalToWorldAABB.z;
				}
			}
			CVec3f temp = m_maxAABB + m_minAABB;
			m_center = temp * 0.5f;
		}
	}
}

CVoid COctree::SplitNode8( COctree* parent )
{
	for( CUInt i = 0; i < 8; i++ )
	{
		CDelete( m_pSubNode[i] ); 
		m_pSubNode[i] = CNew( COctree );
		m_pSubNode[i]->m_pParent = parent;
		m_pSubNode[i]->SetLevel( m_level + 1 );

		//eTOP_RIGHT_FRONT
		if( i == eTOP_RIGHT_FRONT )
		{
			m_pSubNode[i]->SetDimentions( m_center, m_maxAABB );
			CChar temp_name[MAX_NAME_SIZE];
			sprintf( temp_name, "%s%i", "octree_eTOP_RIGHT_FRONT_level_", m_pSubNode[i]->m_level );
			m_pSubNode[i]->SetName( temp_name );
		}
		else if( i == eBOTTOM_RIGHT_FRONT )
		{
			CVec3f temp_min( m_center.x, m_center.y, m_minAABB.z );
			CVec3f temp_max( m_maxAABB.x, m_maxAABB.y, m_center.z );
			m_pSubNode[i]->SetDimentions( temp_min, temp_max );	
			CChar temp_name[MAX_NAME_SIZE];
			sprintf( temp_name, "%s%i", "octree_eBOTTOM_RIGHT_FRONT_level_", m_pSubNode[i]->m_level );
			m_pSubNode[i]->SetName( temp_name );

		}
		else if( i == eBOTTOM_LEFT_BACK )
		{
			m_pSubNode[i]->SetDimentions( m_minAABB, m_center );
			CChar temp_name[MAX_NAME_SIZE];
			sprintf( temp_name, "%s%i", "octree_eBOTTOM_LEFT_BACK_level_", m_pSubNode[i]->m_level );
			m_pSubNode[i]->SetName( temp_name );
		}
		else if( i == eTOP_LEFT_BACK )
		{
			CVec3f temp_min( m_minAABB.x, m_minAABB.y, m_center.z );
			CVec3f temp_max( m_center.x, m_center.y, m_maxAABB.z );
			m_pSubNode[i]->SetDimentions( temp_min, temp_max );
			CChar temp_name[MAX_NAME_SIZE];
			sprintf( temp_name, "%s%i", "octree_eTOP_LEFT_BACK_level_", m_pSubNode[i]->m_level );
			m_pSubNode[i]->SetName( temp_name );
		}
		else if( i == eBOTTOM_RIGHT_BACK )
		{
			CVec3f temp_min( m_center.x, m_minAABB.y, m_minAABB.z );
			CVec3f temp_max( m_maxAABB.x, m_center.y, m_center.z );
			m_pSubNode[i]->SetDimentions( temp_min, temp_max );	
			CChar temp_name[MAX_NAME_SIZE];
			sprintf( temp_name, "%s%i", "octree_eBOTTOM_RIGHT_BACK_level_", m_pSubNode[i]->m_level );
			m_pSubNode[i]->SetName( temp_name );
		}
		else if( i == eTOP_RIGHT_BACK )
		{
			CVec3f temp_min( m_center.x, m_minAABB.y, m_center.z );
			CVec3f temp_max( m_maxAABB.x, m_center.y, m_maxAABB.z );
			m_pSubNode[i]->SetDimentions( temp_min, temp_max );	
			CChar temp_name[MAX_NAME_SIZE];
			sprintf( temp_name, "%s%i", "octree_eTOP_RIGHT_BACK_level_", m_pSubNode[i]->m_level );
			m_pSubNode[i]->SetName( temp_name );
		}
		else if( i == eBOTTOM_LEFT_FRONT )
		{
			CVec3f temp_min( m_minAABB.x, m_center.y, m_minAABB.z );
			CVec3f temp_max( m_center.x, m_maxAABB.y, m_center.z );
			m_pSubNode[i]->SetDimentions( temp_min, temp_max );	
			CChar temp_name[MAX_NAME_SIZE];
			sprintf( temp_name, "%s%i", "octree_eBOTTOM_LEFT_FRONT_level_", m_pSubNode[i]->m_level );
			m_pSubNode[i]->SetName( temp_name );
		}
		else if( i == eTOP_LEFT_FRONT )
		{
			CVec3f temp_min( m_minAABB.x, m_center.y, m_center.z );
			CVec3f temp_max( m_center.x, m_maxAABB.y, m_maxAABB.z );
			m_pSubNode[i]->SetDimentions( temp_min, temp_max );
			CChar temp_name[MAX_NAME_SIZE];
			sprintf( temp_name, "%s%i", "octree_eTOP_LEFT_FRONT_level_", m_pSubNode[i]->m_level );
			m_pSubNode[i]->SetName( temp_name );
		}
		m_pSubNode[i]->AttachGeometriesToNode();
	}
}

CBool COctree::AttachGeometriesToNode()
{
	for( CUInt i = 0 ; i < g_scene.size(); i++ )
	{
		g_render.SetScene( g_scene[i]);
		if( !g_render.GetScene()->m_isTrigger )
		{
			for( CUInt j = 0; j < g_scene[i]->m_instanceGeometries.size(); j++ )
			{
				if (!(g_scene[i]->m_instanceGeometries[j]->m_hasPhysX && g_scene[i]->m_instanceGeometries[j]->m_physXDensity > 0) && !g_scene[i]->m_instanceGeometries[j]->m_renderWithPhysX)
				{
					CGeometry* m_abstractGeometry = g_scene[i]->m_instanceGeometries[j]->m_abstractGeometry;
					if( !m_abstractGeometry->m_hasAnimation )
					{
						for( CUInt k = 0; k < /*8*/m_abstractGeometry->m_vertexcount; k++ )
						{
							CVec3f p ,pt;
							p = m_abstractGeometry->m_points[k];//g_scene[i]->m_instanceGeometries[j]->m_localToWorldVertex[k];
							CMatrixTransform( g_scene[i]->m_instanceGeometries[j]->m_localToWorldMatrix, p, pt );

							if( IsPointInBox( /*&p*/&pt ) )
							{
								g_scene[i]->m_instanceGeometries[j]->m_parentTree.push_back( this );
								m_geoCount++;
								break;
							}
						}
					}
				}
			}
		}
	}
	if( m_geoCount > g_sceneManagerObjectsPerSplit )
	{
		SplitNode8( this );
		m_leaf = CTrue;
	}

	return CTrue;
}

CVoid COctree::AttachLightsToGeometries()
{
	for (CUInt j = 0; j < g_engineLights.size(); j++)
	{
		CInstanceLight *instanceLight = g_engineLights[j];
		if (instanceLight)
		{
			for (CUInt k = 0; k < g_scene.size(); k++)
			{
				if (!g_scene[k]->m_isTrigger)
				{
					for (CUInt l = 0; l < g_scene[k]->m_instanceGeometries.size(); l++)
					{
						CGeometry* m_abstractGeometry = g_scene[k]->m_instanceGeometries[l]->m_abstractGeometry;
						if (!m_abstractGeometry->m_hasAnimation)
						{
							for (CUInt m = 0; m < m_abstractGeometry->m_vertexcount; m++)
							{
								CVec3f p, pt;
								p = m_abstractGeometry->m_points[m];
								CMatrixTransform(g_scene[k]->m_instanceGeometries[l]->m_localToWorldMatrix, p, pt);

								CBool foundTarget = CFalse;
								if (IsPointInLight(&pt, instanceLight))
								{
									g_scene[k]->m_instanceGeometries[l]->m_lights.push_back(instanceLight);
									foundTarget = CTrue;
									break;
								}
								if (foundTarget)
								{
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}

CBool COctree::IsPointInLight(CVec3f* p, CInstanceLight* light)
{
	CDouble lightRadius = light->GetRadius();
	if (lightRadius == 1000000.0f) //Directional light or point light without attenuation
		return CTrue;
	else
	{
		CVec3f  Position;
		if (light->m_parent)
		{
			float *matrix = (float *)light->m_parent->GetLocalToWorldMatrix();
			Position.x = matrix[12]; Position.y = matrix[13]; Position.z = matrix[14];
		}
		else
		{
			Position.x = light->m_abstractLight->GetPosition()[0];
			Position.y = light->m_abstractLight->GetPosition()[1];
			Position.z = light->m_abstractLight->GetPosition()[2];
		}
		CDouble distance = (CDouble)sqrt(pow(p->x - Position.x, 2.0f) + pow(p->y - Position.y, 2.0f) + pow(p->z - Position.z, 2.0f));
		if (distance <= lightRadius) //inside
			return CTrue;
	}

	return CFalse;
}

CBool COctree::IsPointInBox( CVec3f* p )
{
	if( ( m_minAABB.x <= p->x && p->x <= m_maxAABB.x ) &&
		( m_minAABB.y <= p->y && p->y <= m_maxAABB.y ) &&
		( m_minAABB.z <= p->z && p->z <= m_maxAABB.z ) )
		//triangle is inside the box
		return CTrue;

	return CFalse;
}

CVoid COctree::ResetState()
{
	for( CUInt i = 0 ; i < g_scene.size(); i++ )
	{
		for( CUInt j = 0; j < g_scene[i]->m_instanceGeometries.size(); j++ )
		{
			for( CUInt k = 0; k < g_scene[i]->m_instanceGeometries[j]->m_parentTree.size(); k++ )
			{
				g_scene[i]->m_instanceGeometries[j]->m_parentTree[k] = NULL;
			}
			if( g_scene[i]->m_instanceGeometries[j]->m_parentTree.size() > 0 )
				g_scene[i]->m_instanceGeometries[j]->m_parentTree.clear();
		}
	}

	//Detach lights
	for (CUInt i = 0; i < g_scene.size(); i++)
	{
		for (CUInt j = 0; j < g_scene[i]->m_instanceGeometries.size(); j++)
		{
			for (CUInt k = 0; k < g_scene[i]->m_instanceGeometries[j]->m_lights.size(); k++)
			{
				g_scene[i]->m_instanceGeometries[j]->m_lights[k] = NULL;
			}
			if (g_scene[i]->m_instanceGeometries[j]->m_lights.size() > 0)
				g_scene[i]->m_instanceGeometries[j]->m_lights.clear();
		}
	}
	/////////////

	for( CUInt i = 0; i < 8; i++ )
		CDelete( m_pSubNode[i] );
	g_updateOctree = CTrue;
	Init();
}

CVoid COctree::ResetOctreeGeoCount()
{
	for( CUInt k = 0 ; k < g_scene.size(); k++ )
	{
		g_render.SetScene( g_scene[k] );
		if( !g_render.GetScene()->m_isTrigger )
		{
			for( CUInt l = 0; l < g_scene[k]->m_instanceGeometries.size(); l++ )
			{
				g_scene[k]->m_instanceGeometries[l]->m_renderCount = 0;
			}
		}
	}
}