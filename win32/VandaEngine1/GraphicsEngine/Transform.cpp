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
#include "transform.h"
#include "matrix.h"
CTransform::CTransform()
{
	m_type = eCTFormUnknown;
	for( CUInt i = 0; i < MAX_TFORM_ANIM_IDS; i++ )
	{
		m_animation[i] = NULL;
		m_numChannels[i] = 0;
	}
	m_numAnimations = 0;
	memset(m_channelIds, 0, sizeof( m_channelIds ));
	memset(m_sid, 0, sizeof( m_sid ));
}

CTransform::~CTransform()
{
}
	
CVoid CTransform::SetTranslate( CVec4f trans )
{
	m_vector = trans; 
}

CVoid CTransform::SetRotate( CVec4f rotate )
{
	m_vector = rotate; 
}

CVoid CTransform::SetScale( CVec4f scale )
{
	m_vector = scale; 
}

CVoid CTransform::SetLookAt( CVec3f lookAt[] )
{
	m_lookAt[eCLook] = lookAt[eCLook];
	m_lookAt[eCEye] = lookAt[eCEye];
	m_lookAt[eCUp] = lookAt[eCUp];
}

CVoid CTransform::SetMatrix( CVec4f m[] )
{
	for ( CInt i = 0; i < 4; i ++ )
		m_matrix[i] = m[i]; 
}

CVoid CTransform::SetMatrix( CMatrix m )
{
	m_matrix[0].x = m[0]; m_matrix[0].y = m[1]; m_matrix[0].z = m[2]; m_matrix[0].w = m[3]; 
	m_matrix[1].x = m[4]; m_matrix[1].y = m[5]; m_matrix[1].z = m[6]; m_matrix[1].w = m[7]; 
	m_matrix[2].x = m[8]; m_matrix[2].y = m[9]; m_matrix[2].z = m[10]; m_matrix[2].w = m[11]; 
	m_matrix[3].x = m[12]; m_matrix[3].y = m[13]; m_matrix[3].z = m[14]; m_matrix[3].w = m[15]; 
}

CVoid CTransform::AddMatrix( CVec4f m[], CFloat weight )
{
	CMatrix Mr;
	Mr[0] = m_matrix[0].x;  Mr[1] = m_matrix[0].y; Mr[2] = m_matrix[0].z; Mr[3] = m_matrix[0].w; 
	Mr[4] = m_matrix[1].x; Mr[5] = m_matrix[1].y; Mr[6] = m_matrix[1].z; Mr[7] = m_matrix[1].w; 
	Mr[8] = m_matrix[2].x; Mr[9] = m_matrix[2].y; Mr[10] = m_matrix[2].z; Mr[11] = m_matrix[2].w; 
	Mr[12] = m_matrix[3].x; Mr[13] = m_matrix[3].y; Mr[14] = m_matrix[3].z; Mr[15] = m_matrix[3].w; 

	CMatrix Ml;
	Ml[0] = m[0].x * weight;  Ml[1] = m[0].y * weight; Ml[2] = m[0].z * weight; Ml[3] = m[0].w * weight; 
	Ml[4] = m[1].x * weight; Ml[5] = m[1].y * weight; Ml[6] = m[1].z * weight; Ml[7] = m[1].w * weight; 
	Ml[8] = m[2].x * weight; Ml[9] = m[2].y * weight; Ml[10] = m[2].z * weight; Ml[11] = m[2].w * weight; 
	Ml[12] = m[3].x * weight; Ml[13] = m[3].y * weight; Ml[14] = m[3].z * weight; Ml[15] = m[3].w * weight; 

	for( CUInt i = 0; i < 16; i++ )
		Mr[i] += Ml[i];

	m_matrix[0].x = Mr[0]; m_matrix[0].y = Mr[1]; m_matrix[0].z = Mr[2]; m_matrix[0].w = Mr[3]; 
	m_matrix[1].x = Mr[4]; m_matrix[1].y = Mr[5]; m_matrix[1].z = Mr[6]; m_matrix[1].w = Mr[7]; 
	m_matrix[2].x = Mr[8]; m_matrix[2].y = Mr[9]; m_matrix[2].z = Mr[10]; m_matrix[2].w = Mr[11]; 
	m_matrix[3].x = Mr[12]; m_matrix[3].y = Mr[13]; m_matrix[3].z = Mr[14]; m_matrix[3].w = Mr[15]; 
}

CVoid CTransform::SetSid( CChar * sid )
{
	Cpy( m_sid, sid ); 
}

CTFormType CTransform::GetType( CChar * nameType )
{
	// Return a C enum for the type of transform, things that are not transforms like <instance_
	// are returned as eCTFormUnknown and will be handled by other code.
	if( ICmp( nameType, "rotate" ) || ICmp( nameType, "rotation" ))
		return (eCRotate); 
	else if (ICmp(nameType, "translate") || ICmp(nameType, "translation") || ICmp(nameType, "location"))
		return (eCTranslate); 
	else if (ICmp(nameType, "matrix") || ICmp(nameType, "transform"))
		return (eCMatrix); 
	else if ( ICmp( nameType, "scale" ) ) 
		return (eCScale); 
	else if ( ICmp( nameType, "lookat" ) ) 
		return (eCLookAt); 
	else if ( ICmp( nameType, "skew" ) ) 
		return (eCSkew); 
	else 
		return (eCTFormUnknown); 
}
