//Original Work: Copyright 2006 Sony Computer Entertainment Inc.
//Modified Work: Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "../common/utility.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp> 
#include <boost/serialization/string.hpp>

#include <iostream>
#include <sstream>
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
	std::string m_sid;
	CVec4f m_vector; // this will store axis rotation, translation or scale 

private:
	friend class boost::serialization::access;

	template <typename Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & m_type;
		ar & m_animation;
		ar & m_numAnimations;
		ar & m_channelIds;
		ar & m_numChannels;
		ar & m_lookAt; // this will store lookAt, eyePoint and up 
		ar & m_matrix;
		ar & m_sid;
		ar & m_vector; // this will store axis rotation, translation or scale
	}

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

	inline CChar *GetSid(){ return const_cast<CChar*>(m_sid.c_str()); }
	inline CTFormType GetType(){ return m_type; }	
	inline CVec4f &GetVecTrans(){ return m_vector;} // this will be rot,trans or scale depending on type	
	inline CVec3f *GetLookAt(){ return m_lookAt;} 
	inline CAnimation *GetAnimation( CUInt id ){return m_animation[id]; }
	inline CUInt GetChannelId(CUInt animId, CUInt id){return m_channelIds[animId][id]; }
	inline CUInt GetNumChannels(CUInt animationId){return m_numChannels[animationId]; }
	inline CUInt GetNumAnimations(){return m_numAnimations; }
	inline CVec4f *GetMatrix(){return m_matrix; }
};

