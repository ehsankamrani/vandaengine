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
#include "../common/utility.h"
class CAnimation; 

const CUInt MAX_TFORM_CHANNEL_IDS = 15;
const CUInt MAX_TFORM_ANIM_IDS = 15;
class CTransform
{
protected:
	CTFormType m_type; 
	CAnimation*	m_animation[MAX_TFORM_ANIM_IDS];
	CUInt m_numAnimations; 
	CUInt m_channelIds[MAX_TFORM_ANIM_IDS][MAX_TFORM_CHANNEL_IDS]; 
	CUInt m_numChannels[MAX_TFORM_ANIM_IDS]; 
	CVec3f m_lookAt[3]; // this will store lookAt, eyePoint and up 
	CVec4f m_matrix[4];  
	CChar m_sid[MAX_STRING_SIZE];
	CVec4f m_vector; // this will store axis rotation, translation or scale 

public:
	CTransform();
	~CTransform();
	CVoid SetTranslate( CVec4f ); 
	CVoid SetRotate( CVec4f );  
	CVoid SetScale( CVec4f );  
	CVoid SetLookAt( CVec3f v[] ); 
	CVoid SetMatrix( CVec4f m[] ); 
	CVoid SetMatrix( CMatrix m );
	CVoid AddMatrix( CVec4f m[], CFloat weight );
	CVoid SetVector( CVec4f vec ) { m_vector.x = vec.x; m_vector.y = vec.y; m_vector.z = vec.z; m_vector.w = vec.w; }
	CVoid SumVector( CVec4f vec ) { m_vector.x = m_vector.x + vec.x; m_vector.y = m_vector.y + vec.y; m_vector.z = m_vector.z + vec.z; m_vector.w = m_vector.w + vec.w; }
	inline CVoid SetAnimation( CAnimation * Anim )
	{
		if ( m_numAnimations < MAX_TFORM_CHANNEL_IDS ) 
			m_animation[m_numAnimations++] = Anim; 
	}	
	inline CVoid AddChannelId( CUInt id )
	{
		if ( m_numChannels[m_numAnimations-1] < MAX_TFORM_CHANNEL_IDS ) 
			m_channelIds[m_numAnimations-1][m_numChannels[m_numAnimations-1]++] = id; //I call SetAnimation first, So I use m_numAnimations-1
	}

	CVoid SetSid( CChar * Sid ); 
	inline CVoid SetType( CTFormType type ){ m_type = type; };
	static CTFormType GetType( CChar * nameType ); 

	inline CChar *GetSid(){ return m_sid; }
	inline CTFormType GetType(){ return m_type; }	
	inline CVec4f &GetVecTrans(){ return m_vector;} // this will be rot,trans or scale depending on type	
	inline CVec3f *GetLookAt(){ return m_lookAt;} 
	inline CAnimation *GetAnimation( CUInt id ){return m_animation[id]; }
	inline CUInt GetChannelId(CUInt animId, CUInt id){return m_channelIds[animId][id]; }
	inline CUInt GetNumChannels(CUInt animationId){return m_numChannels[animationId]; }
	inline CUInt GetNumAnimations(){return m_numAnimations; }
	inline CVec4f *GetMatrix(){return m_matrix; }
};

