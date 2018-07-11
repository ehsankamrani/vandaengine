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
#include "Animation.h"
CBool CAnimSrc::Parse( const CChar * data )
{
	// parse data 
	const CChar * d = data; 
			
	// allocate for the keys 
	m_array = CNewData( CFloat, m_count ); 

	// copy the data 
	for( CUInt i = 0; i < m_count; i++)
	{
		m_array[i] = GetFloatString( &d ); 
		//PrintInfo(" coping %d ",i);fflush(stdout);
	}

	return CTrue; 
}

CBool CAnimChannel::AddSrc( CAnimSrc * channel )
{
	(CVoid)channel;
	return CTrue; 
}

CFloat CAnimChannel::interpolate( CFloat time )
{
	(CVoid)time; 
	CFloat val = 0; 
	return val; 
}

CVoid CAnimChannel::ParseElementTarget( CChar* targetElementString )
{
	if ( ICmp( targetElementString, "AXIS" ) || ICmp( targetElementString, "ANGLE" ) )
	{
		m_targetElement = eAnimTargetAngle; 
		m_numElementTargets = 1; 
	}
	else
	if( ICmp( targetElementString, "X" )) 		 
	{
		m_targetElement = eAnimTargetX; 
		m_numElementTargets = 1; 
	}
	else 
	if( ICmp( targetElementString, "Y" ) )		 
	{
		m_targetElement = eAnimTargetY; 
		m_numElementTargets = 1; 
	}
	else
	if( ICmp( targetElementString, "Z" ) )		 
	{
		m_targetElement = eAnimTargetZ; 
		m_numElementTargets = 1; 
	}
	else
	if ( ICmp( targetElementString, "Rotate" ) || ICmp( targetElementString, "Rotation" ) ||
		ICmp(targetElementString, "Translate") || ICmp(targetElementString, "Translation") || ICmp(targetElementString, "location") ||
		ICmp( targetElementString, "Scale" ) )
	{
		m_targetElement = eAnimTargetXYZ;
		m_numElementTargets = 3; 
	}
	else if (ICmp(targetElementString, "Matrix") || ICmp(targetElementString, "transform"))
	{
		m_targetElement = eMatrix;
		m_numElementTargets = 16; 
	}
	else
	{
		//PrintInfo( "Unsupported Animation Element Target: ' ", COLOR_RED );
		//PrintInfo( targetElementString, COLOR_RED_BLUE ); 
		//PrintInfo( " '\n", COLOR_RED );
	}	
}

CVoid CAnimChannel::ParseElement( CChar* elementString )
{
	if(  ICmp(elementString, "RotX.AXIS" ) ||
		 ICmp(elementString, "RotX.ANGLE") || 
		 ICmp(elementString, "rotate2.ANGLE" ) ||
		 ICmp(elementString, "rotateX.ANGLE")) 
			m_target = eRotXAxis;
	else
	if(  ICmp(elementString, "RotY.AXIS" ) ||
		 ICmp(elementString, "RotY.ANGLE") ||
		 ICmp(elementString, "rotate1.ANGLE" )||
		 ICmp(elementString, "rotateY.ANGLE") )
			m_target = eRotYAxis;
	else
	if(  ICmp(elementString, "RotZ.AXIS" ) ||
		 ICmp(elementString, "RotZ.ANGLE" )||
		 ICmp(elementString, "rotate0.ANGLE" )||
		 ICmp(elementString, "rotateZ.ANGLE"))
			m_target = eRotZAxis;
	else
	if( ICmp(elementString, "Trans.X" ) ||
		ICmp(elementString, "translate0.X" )||
		ICmp(elementString, "translate.X" ) ||
		ICmp(elementString, "location.X"))
			m_target = eTransXAxis;
	else
	if( ICmp(elementString, "Trans.Y" ) ||
		ICmp(elementString, "translate0.Y" ) ||
		ICmp(elementString, "translate.Y" ) ||
		ICmp(elementString, "location.Y"))
			m_target = eTransYAxis;  
	else
	if( ICmp(elementString, "Trans.Z" ) ||
		ICmp(elementString, "translate0.Z" )||
		ICmp(elementString, "translate.Z" ) ||
		ICmp(elementString, "location.Z"))
			m_target = eTransZAxis;
	else
	if( ICmp(elementString, "Scale.X" ) ||
		ICmp(elementString, "scale0.X" )||
		ICmp(elementString, "scale.X" )) 
			m_target = eScaleXAxis;
	else
	if( ICmp(elementString, "Scale.Y" ) ||
		ICmp(elementString, "scale0.Y" ) ||
		ICmp(elementString, "scale.Y" )) 
			m_target = eScaleYAxis;
	else
	if( ICmp(elementString, "Scale.Z" ) ||
		ICmp(elementString, "scale0.Z" )||
		ICmp(elementString, "scale.Z" )) 
			m_target = eScaleZAxis;
	else
	if (ICmp(elementString, "location") )
		m_target = eTranslate; // XYZ not just one of them 
	else
	if( ICmp(elementString, "Translate" ) || ICmp(elementString, "Translation" ))
		m_target = eTranslate; // XYZ not just one of them 
	else
	if( ICmp(elementString, "Rotate" ) || ICmp(elementString, "Rotation" ))
		m_target = eRotate; // XYZ not just one of them 
	else
	if( ICmp(elementString, "Scale" ) )
		m_target = eScale; // XYZ not just one of them 
	else
		if (ICmp(elementString, "Matrix") || ICmp(elementString, "transform"))
		m_target = 	eMatrix;
	else
	if( CmpIn(elementString, "scale" ) ||
		CmpIn(elementString, "Scale" ) )
	{
		//PrintInfo( "Animation Scale target : ' ", COLOR_RED ); 
		//PrintInfo( elementString, COLOR_RED );
		//PrintInfo( " Unsupported \n", COLOR_RED );
	}
	else
	{
		//PrintInfo( "Animation target : ' ", COLOR_RED ); 
		//PrintInfo( elementString, COLOR_RED );
		//PrintInfo( " ' Unknown \n", COLOR_RED );
		m_target = eTargetUnknown; 
	}
}

CVoid CAnimation::ResolveChannel(CAnimSampler * sampler, const char * target )
{
	CAnimChannel * channel = m_channels[0];

	// need to first separate the target from the element target 
	CChar tempTarget[200]; 	

	Cpy( tempTarget, target, '/' ); 
	
	// get a pointer to the target element 
	CChar * element = FindStr( target, "/") + 1; // to skip the '/' 

	// get a pointer to the final element 
	CChar * targetElement = FindStr( target, "." );

	CUInt c = 0;

	// we will need this later 
    Cpy( m_targetTransform, element ); 

	// if we have a valid target element 
	if ( targetElement )
	{
		// to skip the '.'
		targetElement ++;

		Cpy( m_targetTransformElement, targetElement ); 
	
		// remove the target element from the Target transform 
		targetElement = FindStr( m_targetTransform, ( targetElement - 1 ) );// -1 to get back before the .  
		// terminate the target element leaving only the transform sid 
		targetElement[0] = 0; 
	}
	else
	{
		// in this case the target isn't just one animation element 
		// it is the entire element group like rotateXYZ or TranslateXYZ.
		Cpy( m_targetTransformElement, element ); 
	}
    
	// find the channel with this sampler and set the channel 
	for ( c = 0; c < m_channels.size(); c++)
	{
		channel = m_channels[c]; 

		if (channel->GetSampler() == sampler)
		{
			channel->SetTarget( tempTarget ); 
			channel->ParseElement( element ); 
			channel->ParseElementTarget( m_targetTransformElement ); 
			m_numAnimChannels += channel->GetNumElementTargets(); 

			channel->SetTargetElementTransform( m_targetTransformElement ); 
			channel->SetTargetElement( m_targetTransform ); 
	
			switch( channel->GetTargetElement() )
			{
				case eRotXAxis:
				case eRotYAxis:
				case eRotZAxis:
				case eRotate: 
					
					m_hasRotation = CTrue; 
					break;
				case eTransXAxis:
				case eTransYAxis:
				case eTransZAxis:
				case eTranslate:

					m_hasTranslation = CTrue; 
					break;
				case eScaleXAxis:
				case eScaleYAxis:
				case eScaleZAxis:
				case eScale:

					m_hasScale = CTrue; 
					break;
				default:
					break; 
			};

			break; 
		} 
	}

	//SetTarget( tempTarget ); 
	
}; 

CVoid CAnimation::GenerateKeys()
{

	// generate key frames for the channels in this animation 	
	CAnimChannel* chan = m_channels[0]; 
	
	// allocating for generic key channels New way 
	m_animKeySets = CNewData( CKeySet, m_numAnimChannels ); 

	CUInt animSet = 0;
	for ( CUInt i = 0; i < m_channels.size(); i++ )
	{
		chan = m_channels[i];
		CUInt NumKeys = chan->m_inputSrcPtr->m_count;
		
		// new way //
		for ( CUInt t = 0; t < chan->GetNumElementTargets(); t++)
		{
			//PrintInfo("Generating Keys for Animation Channel: ' " ); 
			//PrintInfo( chan->GetTarget(), COLOR_RED_BLUE ); 
			//PrintInfo(" ' \n" ); 
			m_animKeySets[animSet+t].AllocateKeys( NumKeys ); 
		}
		
		// set the actual key info //
		for ( CUInt i = 0 ; i < NumKeys; i++ )
		{
			// fill in all the keys for each anim key set 
			CUInt numCh = chan->GetNumElementTargets();

			for ( CUInt ch = 0; ch < chan->GetNumElementTargets(); ch++ )
			{
				m_animKeySets[animSet+ch].m_time[i] = chan->m_inputSrcPtr->m_array[i];
				m_animKeySets[animSet+ch].m_keys[i] = chan->m_outputSrcPtr->m_array[i*numCh+ch];
				
				if ( m_animKeySets[animSet+ch].m_time[i] > m_endTime )
					m_endTime = m_animKeySets[animSet+ch].m_time[i]; 

				// set the animKey in the channel for later interpolation 
				chan->SetKeySet( &m_animKeySets[animSet+ch], ch );  
			}			
		}

		// update the current animSet 
		animSet += chan->GetNumElementTargets(); 

		// Old way //
	
		//// allocate for each key set 
		//switch( chan->GetTargetElement() )
		//{
		//case eRotXAxis:
		//	m_rotXKeys.AllocateKeys( NumKeys ); 
		//	break; 
		//case eRotYAxis:
		//	m_rotYKeys.AllocateKeys( NumKeys ); 
		//	break; 
		//case eRotZAxis:
		//	m_rotZKeys.AllocateKeys( NumKeys ); 
		//	break;	
		//case eTransXAxis:
		//	m_transXKeys.AllocateKeys( NumKeys ); 
		//	break;
		//case eTransYAxis:
		//	m_transYKeys.AllocateKeys( NumKeys ); 
		//	break;	
		//case eTransZAxis:
		//	m_transZKeys.AllocateKeys( NumKeys ); 
		//	break;
		//case eScaleXAxis:
		//	m_scaleXKeys.AllocateKeys( NumKeys ); 
		//	break;
		//case eScaleYAxis:
		//	m_scaleYKeys.AllocateKeys( NumKeys ); 
		//	break;	
		//case eScaleZAxis:
		//	m_scaleZKeys.AllocateKeys( NumKeys ); 
		//	break;
		//case eTranslate: // X, Y, and Z 
		//	// allocate for xy and z 
		//	m_transXKeys.AllocateKeys( NumKeys ); 
		//	m_transYKeys.AllocateKeys( NumKeys ); 
		//	m_transZKeys.AllocateKeys( NumKeys ); 
		//	break;
		//case eRotate: // X, Y, and Z 
		//	// allocate for xy and z 
		//	m_rotXKeys.AllocateKeys( NumKeys ); 
		//	m_rotYKeys.AllocateKeys( NumKeys ); 
		//	m_rotZKeys.AllocateKeys( NumKeys ); 
		//	break;
		//case eScale: // X, Y, and Z 
		//	// allocate for xy and z 
		//	m_scaleXKeys.AllocateKeys( NumKeys ); 
		//	m_scaleYKeys.AllocateKeys( NumKeys ); 
		//	m_scaleZKeys.AllocateKeys( NumKeys ); 
		//	break;
		//default:
		//	break; 
		//}

		//// set the rotation data if there is any 
		//for ( CUInt i = 0 ; i < NumKeys; i ++)
		//{
		//	// set the key data based on the channel elements 
		//	if ( m_hasRotation )
		//	{
		//		switch( chan->GetTargetElement() )
		//		{
		//		case eRotXAxis:
		//			m_rotXKeys.m_time[i] = chan->m_inputSrcPtr->m_array[i];
		//			m_rotXKeys.m_keys[i] = chan->m_outputSrcPtr->m_array[i];
		//		
		//			if ( m_rotXKeys.m_time[i] > m_endTime )
		//				m_endTime = m_rotXKeys.m_time[i]; 
		//			break; 
		//		case eRotYAxis:
		//			m_rotYKeys.m_time[i] = chan->m_inputSrcPtr->m_array[i];
		//			m_rotYKeys.m_keys[i] = chan->m_outputSrcPtr->m_array[i];

		//			if ( m_rotYKeys.m_time[i] > m_endTime )
		//				m_endTime = m_rotYKeys.m_time[i]; 
		//			break;
		//		case eRotZAxis:
		//			m_rotZKeys.m_time[i] = chan->m_inputSrcPtr->m_array[i];
		//			m_rotZKeys.m_keys[i] = chan->m_outputSrcPtr->m_array[i];

		//			if ( m_rotZKeys.m_time[i] > m_endTime )
		//				m_endTime = m_rotZKeys.m_time[i]; 
		//			break; 
		//		case eRotate:
		//			// creating 3 key streams, one for each x y and z 
		//			// set X 
		//			m_rotXKeys.m_time[i] = chan->m_inputSrcPtr->m_array[i];
		//			m_rotXKeys.m_keys[i] = chan->m_outputSrcPtr->m_array[i*3];
		//			// set Y 
		//			m_rotYKeys.m_time[i] = chan->m_inputSrcPtr->m_array[i];
		//			m_rotYKeys.m_keys[i] = chan->m_outputSrcPtr->m_array[i*3+1];
		//			// set Z 
		//			m_rotZKeys.m_time[i] = chan->m_inputSrcPtr->m_array[i];
		//			m_rotZKeys.m_keys[i] = chan->m_outputSrcPtr->m_array[i*3+2];
		//			
		//			if ( chan->m_inputSrcPtr->m_array[i] > m_endTime )
		//				m_endTime = chan->m_inputSrcPtr->m_array[i]; 
		//			break; 

		//		default:
		//			break; 
		//		}				
		//	}
		//
		//	if ( m_hasTranslation )
		//	{
		//		switch( chan->GetTargetElement() )
		//		{
		//		case eTransXAxis:
		//			m_transXKeys.m_time[i] = chan->m_inputSrcPtr->m_array[i];
		//			m_transXKeys.m_keys[i] = chan->m_outputSrcPtr->m_array[i];

		//			if ( m_transXKeys.m_time[i] > m_endTime )
		//				m_endTime = m_transXKeys.m_time[i]; 
		//			break; 
		//		case eTransYAxis:
		//			m_transYKeys.m_time[i] = chan->m_inputSrcPtr->m_array[i];
		//			m_transYKeys.m_keys[i] = chan->m_outputSrcPtr->m_array[i];

		//			if ( m_transYKeys.m_time[i] > m_endTime )
		//				m_endTime = m_transYKeys.m_time[i]; 
		//			break;
		//		case eTransZAxis:
		//			m_transZKeys.m_time[i] = chan->m_inputSrcPtr->m_array[i];
		//			m_transZKeys.m_keys[i] = chan->m_outputSrcPtr->m_array[i];

		//			if ( m_transZKeys.m_time[i] > m_endTime )
		//				m_endTime = m_transZKeys.m_time[i]; 
		//			break; 
		//		case eTranslate:
		//			// creating 3 key streams, one for each x y and z 
		//			// set X 
		//			m_transXKeys.m_time[i] = chan->m_inputSrcPtr->m_array[i];
		//			m_transXKeys.m_keys[i] = chan->m_outputSrcPtr->m_array[i*3];
		//			// set Y 
		//			m_transYKeys.m_time[i] = chan->m_inputSrcPtr->m_array[i];
		//			m_transYKeys.m_keys[i] = chan->m_outputSrcPtr->m_array[i*3+1];
		//			// set Z 
		//			m_transZKeys.m_time[i] = chan->m_inputSrcPtr->m_array[i];
		//			m_transZKeys.m_keys[i] = chan->m_outputSrcPtr->m_array[i*3+2];
		//			
		//			if ( chan->m_inputSrcPtr->m_array[i] > m_endTime )
		//				m_endTime = chan->m_inputSrcPtr->m_array[i]; 
		//			break; 
		//		default:
		//			break; 
		//		}						
		//	}		

		//	if ( m_hasScale )
		//	{
		//		switch( chan->GetTargetElement() )
		//		{
		//		case eScaleXAxis:
		//			m_scaleXKeys.m_time[i] = chan->m_inputSrcPtr->m_array[i];
		//			m_scaleXKeys.m_keys[i] = chan->m_outputSrcPtr->m_array[i];
		//		
		//			if ( m_scaleXKeys.m_time[i] > m_endTime )
		//				m_endTime = m_scaleXKeys.m_time[i]; 
		//			break; 
		//		case eScaleYAxis:
		//			m_scaleYKeys.m_time[i] = chan->m_inputSrcPtr->m_array[i];
		//			m_scaleYKeys.m_keys[i] = chan->m_outputSrcPtr->m_array[i];

		//			if ( m_scaleYKeys.m_time[i] > m_endTime )
		//				m_endTime = m_scaleYKeys.m_time[i]; 
		//			break;
		//		case eScaleZAxis:
		//			m_scaleZKeys.m_time[i] = chan->m_inputSrcPtr->m_array[i];
		//			m_scaleZKeys.m_keys[i] = chan->m_outputSrcPtr->m_array[i];

		//			if ( m_scaleZKeys.m_time[i] > m_endTime )
		//				m_endTime = m_scaleZKeys.m_time[i]; 
		//			break; 
		//		case eScale:
		//			// creating 3 key streams, one for each x y and z 
		//			// set X 
		//			m_scaleXKeys.m_time[i] = chan->m_inputSrcPtr->m_array[i];
		//			m_scaleXKeys.m_keys[i] = chan->m_outputSrcPtr->m_array[i*3];
		//			// set Y 
		//			m_scaleYKeys.m_time[i] = chan->m_inputSrcPtr->m_array[i];
		//			m_scaleYKeys.m_keys[i] = chan->m_outputSrcPtr->m_array[i*3+1];
		//			// set Z 
		//			m_scaleZKeys.m_time[i] = chan->m_inputSrcPtr->m_array[i];
		//			m_scaleZKeys.m_keys[i] = chan->m_outputSrcPtr->m_array[i*3+2];
		//			
		//			if ( chan->m_inputSrcPtr->m_array[i] > m_endTime )
		//				m_endTime = chan->m_inputSrcPtr->m_array[i]; 
		//			break; 

		//		default:
		//			break; 
		//		}				
		//	}

		//}	
	}
};

CVoid CAnimation::interp( CFloat & val, CKeySet * keySet, CFloat time )
{
	if ( !keySet->m_keys )
		return; 

	// here need to get an actual interpolated value for this channel but for not just 
	// goint to return the first anim value 
	val = keySet->m_keys[0];

	// need to first find out where the time lies in the keys 
	CInt next = -1;  
	CInt prev = -1;  
	for( CInt i = 0; i < keySet->m_numKeys - 1; i ++)
	{
		if ( time >= keySet->m_time[i] && time < keySet->m_time[i+1] )
		{
			prev = i;
			next = i+1;
			break; 
		}
	}			

	if ( prev == -1 )
	{
		if ( time < keySet->m_time[0] )
			val = keySet->m_keys[0];
		else
			// if time is not in range just set to last key value 
			val = keySet->m_keys[keySet->m_numKeys-1];
	}
	else if (fabs(keySet->m_keys[next] - keySet->m_keys[prev]) / (keySet->m_time[next] - keySet->m_time[prev]) > 1500) //threshold to avoid jittering
	{
		val = keySet->m_keys[next];
	}
	else
	{	
		CFloat tSize = keySet->m_time[next] - keySet->m_time[prev];
		CFloat tDiff = time - keySet->m_time[prev]; 
		CFloat tFactor = 1-((tSize-tDiff)/tSize);
		
		CFloat vSize = keySet->m_keys[next] - keySet->m_keys[prev];
		val = keySet->m_keys[prev] + (vSize * tFactor);
	}
}


CVoid CAnimation::AnimateRotateChannel( CVec4f & vec, CAnimTarget e, CFloat time )
{
	switch( e )
	{
		// old way
	case eRotXAxis:
		interp(vec.w, &m_rotXKeys, time ); 
		break; 
	case eRotYAxis:
		interp(vec.w, &m_rotYKeys, time ); 
		break;
	case eRotZAxis:
		interp(vec.w, &m_rotZKeys, time ); 
		break; 
	default:
		break;
	}
}; 

CVoid CAnimation::AnimateChannel( CVec4f & vec, CVec4f* matrix, CAnimTarget target, CUInt c, CFloat time )
{
	switch( target )
	{
	// new way 
	case eAnimTargetX:
		interp(vec.x, &m_animKeySets[c], time ); 
	break; 
	case eAnimTargetY:
		interp(vec.y, &m_animKeySets[c], time ); 
	break; 
	case eAnimTargetZ:
		interp(vec.z, &m_animKeySets[c], time ); 
	break; 
	case eAnimTargetAngle: 
		interp(vec.w, &m_animKeySets[c], time ); 
	break; 
	case eAnimTargetXYZ:
		interp(vec.x, &m_animKeySets[c], time );
		interp(vec.y, &m_animKeySets[c+1], time );
		interp(vec.z, &m_animKeySets[c+2], time );
		break; 
	case eMatrix:
		interp(matrix[0].x, &m_animKeySets[c], time );
		interp(matrix[1].x, &m_animKeySets[c+1], time );
		interp(matrix[2].x, &m_animKeySets[c+2], time );
		interp(matrix[3].x, &m_animKeySets[c+3], time );

		interp(matrix[0].y, &m_animKeySets[c+4], time );
		interp(matrix[1].y, &m_animKeySets[c+5], time );
		interp(matrix[2].y, &m_animKeySets[c+6], time );
		interp(matrix[3].y, &m_animKeySets[c+7], time );

		interp(matrix[0].z, &m_animKeySets[c+8], time );
		interp(matrix[1].z, &m_animKeySets[c+9], time );
		interp(matrix[2].z, &m_animKeySets[c+10], time );
		interp(matrix[3].z, &m_animKeySets[c+11], time );

		interp(matrix[0].w, &m_animKeySets[c+12], time );
		interp(matrix[1].w, &m_animKeySets[c+13], time );
		interp(matrix[2].w, &m_animKeySets[c+14], time );
		interp(matrix[3].w, &m_animKeySets[c+15], time );
		break; 
	default:
		break; 
	}	
}; 

CVoid CAnimation::AnimateTranslateChannel( CVec3f & vec, CAnimTarget e, CFloat time )
{	
	switch( e )
	{
	case eTransXAxis:
		interp(vec.x, &m_transXKeys, time ); 
		break; 
	case eTransYAxis:
		interp(vec.y, &m_transYKeys, time ); 
		break;
	case eTransZAxis:
		interp(vec.z, &m_transZKeys, time ); 
		break; 
	default:
		break; 
	}	
};

CVoid CAnimation::AnimateScaleChannel( CVec3f & vec, CAnimTarget e, CFloat time )
{	
	switch( e )
	{
	case eScaleXAxis:
		interp(vec.x, &m_scaleXKeys, time ); 
		break; 
	case eScaleYAxis:
		interp(vec.y, &m_scaleYKeys, time ); 
		break;
	case eScaleZAxis:
		interp(vec.z, &m_scaleZKeys, time ); 
		break; 
	default:
		break; 
	}	
};
