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
#include "matrix.h"
#include "transform.h"
#include <vector>

class COrient
{
protected:	
	std::vector<CTransform *> m_transforms[MAX_ANIMATION_CLIPS];
	std::vector<CTransform *> m_sumTransforms;
	std::vector<CFloat> m_sumWeights;
	CBool m_updateLocalMatrix;					// LocalMatrix needs updating (initialize or update due to animations
	CMatrix m_localMatrix;						// Matrix version of just the transforms in this node
	CMatrix	m_localToWorldMatrix;				// Full local to world matrix for this node
	CMatrix	m_inverseLocalToWorldMatrix;
	CMatrix	m_inverseTransposeLocalToWorldMatrix;
	CMatrix	m_inverseBindMatrix; 
	CMatrix	m_combinedSkinMatrix; 

	//When true it causes an update of m_combinedSkinMatrix but unless
	//SetLocalToWorldMatrix is called (and it never is) this will always be true.
	CBool m_updateLocalToWorldMatrix; 

public:
	COrient();
	~COrient();
protected:
	inline CFloat *GetSkinMatrix() {return (CFloat *)m_combinedSkinMatrix;} 	
	
public:

	CMatrix* SetLocalToWorldMatrix(CMatrix * m) 
	{
		memcpy(&m_localToWorldMatrix, m, sizeof(CMatrix));
		m_updateLocalMatrix = CFalse;
		m_updateLocalToWorldMatrix = CFalse;
		return &m_localToWorldMatrix;
	};
	CMatrix* SetLocalMatrix(CMatrix * m)
	{
		memcpy(&m_localMatrix, m, sizeof(CMatrix));
		m_updateLocalMatrix = CFalse;
		return &m_localMatrix;
	};

	inline CMatrix *GetLocalToWorldMatrix(){ return &m_localToWorldMatrix; } 
	inline CMatrix *GetInverseLocalToWorldMatrix(){ return &m_inverseLocalToWorldMatrix; } 
	inline CMatrix *GetInverseTransposeLocalToWorldMatrix(){ return &m_inverseTransposeLocalToWorldMatrix; } 
	inline CMatrix *GetInverseBindMatrix(){ return &m_inverseBindMatrix; }

	inline  CVoid SetUpdateLocalMatrix(CBool b) { m_updateLocalMatrix = (CBool) b;};
	inline  CVoid SetUpdateLocalToWorldMatrix(CBool b) { m_updateLocalToWorldMatrix = (CBool) b;};

};