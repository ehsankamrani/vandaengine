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
#include "scene.h"
#include "base.h"
#include "orient.h"
#include <string>
#include <map>
#include <vector>
class CAnimSrc; //forward 

class CAnimSampler: public CBase
{
public:
	CAnimSampler() {};
	~CAnimSampler()
	{
		//we delete the CAnimSrc object inside CAnimation  
		m_inputs.clear();
	}
	CChar m_id[MAX_NAME_SIZE];
	std::map< std::string, CAnimSrc* > m_inputs;
};

class CAnimSrc: public CBase
{
protected:
	CChar m_id[MAX_NAME_SIZE];
	CFloat*	m_array;
	CUInt m_count; 

public:
	friend class CScene; 
	friend class CAnimation; 

CAnimSrc()
{
	m_id[0] = 0;
	m_array = NULL; 
	m_count = 0; 
}

~CAnimSrc()
{
	CDeleteData( m_array ); 
}
	
CBool Parse( const CChar * data );
inline CVoid SetCount( CInt c ){ m_count = c; };
};

struct CKeySet;  //forward 

class CAnimChannel: public CBase 
{
protected:
	CAnimSampler*  m_sampler;
	
	CChar m_targetNameStr[MAX_NAME_SIZE];
	CChar m_targetElementStr[MAX_NAME_SIZE];	
	CChar m_targetElementTransformStr[MAX_NAME_SIZE];	

	CAnimTarget	m_target;
	CAnimTarget	m_targetElement;
	
	CAnimSrc* m_inputSrcPtr; 
	CAnimSrc* m_outputSrcPtr; 

	CKeySet* m_keys[MAX_KEY_SETS]; 
	CUInt m_numElementTargets; 

public:
	friend class CScene; 
	friend class CAnimation; 

	CAnimChannel()
	{
		m_inputSrcPtr = 0;
		m_outputSrcPtr = 0; 	

		m_sampler = NULL; 
		m_targetNameStr[0] = 0; 
		m_targetElementStr[0] = 0; 
		m_numElementTargets = 0; 

		m_target = eTargetUnknown;

		for ( CUInt i = 0; i < MAX_KEY_SETS; i++)
			m_keys[i] = NULL; 
	}

	~CAnimChannel()
	{
	}

	inline CVoid SetTarget( const CChar * target ) { Cpy( m_targetNameStr, target); }
	inline CVoid SetTargetElement( const CChar*target ) { Cpy( m_targetElementStr, target); }
	inline CVoid SetSampler( CAnimSampler * sampler ) { m_sampler = sampler; }
	inline CVoid SetInputSrc( CAnimSrc * inputPtr )	{ m_inputSrcPtr = inputPtr; }
	inline CVoid SetOutputSrc( CAnimSrc * outputPtr ) { m_outputSrcPtr = outputPtr; }
	inline CVoid SetTargetElementTransform( const CChar*target ) { Cpy( m_targetElementTransformStr, target); }
	
	inline CVoid SetKeySet( CKeySet * set, CUInt i ) 
	{ 
		if ( i < MAX_KEY_SETS)
			m_keys[i] = set; 	
	}

	inline CAnimSampler* GetSampler(){ return m_sampler; }
	inline CAnimTarget GetTargetElement(){ return m_target; }
	inline CAnimTarget GetTargetElement2(){ return m_targetElement; }
	inline CChar* GetTargetElementString() { return m_targetElementStr; }
	inline CChar*GetTargetElementTranform(){ return m_targetElementTransformStr; }
	inline CUInt GetNumElementTargets(){ return m_numElementTargets; }
	inline CChar* GetTarget() { return m_targetNameStr;}

	CBool AddSrc( CAnimSrc * channel );
	CFloat interpolate( CFloat time ); 
	CVoid ParseElement( CChar * elementStr ); 
	CVoid ParseElementTarget( CChar * elementTargetString );
};

struct CAnimKey
{
	COrient	m_orient;
	CFloat m_time; 
	CBool m_hasRot; 
	CBool m_hasTrans; 

	CAnimKey()
	{
		m_orient = COrient(); 
		m_time = 0; 
		m_hasRot = CFalse;  
		m_hasTrans = CFalse;  
	}
};

struct CKeySet
{
	CInt m_numKeys; 
	CFloat*	m_keys; 
	CFloat*	m_time; 	

	CKeySet()
	{
		m_numKeys = 0; 
		m_keys = NULL;
		m_time = NULL; 
	}

	CBool AllocateKeys( CInt nKeys )
	{
		m_keys = CNewData( CFloat, nKeys ); 	
		m_time = CNewData( CFloat, nKeys ); 
		m_numKeys = nKeys; 

		for( CInt i = 0; i < nKeys; i++)
		{
			m_keys[i] = 0;
		}
		return CTrue; 
	}
	CVoid DeAllocateKeys()
	{
		CDeleteData( m_keys ); 	
		CDeleteData( m_time ); 
	}
};

class CAnimationClip: public CBase
{
public:
	CAnimationClip() { m_index = -1; m_currentTime = 0.0; m_currentDelayInTime = 0.0f; m_currentDelayOutTime = 0.0f; m_currentWeight = 0.0f; m_targetDelayIn  = 0.0f; m_targetDelayOut = 0.0; m_startWeight = 0.0f; m_targetWeight = 0.0f; m_animationStatus = eANIM_NONE; m_lock = CFalse; m_reverse = CFalse;}
	~CAnimationClip() {	m_animations.clear(); }

	std::vector< CAnimation* > m_animations;

	//set methods
	CVoid SetStart ( CDouble start ) { m_start = start; }
	CVoid SetEnd( CDouble end ) { m_end = end; }
	CVoid SetIndex( CInt index ) { m_index = index; }
	CVoid SetTargetDelayIn( CFloat delayIn ) { m_targetDelayIn = delayIn; }
	CVoid SetTargetDelayOut( CFloat delayOut ) { m_targetDelayOut = delayOut; }
	CVoid SetCurrentDelayInTime( CFloat delayIn ) { m_currentDelayInTime = delayIn; }
	CVoid SetCurrentDelayInTime2( CFloat elapsedDelayIn ) { m_currentDelayInTime += elapsedDelayIn; }
	CVoid SetCurrentDelayOutTime( CFloat delayOut ) { m_currentDelayOutTime = delayOut; }
	CVoid SetCurrentDelayOutTime2( CFloat elapsedDelayOut ) {m_currentDelayOutTime += elapsedDelayOut; }
	CVoid SetCurrentTime(CFloat time) { m_currentTime = time; }
	CVoid SetCurrentTime2(CFloat elapsedTime) {m_currentTime += elapsedTime; }
	CVoid SetCurrentWeight( CFloat weight ) {m_currentWeight = weight; }
	CVoid SetTargetWeight( CFloat weight ) {m_targetWeight = weight; }
	CVoid SetStartWeight( CFloat weight ) { m_startWeight = weight; }
	CVoid SetAnimationStatus( CAnimationStatus status ) { m_animationStatus = status; }
	CVoid SetLock( CBool lock ) { m_lock = lock; }
	CVoid SetReverse(CBool reverse) { m_reverse = reverse; }

	//get methods
	CInt GetIndex( CVoid ) { return m_index; }
	CDouble GetStart() { return m_start; }
	CDouble GetEnd() { return m_end; }
	CAnimationStatus GetAnimationStatus() {return m_animationStatus; }
	CFloat GetCurrentTime() { return m_currentTime; }
	CFloat GetCurrentDelayInTime() { return m_currentDelayInTime; }
	CFloat GetCurrentDelayOutTime() { return m_currentDelayOutTime; }
	CFloat GetCurrentWeight() { return m_currentWeight; }
	CFloat GetDuration() {return m_end - m_start; }
	CFloat GetStartWeight() { return m_startWeight; }
	CFloat GetTargetWeight() {return m_targetWeight; }
	CFloat GetTargetDelayIn() {return m_targetDelayIn;}
	CFloat GetTargetDelayOut() {return m_targetDelayOut;}
	CBool GetLock() { return m_lock; }
	CBool GetReverse() { return m_reverse; }

private:
	CDouble m_start,m_end;
	CInt m_index;

	//new way. 
	CFloat m_currentTime;
	CFloat m_currentDelayInTime;
	CFloat m_currentDelayOutTime;
	CFloat m_currentWeight;
	CFloat m_targetDelayIn;
	CFloat m_targetDelayOut;
	CFloat m_targetWeight;
	CFloat m_startWeight;
	CAnimationStatus m_animationStatus;
	CBool m_lock;
	CBool m_reverse;

};

class CAnimation: public CBase 
{
	CUInt m_numAnimChannels; // multipule elements can be targeted by one channel. 
	std::vector< CAnimChannel* > m_channels;
			
	CKeySet* m_animKeySets; 

	CKeySet m_rotXKeys; 
	CKeySet	m_rotYKeys; 
	CKeySet	m_rotZKeys; 

	CKeySet m_transXKeys; 
	CKeySet	m_transYKeys;
	CKeySet	m_transZKeys; 

	CKeySet	m_scaleXKeys; 
	CKeySet	m_scaleYKeys;
	CKeySet	m_scaleZKeys; 

	CFloat m_endTime; 

	CFloat m_sampleRate; 
	
	std::map< std::string, CAnimSampler* > m_samplers; 
	std::map< std::string, CAnimSrc* > m_sources; 

	CChar m_target[MAX_NAME_SIZE]; 
	CChar m_targetTransform[MAX_NAME_SIZE];
	CChar m_targetTransformElement[MAX_NAME_SIZE]; 

	//export data 
	CAnimKey *m_keys; 
	CInt m_numKeys; 

	CBool m_hasRotation;
	CBool m_hasTranslation; 
	CBool m_hasScale;
	CBool m_foundTarget; 
	CAnimationClip* m_clipTarget;

public:
	CAnimation()
	{	
		m_animKeySets = NULL; 
		m_numAnimChannels=0; 
		m_sampleRate = 30; // fps; 
		m_target[0]	= 0; 

		m_keys = NULL;
		m_numKeys = 0; 

		m_hasRotation = CFalse;
		m_hasTranslation = CFalse; 
		m_hasScale = CFalse; 

		m_endTime = 0; 

		m_foundTarget = CFalse; 	
	}
	
	~CAnimation()
	{
		//first deallocate all the keys used in animation
		CUInt animSet = 0;
		for ( CUInt i = 0; i < m_channels.size(); i++ )
		{
			CAnimChannel* chan = m_channels[i];
			CUInt NumKeys = chan->m_inputSrcPtr->m_count;
			// new way //
			for ( CUInt t = 0; t < chan->GetNumElementTargets(); t++)
			{
				m_animKeySets[animSet+t].DeAllocateKeys(); 
			}
			animSet += chan->GetNumElementTargets(); 
		}
		CDeleteData( m_animKeySets );
		
		//delete all CAnimSampler objects here
		for(std::map<std::string, CAnimSampler*>::iterator it = m_samplers.begin(); it != m_samplers.end(); it++ )
		{
			CAnimSampler* value = (*it).second;
			CDelete( value );
		}
		m_samplers.clear();

		//delete all CAnimSrc objects here
		for(std::map<std::string, CAnimSrc*>::iterator it = m_sources.begin(); it != m_sources.end(); it++ )
		{
			CAnimSrc* value = (*it).second;
			CDelete( value );
		}
		m_sources.clear();

		//delete all CAnimChannel objects here
		for(std::vector<CAnimChannel*>::iterator it = m_channels.begin(); it != m_channels.end(); it++ )
		{
			CDelete( *it );
		}
		m_channels.clear();

	}

protected:
	friend class CScene; 
	friend class CNode; 

	CVoid	ResolveChannel( CAnimSampler * sampler, const char * target ); 
	
	inline  CVoid SetTarget( const CChar * t ){ Cpy( m_target, t ); }
	inline CVoid SetClipTarget( CAnimationClip* clip ) { m_clipTarget = clip; }
	inline	CChar* GetTarget(){	return m_target; }
	inline CAnimationClip* GetClipTarget() { return m_clipTarget; }
	inline	CChar* GetTransformTarget() { return m_targetTransform; }
	inline	CChar* GetTransformTargetElement(){	return m_targetTransformElement; }

	CVoid	GenerateKeys();

	CVoid 	AnimateRotateChannel( CVec4f & vec, CAnimTarget e, CFloat time ); 
	CVoid 	AnimateTranslateChannel( CVec3f & vec, CAnimTarget e, CFloat time ); 
	CVoid 	AnimateScaleChannel( CVec3f & vec, CAnimTarget e, CFloat time ); 
	CVoid 	AnimateChannel( CVec4f & vec, CVec4f* matrix, CAnimTarget target, CUInt c, CFloat time );

    CVoid interp( CFloat & val, CKeySet * keySet, CFloat time );

	CVoid SetFoundTarget() { m_foundTarget = CTrue; };
	CBool HasFoundTarget() { return m_foundTarget; }

public:
	//---------------------- External interfaces ---------------------------------//	
	inline CBool HasAxisRots(){ return m_hasRotation; } 
	inline CBool HasTrans(){ return m_hasTranslation; }
	inline CBool HasScales(){ return m_hasScale; }
	
	inline CBool GetRotKeyAtTime( CFloat time, CVec4f & AxisRotX, CVec4f & AxisRotY, CVec4f & AxisRotZ)
	{ 
		if ( !m_hasRotation )
			return CFalse; 
		else
		{
			// Get the interpolated x, y and z axis rotations at the current time 
			// passed in 
			AnimateRotateChannel( AxisRotX, eRotXAxis, time ); 
			AnimateRotateChannel( AxisRotY, eRotYAxis, time ); 
			AnimateRotateChannel( AxisRotZ, eRotZAxis, time ); 
			return CTrue;
		}
	}
		
	inline CBool GetTransKeyAtTime( CFloat time, CVec3f & Trans)
	{ 
		if ( !m_hasTranslation )
			return CFalse; 
		else
		{
			// Get the interpolated x, y and z translation at the current time 
			// passed in 
			AnimateTranslateChannel( Trans, eTransXAxis, time ); 
			AnimateTranslateChannel( Trans, eTransYAxis, time ); 
			AnimateTranslateChannel( Trans, eTransZAxis, time ); 

			return CTrue;
		}
	} 	

	inline CBool GetScaleKeyAtTime( CFloat time, CVec3f & Scale)
	{ 
		if ( !m_hasScale )
			return CFalse; 
		else
		{
			// Get the interpolated x, y and z translation at the current time 
			// passed in 
			AnimateScaleChannel( Scale, eScaleXAxis, time ); 
			AnimateScaleChannel( Scale, eScaleYAxis, time ); 
			AnimateScaleChannel( Scale, eScaleZAxis, time ); 

			return CTrue;
		}
	} 	

	inline CFloat GetEndTime(){ return m_endTime; }; 

	//---------------------- End External interfaces ---------------------------------//
};

